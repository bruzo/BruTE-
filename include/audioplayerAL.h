#ifndef AUDIOPLAYERAL_H_INCLUDED
#define AUDIOPLAYERAL_H_INCLUDED

#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>
#include <AL/efx-presets.h>
#include <AL/alext.h>

#include <vector>
#include <algorithm>
#include <list>
#include <deque>
#include <math.h>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
#include "ogg/ogg.h"

#include <fcntl.h>

#ifdef win32
#include <io.h>
#include <windows.h>
#include <share.h>
#include <io.h>
#include <mmsystem.h>
#endif // win32

#include <sys/stat.h>

#include <chrono>
#include <thread>
#include <tuple>

//

#include "brutedefinitions.h"
#include "abc.h"

typedef std::tuple< int64_t, int64_t, int64_t, int, int, float > ToneTuple;



class AudioPlayerAL
{
public:

    void Initialize(float volume, int panning);
    void Play();
    void Stop();
    void Seek(float f);
    float Position();
    void PlayTestTones(int instrument, int pitch);
    void SendABC(std::stringstream * abctext);
    void ExportSamples();
    bool Finished();
    void SetInstrument(int id, int instrument);
    void SetPanning(int id, int panning);
    void SetVolume(float value);
    void SetGlobalPanning(int panning);
    void SetMute(int id, bool value);
    size_t GetNumberOfTracks();
    int GetID(size_t track);
    int GetInstrument(size_t track);
    int GetXNumber(size_t track);
    int GetPanning(size_t track);
    int GetZPanning(size_t track);

    void UpdateABC(std::stringstream * abctext);



    ~AudioPlayerAL();

    int audio_playing = 0;
    int m_stop = 0;
    int m_mute = 0; // 0 is not muted

    ABCInput * GetABC();

private:

    ABCInput * myabc = NULL;

    std::vector< std::vector<  std::vector< uint8_t  >  > > allsamples;

#ifdef win32
    FILE * fmemopen(void *buf, size_t len, const char *type);
#endif // win32
    std::vector<uint8_t> snd_load_file(FILE * oggFile );

    // OpenAl Specifics
    ALCdevice *device;
	ALCcontext *context;
	ALboolean enumeration;

	ALfloat listenerOri[6] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };  // Audience is in the center


	std::vector<ALuint> sources;
	std::vector<ALuint> buffers;
	std::vector<ALint> source_states;
	std::vector<int> bufferbound;

	size_t m_Nabctracks=0;

    std::vector< int > m_mutes; // internal information about tracks being muted

    int m_volume = 100;  // listener volume
    int m_panning = 100; // panning percentage, 100=full, 0 = all in center
    int m_durationseconds;

    // for the synchronization
    std::chrono::time_point<std::chrono::high_resolution_clock> m_ABC_Play_Start;       // this is when we started
    std::chrono::time_point<std::chrono::high_resolution_clock> m_ABC_Play_LastUpdate;  // this is where we are now
    std::thread * PlayThread;

    std::vector<uint64_t> trackpositions;

    void PlayLoop();

    std::vector<float> m_envelope; // constains the envelop multiply function to be used for sending the tone

    void SetEnvelope(int Instrument, uint32_t duration, uint32_t samplesize);
};

ABCInput * AudioPlayerAL::GetABC()
{
    return myabc;
}

size_t AudioPlayerAL::GetNumberOfTracks()
{
    return m_Nabctracks;
}

int AudioPlayerAL::GetID(size_t track)
{
    // return m_id[track];
    return myabc->GetID(track);
}

int AudioPlayerAL::GetInstrument(size_t track)
{
   // return m_instrumentnumber[track];
   return myabc->GetInstrument(track);
}

int AudioPlayerAL::GetXNumber(size_t track)
{
    //return m_Xnumber[track];
    return myabc->GetX(track);
}

int AudioPlayerAL::GetPanning(size_t track)
{
    return myabc->GetStereoPosition(track);
}

int AudioPlayerAL::GetZPanning(size_t track)
{
    //return m_WavZPannings[track];
    return myabc->GetDepthPosition(track);
}

void AudioPlayerAL::UpdateABC(std::stringstream * abctext)
{
    float position = Position();
    Stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    SendABC(abctext);
    Play();
    Seek(position);
}

void AudioPlayerAL::SetInstrument(int id, int instrument)
{
    // search through tracks to find ID
    for (size_t i = 0; i < m_Nabctracks; i++)
    {
        if (id == myabc->GetID(i))
        {
            // this is the one so we have to change all the instruments
            for (size_t j = 0; j < myabc->m_ABCTonesvector[i].size(); j++)
            {
               std::get<3>(myabc->m_ABCTonesvector[i][j]) = instrument;
            }
        }
    }
}

void AudioPlayerAL::SetMute(int id, bool value)
{
    // search through tracks to find ID
    for (size_t i = 0; i < m_Nabctracks; i++)
    {
        if (id == myabc->GetID(i))
        {
            // this is the one so we have to change all the instruments
            m_mutes[i] = value;
        }
    }
}

void AudioPlayerAL::SetPanning(int id, int panning)
{
    // search through tracks to find ID
    for (size_t i = 0; i < m_Nabctracks; i++)
    {
        if (id == myabc->GetID(i))
        {
            // this is the one so we have to change all the instruments
           // m_WavPannings[i] = panning;
            myabc->SetStereoPosition(i, panning);
        }
    }
}

void AudioPlayerAL::SetVolume(float value)
{
    alListenerf(AL_GAIN, 1.0f * value/100.0f);
}

void AudioPlayerAL::SetGlobalPanning(int value)
{
    m_panning = value;
}

void AudioPlayerAL::ExportSamples()
{
    // std::ofstream
    for (size_t i = 0; i < allsamples.size(); i++ )
    {
        for (size_t j = 0; j < allsamples[i].size(); j++)
        {
            std::stringstream filename;
            filename << "samples/sample_" << i << "_" << j;
            std::ofstream outfile;
            outfile.open(filename.str(), std::ofstream::out);

            for ( size_t m = 0; m < allsamples[i][j].size()/2; m = m+1 )
            {
                short * value;
                value = (short*)(&allsamples[i][j][m*2]);
                outfile << m << "  " << value[0] << std::endl;
            }
            outfile.close();
        }
    }
}

void AudioPlayerAL::Play()
{
    m_ABC_Play_Start = std::chrono::high_resolution_clock::now();
    m_ABC_Play_LastUpdate = m_ABC_Play_Start;

    trackpositions.resize(m_Nabctracks);
    std::fill( trackpositions.begin(), trackpositions.end(), 0 );

    PlayThread = new std::thread(&AudioPlayerAL::PlayLoop, this);
    m_stop = 0;

}

void AudioPlayerAL::Stop()
{
   m_stop = 1;
}

void AudioPlayerAL::Seek(float f)
{
   std::chrono::time_point<std::chrono::high_resolution_clock> thisisnow = std::chrono::high_resolution_clock::now();
   thisisnow -= std::chrono::milliseconds(static_cast<uint32_t>(f * m_durationseconds*1000));
   m_mute = 1;
   // we want to jump to a time that corresponds to now - f * duration
   m_ABC_Play_Start = thisisnow;
   m_ABC_Play_LastUpdate = thisisnow + std::chrono::milliseconds(static_cast<uint32_t>(f * m_durationseconds*1000));

   // now we need to set the pointers to the right position

   std::chrono::duration<double> ST = m_ABC_Play_LastUpdate - m_ABC_Play_Start;
   uint64_t st = uint64_t(ST.count()) * uint64_t(44100);  // Starting Time in samples
   for (size_t i = 0; i < m_Nabctracks; i++)
   {
      trackpositions[i]=0;
      // we skip ahead in time
      while (( trackpositions[i] < myabc->m_ABCTonesvector[i].size()  ) && ( static_cast<uint64_t>(std::get<0>(myabc->m_ABCTonesvector[i][trackpositions[i]])) < st  ))
      {
         trackpositions[i]++;
      }
   }
   m_mute = 0;
}

float AudioPlayerAL::Position()
{
    uint64_t position=0;
    uint64_t ending=0;

    for (size_t i = 0; i < trackpositions.size(); i++)
    {
        if (  static_cast<uint64_t>(std::get<0>(myabc->m_ABCTonesvector[i][trackpositions[i]])) > position ) position = std::get<0>(myabc->m_ABCTonesvector[i][trackpositions[i]]);
        if (  static_cast<uint64_t>(std::get<0>(myabc->m_ABCTonesvector[i][myabc->m_ABCTonesvector[i].size()-1])) > ending ) ending = std::get<0>(myabc->m_ABCTonesvector[i][myabc->m_ABCTonesvector[i].size()-1]);
    }
    return (1.0f * position)/ending;
}

bool AudioPlayerAL::Finished()
{
   size_t trackfinished = 0;
   for (size_t i = 0; i < m_Nabctracks; i++)
   {
      if ( trackpositions[i] == myabc->m_ABCTonesvector[i].size() )
         trackfinished++;
   }
   if ( trackfinished == m_Nabctracks)
   {
       return true;
   }
   else
   {
       return false;
   }
}


void AudioPlayerAL::SetEnvelope(int Instrument, uint32_t duration, uint32_t samplesize)
{
    m_envelope.resize(samplesize);
    std::fill(m_envelope.begin(), m_envelope.end(), 1.);


    if ( Instrument < static_cast<int>(adsr.size()) )
    {

        for (size_t segment = 0; segment <  adsr[Instrument].size()-1; segment++ )
        {
            float startvel = adsr_v[Instrument][segment];
            float endvel   = adsr_v[Instrument][segment+1];
            float deltav = endvel-startvel;
            size_t starti = adsr[Instrument][segment];
            size_t endi   = adsr[Instrument][segment+1];

            if (endi > samplesize) endi = samplesize;
            size_t seglength = endi - starti;

            float mv = deltav / seglength;

            for (size_t i = 0; i < seglength; i++)
            {
                m_envelope[starti + i] = startvel  +  i * mv;
            }
        }
    }
}


void AudioPlayerAL::PlayLoop()
{
    // read current time

    while (m_stop == 0)
    {

       // Get current time
       std::chrono::time_point<std::chrono::high_resolution_clock> updatetime = std::chrono::high_resolution_clock::now();

       // Delta Time from last update:
       std::chrono::duration<double> DT = updatetime - m_ABC_Play_LastUpdate;
       std::chrono::duration<double> ST = updatetime - m_ABC_Play_Start;

       uint64_t st = ST.count() * uint64_t(44100);  // Starting Time in samples
       uint64_t dt = DT.count() * uint64_t(44100);  // Delta Time in samples

       for (size_t i = 0; i < m_Nabctracks; i++)
       {
           // find the tones we need to send per track
           // if (std::get<0>(m_ABCTonesvector[i][trackpositions[i]]) >= st)

           // we take the next couple of tones in this track that had to be played
           while ((trackpositions[i] < myabc->m_ABCTonesvector[i].size()) && ( std::get<0>(myabc->m_ABCTonesvector[i][trackpositions[i]]) < static_cast<int64_t>(st+dt)  ))
           {

               int instrument = std::get<3>(myabc->m_ABCTonesvector[i][trackpositions[i]]);
               int pitch = std::get<4>(myabc->m_ABCTonesvector[i][trackpositions[i]]) - 36;
               if (instrument == 10) pitch = 0;
               if (instrument == 9) pitch = 0;
               int velocity = std::get<5>(myabc->m_ABCTonesvector[i][trackpositions[i]]);
               size_t duration = std::get<2>(myabc->m_ABCTonesvector[i][trackpositions[i]]);

               trackpositions[i]++;   // next tone

               if ((m_mute == 0) && ( m_mutes[i] == 0))
               {
                   // find first free slot
                   size_t ii = 0;

                   ALint sourcestate;
                   alGetSourcei(sources[0], AL_SOURCE_STATE, &sourcestate);

                   while (( sourcestate == AL_PLAYING ) && ( ii < 64 ))
                   {
                       ii++;
                       alGetSourcei(sources[ii], AL_SOURCE_STATE, &sourcestate);
                   }
                   //  std::cout << " Source " << i << " not playing " << std::endl;
                   // If there is no free slot the sample will not be played - this maybe different in the game
                   if ( ii < 64)
                   {
                       std::vector<uint8_t> thissample;
                       uint32_t fadesamples = static_cast<uint32_t>(fadeouts[instrument] * 44100);
                       size_t mysize = 0;
                       if ( fadeouttype[instrument] == 0) // constant duration gets send as a whole
                       {
                           mysize = allsamples[instrument][pitch+36].size();  // size is always in 8bit units even if singular samples are 2 byte
                         //  std::cout << " Sample Size " << mysize << std::endl;
                       }
                       else
                       {
                           mysize = duration * 2 + fadesamples*2;  // size is memory for this sample in bytes
                        //   std::cout << " Sample Size Asked " << mysize << std::endl;
                           if (mysize > allsamples[instrument][pitch+36].size() ) mysize = allsamples[instrument][pitch+36].size();
                         //  std::cout << "Sample Size Got " << mysize << std::endl;
                             // if the sample is over then it is over
                       }
                       thissample.resize(mysize); // copy over all the data into thissample
                       for (size_t ij = 0; ij < mysize; ij++) thissample[ij] = allsamples[instrument][pitch+36][ij];


                       // we got the sample, now make sure we do the fadeout
                       // SetEnvelope(instrument, 1.0, allsamples[instrument][pitch+36].size()/2);

                       short * modulator = (short*)( &thissample[0] );
                       size_t fstart = thissample.size()/2-fadesamples;
                       size_t fend = thissample.size()/2;

                     //  std::cout << fadesamples << "   " << fstart << "   " << fend << std::endl;

                       for (size_t ij = fstart; ij < fend; ij++)  // we move from the regular play time end till the fadeout end
                       {
                           modulator[ij] = (short)(  ( modulator[ij] * (  (fend-ij)/(1.0f*fadesamples)  ) )+0.5 );
                       }


                       // was this buffer used before, if yes we have to do some stuff first?
                       if ( bufferbound[ii] == 1)
                       {
                            alSourceStop(sources[ii]);
                            alSourcei(sources[ii], AL_BUFFER, AL_NONE);
                            bufferbound[ii] = 0;
                       }

                       alBufferData(buffers[ii], AL_FORMAT_MONO16, &thissample[0], thissample.size(), 44100);
                   //    std::cout << "Dur " << duration << "  " << allsamples[instrument][pitch+36].size() << std::endl;
	                   alSourcei(sources[ii], AL_BUFFER, buffers[ii]);
	                   bufferbound[ii] = 1;

	                  // float mygain = fullvolumegains[instrument][velocity];
	                   float mygain = relativegain[instrument] * pitchgains[velocity] ;
                       alSourcef(sources[ii], AL_GAIN, mygain);

                       //float myp = m_WavPannings[i]*0.01 * m_panning*0.01;
                       float myp = myabc->GetStereoPosition(i) * 0.01 * m_panning * 0.01;

                    //   std::cout << "Setting Tone at " << i << " Panning " << m_WavPannings[i] << "  " << myp << "  Time " << std::get<0>(m_ABCTonesvector[i][trackpositions[i]])* 1.0f/(44100) << std::endl;



                       alSource3f(sources[ii], AL_POSITION, myp, 0, 0);

                   //    std::cout << "Playing Source " << i << " Instrument " << instrument << " Pitch " << pitch << " Gain " << mygain << " Samplesize " << allsamples[instrument][pitch+36].size() << std::endl;
	                   alSourcePlay(sources[ii]);
	                  // std::this_thread::sleep_for(std::chrono::milliseconds(1));

                   }
                   //else{std::cout << "Dropping Tone" << std::endl;}
               }
           }
       }


       // Wait a little and recall this routine if we are not supposed to stop yet
       m_ABC_Play_LastUpdate = updatetime;
       std::this_thread::sleep_for(std::chrono::milliseconds(2));

    }
}

AudioPlayerAL::~AudioPlayerAL()
{
    alDeleteSources(64, &sources[0]);
	alDeleteBuffers(64, &buffers[0]);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
    if ( &OV_CALLBACKS_DEFAULT == &OV_CALLBACKS_NOCLOSE ) {};
    if ( &OV_CALLBACKS_STREAMONLY_NOCLOSE == &OV_CALLBACKS_STREAMONLY ) {};
}

void AudioPlayerAL::Initialize(float volume, int panning)
{
    // Allocate Sample Space
    allsamples.resize(oggpitchnumbers.size());
	for (size_t i = 0; i < oggpitchnumbers.size(); i++)
	{
	    allsamples[i].resize(73); // yes we also allocate 0s for the pitches below the ones we actually use ...
	    for (size_t j = 0; j < oggpitchnumbers[i].size(); j++)
        {
            int mypoint = oggpitchnumbers[i][j];
            allsamples[i][mypoint].resize(1);
        }
	}

	// Load and Decompress the Samples
    FILE * mysoundsfile = fopen("allsounds.dat","rb");
    uint32_t filesize;



    std::vector<uint8_t> datablock;

    for (size_t i = 0; i < allsamples.size(); i++) //allsamples.size(); i++)
    {
    std::cout << "Instrument " << lotroinstruments_formal[i] << std::endl;

     for (size_t j = 0; j < allsamples[i].size(); j++)
     {
        // std::cout << i << "  " << j << " " << allsamples[i][j].size() << std::endl;
        if (allsamples[i][j].size() > 0)
        {
          size_t readbyte = fread(&filesize, sizeof(uint32_t), 1, mysoundsfile);
          if (readbyte == 0) { std::cout << "We have a file reading issue on the soundsfile." << std::endl;}

          datablock.resize(filesize);
          size_t actualread = fread(&datablock[0], filesize, 1, mysoundsfile);
          if (actualread != 1) std::cout<<"Error in Instrument File" << std::endl;
          FILE * thisfile = fmemopen(&datablock[0], filesize, "rb" );

//          std::cout << i << "  " << j << "  " << filesize << " actual " << actualread << " info " << infoblock << std::endl;

          allsamples[i][j] = snd_load_file(thisfile);


//          std::cout << i << "  " << j << "  " << filesize << "  " << allsamples[i][j].size() << std::endl;
          fclose(thisfile);
        }
     }
    }

    // Check for Enumeration
    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

	if (enumeration == AL_FALSE)
		fprintf(stderr, "enumeration extension not available\n");
    else std::cout << "Enumeration possible" << std::endl;

    // Allocate OpenAl Device
    device = alcOpenDevice(NULL);
    std::cout << "Using " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;

    if (alcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_FALSE)
    {
        std::cout << " no effects " << std::endl;
    }
    else{ std::cout << "effects possible" << std::endl;}

    if(alcIsExtensionPresent(NULL, "ALC_SOFT_loopback"))
    {
        std::cout << "Loopback supported" << std::endl;
    }

    ALint srate;
    alcGetIntegerv(device, ALC_FREQUENCY, 1, &srate);
    std::cout << "OpenAL Frequency: " << srate << std::endl;

    // Create the OpenAl Context
    context = alcCreateContext(device, NULL);

    if (!alcMakeContextCurrent(context)) {
		fprintf(stderr, "failed to make default context\n");
	}

	// Set the listener to 0 by default
    alListener3f(AL_POSITION, 0, 0, -1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
	//alListenerf(AL_GAIN, 0.985f);
    alListenerf(AL_GAIN, 1.0f * m_volume/100.0f);

	// Allocate and initialize all 64 sources
    sources.resize(64);
	alGenSources((ALuint)64, &sources[0]);
	for (size_t i = 0; i < sources.size(); i ++)
    {
	   alSourcef(sources[i], AL_PITCH, 1);
	   alSourcef(sources[i], AL_GAIN, 1);
	   alSource3f(sources[i], AL_POSITION, 0, 0, 0);
	   alSource3f(sources[i], AL_VELOCITY, 0, 0, 0);
	   alSourcei(sources[i], AL_LOOPING, AL_FALSE);
    }

    // we use one buffer per source .. as simple as possible
    buffers.resize(64);
    alGenBuffers((ALuint)64, &buffers[0]);
    bufferbound.resize(64);
    std::fill(bufferbound.begin(), bufferbound.end(), 0);

    source_states.resize(64);
    m_panning = panning;
}


#ifdef win32
FILE *  AudioPlayerAL::fmemopen(void *buf, size_t len, const char *type)
{
	int fd;
	FILE *fp;
	char tp[MAX_PATH - 13];
	char fn[MAX_PATH + 1];
	int * pfd = &fd;
	int retner = -1;
	char tfname[] = "MemTF_";
	if (!GetTempPathA(sizeof(tp), tp))
		return NULL;
	if (!GetTempFileNameA(tp, tfname, 0, fn))
		return NULL;
	retner = _sopen_s(pfd, fn, _O_CREAT | _O_SHORT_LIVED | _O_TEMPORARY | _O_RDWR | _O_BINARY | _O_NOINHERIT, _SH_DENYRW, _S_IREAD | _S_IWRITE);
	if (retner != 0)
		return NULL;
	if (fd == -1)
		return NULL;
	fp = _fdopen(fd, "wb+");
	if (!fp) {
		_close(fd);
		return NULL;
	}
	// File descriptors passed into _fdopen are owned by the returned FILE * stream.If _fdopen is successful, do not call _close on the file descriptor.Calling fclose on the returned FILE * also closes the file descriptor.
	fwrite(buf, len, 1, fp);
	rewind(fp);
	return fp;
}
#endif

std::vector<uint8_t> AudioPlayerAL::snd_load_file(FILE * oggFile ){

	//FILE*           oggFile;
	OggVorbis_File  oggStream;
	vorbis_info*    vorbisInfo;

	//vorbis_comment* vorbisComment;

	ALenum format;
	uint32_t BUFFER_SIZE = 8*4096;

	int result = ov_open(oggFile, &oggStream, NULL, 0);

	vorbisInfo = ov_info(&oggStream, -1);
	//vorbisComment = ov_comment(&oggStream, -1);

	if(vorbisInfo->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;
    if (format == AL_FORMAT_MONO16) {};

//	char * dyn_data = NULL;
	int  mysize = 0;
	int  section;
	result = 1;
	// printf("Loading sound file\n");

	std::vector<uint8_t> outdata;

	while(result > 0){

		char data[BUFFER_SIZE];
        result = ov_read(&oggStream, data, BUFFER_SIZE, 0, 2, 1, &section);

		if(result > 0){

			mysize += result;
			outdata.resize(mysize);
			memcpy(&outdata[mysize-result], data, result  );
		} else if(result < 0){
			switch(result){
				case OV_HOLE:
					printf("Interruption in the data.%d\n", result);
					printf("one of: garbage between pages, loss of sync followed by recapture, or a corrupt page\n");
					break;
				case OV_EBADLINK:
					printf("an invalid stream section was supplied to libvorbisfile, or the requested link is corrupt.\n");
					break;
				case OV_EINVAL:
					printf("the initial file headers can't be read or are corrupt, or the initial open call for vf failed.\n");
					break;
			}

		} else if(mysize == 0){
			printf("Data not read.\n");
		}
	}
	//free(dyn_data);
	return outdata;
}

void AudioPlayerAL::PlayTestTones(int instrument, int pitch)
{
    // we only use the first buffer, first fill it, then bind it to source


   SetEnvelope(instrument, 1.0, allsamples[instrument][pitch].size()/2);
   short * modulator = (short*)( &allsamples[instrument][pitch][0] );

   for (size_t i = 0; i < allsamples[instrument][pitch].size()/2; i++)
   {
      modulator[i] = (short)(  (modulator[i] * m_envelope[i])+0.5 );
   }



    alBufferData(buffers[0], AL_FORMAT_MONO16, &allsamples[instrument][pitch][0], allsamples[instrument][pitch].size(), 44100);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);


    auto start = std::chrono::high_resolution_clock::now();

    /*
	for (int i = 0; i < 509; i++)
    {
        float mygain = 0.;
        int myvol = i-9;  // ignore first 9 tones

        if (i -9 < 0) {mygain = 0.001f;};
        if ( i - 9 >= 0)
        {
            mygain = (i-9) * 0.002f;
        }

        //if (myvol < 0 ) myvol = 0;
        //mygain =  fullvolumegains[myvol/3] * relvol[instrument];


        alSourcef(sources[0], AL_GAIN, mygain);

	    alSourcePlay(sources[0]);

	    ALint sourcestate;

        alGetSourcei(sources[0], AL_SOURCE_STATE, &sourcestate);

        while (sourcestate == AL_PLAYING) {

		   alGetSourcei(sources[0], AL_SOURCE_STATE, &sourcestate);

		   std::this_thread::sleep_for(std::chrono::milliseconds(5));
		//sleep(1.8);
	    }

     std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
	 while ( diff.count() < 2.88 * (i+1)  )
     {
         std::this_thread::sleep_for(std::chrono::milliseconds(5));
         diff = std::chrono::high_resolution_clock::now() - start;
     }

    }
    */

    	for (int i = 0; i < 48*9+48; i++)
    {
        int j = i - 48;
        if (j<0) j = 0;

        float mygain = 0.7;


        //if (myvol < 0 ) myvol = 0;
        //mygain =  fullvolumegains[myvol/3] * relvol[instrument];


        alSourcef(sources[0], AL_GAIN, mygain);

	    alSourcePlay(sources[0]);

	    ALint sourcestate;

        alGetSourcei(sources[0], AL_SOURCE_STATE, &sourcestate);

        while (sourcestate == AL_PLAYING) {

		   alGetSourcei(sources[0], AL_SOURCE_STATE, &sourcestate);

		   std::this_thread::sleep_for(std::chrono::milliseconds(5));
		//sleep(1.8);
	    }

     std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
	 while ( diff.count() < 2.88 * (i+1)  )
     {
         std::this_thread::sleep_for(std::chrono::milliseconds(5));
         diff = std::chrono::high_resolution_clock::now() - start;
     }

    }
}


void AudioPlayerAL::SendABC(std::stringstream * abctext)
{
    ABCInput * newabc = new ABCInput();

    newabc->LoadABC(abctext);

    m_Nabctracks = newabc->Nabctracks();

   // m_instrumentnumber.resize(m_Nabctracks);
    m_mutes.resize(m_Nabctracks, false);


    m_durationseconds = newabc->GetDuration();
  //  m_ABCTonesvector = newabc->m_ABCTonesvector;



    if (myabc == NULL)
    {
        myabc = newabc;
    }
    else
    {
        delete(myabc);
        myabc = newabc;
    }

    if ((m_Nabctracks>0) && (newabc->GetID(0) == -1))
    {
        // this ABC didn't have ID info so we're setting this
        for (int i = 0; i < static_cast<int>(m_Nabctracks); i++) myabc->SetID(i, i+1);
    }

}


#endif // AUDIOPLAYERAL_H_INCLUDED

#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED


#include "brute.h"
#include "midipreview.h"
#include "bandview.h"
#include <SDL.h>

class AudioPlayer
{
public:

    SDL_AudioDeviceID myaudio;
    Uint32 wav_length;
    Uint8 *wav_buffer;
    SDL_AudioSpec audiowant, audiohave;
    int audio_playing = 0;   // 0 is not playing at the moment

    Brute * myBrute;
    MidiPreview * myMidiPreview;

    void Play();
    void Stop();
    void Seek(float f);

    uint64_t soundsize = 0;

    AudioPlayer(Brute * myBrutep, MidiPreview * myMidiPreviewp);

private:

};

AudioPlayer::AudioPlayer(Brute * myBrutep, MidiPreview * myMidiPreviewp)
{
    myBrute = myBrutep;
    myMidiPreview = myMidiPreviewp;

        // initialize Audio
    SDL_Init(SDL_INIT_AUDIO);
}

void AudioPlayer::Play()
{
    SDL_AudioSpec want, have;

    SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
    want.freq = 44100;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 4096;
    want.callback = NULL;  // you wrote this function elsewhere.

  //  Uint32 myposition = 0;

    // are we already playing?
    if (audio_playing > 0)
    {
        // if yes then stop
    //    myposition = SDL_GetQueuedAudioSize(myaudio);
        SDL_CloseAudioDevice(myaudio);
        SDL_ClearQueuedAudio(myaudio);
      //  SDL_FreeWAV(wav_buffer);
    }

    // and queue the current audio buffer
    audio_playing = 1;
    myaudio = SDL_OpenAudioDevice(NULL, 0,  &want, &have, 0);
    SDL_QueueAudio(myaudio, &myMidiPreview->m_StereoStream[0]  , myMidiPreview->m_StereoStream.size()*2 );
    SDL_PauseAudioDevice(myaudio, 0);
}


void AudioPlayer::Stop()
{
 //   Uint32 myposition = 0;
    if (audio_playing > 0)
    {
        // if yes then stop
   //     myposition = SDL_GetQueuedAudioSize(myaudio);
        SDL_CloseAudioDevice(myaudio);
        SDL_ClearQueuedAudio(myaudio);
      //  SDL_FreeWAV(wav_buffer);
    }
}

void AudioPlayer::Seek(float f)
{
    if (audio_playing > 0)
    {
        SDL_AudioSpec want, have;

        SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
        want.freq = 44100;
        want.format = AUDIO_S16SYS;
        want.channels = 2;
        want.samples = 4096;
        want.callback = NULL;  // you wrote this function elsewhere.

        SDL_CloseAudioDevice(myaudio);
        SDL_ClearQueuedAudio(myaudio);

      //  std::cout << "Seek to " << f << std::endl;
      //  std::cout << "Elements in Stereo " << myMidiPreview->m_StereoStream.size() << "  sizeof " << sizeof(myMidiPreview->m_StereoStream[0]) * myMidiPreview->m_StereoStream.size() << std::endl;

        uint64_t myposition = uint64_t((myMidiPreview->m_StereoStream.size() * f));
        // rounding position to be on stereo 0
        myposition = ( myposition / 2 )*2*2;

        myaudio = SDL_OpenAudioDevice(NULL, 0,  &want, &have, 0);

       // std::cout << "Jumping to " << myposition << " which is " << (myposition*1.0)/myMidiPreview->m_StereoStream.size() << " of n_elements " << std::endl;
       // std::cout << "Length " << myMidiPreview->m_StereoStream.size() - myposition << std::endl;
      //  std::cout << "size of sample " << sizeof(myMidiPreview->m_StereoStream[0]) << std::endl;
        SDL_QueueAudio(myaudio, &myMidiPreview->m_StereoStream[myposition], myMidiPreview->m_StereoStream.size()*2 - myposition*2 );
        SDL_PauseAudioDevice(myaudio, 0);
    }
}

#endif // AUDIOPLAYER_H_INCLUDED

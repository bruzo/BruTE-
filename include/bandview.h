#ifndef BANDVIEW_H_INCLUDED
#define BANDVIEW_H_INCLUDED



#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/bitmap.h"
#include <algorithm>
#include "miditrackdialogue.h"
#include "abctrackdialogue.h"
#include "bandviewabctrack.h"
#include "bandviewmiditrack.h"
#include "audioplayerAL.h"
//#include "midipreview.h"
#include "audiencedialogue.h"
#include "overloadpicture.h"
#include "miditrackview.h"
#include "abcheader.h"
#include "gainsettingsdialogue.h"
#include "abcsettingsdialogue.h"


/* m_directmapping  .. to map one input pitch to one specific output pitch .. for cowbell, student fiddle and very custom drum mapping */


class BandView : public wxPanel
{

public:
    BandView(wxFrame* parent, Brute * myBrute, MidiTrackView * myMidiTrackViewp, AudioPlayerAL * myAudioPlayerAL);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);
    void DrawLotroInstruments(wxDC& dc);
    void DrawOneInstrument(wxDC& dc, int x, int y, wxString mytext, bool muted);
    void DrawMidiTracks(wxDC& dc);
    void DrawOneMidiTrack(wxDC& dc, int x, int y, int i, size_t midiinstrumentnumber);
    void DrawOneMidiTrack(wxMemoryDC& dc, int x, int y, int i, size_t midiinstrumentnumber);
    void DrawABCTracks(wxDC& dc);

    void AppendMapping();   // this will write the mapping info into the brute instance

    void GetMapping();
    void GenerateConfigHeader();

    size_t LotroInstrumentPicked(int x, int y);
    size_t MidiTrackPicked(int x, int y);
    size_t ABCTrackPicked(int x, int y);
    bool ABCTrackMuted(int x, int y);
    size_t MidiTrackInABCTrackPicked(int x, int y);
    size_t WhichMidiTrackInABCTrackPicked(int x, int y);

    Brute * myBrute;  // our instance of Brute
   // AudioPlayer * myaudioplayer; // our instance of the AudioPlayer
    AudioPlayerAL * myaudioplayerAL;
    // MidiPreview * myMidiPreview;

    void mouseLeftDown(wxMouseEvent& event);
    void mouseLeftUp(wxMouseEvent& event);
    void mouseRightDown(wxMouseEvent& event);

    bool lotroinstrumentclicked = false;
    size_t lotroinstrumentclickednumber;

    bool abctrackclicked = false;
    size_t abctrackclickednumber;

    bool miditrackclicked = false;
    size_t miditrackclickednumber;

    bool midiinabctrackclicked = false;

    std::vector<BandViewABCTrack> BVabctracks = {};
    BandViewABCTrack MovingABCTrack;
    BandViewMidiTrack MovingMidiTrack;
    int MovingMidiTrackNumber;

    ABCHeader myABCHeader;

    int RelX(int m);
    int RelY(int m);

    int click_relx;
    int click_rely;

    int m_globalid = 0;

    bool BetterUpdateYourABCfromBrute = false;
    bool CRTLIsDown = false;
    bool ShiftIsDown = false;

    void GenerateDefaultMapping();


    wxBitmap * myOverLoadPic = new wxBitmap(690,50,-1);

    MidiTrackView * myMidiTrackView;

    void OnDropFiles(wxDropFilesEvent& event);

    void LiveUpdateAudio();

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    bool m_ABCMODE = false;
    bool m_MIDIMODE = true;

private:

    int m_ABCnamingscheme = 0;
    std::string Transcriber = "Himbeertony";

    int m_volume=100;
    int m_panning=100;

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

     wxBitmap * m_bitmap;
     wxImage * m_image;
     unsigned char * m_alphachannel;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(BandView, wxPanel)
// some useful events
/*
 EVT_MOTION(BandView::mouseMoved)
 */
 EVT_LEFT_DOWN(BandView::mouseLeftDown)
 EVT_LEFT_UP(BandView::mouseLeftUp)
 EVT_RIGHT_DOWN(BandView::mouseRightDown)

 // check for keys behind down
 EVT_KEY_DOWN(BandView::OnKeyDown)
 EVT_KEY_UP(BandView::OnKeyUp)
 /*
 EVT_RIGHT_DOWN(BandView::rightClick)
 EVT_LEAVE_WINDOW(BandView::mouseLeftWindow)
 EVT_KEY_DOWN(BandView::keyPressed)
 EVT_KEY_UP(BandView::keyReleased)
 EVT_MOUSEWHEEL(BandView::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BandView::paintEvent)

// catch files dropped
EVT_DROP_FILES(BandView::OnDropFiles)

END_EVENT_TABLE()


// some useful events
/*
 void BandView::mouseMoved(wxMouseEvent& event) {}
 void BandView::mouseDown(wxMouseEvent& event) {}
 void BandView::mouseWheelMoved(wxMouseEvent& event) {}
 void BandView::mouseReleased(wxMouseEvent& event) {}
 void BandView::rightClick(wxMouseEvent& event) {}
 void BandView::mouseLeftWindow(wxMouseEvent& event) {}
 void BandView::keyPressed(wxKeyEvent& event) {}
 void BandView::keyReleased(wxKeyEvent& event) {}
 */

void BandView::OnKeyDown(wxKeyEvent & event)
{
   int keycode = event.GetKeyCode();
   if (keycode ==  WXK_CONTROL )
   {
      CRTLIsDown = true;
   }
   if (keycode == WXK_SHIFT)
   {
       ShiftIsDown = true;
   }
   event.Skip();
}

void BandView::OnKeyUp(wxKeyEvent & event)
{
   int keycode = event.GetKeyCode();
   if (keycode ==  WXK_CONTROL )
   {
      CRTLIsDown = false;
   }
   if (keycode == WXK_SHIFT)
   {
       ShiftIsDown = false;
   }
   event.Skip();
}

void BandView::LiveUpdateAudio()
{
   if ( myaudioplayerAL->audio_playing == 1 )   // check if we are playing
   {
      GenerateConfigHeader();
      AppendMapping();
      myBrute->Transcode(&myBrute->m_MappingText);
   //   int64_t realduration;
    //  myMidiPreview->GeneratePreviewMidi2(&myBrute->m_ABCText, &realduration );
      myaudioplayerAL->UpdateABC(&myBrute->m_ABCText);
   }
}



 void BandView::AppendMapping()
 {
     std::stringstream bvmappingtext;

     // sort by Y appearance
     std::vector< std::pair<int,int> > myneworder;

     for (size_t i = 0; i < BVabctracks.size(); i++)
        myneworder.push_back( std::make_pair( BVabctracks[i].y, i) );
     std::sort( myneworder.rbegin(), myneworder.rend() );

     for (size_t m = 0; m < BVabctracks.size(); m++)
     {
        // size_t i = m; // In case we do not want to  reorder
        size_t i = myneworder[m].second; // write out the correct part based on the ordering
        // if (BVabctracks[i].muted ) bvmappingtext << "*" << std::endl;
        bvmappingtext << "abctrack begin" << std::endl;
        bvmappingtext << "%voladjust    %uncomment to try automatic compensation for U16.1 volumes (experimental!)" << std::endl;
        std::string pdirection = "top";
        if (BVabctracks[i].polydirection == 0) pdirection = "bottom";
        bvmappingtext << "polyphony " << BVabctracks[i].polyphony  <<" " << pdirection << " % options: top removes tones from higher pitch first, bottom lower pitch first" << std::endl;

        bvmappingtext << "duration " << BVabctracks[i].duration_min;
        if (BVabctracks[i].duration_max > 2) bvmappingtext << " " << BVabctracks[i].duration_max;
        bvmappingtext << std::endl;

        bvmappingtext << "panning " <<  -int( 100 * ((BVabctracks[i].x-100)/590.0 - 0.5)   ) << "  " << BVabctracks[i].y  << "  " << BVabctracks[i].id << std::endl;


        if (BVabctracks[i].instrument != 8) // for all instruments except drums we can just write the instrument
        {
         bvmappingtext << "instrument " << lotroinstruments[BVabctracks[i].instrument] << std::endl;
        }
        //else
        //{
        // bvmappingtext << "instrument drums "  << std::endl;
        //}
        for (size_t j = 0; j < BVabctracks[i].miditrackinfo.size(); j++)
        {
           if (BVabctracks[i].instrument == 8) // for the drums we have to add the mapping used for the following midi track seperatly
           {
                bvmappingtext << "instrument drums " << BVabctracks[i].miditrackinfo[j].drummapping << std::endl;
           }
           bvmappingtext << "%" << std::endl;
           int midioriginal = BVabctracks[i].miditrackinfo[j].midiinstrument;
           if (( BVabctracks[i].miditrackinfo[j].range_l > 0 ) || ( BVabctracks[i].miditrackinfo[j].range_h < 36))
            bvmappingtext << "range " << BVabctracks[i].miditrackinfo[j].range_l << " " << BVabctracks[i].miditrackinfo[j].range_h << std::endl;
           if (BVabctracks[i].miditrackinfo[j].alternateparts > 1)
            bvmappingtext << "alternate " << BVabctracks[i].miditrackinfo[j].alternateparts << " " << BVabctracks[i].miditrackinfo[j].alternatemypart << std::endl;
           if (BVabctracks[i].miditrackinfo[j].split > 0)
            bvmappingtext << "split " << BVabctracks[i].miditrackinfo[j].split << std::endl;
           if (BVabctracks[i].miditrackinfo[j].triller > 0.01)
            bvmappingtext << "triller " << BVabctracks[i].miditrackinfo[j].triller << std::endl;
           if (BVabctracks[i].miditrackinfo[j].pitchbendmethod > 0)
            bvmappingtext << "pitchbendinfo " << BVabctracks[i].miditrackinfo[j].pitchbendqduration  << "  "  << BVabctracks[i].miditrackinfo[j].pitchbendmethod << std::endl;
           if (BVabctracks[i].miditrackinfo[j].durationsplitlength > 0)
            bvmappingtext << "durationsplit " << BVabctracks[i].miditrackinfo[j].durationsplitlength << "  "  << BVabctracks[i].miditrackinfo[j].durationsplitpart << std::endl;
           if (BVabctracks[i].miditrackinfo[j].directmapping > -1)
           {
               bvmappingtext << "directmapping " << BVabctracks[i].miditrackinfo[j].drumtone << "  " << BVabctracks[i].miditrackinfo[j].directmapping << std::endl;
           }
           if ((midioriginal >= 0)&&(midioriginal < 128))
            bvmappingtext << "% Miditrack original Instrument " << GMinstrument[ midioriginal ] << std::endl;
           bvmappingtext << "miditrack " << BVabctracks[i].miditrackinfo[j].miditrack << " pitch " << BVabctracks[i].miditrackinfo[j].pitch << " volume " << BVabctracks[i].miditrackinfo[j].volume << " delay " << BVabctracks[i].miditrackinfo[j].delay << " prio 1" << std::endl;
        }
        bvmappingtext << "abctrack end" << std::endl;
        bvmappingtext << std::endl;
        bvmappingtext << std::endl;
     }

     // also include positions of the abctracks in the view
     for (size_t m = 0; m < BVabctracks.size(); m++)
     {
        size_t i = myneworder[m].second;
        bvmappingtext << "%BV " << m << "  x:  " << BVabctracks[i].x << "  y: " << BVabctracks[i].y << std::endl;
     }
     bvmappingtext << std::endl;
     bvmappingtext << std::endl;

     myBrute->m_MappingText << bvmappingtext.rdbuf();
 }

void BandView::GetMapping()
{
    // find out how many ABC Tracks we have     std::vector < std::vector < int > > m_trackmap;  // list of miditracks per itrack
    BVabctracks = {};
    int ntracks = myBrute->m_Mapping.m_trackmap.size();
    for (int i = 0; i < ntracks; i++)
    {
        BandViewABCTrack newabctrack;
        newabctrack.instrument = myBrute->m_Mapping.m_instrumap[i];
        newabctrack.x = myBrute->m_Mapping.abctrackpositions_x[i];
        newabctrack.y = myBrute->m_Mapping.abctrackpositions_y[i];
        newabctrack.polyphony = myBrute->m_Mapping.m_polymap[i];
        newabctrack.polydirection = myBrute->m_Mapping.m_polymapdir[i];
        newabctrack.duration_min = myBrute->m_Mapping.m_durmap[i];
        newabctrack.duration_max = myBrute->m_Mapping.m_durmaxmap[i];
        newabctrack.id = m_globalid; m_globalid++;

        BVabctracks.push_back(newabctrack);

        int nmiditracks = myBrute->m_Mapping.m_trackmap[i].size();
        for (int j = 0; j < nmiditracks; j++)
        {
            BandViewMidiTrack newmiditrack;
            newmiditrack.miditrack = myBrute->m_Mapping.m_trackmap[i][j];
            newmiditrack.midiinstrument = myBrute->GetMidiInstrument( newmiditrack.miditrack );
            newmiditrack.isdrum = myBrute->GetMidiIsDrum(newmiditrack.miditrack );
            if (myBrute->GetToneCount(newmiditrack.miditrack)==0)
                newmiditrack.isempty = true;

            newmiditrack.range_h = myBrute->m_Mapping.m_rangemaph[i][j];
            newmiditrack.range_l = myBrute->m_Mapping.m_rangemapl[i][j];
            newmiditrack.volume  = myBrute->m_Mapping.m_volumemap[i][j];
            newmiditrack.pitch   = myBrute->m_Mapping.m_pitchmap[i][j];

            newmiditrack.alternateparts = myBrute->m_Mapping.m_alternatemap[i][j];
            newmiditrack.alternatemypart = myBrute->m_Mapping.m_alternatepart[i][j];
            newmiditrack.split = myBrute->m_Mapping.m_splitvoicemap[i][j];
            newmiditrack.delay = myBrute->m_Mapping.m_delaymap[i][j];
            newmiditrack.drummapping = myBrute->m_Mapping.m_drumstylemap[i][j];
            newmiditrack.triller = myBrute->m_Mapping.m_trillermap[i][j];
            newmiditrack.pitchbendqduration = myBrute->m_Mapping.m_pitchbendmap[i][j];
            newmiditrack.pitchbendmethod = myBrute->m_Mapping.m_pitchbendmethodmap[i][j];
            newmiditrack.durationsplitlength = myBrute->m_Mapping.m_durationsplitmap[i][j];
            newmiditrack.durationsplitpart = myBrute->m_Mapping.m_durationsplitpartmap[i][j];

            newmiditrack.haspitchbends = (myBrute->m_pitchbendcounter[newmiditrack.miditrack] > 0);
            newmiditrack.directmapping = myBrute->m_Mapping.m_directmapping[i][j];
            newmiditrack.drumtone      = myBrute->m_Mapping.m_drumsingleinstrument[i][j];
            newmiditrack.samples = &myBrute->m_samplesused[ myBrute->m_Mapping.m_trackmap[i][j] ];

            BVabctracks[i].miditrackinfo.push_back(newmiditrack);
        }
    }

    myABCHeader.globalpitch = myBrute->m_Mapping.m_generalpitch;
    myABCHeader.globalvolume = myBrute->m_Mapping.m_globalvolume;
    myABCHeader.speedup = myBrute->m_Mapping.m_minstepmod;
    myABCHeader.Transcriber = myBrute->m_Mapping.m_transcribername;
    myABCHeader.SongName = myBrute->m_Mapping.m_songname;

    this->Refresh();
}


size_t BandView::LotroInstrumentPicked(int x, int y)
{
    // x/y 97/18
    size_t retvalue = 100;
    int ystart = 50;
    int xstart = 800;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart)     && ( y < ystart+18) )     return retvalue = 0;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart)     && ( y < ystart+18) )     return retvalue = 11;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+20)  && ( y < ystart+20+18) )  return retvalue = 1;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+20)  && ( y < ystart+20+18) )  return retvalue = 12;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+40)  && ( y < ystart+40+18) )  return retvalue = 2;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+40)  && ( y < ystart+40+18) )  return retvalue = 16;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+60)  && ( y < ystart+60+18) )  return retvalue = 5;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+60)  && ( y < ystart+60+18) )  return retvalue = 7;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+80)  && ( y < ystart+80+18) )  return retvalue = 4;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+80)  && ( y < ystart+80+18) )  return retvalue = 3;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+100) && ( y < ystart+100+18) ) return retvalue = 6;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+100) && ( y < ystart+100+18) ) return retvalue = 19;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+120) && ( y < ystart+120+18) ) return retvalue = 20;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+120) && ( y < ystart+120+18) ) return retvalue = 21;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+140) && ( y < ystart+140+18) ) return retvalue = 18;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+140) && ( y < ystart+140+18) ) return retvalue = 13;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+160) && ( y < ystart+160+18) ) return retvalue = 14;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+160) && ( y < ystart+160+18) ) return retvalue = 15;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+180) && ( y < ystart+180+18) ) return retvalue = 8;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+180) && ( y < ystart+180+18) ) return retvalue = 9;
    if (( x > xstart )    &&( x < xstart+98)  && (y > ystart+200) && ( y < ystart+200+18) ) return retvalue = 10;
    if (( x > xstart+100 )&&( x < xstart+198) && (y > ystart+200) && ( y < ystart+200+18) ) return retvalue = 17;
    return retvalue;
}

size_t BandView::MidiTrackPicked(int x, int y)
{
    size_t retvalue = 1000;
    int nMidiTracks = myBrute->GetNumberOfMidiTracks();

    for (int i = 1; i < nMidiTracks; i++)
    {
         int xt = 30 + ((i-1)%2) * 25;
         int yt = (i-1) * 20 + 70;
         if (( ( x-xt )*(x-xt)+(y-yt)*(y-yt) < 10*10 ) &&  ( myBrute->GetToneCount(i)> 0))
            retvalue = i;
    }
    return retvalue;
}

size_t BandView::ABCTrackPicked(int x, int y)
{
    size_t retvalue = 1000;
    for (size_t i = 0; i < BVabctracks.size(); i++)
    {
       if (( x > BVabctracks[i].x )&&(x < BVabctracks[i].x+97) && ( y > BVabctracks[i].y ) && ( y < BVabctracks[i].y+18 ))
       retvalue = i;
    }
    return retvalue;
}

bool BandView::ABCTrackMuted(int x, int y)
{
    bool retvalue = false;
    for (size_t i = 0; i < BVabctracks.size(); i++)
    {
       if (( x > BVabctracks[i].x+87 )&&(x < BVabctracks[i].x+97) && ( y > BVabctracks[i].y ) && ( y < BVabctracks[i].y+18 ))
       retvalue = true;
    }
    return retvalue;
}

size_t BandView::MidiTrackInABCTrackPicked(int x, int y)
{
    size_t retvalue = 1000;
    // first go to the ABCtrack on the band
    for (size_t i = 0; i < BVabctracks.size(); i++)
    {
       int myx = BVabctracks[i].x;
       int myy = BVabctracks[i].y;
       // now loop through all the attached miditracks
       for (size_t j =0; j < BVabctracks[i].miditrackinfo.size(); j++ )
       {
           int midix = myx + RelX(j);
           int midiy = myy + RelY(j);
           if (( (midix-x)*(midix-x)+(midiy-y)*(midiy-y)) < 10*10) retvalue = i;
       }
    }
    return retvalue;
}

size_t BandView::WhichMidiTrackInABCTrackPicked(int x, int y)
{
    size_t retvalue = 1000;
    // first go to the ABCtrack on the band
    for (size_t i = 0; i < BVabctracks.size(); i++)
    {
       int myx = BVabctracks[i].x;
       int myy = BVabctracks[i].y;
       // now loop through all the attached miditracks
       for (size_t j =0; j < BVabctracks[i].miditrackinfo.size(); j++ )
       {
           int midix = myx + RelX(j);
           int midiy = myy + RelY(j);
           if (( (midix-x)*(midix-x)+(midiy-y)*(midiy-y)) < 10*10) retvalue = j;
       }
    }
    return retvalue;
}

void BandView::mouseRightDown(wxMouseEvent& event)
{
    const wxPoint pt = wxGetMousePosition();
    int mouseX = pt.x - this->GetScreenPosition().x;
    int mouseY = pt.y - this->GetScreenPosition().y;

    size_t mypossibleMidiInABCTrack = MidiTrackInABCTrackPicked(mouseX, mouseY);
    if ((mypossibleMidiInABCTrack != 1000) &&(m_ABCMODE == false))
    {
         // std::cout << "Someone Picked a MidiTrack in an ABC Track" << std::endl;
         size_t whichmidi = WhichMidiTrackInABCTrackPicked(mouseX, mouseY);
         if (whichmidi !=1000)
         {
             std::cout <<"Right Click on Miditrack " << whichmidi << " in ABC Track " << mypossibleMidiInABCTrack;
             MidiTrackDialogue * custom = new MidiTrackDialogue( &BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi], &BVabctracks[mypossibleMidiInABCTrack] );
             custom->Show(true);
         }
    }

    size_t mypossibleABCTrack = ABCTrackPicked(mouseX, mouseY);
    if ((mypossibleABCTrack != 1000)  && (m_ABCMODE == false))
    {
        //std::cout << "Right Click on ABCtrack " << mypossibleABCTrack << std::endl;
        ABCTrackDialogue * custom = new ABCTrackDialogue( &BVabctracks[mypossibleABCTrack] );
        custom->Show(true);
        this->Refresh();
    }

    if (( mouseY > 545 ) && (mouseY < 570 ) && ( mouseX > 440) && (mouseX < 500))
    {
        // audience right clicked
        AudienceDialogue * myaudience = new AudienceDialogue( &m_volume, &m_panning );         if (myaudience == NULL) {};
        myaudioplayerAL->SetVolume(m_volume);
        myaudioplayerAL->SetGlobalPanning(m_panning);
    }

         // check for miditrack picked
     size_t mypossiblemiditrack = MidiTrackPicked(mouseX, mouseY);
     if (mypossiblemiditrack != 1000)
     {
         std::cout << " Asking for Midi Track " << mypossiblemiditrack << std::endl;

         MidiTrackView * newview = new MidiTrackView(myBrute, mypossiblemiditrack); if (newview == NULL) {}
        // this->SetCursor(wxCursor(wxCURSOR_HAND));
        // miditrackclicked = true;
        // miditrackclickednumber = mypossiblemiditrack;
     }

     size_t mypossiblelotroinstrument = LotroInstrumentPicked(mouseX, mouseY);
     if (mypossiblelotroinstrument!=100)
     {
         // an instrument was picked, so put hand icon
         this->SetCursor(wxCursor(wxCURSOR_HAND));

         lotroinstrumentclicked = false;
         lotroinstrumentclickednumber = mypossiblelotroinstrument;
         click_relx = 50;
         click_rely = 10;
         GainSettingsDialogue * newgains = new GainSettingsDialogue(lotroinstrumentclickednumber, &relativegain[lotroinstrumentclickednumber], &fadeouts[lotroinstrumentclickednumber] ); if (newgains == NULL) {}
     }


}

void BandView::mouseLeftDown(wxMouseEvent& event)
{
     const wxPoint pt = wxGetMousePosition();
     int mouseX = pt.x - this->GetScreenPosition().x;
     int mouseY = pt.y - this->GetScreenPosition().y;

     // check for instrument picked
     size_t mypossiblelotroinstrument = LotroInstrumentPicked(mouseX, mouseY);
     if (mypossiblelotroinstrument!=100)
     {
         // an instrument was picked, so put hand icon
         this->SetCursor(wxCursor(wxCURSOR_HAND));
         lotroinstrumentclicked = true;
         lotroinstrumentclickednumber = mypossiblelotroinstrument;
         click_relx = 50;
         click_rely = 10;
     }

     // check for miditrack picked
     size_t mypossiblemiditrack = MidiTrackPicked(mouseX, mouseY);
     if (mypossiblemiditrack != 1000)
     {
         std::cout << " Selected Midi Track " << mypossiblemiditrack << std::endl;
//         this->SetCursor(wxCursor(wxCURSOR_HAND));
          wxBitmap bitmap(32,32);
          wxMemoryDC dc;
          dc.SelectObject(bitmap);
          dc.SetBackground(*wxBLACK_BRUSH);  //   *wxTRANSPARENT_BRUSH);
          dc.Clear();


          int mymidiinstrument = myBrute->GetMidiInstrument( mypossiblemiditrack );
          bool myisdrum = myBrute->GetMidiIsDrum(mypossiblemiditrack);
          if (myisdrum) mymidiinstrument = 201;
          DrawOneMidiTrack(dc, 12, 12, mypossiblemiditrack , mymidiinstrument );
          wxImage image(bitmap.ConvertToImage());

          unsigned char* m_alphachannel = new unsigned char[image.GetWidth() * image.GetHeight()];
          for (int y = 0; y < image.GetHeight(); y++)
         {for (int x = 0; x < image.GetWidth(); x++){
          int dx = x - 12;
          int dy = y - 12;
          if (dx * dx + dy * dy <= 12*12){m_alphachannel[y * image.GetWidth() + x] = 255;}
           else{m_alphachannel[y * image.GetWidth() + x] = 0;}}}

          image.SetAlpha(m_alphachannel);
          wxCursor mycursornow(image);
          this->SetCursor(mycursornow);

       //  delete[] m_alphachannel;
         miditrackclicked = true;
         miditrackclickednumber = mypossiblemiditrack;
     }

     // check for ABCTrack picked
     size_t mypossibleABCtrack = ABCTrackPicked(mouseX, mouseY);
    // bool muter = ABCTrackMuted(mouseX, mouseY);
     if ((mypossibleABCtrack !=1000)  && ( CRTLIsDown == false))
     {
           // std::cout << " Selected ABC Track " << mypossibleABCtrack << std::endl;
            this->SetCursor(wxCursor(wxCURSOR_HAND));
            MovingABCTrack = BVabctracks[mypossibleABCtrack];
            click_relx = BVabctracks[mypossibleABCtrack].x - mouseX;
            click_rely = BVabctracks[mypossibleABCtrack].y - mouseY;
            BVabctracks.erase(BVabctracks.begin()+mypossibleABCtrack);
            abctrackclicked = true;
            this->Refresh();
     }
    //
     if ((mypossibleABCtrack != 1000) && ( CRTLIsDown == true) && (ShiftIsDown == false) )  // ctrl + left mouse switch mute for single track
     {
            BVabctracks[mypossibleABCtrack].muted = !BVabctracks[mypossibleABCtrack].muted;
            myaudioplayerAL->SetMute(BVabctracks[mypossibleABCtrack].id, BVabctracks[mypossibleABCtrack].muted);
            this->Refresh();
     }
     if ((mypossibleABCtrack != 1000) && ( CRTLIsDown == true) && (ShiftIsDown == true) )  // ctrl + shift + left mouse  mute all other tracks
     {
         for (size_t i = 0; i < BVabctracks.size(); i++)
         {
             if (i!=mypossibleABCtrack)
             {
                 BVabctracks[i].muted = true;
                 myaudioplayerAL->SetMute(BVabctracks[i].id, true);
             }
         }
         myaudioplayerAL->SetMute(BVabctracks[mypossibleABCtrack].id, false);
         BVabctracks[mypossibleABCtrack].muted = false;
         this->Refresh();
     }



     // check for Midi in ABC Track picked
     size_t mypossibleMidiInABCTrack = MidiTrackInABCTrackPicked(mouseX, mouseY);
     if ((mypossibleMidiInABCTrack != 1000) && ( !CRTLIsDown ) && (!ShiftIsDown))
     {
         // std::cout << "Someone Picked a MidiTrack in an ABC Track" << std::endl;
         size_t whichmidi = WhichMidiTrackInABCTrackPicked(mouseX, mouseY);
         if (whichmidi !=1000)
         {
             // std::cout <<"Someone Picked Miditrack " << whichmidi << " in ABC Track " << mypossibleMidiInABCTrack;


             wxBitmap bitmap(32,32);
             wxMemoryDC dc;
             dc.SelectObject(bitmap);
             dc.SetBackground(*wxBLACK_BRUSH);  //   *wxTRANSPARENT_BRUSH);
             dc.Clear();
             int mymidiinstrument = BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi].midiinstrument;
             if (BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi].isdrum) mymidiinstrument = 201;
             DrawOneMidiTrack(dc, 12, 12, BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi].miditrack , mymidiinstrument );
             wxImage image(bitmap.ConvertToImage());

          unsigned char* m_alphachannel = new unsigned char[image.GetWidth() * image.GetHeight()];
          for (int y = 0; y < image.GetHeight(); y++)
         {for (int x = 0; x < image.GetWidth(); x++){
          int dx = x - 12;
          int dy = y - 12;
          if (dx * dx + dy * dy <= 12*12){m_alphachannel[y * image.GetWidth() + x] = 255;}
           else{m_alphachannel[y * image.GetWidth() + x] = 0;}}}

             image.SetAlpha(m_alphachannel);
             wxCursor mycursornow(image);

             this->SetCursor(mycursornow);

             MovingMidiTrack = BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi];
            // MovingMidiTrackNumber = BVabctracks[mypossibleMidiInABCTrack].miditracks[whichmidi];

            // BVabctracks[mypossibleMidiInABCTrack].miditracks.erase( BVabctracks[mypossibleMidiInABCTrack].miditracks.begin() + whichmidi );
             BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.erase( BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.begin() + whichmidi );

             midiinabctrackclicked = true;

             this->Refresh();
         }
     }

     if ((mypossibleMidiInABCTrack != 1000) && ( CRTLIsDown ) && (!ShiftIsDown))
     {
         size_t whichmidi = WhichMidiTrackInABCTrackPicked(mouseX, mouseY);
         if ( whichmidi != 1000)
         {
             // we decided to split a midi track into the singular instruments, but we should only do that for drums right now
             BandViewMidiTrack TempMidi = BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi];
             BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.erase( BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.begin() + whichmidi );
             int drummapping = TempMidi.drummapping;

             for (size_t i = 0; i < TempMidi.samples->size(); i++)
             {
                 if (TempMidi.samples->at(i))
                    {
                        TempMidi.drumtone = i;
                        TempMidi.directmapping = myBrute->m_Mapping.m_drumsmapd[drummapping][i];

                        BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.push_back(TempMidi);
                    }
             }

             this->Refresh();
         }
     }

     if ((mypossibleMidiInABCTrack != 1000) && ( !CRTLIsDown ) && (ShiftIsDown))
     {
         size_t whichmidi = WhichMidiTrackInABCTrackPicked(mouseX, mouseY);
         if ( whichmidi != 1000)
         {
             // we decided to split a midi track into the singular instruments, but we should only do that for drums right now
             BandViewMidiTrack TempMidi = BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi];
             BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.push_back(TempMidi);
             this->Refresh();
         }
     }
     /*
    bool abctrackclicked = false;
    size_t abctrackclickednumber;
     */

    if (( mouseY > 580 ) && (mouseY<630) && ( mouseX > 100 ) && ( mouseX < 790 ))
    {
        myaudioplayerAL->Seek( ((mouseX-100.0)/690.0)  );
    }

    if (( mouseY > 545 ) && (mouseY < 570 ) && ( mouseX > 440) && (mouseX < 500))
    {
       //  std::cout << "Audience clicked" << std::endl;
        if ( myaudioplayerAL->audio_playing > 0 )
        {
            myaudioplayerAL->Stop();
            myaudioplayerAL->audio_playing=0;

            this->Refresh();
        }
        else
        if (myBrute->DoIHaveAMidi())
        {

            GenerateConfigHeader();
            AppendMapping();


            myBrute->Transcode(&myBrute->m_MappingText);


//            myMidiPreview->GeneratePreviewMidi(&myBrute->m_ABCText, int64_t( myBrute->m_globalmaxtick/0.36) );
         //   int64_t realduration;
            // myMidiPreview->GeneratePreviewMidi2(&myBrute->m_ABCText, &realduration );

            myaudioplayerAL->SendABC(&myBrute->m_ABCText);
            myaudioplayerAL->GetABC()->UpdateToneCounts();
            myaudioplayerAL->Play();

            myaudioplayerAL->audio_playing = 1;

            this->Refresh();
        }
    }

    // Open a Midifile
    if (( mouseY > 25 ) && ( mouseY < 50 ) && (mouseX > 5) && (mouseX < 80))
    {
        // Miditracks clicked left -> Open File Open Menu
        wxFileDialog *openDialog = new wxFileDialog(this, wxT("Select Midi File~"), wxT(""), wxT(""), wxT("Midi Files (*.mid)|*.mid"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        int response = openDialog->ShowModal();
        if (response == wxID_OK)
        {
           // load this midi file
           wxString MidiFileName = openDialog->GetPath();

           char cstring[1024];
           strncpy(cstring, (const char*)MidiFileName.mb_str(wxConvUTF8), 1023);

          // delete(this->myBrute);
          // this->myBrute = new(Brute);
           myBrute->LoadMidi(cstring);  // this loads the midi into the Brute instance
        }
        GenerateConfigHeader();
        Refresh();
    }

    if ((mouseX>100) && (mouseY > 505) && (mouseX < 135) && (mouseY < 540))
    {
        // clear arrangement
        GenerateConfigHeader();
        myBrute->ParseConfig(&myBrute->m_MappingText);
        GetMapping();
        Refresh();
    }

    if ((mouseX>740) && (mouseY > 505) && (mouseX < 790) && (mouseY < 540))
    {
        if (myBrute->DoIHaveAMidi())
        {
           myBrute->GenerateDefaultConfig();
           myBrute->ParseConfig(&myBrute->m_MappingText);
           GetMapping();
           Refresh();
        }
    }

    // clicking load map
    if ((mouseX>157) && (mouseY > 505) && (mouseX < 257) && (mouseY < 540))    // 157 + 100
    {
        if (myBrute->DoIHaveAMidi())
        {
           wxFileDialog *openDialog = new wxFileDialog(this, wxT("Load Mapping~"), wxT(""), wxT(""), wxT("Mapping Files (*.txt)|*.txt"), wxFD_OPEN);
           int response = openDialog->ShowModal();
           if (response == wxID_OK)
           {
               myBrute->m_MappingText.str(  std::string() );
               std::ifstream mappingfile;
               mappingfile.open(openDialog->GetPath());
               myBrute->m_MappingText << mappingfile.rdbuf();
               mappingfile.close();
               myBrute->ParseConfig(&myBrute->m_MappingText);
               GetMapping();
           }
        }
    }

    // clicking save map
    if ((mouseX>280) && (mouseY > 505) && (mouseX < 380) && (mouseY < 540))    // 157 + 100
    {
        if (myBrute->DoIHaveAMidi())
        {

           wxFileDialog *openDialog = new wxFileDialog(this, wxT("Save Mapping~"), wxT(""), wxT(""), wxT("Mapping Files (*.txt)|*.txt"), wxFD_SAVE);
           int response = openDialog->ShowModal();
           if (response == wxID_OK)
           {
               GenerateConfigHeader();   // this is just a placeholder real deal should come from bandview
               AppendMapping();

               std::ofstream mappingfile;
               mappingfile.open(openDialog->GetPath());
               mappingfile << myBrute->m_MappingText.rdbuf();
               mappingfile.close();
           }

        }
    }

    // clicking ABC export
    if ((mouseX>400) && (mouseY > 505) && (mouseX < 435) && (mouseY < 540))    // 157 + 100
    {
        if (myBrute->DoIHaveAMidi())
        {
            // std::cout << " ABC save clicked " << std::endl;
           wxFileDialog *openDialog = new wxFileDialog(this, wxT("Export ABC File~"), wxT(""), wxT(""), wxT("ABC Files (*.abc)|*.abc"), wxFD_SAVE);
           int response = openDialog->ShowModal();
           if (response == wxID_OK)
           {
               // set the ABC output file name
               GenerateConfigHeader();   // this is just a placeholder real deal should come from bandview
               AppendMapping();

               myBrute->Transcode(&myBrute->m_MappingText);
            //   myBrute->GenerateABC();

               std::ofstream abcoutfile;
               abcoutfile.open(openDialog->GetPath());
               abcoutfile << myBrute->m_ABCText.rdbuf();
               abcoutfile.close();
           }
        }
    }


        // clicking ABC settings
    if ((mouseX>450) && (mouseY > 505) && (mouseX < 530) && (mouseY < 540))    // 157 + 100
    {
        if (myBrute->DoIHaveAMidi())
        {
            std::cout << " ABC settings clicked " << std::endl;
            //
            ABCSettingsDialogue * abcsettings = new ABCSettingsDialogue(   &m_ABCnamingscheme , &myABCHeader );
            if (abcsettings == NULL) {};
        }
    }
 }

 void BandView::mouseLeftUp(wxMouseEvent& event)
 {
     this->SetCursor(wxCursor(wxCURSOR_ARROW));

     const wxPoint pt = wxGetMousePosition();
     int mouseX = pt.x - this->GetScreenPosition().x;
     int mouseY = pt.y - this->GetScreenPosition().y;

     if (miditrackclicked)
     {
         // find out if we hit an ABC Track
         size_t mypossibleABCtrack = ABCTrackPicked(mouseX+12, mouseY+12);
         if (mypossibleABCtrack !=1000)
         {
             // ok we dropped the Miditrack on an ABC Track
         //    BVabctracks[mypossibleABCtrack].miditracks.push_back(miditrackclickednumber);
             BandViewMidiTrack newtrack;
             newtrack.miditrack = miditrackclickednumber;
             newtrack.midiinstrument = myBrute->GetMidiInstrument( miditrackclickednumber );
             newtrack.isdrum = myBrute->GetMidiIsDrum(miditrackclickednumber);
             newtrack.haspitchbends = (myBrute->m_pitchbendcounter[newtrack.miditrack] > 0);
             newtrack.samples = &myBrute->m_samplesused[ miditrackclickednumber ];
             BVabctracks[mypossibleABCtrack].miditrackinfo.push_back(newtrack);


             std::cout << " Added Miditrack to ABCtrack " << mypossibleABCtrack << "  Midi " << miditrackclickednumber << std::endl;

             miditrackclicked = false;
             this->Refresh();
             //LiveUpdateAudio();
         }
     }

     // std::cout << " dropped at " << mouseX << "  " << mouseY << std::endl;
     if (lotroinstrumentclicked)
     {
         // are we dropping a new ABC track or are we switching instrument on an existing one?
         size_t mypossibleABCtrack = ABCTrackPicked(mouseX, mouseY);
         if ( mypossibleABCtrack !=1000)
         {
             BVabctracks[mypossibleABCtrack].instrument = lotroinstrumentclickednumber;
             lotroinstrumentclicked = false;
             this->Refresh();
             // Are we currently playing stuff? If yes lets also update the instrument in the Audioplayer
             if ( myaudioplayerAL->audio_playing > 0)
                myaudioplayerAL->SetInstrument( BVabctracks[mypossibleABCtrack].id ,lotroinstrumentclickednumber);
         }
         else
         // check if we are in the band area
         if ((mouseX > 100)&&(mouseX<800)&&(mouseY>50)&&(mouseY<900))
         {
             // For now just add this, we have to check if we are hitting an existing one of course
             // Add this to the ABCTracks
             BandViewABCTrack newplayer;
             newplayer.x = mouseX-click_relx;
             newplayer.y = mouseY-click_rely;
             click_relx = 0;
             click_rely = 0;
             newplayer.id = m_globalid; m_globalid++;
             newplayer.instrument = lotroinstrumentclickednumber;
         //    newplayer.miditracks = {};
             BVabctracks.push_back(newplayer);
             lotroinstrumentclicked = false;
             this->Refresh();
         }
     }
     if (abctrackclicked)
     {
         if ((mouseX > 100)&&(mouseX<800)&&(mouseY>50)&&(mouseY<900))
         {
             // we just dropped an already existing track, so we have to update the position
             MovingABCTrack.x = mouseX+click_relx;
             MovingABCTrack.y = mouseY+click_rely;
             click_relx = 0;
             click_rely = 0;
             BVabctracks.push_back(MovingABCTrack);
             abctrackclicked=false;
             this->Refresh();
             myaudioplayerAL->SetPanning(  BVabctracks[ BVabctracks.size()-1 ].id  , -int( m_panning * ((BVabctracks[BVabctracks.size()-1].x-100)/590.0 - 0.5)   ));
         }
     }
     // someone is dropping a miditrack that was picked up from an ABC Track
     if (midiinabctrackclicked)
     {

         size_t mypossibleABCtrack = ABCTrackPicked(mouseX+12, mouseY+12);
         // dropping on an ABCtrack
         if (mypossibleABCtrack != 1000)
         {
        //     BVabctracks[mypossibleABCtrack].miditracks.push_back(MovingMidiTrackNumber);
             BVabctracks[mypossibleABCtrack].miditrackinfo.push_back(MovingMidiTrack);
             miditrackclicked = false;
             this->Refresh();
             //LiveUpdateAudio();
         }
     }

     // Mouse was released, so nothing is held anymore
     midiinabctrackclicked = false;
     abctrackclicked = false;
     lotroinstrumentclicked = false;
     miditrackclicked = false;
 }

BandView::BandView(wxFrame* parent, Brute * myBrutep, MidiTrackView * myMidiTrackViewp, AudioPlayerAL * myAudioPlayerAL) :
wxPanel(parent)
{
    parent->SetLabel (wxT("Band View"));
    parent->EnableCloseButton(false);
    myBrute = myBrutep;
   // myaudioplayer = myaudioplayerp;
    myaudioplayerAL = myAudioPlayerAL;
    myMidiTrackView = myMidiTrackViewp;


    // Paint the Sample Load Picture White
    wxMemoryDC dc2;
    dc2.SelectObject(myOverLoadPic[0]);
    for (int i = 0; i < 690; i++)
    {
        dc2.SetPen( wxPen( wxColor(255,255,255), 1));
        dc2.DrawLine(i, 0, i, 50);
    }
    //myOverLoadPicture = new OverLoadPicture(myMidiPreview);
    DragAcceptFiles(true);

  //  Bind(wxEVT_KEY_DOWN, &BandView::OnKeyDown, this);


    wxBitmap bitmap(32, 32);
    wxMemoryDC dc(bitmap);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    wxImage image(bitmap.ConvertToImage());

    unsigned char* m_alphachannel = new unsigned char[image.GetWidth() * image.GetHeight()];
    for (int y = 0; y < image.GetHeight(); y++)
    {for (int x = 0; x < image.GetWidth(); x++){
       int dx = x - 12;
       int dy = y - 12;
       if (dx * dx + dy * dy <= 12*12){m_alphachannel[y * image.GetWidth() + x] = 255;}
       else{m_alphachannel[y * image.GetWidth() + x] = 0;}}}
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BandView::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BandView::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
 void BandView::DrawMidiTracks(wxDC& dc)
 {
     int nMidiTracks = myBrute->GetNumberOfMidiTracks();
     for (int i = 1; i < nMidiTracks; i++)
     {
         size_t midiinstrumentnumber = myBrute->GetMidiInstrument(i);
         int x = 30 + ((i-1)%2) * 25;
         int y = (i-1) * 20 + 70;
         if ( myBrute->GetMidiIsDrum(i) ) midiinstrumentnumber = 201;
         if ( myBrute->GetToneCount(i) > 0 ) DrawOneMidiTrack(dc, x, y, i, midiinstrumentnumber);
     }
 }



void BandView::DrawOneMidiTrack(wxDC& dc, int x, int y, int i, size_t midiinstrumentnumber)
{
   dc.SetBrush(*wxGREEN_BRUSH); // green filling

   wxColor mycolor;
   mycolor.Set("rgb(255,255,255)"); // default is white
   if ( midiinstrumentnumber < 17) mycolor.Set("rgb(255,200,200)");  // pale red for pianos
   if (( midiinstrumentnumber > 16) && ( midiinstrumentnumber < 25)) mycolor.Set("rgb(200,200,255)"); // pale blue  for organs
   if (( midiinstrumentnumber > 24) && ( midiinstrumentnumber < 33)) mycolor.Set("rgb(255,150,150)"); // stronger red  for guitars
   if (( midiinstrumentnumber > 32) && ( midiinstrumentnumber < 41)) mycolor.Set("rgb(255,100,100)"); // even stronger red  for base
   if (( midiinstrumentnumber > 40) && ( midiinstrumentnumber < 49)) mycolor.Set("rgb(150,150,255)"); // stronger blue  for strings
   if (( midiinstrumentnumber > 48) && ( midiinstrumentnumber < 57)) mycolor.Set("rgb(100,100,255)"); // even stronger blue  for ensemble
   if (( midiinstrumentnumber > 56) && ( midiinstrumentnumber < 65)) mycolor.Set("rgb(200,255,200)"); // green  for brass
   if (( midiinstrumentnumber > 64) && ( midiinstrumentnumber < 73)) mycolor.Set("rgb(150,255,150)"); // green  for reed
   if (( midiinstrumentnumber > 72) && ( midiinstrumentnumber < 81)) mycolor.Set("rgb(100,255,100)"); // green  for pipes
   if (( midiinstrumentnumber > 80) && ( midiinstrumentnumber < 97)) mycolor.Set("rgb(255,255,200)"); // green  for synth lead
   if (( midiinstrumentnumber > 96) && ( midiinstrumentnumber < 105)) mycolor.Set("rgb(255,255,150)"); // green  for synth
   if (( midiinstrumentnumber > 104) && ( midiinstrumentnumber < 113)) mycolor.Set("rgb(255,200,255)"); // green  for ethnic
   if (midiinstrumentnumber == 201) mycolor.Set("rgb(150,150,150)"); // dark grey for Drums


   dc.SetBrush(mycolor);


   dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 5-pixels-thick red outline
   dc.DrawCircle( wxPoint(x,y), 12); /* radius */ // );
   std::stringstream mytext;
   mytext << i;
   dc.DrawText(mytext.str(), x-4,y-6);
 }

 void BandView::DrawOneMidiTrack(wxMemoryDC& dc, int x, int y, int i, size_t midiinstrumentnumber)
{
   dc.SetBrush(*wxGREEN_BRUSH); // green filling

   wxColor mycolor;
   mycolor.Set("rgb(255,255,255)"); // default is white
   if ( midiinstrumentnumber < 17) mycolor.Set("rgb(255,200,200)");  // pale red for pianos
   if (( midiinstrumentnumber > 16) && ( midiinstrumentnumber < 25)) mycolor.Set("rgb(200,200,255)"); // pale blue  for organs
   if (( midiinstrumentnumber > 24) && ( midiinstrumentnumber < 33)) mycolor.Set("rgb(255,150,150)"); // stronger red  for guitars
   if (( midiinstrumentnumber > 32) && ( midiinstrumentnumber < 41)) mycolor.Set("rgb(255,100,100)"); // even stronger red  for base
   if (( midiinstrumentnumber > 40) && ( midiinstrumentnumber < 49)) mycolor.Set("rgb(150,150,255)"); // stronger blue  for strings
   if (( midiinstrumentnumber > 48) && ( midiinstrumentnumber < 57)) mycolor.Set("rgb(100,100,255)"); // even stronger blue  for ensemble
   if (( midiinstrumentnumber > 56) && ( midiinstrumentnumber < 65)) mycolor.Set("rgb(200,255,200)"); // green  for brass
   if (( midiinstrumentnumber > 64) && ( midiinstrumentnumber < 73)) mycolor.Set("rgb(150,255,150)"); // green  for reed
   if (( midiinstrumentnumber > 72) && ( midiinstrumentnumber < 81)) mycolor.Set("rgb(100,255,100)"); // green  for pipes
   if (( midiinstrumentnumber > 80) && ( midiinstrumentnumber < 97)) mycolor.Set("rgb(255,255,200)"); // green  for synth lead
   if (( midiinstrumentnumber > 96) && ( midiinstrumentnumber < 105)) mycolor.Set("rgb(255,255,150)"); // green  for synth
   if (( midiinstrumentnumber > 104) && ( midiinstrumentnumber < 113)) mycolor.Set("rgb(255,200,255)"); // green  for ethnic
   if (midiinstrumentnumber == 201) mycolor.Set("rgb(150,150,150)"); // dark grey for Drums


   dc.SetBrush(mycolor);


   dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 5-pixels-thick red outline
   dc.DrawCircle( wxPoint(x,y), 12); /* radius */ // );
   std::stringstream mytext;
   mytext << i;
   dc.DrawText(mytext.str(), x-4,y-6);
 }

 void BandView::DrawOneInstrument(wxDC& dc, int x, int y, wxString mytext, bool muted)
 {
    dc.SetBrush(*wxWHITE_BRUSH); // blue filling
    dc.SetPen( wxPen( wxColor(255,175,175), 1 ) ); // 10-pixels-thick pink outline
    dc.DrawRectangle( x, y, 97, 18 );
    dc.DrawText(mytext, x+3, y+1);
    if (muted)
    {
        dc.SetPen ( wxPen( wxColor(0,0,0), 2 ) );
        dc.DrawLine( x,y, x+97, y+18  );
        dc.DrawLine( x+97,y, x, y+18 );
    }
 }


 void BandView::DrawLotroInstruments(wxDC& dc)
 {
    int x = 800;
    int x2 = x+100;

    DrawOneInstrument(dc, x , 50,  lotroinstruments_formal[0], false );
    DrawOneInstrument(dc, x2, 50, lotroinstruments_formal[11], false);
    DrawOneInstrument(dc, x, 70, lotroinstruments_formal[1], false);
    DrawOneInstrument(dc, x2, 70, lotroinstruments_formal[12], false);
    DrawOneInstrument(dc, x, 90, lotroinstruments_formal[2], false);
    DrawOneInstrument(dc, x2, 90, lotroinstruments_formal[16], false);
    DrawOneInstrument(dc, x, 110, lotroinstruments_formal[5], false);
    DrawOneInstrument(dc, x2, 110, lotroinstruments_formal[7], false);
    DrawOneInstrument(dc, x, 130, lotroinstruments_formal[4], false);
    DrawOneInstrument(dc, x2, 130, lotroinstruments_formal[3], false);
    DrawOneInstrument(dc, x, 150, lotroinstruments_formal[6], false);
    DrawOneInstrument(dc, x2, 150, lotroinstruments_formal[19], false);
    DrawOneInstrument(dc, x, 170, lotroinstruments_formal[20], false);
    DrawOneInstrument(dc, x2, 170, lotroinstruments_formal[21], false);
    DrawOneInstrument(dc, x, 190, lotroinstruments_formal[18], false);
    DrawOneInstrument(dc, x2, 190, lotroinstruments_formal[13], false);
    DrawOneInstrument(dc, x, 210, lotroinstruments_formal[14], false);
    DrawOneInstrument(dc, x2, 210, lotroinstruments_formal[15], false);
    DrawOneInstrument(dc, x, 230, lotroinstruments_formal[8], false);
    DrawOneInstrument(dc, x2, 230, lotroinstruments_formal[9], false);
    DrawOneInstrument(dc, x, 250, lotroinstruments_formal[10], false);
    DrawOneInstrument(dc, x2, 250, lotroinstruments_formal[17], false);
 }

int BandView::RelX(int m)
{
    std::vector<int> vals = {0, 25,50,75,100, 109, 100, 75, 50, 25, 0, -10};
    return vals[m%12];
}

int BandView::RelY(int m)
{
    std::vector<int> vals = {-14, -14, -14, -14, -14, 8, 30,30,30,30,30,8};
    return vals[m%12] + (m/12) * (vals[m%12]-8);
}

void BandView::DrawABCTracks(wxDC& dc)
{
   for (size_t i = 0; i < BVabctracks.size(); i++)
   {
       int ABCinstrument = BVabctracks[i].instrument;
       DrawOneInstrument(dc, BVabctracks[i].x, BVabctracks[i].y, lotroinstruments_formal[ABCinstrument], BVabctracks[i].muted );

       for (size_t m = 0; m < BVabctracks[i].miditrackinfo.size(); m++)
       {
           int midiinstrument = BVabctracks[i].miditrackinfo[m].midiinstrument;
           int miditrack = BVabctracks[i].miditrackinfo[m].miditrack;
           if (BVabctracks[i].miditrackinfo[m].isdrum) midiinstrument = 201;
           DrawOneMidiTrack(dc, BVabctracks[i].x+RelX(m), BVabctracks[i].y+RelY(m), miditrack, midiinstrument);
       }
   }
}

void BandView::GenerateConfigHeader()
{
    myBrute->m_MappingText.str(std::string());

    // default.config values
    int drumtype = 0;
    char defaultdrumhandling[127] = "nosplit";
    char ABCstyle[127] = "Rocks";
    char defaulttranscriber[127] = "Himbeertony";
    char dummy[127];

    // check for defaults file
    std::ifstream defaultsfile;
    defaultsfile.open("default.config");
    if (!defaultsfile.fail() )
    {
        std::cout << "Using default.config" << std::endl;
        defaultsfile >> dummy;
        defaultsfile >> drumtype >> defaultdrumhandling;
        defaultsfile >> dummy;
        defaultsfile >> ABCstyle;
        defaultsfile >> dummy;
        defaultsfile >> defaulttranscriber;
        defaultsfile.close();
    }
    else
    {
        std::cout << "No default.config, using intrinsic defaults" << std::endl;
        std::ofstream newdefaultsfile;
        newdefaultsfile.open("default.config");
        newdefaultsfile << "Drums: 0 nosplit" << std::endl;
        newdefaultsfile << "Style: Rocks" << std::endl;
        newdefaultsfile << "Transcriber:" << std::endl;
        newdefaultsfile << "Himbeertony" << std::endl;
        newdefaultsfile.close();
    }
    bool drumsplitting = true; if (drumsplitting == false ) {};
    if (strcmp("nosplit", defaultdrumhandling) >= 0)
        drumsplitting = false;

    myBrute->m_MappingText << "Name: " << myABCHeader.SongName << std::endl;
    myBrute->m_MappingText << "Speedup: " << myABCHeader.speedup << std::endl;
    myBrute->m_MappingText << "Pitch: " << myABCHeader.globalpitch << std::endl;

    // remark .. think about adding compressor values!!!

    myBrute->m_MappingText << "Style: " << ABCStyleNames[ m_ABCnamingscheme ] << "  % Defaults for -a rock and a hard place-, others: TSO, Meisterbarden, Bara" << std::endl;
    myBrute->m_MappingText << "Volume: " << myABCHeader.globalvolume << "       % scaled, midi volume was " << myBrute->GetGlobalMaxVel() - 254 << std::endl;

    myBrute->m_MappingText << "Compress: 1.0" << "   % default : midi dynamics, between 0 and 1: smaller loudness differences, >1: increase loudness differences" << std::endl;
    myBrute->m_MappingText << "%no pitch guessing   %uncomment to switch off guessing of default octaves" << std::endl;
    myBrute->m_MappingText << "%no back folding     %uncomment to switch off folding of tone-pitches inside the playable region" << std::endl;
    myBrute->m_MappingText << "fadeout length 0    %seconds before the end to start with fadeout (try something between 5 and 15)" << std::endl;
    myBrute->m_MappingText << "Transcriber " << myABCHeader.Transcriber << std::endl;
    myBrute->m_MappingText << std::endl;
    myBrute->m_MappingText << std::endl;

}

void BandView::render(wxDC&  dc)
{
    // draw some text
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // black line, 3 pixels thick
    dc.DrawLine(5, 25, 80, 25);
    dc.DrawLine(5, 50, 80, 50);
    dc.DrawLine(5, 25, 5, 50);
    dc.DrawLine(80, 25, 80, 50);

    if (myBrute->DoIHaveAMidi())
    {
        dc.SetBrush( wxBrush(wxColor( 100,250,100 )) ); // light green
    }
    else
    {
        dc.SetBrush( wxBrush(wxColor( 200,100,100 )) ); // blue filling
    }
    dc.DrawRectangle(6, 26, 73 , 23);
    dc.DrawText(wxT("MIDI Tracks"), 10, 30);

    int x = 105; int y = 510;

    dc.DrawLine( x-5, y - 5, x + 5 + 30, y - 5 );
    dc.DrawLine( x-5, y +20, x + 5 + 30, y +20 );
    dc.DrawLine( x + 5 + 30, y-5, x + 5 + 30, y+20);
    dc.DrawLine( x -5, y - 5, x - 5, y + 20);           // 100, 505, 135, 540
    dc.DrawRectangle( x-4, y - 4, 38, 23);
    dc.DrawText(wxT("Clear"), x, y);


    x = 745;

    dc.DrawLine( x-5, y - 5, x + 5 + 40, y - 5 );
    dc.DrawLine( x-5, y+20 , x + 5 + 40, y + 20);
    dc.DrawLine( x-5, y-5, x-5, y+20);
    dc.DrawLine( x+45, y-5, x+45, y + 20);
    dc.DrawRectangle( x-4, y-4, 48, 23 );           // 740, 505, 790, 540
    dc.DrawText(wxT("Default"), x, y);

    int sx = 100;
    x = 157;
    dc.DrawLine( x-5, y - 5, x + 5 + sx, y - 5 );
    dc.DrawLine( x-5, y +20, x + 5 + sx, y +20 );
    dc.DrawLine( x + 5 + sx, y-5, x + 5 + sx, y+20);
    dc.DrawLine( x -5, y - 5, x - 5, y + 20);           // 100, 505, 135, 540
    dc.DrawRectangle( x-4, y - 4, 8 + sx, 23);
    dc.DrawText(wxT("Load Arrangement"), x, y);

    x = 280; sx = 100;
    dc.DrawLine( x-5, y - 5, x + 5 + sx, y - 5 );
    dc.DrawLine( x-5, y +20, x + 5 + sx, y +20 );
    dc.DrawLine( x + 5 + sx, y-5, x + 5 + 30, y+20);
    dc.DrawLine( x -5, y - 5, x - 5, y + 20);           // 100, 505, 135, 540
    dc.DrawRectangle( x-4, y - 4, 8 + sx, 23);
    dc.DrawText(wxT("Save Arrangement"), x, y);


    x = 400; sx = 35;
    dc.DrawLine( x-5, y - 5, x + 5 + sx, y - 5 );
    dc.DrawLine( x-5, y +20, x + 5 + sx, y +20 );
    dc.DrawLine( x + 5 + sx, y-5, x + 5 + 30, y+20);
    dc.DrawLine( x -5, y - 5, x - 5, y + 20);           // 100, 505, 135, 540
    dc.DrawRectangle( x-4, y - 4, 8 + sx, 23);
    dc.DrawText(wxT("ABC"), x, y);

    x = 450; sx = 80;
    dc.DrawLine( x-5, y - 5, x + 5 + sx, y - 5 );
    dc.DrawLine( x-5, y +20, x + 5 + sx, y +20 );
    dc.DrawLine( x + 5 + sx, y-5, x + 5 + 30, y+20);
    dc.DrawLine( x -5, y - 5, x - 5, y + 20);           // 100, 505, 135, 540
    dc.DrawRectangle( x-4, y - 4, 8 + sx, 23);
    dc.DrawText(wxT("ABC Settings"), x, y);

    // draw a line
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 100, 50, 100, 500 ); // draw line across the rectangle

    dc.DrawText(wxT("Instruments"), 810, 30);
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 790, 50, 790, 500 ); // draw line across the rectangle

    dc.DrawLine( 100,500, 790, 500 );
    dc.DrawLine( 100, 50, 790, 50);

    dc.DrawLine( 440, 545, 500, 545);
    dc.DrawLine( 440, 570, 500, 570);
    dc.DrawLine( 440, 545, 440, 570);
    dc.DrawLine( 500, 545, 500, 570);

    if ( myaudioplayerAL->audio_playing > 0)
    {
        dc.SetPen( wxPen( wxColor(200,50,200) ) );
        dc.SetBrush( wxBrush(wxColor( 50,200,50 )) ); // blue filling
       // float position = myaudioplayerAL->Position();

    }
    else
    {
        dc.SetPen( wxPen( wxColor(180,180,180) ) );
        dc.SetBrush( wxBrush(wxColor( 200,100,100 )) ); // blue filling

    }
    dc.DrawRectangle(441, 546, 58 , 23);

    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) );
    dc.DrawText(wxT("Audience"), 445, 550);


    // Draw Overloading Info at 100,600 - 790, 700

    if (myaudioplayerAL->GetABC() != NULL)
    {


    if (( myaudioplayerAL->GetABC()->AudioReady) && !(myaudioplayerAL->GetABC()->AudioRedrawn))
    {
       wxMemoryDC dc2;
       dc2.SelectObject(myOverLoadPic[0]);

       for (size_t i = 0; i < myaudioplayerAL->GetABC()->m_TotalToneCounts.size(); i++)
       {
           dc2.SetPen( wxPen( wxColor(0,0,0), 1));
           if ( myaudioplayerAL->GetABC()->m_TotalToneCounts[i] > 64) dc2.SetPen( wxPen( wxColor(255,0,0), 1));
           if ( myaudioplayerAL->GetABC()->m_TotalToneCounts[i] < 65) dc2.SetPen( wxPen( wxColor(0,255,0), 1));
           dc2.DrawLine(i, 50, i, 50-myaudioplayerAL->GetABC()->m_TotalToneCounts[i]/2);
           dc2.SetPen( wxPen( wxColor(255,255,255), 1));
           dc2.DrawLine(i, 50-myaudioplayerAL->GetABC()->m_TotalToneCounts[i]/2, i, 0);
       }
       myaudioplayerAL->GetABC()->AudioRedrawn = true;
    }
    }


    dc.DrawBitmap(myOverLoadPic[0], 100, 580, false);


    //dc.SetPen( wxPen( wxColor(50,50,50), 3));
    //dc.DrawLine( 100, 600, 790, 600);
    //dc.DrawLine( 100, 620, 790, 620);
    //dc.SetPen( wxPen( wxColor(100,100,100), 3));
    //for (int m = 0; m < 24; m++)
    //     dc.DrawLine( 100 + m * 30, 601, 100+m*30, 619 );


    DrawLotroInstruments(dc);
    DrawMidiTracks(dc);
    DrawABCTracks(dc);


  /*  // draw a rectangle
    dc.SetBrush(*wxBLUE_BRUSH); // blue filling
    dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
    dc.DrawRectangle( 300, 100, 400, 200 );
*/

    // Look at the wxDC docs to learn how to draw other stuff
}

void BandView::OnDropFiles(wxDropFilesEvent& event) {
    //wxArrayString * files;
    auto files = event.GetFiles();
    // std::cout<< "Files dropped " << files[0] << std::endl;
    // Do something with the files...
    wxString MidiFileName = files[0];
    // is this actually a midi???
    char cstring[1024];
    strncpy(cstring, (const char*)MidiFileName.mb_str(wxConvUTF8), 1023);


    if ((MidiFileName.Find(".mid") != wxNOT_FOUND)||(MidiFileName.Find(".MID") != wxNOT_FOUND))
    {
       m_ABCMODE = false;
       m_MIDIMODE = true;
       myBrute->LoadMidi(cstring);
       Refresh();
    }

    if ((MidiFileName.Find(".abc")!=wxNOT_FOUND)||(MidiFileName.Find(".ABC")!=wxNOT_FOUND))
    {
       m_ABCMODE = true;
       m_MIDIMODE = false;
       std::cout << " Switching to pure playback " << std::endl;

       // this is a hack right now:
       std::ifstream myabcfile;
       myabcfile.open(MidiFileName);
       myBrute->m_ABCText.str(std::string());
       myBrute->m_ABCText << myabcfile.rdbuf();
       myabcfile.close();
       myBrute->DeleteMidi();
       myaudioplayerAL->Stop();
       myaudioplayerAL->SendABC(&myBrute->m_ABCText);
       myaudioplayerAL->GetABC()->UpdateToneCounts();
       myaudioplayerAL->Play();
       myaudioplayerAL->audio_playing = 1;
       BVabctracks.resize(myaudioplayerAL->GetNumberOfTracks());
       for (size_t i = 0; i < BVabctracks.size(); i++)
       {
           BVabctracks[i].miditrackinfo.resize(1);
           BVabctracks[i].miditrackinfo[0].miditrack = myaudioplayerAL->GetXNumber(i);
           BVabctracks[i].miditrackinfo[0].midiinstrument = 10;
           BVabctracks[i].id = myaudioplayerAL->GetID(i);
           BVabctracks[i].instrument = myaudioplayerAL->GetInstrument(i);
           BVabctracks[i].x = int(100+590*(0.5 - myaudioplayerAL->GetPanning(i)*0.01));
           BVabctracks[i].y = myaudioplayerAL->GetZPanning(i);

       }
       Refresh();
    }

}



#endif

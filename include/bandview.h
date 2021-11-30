#include "wx/wx.h"
#include "wx/sizer.h"
#include <algorithm>
#include "miditrackdialogue.h"
#include "bandviewmiditrack.h"


//#include "include/brute.h"




class BandViewABCTrack
{
public:
    int instrument;
    int x;
    int y;
   // std::vector<int> miditracks = {};
    std::vector<BandViewMidiTrack> miditrackinfo = {};
};

class BandView : public wxPanel
{

public:
    BandView(wxFrame* parent, Brute * myBrute);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);
    void DrawLotroInstruments(wxDC& dc);
    void DrawOneInstrument(wxDC& dc, int x, int y, wxString mytext);
    void DrawMidiTracks(wxDC& dc);
    void DrawOneMidiTrack(wxDC& dc, int x, int y, int i, size_t midiinstrumentnumber);
    void DrawABCTracks(wxDC& dc);

    void AppendMapping();   // this will write the mapping info into the brute instance
    void GetMapping();

    size_t LotroInstrumentPicked(int x, int y);
    size_t MidiTrackPicked(int x, int y);
    size_t ABCTrackPicked(int x, int y);
    size_t MidiTrackInABCTrackPicked(int x, int y);
    size_t WhichMidiTrackInABCTrackPicked(int x, int y);

    Brute * myBrute;  // our instance of Brute

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

    int RelX(int m);
    int RelY(int m);

    int click_relx;
    int click_rely;

    bool BetterUpdateYourABCfromBrute = false;

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
 /*
 EVT_RIGHT_DOWN(BandView::rightClick)
 EVT_LEAVE_WINDOW(BandView::mouseLeftWindow)
 EVT_KEY_DOWN(BandView::keyPressed)
 EVT_KEY_UP(BandView::keyReleased)
 EVT_MOUSEWHEEL(BandView::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BandView::paintEvent)

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

 void BandView::AppendMapping()
 {
     std::stringstream bvmappingtext;

     // sort by Y appearance
     std::vector< std::pair<int,int> > myneworder;

     for (size_t i = 0; i < BVabctracks.size(); i++)
        myneworder.push_back( std::make_pair( BVabctracks[i].y, i) );

     for (size_t i = 0; i < myneworder.size(); i++)
        std::cout << myneworder[i].first << "  " << myneworder[i].second << std::endl;

     std::sort( myneworder.rbegin(), myneworder.rend() );


     for (size_t i = 0; i < myneworder.size(); i++)
        std::cout << myneworder[i].first << "  " << myneworder[i].second << std::endl;

     for (size_t m = 0; m < BVabctracks.size(); m++)
     {
        size_t i = myneworder[m].second;
        bvmappingtext << "abctrack begin" << std::endl;
        bvmappingtext << "%voladjust    %uncomment to try automatic compensation for U16.1 volumes (experimental!)" << std::endl;
        bvmappingtext << "polyphony 6 top  % options: top removes tones from higher pitch first, bottom lower pitch first" << std::endl;
        bvmappingtext << "duration 2" << std::endl;
        bvmappingtext << "panning " << 128 - int(  (BVabctracks[i].x-100)/590.0 * 128  ) << std::endl;
        if (BVabctracks[i].instrument != 8)
        {
         bvmappingtext << "instrument " << lotroinstruments[BVabctracks[i].instrument] << std::endl;
        }
        else
        {
         bvmappingtext << "instrument drums 5" << std::endl;
        }
        for (size_t j = 0; j < BVabctracks[i].miditrackinfo.size(); j++)
        {
           bvmappingtext << "%" << std::endl;
           int midioriginal = BVabctracks[i].miditrackinfo[j].midiinstrument;
           bvmappingtext << "range " << BVabctracks[i].miditrackinfo[j].range_l << " " << BVabctracks[i].miditrackinfo[j].range_h << std::endl;
           if ((midioriginal >= 0)&&(midioriginal < 128))
            bvmappingtext << "% Miditrack original Instrument " << GMinstrument[ midioriginal ] << std::endl;
           bvmappingtext << "miditrack " << BVabctracks[i].miditrackinfo[j].miditrack << " pitch " << BVabctracks[i].miditrackinfo[j].pitch << " volume " << BVabctracks[i].miditrackinfo[j].volume << " delay 0 prio 1" << std::endl;
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

        BVabctracks.push_back(newabctrack);

        int nmiditracks = myBrute->m_Mapping.m_trackmap[i].size();
        for (int j = 0; j < nmiditracks; j++)
        {
            BandViewMidiTrack newmiditrack;
            newmiditrack.miditrack = myBrute->m_Mapping.m_trackmap[i][j];
            newmiditrack.midiinstrument = myBrute->GetMidiInstrument( newmiditrack.miditrack );
            newmiditrack.isdrum = myBrute->GetMidiIsDrum(newmiditrack.miditrack );

            newmiditrack.range_h = myBrute->m_Mapping.m_rangemaph[i][j];
            newmiditrack.range_l = myBrute->m_Mapping.m_rangemapl[i][j];
            newmiditrack.volume  = myBrute->m_Mapping.m_volumemap[i][j];
            newmiditrack.pitch   = myBrute->m_Mapping.m_pitchmap[i][j];

            BVabctracks[i].miditrackinfo.push_back(newmiditrack);
        }
    }
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
         if ( ( x-xt )*(x-xt)+(y-yt)*(y-yt) < 10*10 )
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
    if (mypossibleMidiInABCTrack != 1000)
    {
         // std::cout << "Someone Picked a MidiTrack in an ABC Track" << std::endl;
         size_t whichmidi = WhichMidiTrackInABCTrackPicked(mouseX, mouseY);
         if (whichmidi !=1000)
         {
             std::cout <<"Right Click on Miditrack " << whichmidi << " in ABC Track " << mypossibleMidiInABCTrack;
             MidiTrackDialogue * custom = new MidiTrackDialogue( &BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi] );
             custom->Show(true);
         }
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
         this->SetCursor(wxCursor(wxCURSOR_HAND));
         miditrackclicked = true;
         miditrackclickednumber = mypossiblemiditrack;
     }

     // check for ABCTrack picked
     size_t mypossibleABCtrack = ABCTrackPicked(mouseX, mouseY);
     if (mypossibleABCtrack !=1000)
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

     // check for Midi in ABC Track picked
     size_t mypossibleMidiInABCTrack = MidiTrackInABCTrackPicked(mouseX, mouseY);
     if (mypossibleMidiInABCTrack != 1000)
     {
         // std::cout << "Someone Picked a MidiTrack in an ABC Track" << std::endl;
         size_t whichmidi = WhichMidiTrackInABCTrackPicked(mouseX, mouseY);
         if (whichmidi !=1000)
         {
             std::cout <<"Someone Picked Miditrack " << whichmidi << " in ABC Track " << mypossibleMidiInABCTrack;

             this->SetCursor(wxCursor(wxCURSOR_HAND));
             MovingMidiTrack = BVabctracks[mypossibleMidiInABCTrack].miditrackinfo[whichmidi];
            // MovingMidiTrackNumber = BVabctracks[mypossibleMidiInABCTrack].miditracks[whichmidi];

            // BVabctracks[mypossibleMidiInABCTrack].miditracks.erase( BVabctracks[mypossibleMidiInABCTrack].miditracks.begin() + whichmidi );
             BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.erase( BVabctracks[mypossibleMidiInABCTrack].miditrackinfo.begin() + whichmidi );

             midiinabctrackclicked = true;

             this->Refresh();
         }
     }
     /*
    bool abctrackclicked = false;
    size_t abctrackclickednumber;
     */
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
         size_t mypossibleABCtrack = ABCTrackPicked(mouseX, mouseY);
         if (mypossibleABCtrack !=1000)
         {
             // ok we dropped the Miditrack on an ABC Track
         //    BVabctracks[mypossibleABCtrack].miditracks.push_back(miditrackclickednumber);
             BandViewMidiTrack newtrack;
             newtrack.range_l=0;
             newtrack.range_h=36;
             newtrack.volume=0;
             newtrack.miditrack = miditrackclickednumber;
             newtrack.midiinstrument = myBrute->GetMidiInstrument(miditrackclickednumber);
             newtrack.isdrum = myBrute->GetMidiIsDrum(miditrackclickednumber);
             BVabctracks[mypossibleABCtrack].miditrackinfo.push_back(newtrack);
             miditrackclicked = false;
             this->Refresh();
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
             MovingABCTrack.x = mouseX+click_relx;
             MovingABCTrack.y = mouseY+click_rely;
             click_relx = 0;
             click_rely = 0;
             BVabctracks.push_back(MovingABCTrack);
             abctrackclicked=false;
             this->Refresh();
         }
     }
     // someone is dropping a miditrack that was picked up from an ABC Track
     if (midiinabctrackclicked)
     {

         size_t mypossibleABCtrack = ABCTrackPicked(mouseX, mouseY);
         // dropping on an ABCtrack
         if (mypossibleABCtrack != 1000)
         {
        //     BVabctracks[mypossibleABCtrack].miditracks.push_back(MovingMidiTrackNumber);
             BVabctracks[mypossibleABCtrack].miditrackinfo.push_back(MovingMidiTrack);
             miditrackclicked = false;
             this->Refresh();
         }
     }

     // Mouse was released, so nothing is held anymore
     midiinabctrackclicked = false;
     abctrackclicked = false;
     lotroinstrumentclicked = false;
     miditrackclicked = false;
 }

BandView::BandView(wxFrame* parent, Brute * myBrutep) :
wxPanel(parent)
{
    parent->SetLabel (wxT("Band View"));
    parent->EnableCloseButton(false);
    myBrute = myBrutep;
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
         DrawOneMidiTrack(dc, x, y, i, midiinstrumentnumber);
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
   if (midiinstrumentnumber == 201) mycolor.Set("rgb(50,50,50)"); // dark grey for Drums


   dc.SetBrush(mycolor);


   dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 5-pixels-thick red outline
   dc.DrawCircle( wxPoint(x,y), 12); /* radius */ // );
   std::stringstream mytext;
   mytext << i;
   dc.DrawText(mytext.str(), x-4,y-6);
 }

 void BandView::DrawOneInstrument(wxDC& dc, int x, int y, wxString mytext)
 {
    dc.SetBrush(*wxWHITE_BRUSH); // blue filling
    dc.SetPen( wxPen( wxColor(255,175,175), 1 ) ); // 10-pixels-thick pink outline
    dc.DrawRectangle( x, y, 97, 18 );
    dc.DrawText(mytext, x+3, y+1);
 }


 void BandView::DrawLotroInstruments(wxDC& dc)
 {
    int x = 800;
    int x2 = x+100;

    DrawOneInstrument(dc, x , 50,  lotroinstruments_formal[0] );
    DrawOneInstrument(dc, x2, 50, lotroinstruments_formal[11]);
    DrawOneInstrument(dc, x, 70, lotroinstruments_formal[1]);
    DrawOneInstrument(dc, x2, 70, lotroinstruments_formal[12]);
    DrawOneInstrument(dc, x, 90, lotroinstruments_formal[2]);
    DrawOneInstrument(dc, x2, 90, lotroinstruments_formal[16]);
    DrawOneInstrument(dc, x, 110, lotroinstruments_formal[5]);
    DrawOneInstrument(dc, x2, 110, lotroinstruments_formal[7]);
    DrawOneInstrument(dc, x, 130, lotroinstruments_formal[4]);
    DrawOneInstrument(dc, x2, 130, lotroinstruments_formal[3]);
    DrawOneInstrument(dc, x, 150, lotroinstruments_formal[6]);
    DrawOneInstrument(dc, x2, 150, lotroinstruments_formal[19]);
    DrawOneInstrument(dc, x, 170, lotroinstruments_formal[20]);
    DrawOneInstrument(dc, x2, 170, lotroinstruments_formal[21]);
    DrawOneInstrument(dc, x, 190, lotroinstruments_formal[18]);
    DrawOneInstrument(dc, x2, 190, lotroinstruments_formal[13]);
    DrawOneInstrument(dc, x, 210, lotroinstruments_formal[14]);
    DrawOneInstrument(dc, x2, 210, lotroinstruments_formal[15]);
    DrawOneInstrument(dc, x, 230, lotroinstruments_formal[8]);
    DrawOneInstrument(dc, x2, 230, lotroinstruments_formal[9]);
    DrawOneInstrument(dc, x, 250, lotroinstruments_formal[10]);
    DrawOneInstrument(dc, x2, 250, lotroinstruments_formal[17]);
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
       DrawOneInstrument(dc, BVabctracks[i].x, BVabctracks[i].y, lotroinstruments_formal[ABCinstrument]);

       for (size_t m = 0; m < BVabctracks[i].miditrackinfo.size(); m++)
       {
           int midiinstrument = BVabctracks[i].miditrackinfo[m].midiinstrument;
           int miditrack = BVabctracks[i].miditrackinfo[m].miditrack;
           if (BVabctracks[i].miditrackinfo[m].isdrum) midiinstrument = 201;
           DrawOneMidiTrack(dc, BVabctracks[i].x+RelX(m), BVabctracks[i].y+RelY(m), miditrack, midiinstrument);
       }
   }
}

void BandView::render(wxDC&  dc)
{
    // draw some text
    dc.DrawText(wxT("MIDI Tracks"), 10, 30);

    // draw a line
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 100, 50, 100, 500 ); // draw line across the rectangle

    dc.DrawText(wxT("Instruments"), 810, 30);
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 790, 50, 790, 500 ); // draw line across the rectangle

    dc.DrawLine( 100,500, 790, 500 );
    dc.DrawLine( 100, 50, 790, 50);

    dc.DrawText(wxT("Audience"), 445, 550);

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

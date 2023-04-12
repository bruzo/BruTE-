#ifndef MIDITRACKVIEW_H_INCLUDED
#define MIDITRACKVIEW_H_INCLUDED

#include "brute.h"
#include <wx/wx.h>
#include <string>


class PictureFrame : public wxFrame
{
public:
    PictureFrame(wxBitmap * mybitmap,int number, wxString name) : wxFrame(NULL, wxID_ANY, name)
    {
        m_Bitmap = mybitmap;
        mynumber = number;
        this->SetSize(818, 168);
    }


private:
	wxBitmap * m_Bitmap;
	int mynumber;

	void OnPaint(wxPaintEvent&);	// Paint-Event-Handler

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(PictureFrame, wxFrame)
	EVT_PAINT(PictureFrame::OnPaint)
END_EVENT_TABLE()

void PictureFrame::OnPaint(wxPaintEvent&)
{
	wxPaintDC PaintDC(this);	// needs to be called
	if (m_Bitmap->IsOk())
		PaintDC.DrawBitmap(m_Bitmap[0], 0, 0);	// show bitmap if successfull
}



class MidiTrackView
{
public:
   MidiTrackView(Brute * myBrute, int miditrack);

   Brute * myBrute;
   int myMidiTrack;
};

MidiTrackView::MidiTrackView(Brute * myBrutep, int miditrack)
{
    myBrute = myBrutep;
    myMidiTrack = miditrack;

    wxString name = "Miditrack " + std::to_string(miditrack);

    int octavepitch = myBrutep->GetOctavePitch(miditrack)*12;

    std::cout << "Miditrack " << miditrack << "  Octavepitch " << octavepitch << std::endl;

    wxBitmap * mybitmap = new wxBitmap(800,128,-1);

    wxMemoryDC dc;
    dc.SelectObject(mybitmap[0]);

    dc.SetPen( wxPen( wxColor(0,0,0),1));
    for (int i = 0; i < 128; i++)
    {
       if (!myBrutep->GetMidiIsDrum(miditrack))
       {
          if ( 127-(i+octavepitch-60 ) > 127-36 ) dc.SetPen( wxPen( wxColor(90,0,0), 1 ) );
          if ( 127-(i+octavepitch-60 ) < 127-72 ) dc.SetPen( wxPen( wxColor(90,0,0), 1 ) );
       }
       dc.DrawLine(0, i, 799, i);
       dc.SetPen( wxPen( wxColor(0,0,0),1));
    }
    double timerange = myBrute->m_globalmaxtick;

    dc.SetPen( wxPen( wxColor(255,255,255), 1 ) );

    double timetopixel = 799.0/timerange;

    for (int i = 0; i < myBrute->GetNumberOfTones(miditrack); i++)
    {
        int tonestart = int(myBrute->GetToneStart(miditrack,i) * timetopixel);
        int toneend   = int(myBrute->GetToneEnd(miditrack, i) * timetopixel);
        int pitch     = myBrute->GetTonePitch(miditrack, i);

        if ( toneend == tonestart ) toneend = tonestart+1;
        if (pitch > 127) pitch = 127;
        if (pitch < 0) pitch = 0;

        if (tonestart < 0) tonestart = 0;
        if (tonestart > 799) tonestart = 799;
        if (toneend < 0) toneend = 0;
        if (toneend > 799) toneend = 799;
        dc.DrawLine(tonestart, 127-pitch, toneend, 127-pitch);
        //dc.SetPen( wxPen( wxColor(255,255,255), 1 ) );
    }

    PictureFrame * myframe = new PictureFrame(mybitmap, miditrack, name);

    myframe->Show();
}

#endif // MIDITRACKVIEW_H_INCLUDED

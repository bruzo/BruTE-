#ifndef OVERLOADPICTURE_H_INCLUDED
#define OVERLOADPICTURE_H_INCLUDED

#include "midipreview.h"

class OverLoadPicture
{
public:

   OverLoadPicture(MidiPreview * myMidiPreviewp);

   MidiPreview * myMidiPreview;

   void UpdateView();

//   wxBitmap m_BitMap("well", 690,100, wxBITMAP_SCREEN_DEPTH);

};

OverLoadPicture::OverLoadPicture(MidiPreview * myMidiPreviewp)
{
    myMidiPreview = myMidiPreviewp;
}

void OverLoadPicture::UpdateView()
{
    wxMemoryDC dc;
//    dc.SelectObject(m_BitMap);

  //  uint64_t chunksperpixel = myMidiPreview->m_ToneCounts[0].size() / 690;
  //  std::vector< uint32_t > counters;
  //  counters.resize(690);
  //  std::fill( counters.begin(), counters.end(), 0 );

    /*
    for ( uint64_t i = 0; i < myMidiPreview->m_ToneCounts[0].size(); i++ )
    {
        // count full number of tones per slot and pic largest
        uint32_t val = 0;
        for (size_t j = 0; j < myMidiPreview->m_ToneCounts.size(); j++)
        {
            val = val + myMidiPreview->m_ToneCounts[j][i];
        }
        if ( val > counters[i / chunksperpixel] ) counters[i/chunksperpixel] = val;
    }*/

    /*
    for (size_t i = 0; i < counters.size(); i++)
    {
       dc.SetPen(wxPen( wxColor(0 ,0 ,0) ));
       if ( counters[i] < 100 ) dc.SetPen( wxPen( wxColor(255 ,0 ,0) ) );
       if ( counters[i] < 64 ) dc.SetPen( wxPen( wxColor(0 ,0 ,255) ) );
       if ( counters[i] < 32 ) dc.SetPen( wxPen( wxColor(0 ,255 ,0) ) );

       int length = counters[i];
       if (length >= 100) length = 99;

       dc.DrawLine( i, 99, i, 99-length  );
    }*/
}



#endif // OVERLOADPICTURE_H_INCLUDED

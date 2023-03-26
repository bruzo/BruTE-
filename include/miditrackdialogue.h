#ifndef MIDITRACKDIALOG_H
#define MIDITRACKDIALOG_H

#include <wx/wx.h>
#include "bandviewmiditrack.h"
#include "bandviewabctrack.h"
#include "brutedefinitions.h"


class SampleInfo : public wxFrame
{
public:
    SampleInfo(std::string Input) : wxFrame(NULL, wxID_ANY, "Miditrack Info")
    {
        // create a text control with the multi-line style
        m_textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);


        m_textCtrl->SetValue(Input);

        // add the text control to a sizer
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(m_textCtrl, 1, wxEXPAND | wxALL, 10);

        // set the sizer for the frame
        SetSizer(sizer);
    }

private:
    wxTextCtrl* m_textCtrl;
};


class MidiTrackDialogue : public wxDialog
{
public:
  MidiTrackDialogue(BandViewMidiTrack * myMidiTrack, BandViewABCTrack * myABCTrack);

  wxStaticBox * stvolume;
  wxTextCtrl *tcvolume;
  wxStaticBox *stpitch;
  wxTextCtrl *tcpitch;
  wxStaticBox *strange;
  wxTextCtrl *tcrangel;
  wxTextCtrl *tcrangeh;
  wxButton *okButton;
  wxStaticBox * alternatebox;
  wxTextCtrl * alternatepart;
  wxTextCtrl * alternateparts;

  wxStaticBox * splitbox;
  wxTextCtrl * splitnumber;

  wxStaticBox * stdelay;
  wxTextCtrl *tcdelay;

  wxStaticBox * stdmap;
  wxTextCtrl *tcdmap;

  wxStaticBox * pitchbend;
  wxTextCtrl * pitchbendqduration;
  wxStaticBox * pitchbendmethod;
  wxTextCtrl * pitchbendmethodvalue;
  wxComboBox * pitchbendcombo;

  wxStaticBox * triller;
  wxTextCtrl * trillerfreq;

  wxStaticBox * dusplit;
  wxTextCtrl * durationsplitl;
  wxTextCtrl * durationsplitp;

  wxStaticBox * directmapping;
  wxTextCtrl * directm;
  wxTextCtrl * drumm;
  wxCheckBox * directbox;


  wxButton* sampleinfobutton;

  BandViewMidiTrack * thisMiditrack;

  void OnButtonOK(wxCommandEvent& event);

  void ShowInfo(wxCommandEvent& event);
/*
  enum MenuControls {
         idButtonOK = 1001,
  };
*/
private:
  DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MidiTrackDialogue, wxDialog)
EVT_BUTTON(wxID_OK, MidiTrackDialogue::OnButtonOK)
END_EVENT_TABLE()

void MidiTrackDialogue::ShowInfo(wxCommandEvent& event)
{
        std::string Message = "";

        for (size_t i = 0; i < thisMiditrack->samples->size(); i++  )
            if (thisMiditrack->samples->at(i)) Message = Message + std::to_string(i) + "   " + GMdrumnames[i] + "\t";

        Message = Message + "\n\n";
      //  for (size_t i = 0; i < LotroDrumSampleNames.size(); i++)
      //      Message = Message + LotroDrumSampleNames[i] + "  " + "\t";

        SampleInfo* frame = new SampleInfo(Message);
        frame->Show();
}

MidiTrackDialogue::MidiTrackDialogue(BandViewMidiTrack * myMidiTrack, BandViewABCTrack * myABCTrack)
       : wxDialog(NULL, -1, wxT("Midi Track Settings"), wxDefaultPosition, wxSize(350, 400))
{
  thisMiditrack = myMidiTrack;
  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  int x, y, sx, sy;

  x = 5; y = 20; sx = 70; sy = 45;
  stvolume = new wxStaticBox(panel, -1, wxT("Volume"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcvolume = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->volume), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));

  x = 90; y = 20; sx = 70; sy = 45;
  stpitch = new wxStaticBox(panel, -1, wxT("Pitch"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcpitch = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->pitch), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));

  x = 5; y = 70; sx = 155; sy = 45;
  strange = new wxStaticBox(panel, -1, wxT("Pitch Range ( low, high )"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcrangel = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->range_l), wxPoint(x+10, y+20), wxSize(45,sy-25));
  tcrangeh = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->range_h), wxPoint(x+95, y+20), wxSize(45,sy-25));

  x = 5; y = 120; sx = 155; sy = 45;
  alternatebox = new wxStaticBox(panel, -1, wxT("Alternate (part, n_parts)"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  alternatepart = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->alternatemypart) , wxPoint(x+10, y+20), wxSize(45,20));
  alternateparts = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->alternateparts), wxPoint(x+95, y+20), wxSize(45,20));

  x = 170; y = 20; sx = 70; sy = 45;
  splitbox = new wxStaticBox(panel, -1, wxT("Split"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  splitnumber = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->split ) , wxPoint(x+10, y+20), wxSize(45,20));

  x = 170; y = 70; sx = 70; sy = 45;
  stdelay = new wxStaticBox(panel, -1, wxT("Delay"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  wxString delvalue; delvalue.Printf("%.2f", myMidiTrack->delay);
  tcdelay = new wxTextCtrl(panel, -1, delvalue , wxPoint(x+10, y+20), wxSize(45,20));

  if ( myABCTrack->instrument == 8 ) // this midi is associated to a drum, so we have to allow picking a drum map
  {
      x = 170; y = 120; sx = 70; sy = 45;
      stdmap = new wxStaticBox(panel, -1, wxT("Drum Map"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
      tcdmap = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->drummapping ) , wxPoint(x+10, y+20), wxSize(45,20));
  }

  // Pitchbends only make sense for non-drum tracks so we use the same space
  if (( myMidiTrack->haspitchbends )&&(myABCTrack->instrument != 8))
  {
	  x = 5; y = 170; sx = 155; sy = 45;
	  pitchbend = new wxStaticBox(panel, -1, wxT("Pitchbends (min duration)"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);

      std::vector<wxString> items =  {"No Bending", "Round to 8", "Round to 12", "Truncate to 8", "Truncate to 12"};
	  pitchbendcombo = new wxComboBox(panel, -1, "", wxPoint(x+10,y+18), wxSize(95,20), items.size(),  items.data(), wxCB_DROPDOWN | wxCB_READONLY);

      x = x+100; y = 170; sx = 120; sy = 45;
	  pitchbendqduration = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->pitchbendqduration) , wxPoint(x+10, y+20), wxSize(35,20));

	 // pitchbendmethodvalue = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->pitchbendmethod) , wxPoint(x+10, y+20), wxSize(45,20));

        // Set the first item as the default selection
      pitchbendcombo->SetSelection(myMidiTrack->pitchbendmethod);

  }

  x = 5; y = 220; sx = 70; sy = 45;
  triller = new wxStaticBox(panel, -1, wxT("Triller"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  wxString tvalue;
  tvalue.Printf("%.2f",myMidiTrack->triller);
  trillerfreq = new wxTextCtrl(panel, -1, tvalue , wxPoint(x+10, y+20), wxSize(45,20));

  x = 90; y = 220; sx = 155; sy = 45;
  dusplit = new wxStaticBox(panel, -1, wxT("Duration Split time/part"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  durationsplitl = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->durationsplitlength), wxPoint(x+10, y+20), wxSize(45,sy-25));
  durationsplitp = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->durationsplitpart), wxPoint(x+95, y+20), wxSize(45,sy-25));

  x = 5; y = 270; sx = 200; sy = 45;
  directmapping = new wxStaticBox(panel, -1, wxT("Direct Mapping"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);

  drumm = new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->drumtone), wxPoint(x+10, y+20), wxSize(45,sy-25));
  directm =new wxTextCtrl(panel, -1, std::to_string(myMidiTrack->directmapping), wxPoint(x+85, y+20), wxSize(45,sy-25));
  sampleinfobutton = new wxButton(panel, -1, wxT("Info"), wxPoint(x+150, y+20), wxSize(40,sy-25));
  sampleinfobutton->Bind(wxEVT_BUTTON, &ShowInfo, this);

  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);

  Centre();
  ShowModal();

  thisMiditrack->volume =  wxAtoi(tcvolume->GetValue());
  thisMiditrack->pitch = wxAtoi(tcpitch->GetValue());
  thisMiditrack->range_l = wxAtoi(tcrangel->GetValue());
  thisMiditrack->range_h = wxAtoi(tcrangeh->GetValue());
  thisMiditrack->alternatemypart = wxAtoi(alternatepart->GetValue());
  thisMiditrack->alternateparts = wxAtoi(alternateparts->GetValue());
  thisMiditrack->split = wxAtoi(splitnumber->GetValue());
  thisMiditrack->delay = wxAtof(tcdelay->GetValue());

  if ( myABCTrack->instrument == 8 ) // this midi is associated to a drum, so we have to allow picking a drum map
  {
     thisMiditrack->drummapping = wxAtoi(tcdmap->GetValue());
  }
  if (( myMidiTrack->haspitchbends )&&(myABCTrack->instrument != 8))
  {
      thisMiditrack->pitchbendqduration = wxAtoi(pitchbendqduration->GetValue());
      thisMiditrack->pitchbendmethod = pitchbendcombo->GetSelection();
  }
  thisMiditrack->triller = wxAtof(trillerfreq->GetValue());
  thisMiditrack->durationsplitlength = wxAtoi(durationsplitl->GetValue());
  thisMiditrack->durationsplitpart = wxAtoi(durationsplitp->GetValue());

  thisMiditrack->drumtone = wxAtoi(drumm->GetValue());
  thisMiditrack->directmapping = wxAtoi(directm->GetValue());

  Destroy();
}

void MidiTrackDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif

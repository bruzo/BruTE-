#ifndef MIDITRACKDIALOG_H
#define MIDITRACKDIALOG_H

#include <wx/wx.h>
#include "bandviewmiditrack.h"
#include "brutedefinitions.h"

class MidiTrackDialogue : public wxDialog
{
public:
  MidiTrackDialogue(BandViewMidiTrack * myMidiTrack);

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

  BandViewMidiTrack * thisMiditrack;

  void OnButtonOK(wxCommandEvent& event);

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

MidiTrackDialogue::MidiTrackDialogue(BandViewMidiTrack * myMidiTrack)
       : wxDialog(NULL, -1, wxT("Midi Track Settings"), wxDefaultPosition, wxSize(350, 270))
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



  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);

  Centre();
  ShowModal();
  Destroy();
}

void MidiTrackDialogue::OnButtonOK(wxCommandEvent& event)
{

    thisMiditrack->volume =  wxAtoi(tcvolume->GetValue());
    thisMiditrack->pitch = wxAtoi(tcpitch->GetValue());
    thisMiditrack->range_l = wxAtoi(tcrangel->GetValue());
    thisMiditrack->range_h = wxAtoi(tcrangeh->GetValue());
    thisMiditrack->alternatemypart = wxAtoi(alternatepart->GetValue());
    thisMiditrack->alternateparts = wxAtoi(alternateparts->GetValue());
    thisMiditrack->split = wxAtoi(splitnumber->GetValue());

    this->Destroy();
}

#endif

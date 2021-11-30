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
       : wxDialog(NULL, -1, wxT("Midi Track Info"), wxDefaultPosition, wxSize(250, 230))
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

    this->Destroy();
}

#endif

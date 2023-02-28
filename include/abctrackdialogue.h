#ifndef ABCTRACKDIALOGUE_H_INCLUDED
#define ABCTRACKDIALOGUE_H_INCLUDED

#include <wx/wx.h>
#include "bandviewabctrack.h"
#include "brutedefinitions.h"

class ABCTrackDialogue : public wxDialog
{
public:
    ABCTrackDialogue(BandViewABCTrack * myABCTrack);

    void OnButtonOK(wxCommandEvent& event);

    wxButton *okButton;

    wxStaticBox * stpoly;
    wxTextCtrl *tcpoly;
    wxStaticBox * stpolydir;
    wxChoice * tcpolydir;

    wxStaticBox * stduration;
    wxTextCtrl *tcdmin;
    wxTextCtrl *tcdmax;

    wxStaticBox * stmuted;
    wxCheckBox * tcmuted;


private:
    BandViewABCTrack * thisABCTrack;

  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(ABCTrackDialogue, wxDialog)
EVT_BUTTON(wxID_OK, ABCTrackDialogue::OnButtonOK)
END_EVENT_TABLE()

ABCTrackDialogue::ABCTrackDialogue(BandViewABCTrack * myABCTrack)
       : wxDialog(NULL, -1, wxT("ABC Track Settings"), wxDefaultPosition, wxSize(350, 270))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  thisABCTrack = myABCTrack;

  int x, y, sx, sy;

  x = 5; y = 20; sx = 70; sy = 45;
  stpoly = new wxStaticBox(panel, -1, wxT("Polyphony"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcpoly = new wxTextCtrl(panel, -1, std::to_string(myABCTrack->polyphony), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));

  x = 90; y = 20; sx = 100; sy = 45;
  stpolydir = new wxStaticBox(panel, -1, wxT("Remove from"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);

  wxArrayString str; str.Add("Bottom"); str.Add("Top");
  wxChoice * tcpolydir = new wxChoice(panel,-1, wxPoint(x+10, y+20), wxSize(sx-25,sy-25),str);
  tcpolydir->SetSelection( thisABCTrack->polydirection );

  x = 200; y = 20; sx = 70; sy = 40;
  stmuted = new wxStaticBox(panel, -1, wxT("Mute"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcmuted = new wxCheckBox(panel, -1, wxT(""), wxPoint(x+15, y+15), wxSize(20, 20), 0, wxDefaultValidator  );
  tcmuted->SetValue( myABCTrack->muted );

  x = 5; y = 70; sx = 185; sy = 45;
  stduration = new wxStaticBox(panel, -1, wxT("Duration Limits ( min, max )"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcdmin = new wxTextCtrl(panel, -1, std::to_string(myABCTrack->duration_min), wxPoint(x+10, y+20), wxSize(45,sy-25));
  tcdmax = new wxTextCtrl(panel, -1, std::to_string(myABCTrack->duration_max), wxPoint(x+95, y+20), wxSize(60,sy-25));

  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);



  Centre();
  ShowModal();

  thisABCTrack->polyphony =  wxAtoi(tcpoly->GetValue());
  thisABCTrack->polydirection = tcpolydir->GetSelection();
  thisABCTrack->duration_min = wxAtoi(tcdmin->GetValue());
  thisABCTrack->duration_max = wxAtoi(tcdmax->GetValue());
  thisABCTrack->muted = tcmuted->GetValue();

  Destroy();
}

void ABCTrackDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif // ABCTRACKDIALOGUE_H_INCLUDED

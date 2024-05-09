#ifndef SETTINGSDIALOGUE_H_INCLUDED
#define SETTINGSDIALOGUE_H_INCLUDED

#include "brutedefinitions.h"
#include "abcheader.h"


class SettingsDialogue : public wxDialog
{
public:
    SettingsDialogue(size_t * nthreads, int * seed);

    void OnButtonOK(wxCommandEvent& event);

    wxButton *okButton;

    wxStaticBox * threadsbox;
    wxTextCtrl * threadsnumber;
    
    wxStaticBox * seedbox;
    wxTextCtrl * seedv;

 //   wxTextCtrl *tcvol;
 //   wxStaticBox * stpan;
 //   wxTextCtrl * tcpan;


private:

  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(SettingsDialogue, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialogue::OnButtonOK)
END_EVENT_TABLE()


SettingsDialogue::SettingsDialogue( size_t * nthreads, int * seed )
       : wxDialog(NULL, -1, wxT("Settings"), wxDefaultPosition, wxSize(350, 270))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  int x, y, sx, sy;

  x = 5; y = 20; sx = 100; sy = 45;
  threadsbox = new wxStaticBox(panel, -1, wxT("Threads"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  threadsnumber = new wxTextCtrl(panel, -1, std::to_string( nthreads[0] ), wxPoint(x+19, y+20), wxSize(sx-25, sy-25) );

  x = 120; y = 20; sx = 100; sy = 45;
  seedbox = new wxStaticBox(panel, -1, wxT("RNG Seed"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  seedv = new wxTextCtrl(panel, -1, std::to_string( seed[0] ), wxPoint(x+19, y+20), wxSize(sx-25, sy-25) );


  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);


  Centre();
  ShowModal();

  nthreads[0] = wxAtoi(threadsnumber->GetValue());
  seed[0] = wxAtoi(seedv->GetValue());

  Destroy();
}


void SettingsDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif // SettingsDialogue_H_INCLUDED

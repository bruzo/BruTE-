#ifndef ABCSETTINGSDIALOGUE_H_INCLUDED
#define ABCSETTINGSDIALOGUE_H_INCLUDED

#include "brutedefinitions.h"
#include "abcheader.h"


class ABCSettingsDialogue : public wxDialog
{
public:
    ABCSettingsDialogue(int * naming, ABCHeader * abcheader);

    void OnButtonOK(wxCommandEvent& event);

    wxButton *okButton;

    wxStaticBox * namingbox;
    wxComboBox * namingscheme;

    wxStaticBox * transcriberbox;
    wxTextCtrl * transcribername;

    wxStaticBox * songnamebox;
    wxTextCtrl * songname;

    wxStaticBox * globalpitchbox;
    wxTextCtrl * globalpitchtext;

 //   wxTextCtrl *tcvol;
 //   wxStaticBox * stpan;
 //   wxTextCtrl * tcpan;


private:

  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(ABCSettingsDialogue, wxDialog)
EVT_BUTTON(wxID_OK, ABCSettingsDialogue::OnButtonOK)
END_EVENT_TABLE()


ABCSettingsDialogue::ABCSettingsDialogue( int * naming, ABCHeader * abcheader)
       : wxDialog(NULL, -1, wxT("ABC Settings"), wxDefaultPosition, wxSize(350, 270))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  int x, y, sx, sy;

  x = 5; y = 20; sx = 107; sy = 45;
  namingbox = new wxStaticBox(panel, -1, wxT("ABC Style"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);

  std::vector<wxString> items =  {};
  for (size_t i = 0; i < ABCStyleNames.size(); i++) items.push_back( ABCStyleNames[i] )  ;
  namingscheme =   new wxComboBox(panel, -1, "", wxPoint(x+8,y+17), wxSize(95,20), items.size(),  items.data(), wxCB_DROPDOWN | wxCB_READONLY);
  namingscheme->SetSelection( *naming );

  x = 120; y = 20; sx = 120; sy = 45;
  transcriberbox = new wxStaticBox(panel, -1, wxT("Transcriber"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  transcribername = new wxTextCtrl(panel, -1, (abcheader[0].Transcriber), wxPoint(x+19, y+20), wxSize(sx-25, sy-25) );

  x = 5; y = 70; sx = 235; sy = 45;
  songnamebox = new wxStaticBox(panel, -1, wxT("Songname"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  songname = new wxTextCtrl(panel, -1, (abcheader[0].SongName ), wxPoint(x+19, y+20), wxSize(sx-25, sy-25) );

  x = 5; y = 120; sx = 60; sy = 45;
  globalpitchbox = new wxStaticBox(panel, -1, wxT("Pitch"), wxPoint(x,y), wxSize(sx,sy), wxTE_READONLY);
  globalpitchtext = new wxTextCtrl(panel, -1, std::to_string(abcheader[0].globalpitch), wxPoint(x+19, y+20), wxSize(sx-25, sy-25));

  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);



  Centre();
  ShowModal();

 // volume[0] =  wxAtoi(tcvol->GetValue());
 // panning[0] = wxAtoi(tcpan->GetValue());
  *naming = namingscheme->GetSelection();
  abcheader[0].Transcriber = transcribername->GetValue();
  abcheader[0].SongName = songname->GetValue();
  abcheader[0].globalpitch = wxAtoi(globalpitchtext->GetValue());

  Destroy();
}


void ABCSettingsDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif // ABCSettingsDialogue_H_INCLUDED

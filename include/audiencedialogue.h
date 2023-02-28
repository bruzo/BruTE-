#ifndef AUDIENCEDIALOGUE_H_INCLUDED
#define AUDIENCEDIALOGUE_H_INCLUDED




class AudienceDialogue : public wxDialog
{
public:
    AudienceDialogue(int * volume, int * panning);

    void OnButtonOK(wxCommandEvent& event);

    wxButton *okButton;

    wxStaticBox * stvol;
    wxTextCtrl *tcvol;
    wxStaticBox * stpan;
    wxTextCtrl * tcpan;


private:

  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(AudienceDialogue, wxDialog)
EVT_BUTTON(wxID_OK, AudienceDialogue::OnButtonOK)
END_EVENT_TABLE()


AudienceDialogue::AudienceDialogue(int * volume, int * panning)
       : wxDialog(NULL, -1, wxT("Audience Settings"), wxDefaultPosition, wxSize(350, 270))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  int x, y, sx, sy;

  x = 5; y = 20; sx = 70; sy = 45;
  stvol = new wxStaticBox(panel, -1, wxT("Volume"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcvol = new wxTextCtrl(panel, -1, std::to_string(volume[0]), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));

  x = 5; y = 70; sx = 70; sy = 45;
  stpan = new wxStaticBox(panel, -1, wxT("Panning"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcpan = new wxTextCtrl(panel, -1, std::to_string(panning[0]), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));

  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);



  Centre();
  ShowModal();

  volume[0] =  wxAtoi(tcvol->GetValue());
  panning[0] = wxAtoi(tcpan->GetValue());

  Destroy();
}


void AudienceDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif // AUDIENCEDIALOGUE_H_INCLUDED

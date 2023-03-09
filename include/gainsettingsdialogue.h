#ifndef GAINSETTINGSDIALOG_H
#define GAINSETTINGSDIALOG_H

#include <wx/wx.h>
#include "brutedefinitions.h"

class GainSettingsDialogue : public wxDialog
{
public:
  GainSettingsDialogue(int instrument, float * gain, float * fadeout);

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


  void OnButtonOK(wxCommandEvent& event);

/*
  enum MenuControls {
         idButtonOK = 1001,
  };
*/
private:
  DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(GainSettingsDialogue, wxDialog)
EVT_BUTTON(wxID_OK, GainSettingsDialogue::OnButtonOK)
END_EVENT_TABLE()

GainSettingsDialogue::GainSettingsDialogue(int instrument, float * gain, float * fadeout)
       : wxDialog(NULL, -1,  wxString( lotroinstruments_formal[instrument]) , wxDefaultPosition, wxSize(350, 270))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);


  int x, y, sx, sy;

  x = 5; y = 20; sx = 100; sy = 45;
  stvolume = new wxStaticBox(panel, -1, wxT("Gain"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcvolume = new wxTextCtrl(panel, -1, std::to_string(gain[0]), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));

  x = 110; y = 20; sx = 100; sy = 45;
  stpitch = new wxStaticBox(panel, -1, wxT("Fade Out"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  tcpitch = new wxTextCtrl(panel, -1, std::to_string(fadeout[0]), wxPoint(x+10, y+20), wxSize(sx-25,sy-25));


  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));
  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);

  Centre();
  ShowModal();

  gain[0] = static_cast<float>(wxAtof(tcvolume->GetValue()));
  fadeout[0] = static_cast<float>(wxAtof(tcpitch->GetValue()));

  Destroy();
}

void GainSettingsDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif

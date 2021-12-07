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

private:
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

  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);

  Centre();
  ShowModal();
  Destroy();
}

void ABCTrackDialogue::OnButtonOK(wxCommandEvent& event)
{
    this->Destroy();
}

#endif // ABCTRACKDIALOGUE_H_INCLUDED

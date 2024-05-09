#ifndef HUMANIZATIONLIGHTDIALOGUE_H_INCLUDED
#define HUMANIZATIONLIGHTDIALOGUE_H_INCLUDED

#include "brutedefinitions.h"
#include "abcheader.h"
#include "bandviewabctrack.h"


class HumanizationLightDialogue : public wxDialog
{
public:
    HumanizationLightDialogue(std::vector<BandViewABCTrack> &BVTracks);

    void OnButtonOK(wxCommandEvent& event);

    wxButton *okButton;

    wxStaticBox * ampsbox;
    wxStaticBox * couplingsbox;
    wxTextCtrl * amps;
    wxTextCtrl * couplings;


private:

  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(HumanizationLightDialogue, wxDialog)
EVT_BUTTON(wxID_OK, HumanizationLightDialogue::OnButtonOK)
END_EVENT_TABLE()


HumanizationLightDialogue::HumanizationLightDialogue( std::vector<BandViewABCTrack> &BVTracks )
       : wxDialog(NULL, -1, wxT("Free Folkization"), wxDefaultPosition, wxSize( 150, 150))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);


  int x, y, sx, sy;

  // first make sure all the data structures have the correct size
  size_t nabctracks = BVTracks.size();

  for (size_t i = 0; i < nabctracks; i++)
  {
      BVTracks[i].hcoupling.resize(nabctracks);
  }

  x = 5; y = 20; sx = 50; sy = 50;
  ampsbox = new wxStaticBox(panel, -1, wxT("Quality"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  amps = new wxTextCtrl(panel, -1, std::to_string( 0 ), wxPoint(x+5, y+20), wxSize(35, sy-25) );

  x = 60; y = 20; sx = 50; sy = 50;
  couplingsbox = new wxStaticBox(panel, -1, wxT("Coupling"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  couplings = new wxTextCtrl(panel, -1, std::to_string( 0 ), wxPoint(x+5, y+20), wxSize(35, sy-25) );
  
  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));
  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);


  Centre();
  ShowModal();

  float myamplitude = wxAtof( amps->GetValue());
  float mycoupling = wxAtof( couplings->GetValue());

  for (size_t i = 0; i < nabctracks; i++)
  {
      BVTracks[i].hshift = 0.;
      BVTracks[i].hamp = myamplitude;

      for (size_t j=0; j < nabctracks; j++)
      {
          BVTracks[i].hcoupling[j] = mycoupling;
      }
      
      BVTracks[i].hcoupling[i] = 1.0;
  }

  Destroy();
}


void HumanizationLightDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif // HumanizationLightDialogue

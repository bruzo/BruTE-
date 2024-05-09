#ifndef HUMANIZATIONDIALOGUE_H_INCLUDED
#define HUMANIZATIONDIALOGUE_H_INCLUDED

#include "brutedefinitions.h"
#include "abcheader.h"
#include "bandviewabctrack.h"


class HumanizationDialogue : public wxDialog
{
public:
    HumanizationDialogue(std::vector<BandViewABCTrack> &BVTracks);

    void OnButtonOK(wxCommandEvent& event);

    wxButton *okButton;

    std::vector< std::vector< wxTextCtrl * >> couplingmatrix;
    std::vector< wxTextCtrl * > hamps;
    std::vector< wxTextCtrl * > shifts;

    wxStaticBox * couplingsbox;
    wxStaticBox * ampsbox;
    std::vector< wxStaticBox * > ampsboxes;
    std::vector< wxStaticBox * > gboxes;
    wxStaticBox * shiftsbox;
    std::vector< wxStaticBox * > shiftboxes;


private:

  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(HumanizationDialogue, wxDialog)
EVT_BUTTON(wxID_OK, HumanizationDialogue::OnButtonOK)
END_EVENT_TABLE()


HumanizationDialogue::HumanizationDialogue( std::vector<BandViewABCTrack> &BVTracks )
       : wxDialog(NULL, -1, wxT("Free Folkization"), wxDefaultPosition, wxSize(BVTracks.size()*50+150, BVTracks.size()*50+300))
{

  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);


  int x, y, sx, sy;
/*  x = 5; y = 20; sx = 100; sy = 45;
  threadsbox = new wxStaticBox(panel, -1, wxT("Threads"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  threadsnumber = new wxTextCtrl(panel, -1, std::to_string( nthreads[0] ), wxPoint(x+19, y+20), wxSize(sx-25, sy-25) );
  */

  // first make sure all the data structures have the correct size
  size_t nabctracks = BVTracks.size();

  couplingmatrix.resize(nabctracks);
  ampsboxes.resize(nabctracks);
  gboxes.resize(nabctracks);
  hamps.resize(nabctracks);
  shiftboxes.resize(nabctracks);
  shifts.resize(nabctracks);


  for (size_t i = 0; i < nabctracks; i++)
  {
      BVTracks[i].hcoupling.resize(nabctracks);
      couplingmatrix[i].resize(nabctracks);

  }

  x = 5; y = 20; sx = 50*nabctracks+5; sy = 65;
  ampsbox = new wxStaticBox(panel, -1, wxT("Quality"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  for (size_t i = 0; i < nabctracks; i++)
  {
      x = 5 + 5 + i * 50; y = 35; sx = 45; sy = 45;
      ampsboxes[i] = new wxStaticBox(panel, -1, std::to_string( BVTracks[i].id ), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
      hamps[i] = new wxTextCtrl(panel, -1, std::to_string( int(BVTracks[i].hamp) ), wxPoint(x+5, y+20), wxSize(35, sy-25) );
  }

  x = 5; y = 85; sx = 50*nabctracks+5; sy = 65;
  shiftsbox = new wxStaticBox(panel, -1, wxT("Rush/Lag"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  for (size_t i = 0; i < nabctracks; i++)
  {
      x = 5 + 5 + i * 50; y = 35+65; sx = 45; sy = 45;
      shiftboxes[i] = new wxStaticBox(panel, -1, std::to_string( BVTracks[i].id ), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
      shifts[i] = new wxTextCtrl(panel, -1, std::to_string( int(BVTracks[i].hshift) ), wxPoint(x+5, y+20), wxSize(35, sy-25) );
  }

  x = 5; y = 85+65; sx = 50*nabctracks+5; sy = 50*nabctracks + 5;
  shiftsbox = new wxStaticBox(panel, -1, wxT("Coupling Matrix"), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
  for (size_t i = 0; i < nabctracks; i++)
  {
    for (size_t j = 0; j < nabctracks; j++)
    {
      x = 5 + 5 + i * 50; y = 85+65 + j*50; sx = 45; sy = 45;
      couplingmatrix[i][j] = new wxTextCtrl(panel, -1, std::to_string( BVTracks[i].hcoupling[j] ), wxPoint(x+3, y+20), wxSize(39, sy-25) );
      
    }
    x = 5 + 5 + nabctracks*50; y = 85+70+ i*50;
    gboxes[i] = new wxStaticBox(panel, -1, std::to_string( BVTracks[i].id ), wxPoint(x, y), wxSize(sx, sy), wxTE_READONLY);
   
  }

  okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));
  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  SetSizer(vbox);


  Centre();
  ShowModal();

  //nthreads[0] = wxAtoi(threadsnumber->GetValue());
  for (size_t i = 0; i < nabctracks; i++)
  {
      BVTracks[i].hshift = wxAtof(shifts[i]->GetValue());
      BVTracks[i].hamp = wxAtof(hamps[i]->GetValue());

      for (size_t j=0; j < nabctracks; j++)
      {
          BVTracks[i].hcoupling[j] = wxAtof( couplingmatrix[i][j]->GetValue() );
      }
  }

  Destroy();
}


void HumanizationDialogue::OnButtonOK(wxCommandEvent& event)
{

    this->Destroy();
}

#endif // HumanizationDialogue

#include <wx/wx.h>
#include "stdio.h"
#include <iostream>
#include <string>
#include <list>

#ifdef win32
#include "windows.h"
#include "commctrl.h"
#endif

#include "include/brute.h"
#include "include/brutedefinitions.h"
//#include "include/midipreview.h"
#include "include/bandview.h"
#include "include/audioplayerAL.h"
#include "include/miditrackview.h"



class Notepad : public wxFrame {
    public:
        Notepad();
        wxString MidiFileName;
        wxString ABCFileName;

        Brute * myBrute;  // instance of the conversion class, for simplicity this is public for now

//        MidiPreview * myMidiPreview; // the object that will be handling the midi preview

        MidiTrackView * myMidiTrackView;

        wxFrame *frame;
        BandView * bandview;
        AudioPlayerAL * myaudioplayerAL;

        int audio_playing = 0;   // 0 is not playing at the moment

    private:

        wxMenuBar *menu; // the menu bar
        wxMenu *file; // the midi file menu (keep this simple
        wxMenu *abcmap; // the menu to manage the mapping files
        wxMenu *transcode; // the menu for transcoding
        wxMenu *band; // the menu for bandview interaction
        wxMenu *listen; // the menu for checking the audio preview
        wxMenu *statistics; // the menu for statistics

        wxTextCtrl *text; // the main text area

        void OnMidiFileSelect(wxCommandEvent &event); // the click event for "Select Midi File"
        void OnExit(wxCommandEvent &event); // the click event for "close"
        void OnDefaultMap(wxCommandEvent &event); // the click event to generate the default map
        void EmptyMap();
        void OnUpdateMap(wxCommandEvent &event);
        void OnPushMap(wxCommandEvent &event);

        void OnSave(wxCommandEvent &event); // the click event for "map save"
        void OnOpen(wxCommandEvent &event); // the click event for "map open"

        void OnSelectABCFile(wxCommandEvent &event); // click event for selecting ABC file name
    //    void OnTranscode(wxCommandEvent &event); // the click event for "transcode"

        void OnPlaywithABCPlayer(wxCommandEvent &event); // click event for playing with ABC Player
        void OnWavRender(wxCommandEvent &event); // click event for Rendering a WAVE File
        void OnPlayDirectly(wxCommandEvent &event); // click event to play directly

        void OnLogFile(wxCommandEvent &event); // click event to open the logfile


        // declare some ID values for our menu items
        enum MenuControls {
            idSave = 1000,
            idOpen = 1100,
            idExit = 1200,
            idMidiFileSelect = 1300,
            idSelectABCFile = 1400,
            idTranscode = 1500,
            idPlaywithABCPlayer = 1600,
            idWavRender = 1700,
            idPlayDirectly = 1800,
            idLogFile = 1900,
            idDefaultMap = 2000,
            idUpdateMap = 2100,
            idPushMap = 2200,
        };

        DECLARE_EVENT_TABLE()
};

// this is our event table, where we assign functions to specific events
BEGIN_EVENT_TABLE(Notepad, wxFrame) // begin the event table for our Notepad class, which inherits wxFrame
    EVT_MENU(idSave, Notepad::OnSave) // set an event for our idSave, and the function OnSave
    EVT_MENU(idOpen, Notepad::OnOpen) // set an event for open
    EVT_MENU(idExit, Notepad::OnExit) // set an event for exit
    EVT_MENU(idMidiFileSelect, Notepad::OnMidiFileSelect) // set an event for MidiFileSelect
    EVT_MENU(idSelectABCFile, Notepad::OnSelectABCFile) // set an event for ABC File Select
  //  EVT_MENU(idTranscode, Notepad::OnTranscode)         // set an event for Transcoding
    EVT_MENU(idLogFile, Notepad::OnLogFile)
    EVT_MENU(idDefaultMap, Notepad::OnDefaultMap)
    EVT_MENU(idPlaywithABCPlayer, Notepad::OnPlaywithABCPlayer)
    EVT_MENU(idWavRender, Notepad::OnWavRender)
    EVT_MENU(idPlayDirectly, Notepad::OnPlayDirectly)
    EVT_MENU(idUpdateMap, Notepad::OnUpdateMap)
    EVT_MENU(idPushMap, Notepad::OnPushMap)
END_EVENT_TABLE() // end the event table



Notepad::Notepad() : wxFrame(NULL, wxID_ANY, wxT("BruTE++AL 0.01"), wxDefaultPosition, wxSize(650,500)) {
    this->menu = new wxMenuBar(); // instantiate our menu bar

    this->file = new wxMenu(); // instantiate our file menu for our menu bar

    this->file->Append(idMidiFileSelect, wxT("Select Midi File\tCtrl-M"));  // Select Midi File

    this->file->AppendSeparator(); // add a separator (between our file I/O options and our exit option
    this->file->Append(idExit, wxT("E&xit\tCtrl-F4")); // add an exit option to the file menu
    this->menu->Append(file, wxT("&Midi")); // add the file menu to the menubar, and give it the title "File"

    this->abcmap = new wxMenu();
    this->abcmap->Append(idDefaultMap, wxT("&Generate Default Map\tCtrl-D"));
    this->abcmap->Append(idOpen, wxT("&Open Mapping File\tCtrl-O"));
    this->abcmap->Append(idSave, wxT("&Save Mapping File\tCtrl-S"));
    this->menu->Append(abcmap, wxT("&Map"));

    this->transcode = new wxMenu();
    this->transcode->Append(idSelectABCFile, wxT("&Save ABC file\tCtrl-A"));
    // this->transcode->Append(idTranscode, wxT("&Transcode\tCtrl-T"));
    this->menu->Append(transcode, wxT("&Transcode"));

    this->band = new wxMenu();
    this->band->Append(idUpdateMap, wxT("Poll Map from Bandview\tCtrl-P"));
    this->band->Append(idPushMap, wxT("Send Map to Bandview\tCtrl-B"));
    this->menu->Append(band, wxT("&BandView"));

    this->listen = new wxMenu();
    this->listen->Append(idPlaywithABCPlayer, wxT("&Play with ABCPlayer\tCtrl-P"));
    this->listen->Append(idWavRender, wxT("&Play ABC in BruTE\tCtrl-W"));
    this->listen->Append(idPlayDirectly, wxT("&Stop Playing\tCtrl-D"));
    this->menu->Append(listen, wxT("&Play ABC"));

    this->statistics = new wxMenu();
    this->statistics->Append(idLogFile, wxT("&View Log File\tCtrl-L"));
    this->menu->Append(statistics, wxT("&Statistics"));

    this->SetMenuBar(menu); // set our menu bar to be visible on the application

    this->text = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE);

}

void Notepad::OnSave(wxCommandEvent &event) {

    wxFileDialog *saveDialog = new wxFileDialog(this, wxT("Save File~"), wxT(""), wxT(""),
                                                wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxFD_SAVE);

    int response = saveDialog->ShowModal();
    if (response == wxID_OK) { // if the user clicked OK, we should save the text
        this->text->SaveFile(saveDialog->GetPath()); // this is pretty cool. we can save it with just one line!
    }
}

void Notepad::OnOpen(wxCommandEvent &event) {
    wxFileDialog *openDialog = new wxFileDialog(this, wxT("Open File~"), wxT(""), wxT(""),
                                                wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    int response = openDialog->ShowModal();
    if (response == wxID_OK) {
        this->text->LoadFile(openDialog->GetPath());
    }
}

void Notepad::OnMidiFileSelect(wxCommandEvent &event)
{
    wxFileDialog *openDialog = new wxFileDialog(this, wxT("Select Midi File~"), wxT(""), wxT(""), wxT("Midi Files (*.mid)|*.mid"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    int response = openDialog->ShowModal();
    if (response == wxID_OK)
    {
        // load this midi file
        this->MidiFileName = openDialog->GetPath();

        char cstring[1024];
        strncpy(cstring, (const char*)this->MidiFileName.mb_str(wxConvUTF8), 1023);

       // delete(this->myBrute);
       // this->myBrute = new(Brute);
        this->myBrute->LoadMidi(cstring);  // this loads the midi into the Brute instance

    }
    EmptyMap();
    this->bandview->Refresh();
}

void Notepad::OnSelectABCFile(wxCommandEvent &event)
{
    wxFileDialog *openDialog = new wxFileDialog(this, wxT("Select ABC File~"), wxT(""), wxT(""), wxT("ABC Files (*.abc)|*.abc"), wxFD_SAVE);
    int response = openDialog->ShowModal();
    if (response == wxID_OK)
    {
        // set the ABC output file name
        this->ABCFileName = openDialog->GetPath();
    }

    m_log.clear();
    // 1st get a stringstream of the Notepad Text, then parse the mapping
    std::stringstream mappingstream(  std::string(this->text->GetValue().mb_str())  );

    myBrute->Transcode(&mappingstream);

    // Now we can export an ABC file
    char abcname[8] = "new.abc";
    myBrute->ExportABC(abcname);

    std::ofstream logfile;
    logfile.open("logfile.txt");
    logfile.clear();
    logfile << m_log.rdbuf();
    logfile.close();

    if (ABCFileName != "")
    {
        myBrute->GenerateABC();
        // also save the ABC file in the targeted location .. a bit unintuitive but easier to use when checking the file all the time with the abc player
        std::ofstream abcoutfile;
        abcoutfile.open(ABCFileName.mb_str());

        abcoutfile << myBrute->m_ABCText.rdbuf();
        abcoutfile.close();
    }

}

void Notepad::OnPlaywithABCPlayer(wxCommandEvent &event)
{
    // play with ABC Player
    std::cout << " Play with ABC Player " << std::endl;

    auto reported = system("new.abc");
    if ( reported > 0) { std::cout << " Issue with Playing " << std::endl; }

}

void Notepad::OnWavRender(wxCommandEvent &event)
{
    // Render the WAV and play
    if (myBrute->DoIHaveAMidi() && myBrute->DoIHaveAMap())
    {
       myBrute->GenerateABC();
   //    myMidiPreview->GeneratePreviewMidi(&myBrute->m_ABCText, int64_t( myBrute->m_globalmaxtick/0.36) );
      // myaudioplayer->Play();
      myaudioplayerAL->SendABC(&myBrute->m_ABCText);
      myaudioplayerAL->Play();
    }
    else
    {
       wxString message;
       if (!myBrute->DoIHaveAMap()) message = wxT("No Mapping defined.");
       if (!myBrute->DoIHaveAMidi()) message = wxT("No Midi loaded.");
       wxMessageDialog * edialog = new wxMessageDialog(NULL, message, wxT("Info"), wxOK);
       edialog->ShowModal();
    }
    bandview->Refresh();
}

void Notepad::OnPlayDirectly(wxCommandEvent &event)
{
    myaudioplayerAL->Stop();
}

void Notepad::OnLogFile(wxCommandEvent &event)
{
    // Play directly
    // auto logfiledisplay = new wxTextCtrl(m_log);
}

void Notepad::OnDefaultMap(wxCommandEvent &event)
{
    // Generate a Default Map
    myBrute->GenerateDefaultConfig();

    this->text->Clear();

    wxString newdata(myBrute->m_MappingText.str().c_str(), wxConvUTF8);   // stringstream to string to c_string to make a wxString .. kind of cumbersome

    this->text->ChangeValue( newdata );

    // Somehow get the text into the Notepadwindow
}

void Notepad::EmptyMap()
{
    myBrute->GenerateEmptyConfig();
    this->text->Clear();
    wxString newdata(myBrute->m_MappingText.str().c_str(), wxConvUTF8);
    this->text->ChangeValue(newdata);
}

// Take the text from the m_Mappingtext to the Notepad
void Notepad::OnUpdateMap(wxCommandEvent &event)
{
    //this->bandview->MakeMappingHeader();  // myBrute->GenerateEmptyConfig();   // this is just a placeholder real deal should come from bandview
    this->bandview->GenerateConfigHeader();
    this->bandview->AppendMapping();  // as Bandview has a pointer to myBrute it can add the mapping text to the map itself

    this->text->Clear();
    wxString newdata(myBrute->m_MappingText.str().c_str(), wxConvUTF8);
    this->text->ChangeValue(newdata);
}

void Notepad::OnPushMap(wxCommandEvent &event)
{
    std::stringstream mappingstream(  std::string(this->text->GetValue().mb_str())  );
    myBrute->ParseConfig(&mappingstream);
    bandview->GetMapping();
}

// if the user clicks exit (from the menu) then we should close the window
void Notepad::OnExit(wxCommandEvent &event) {
    this->frame->Destroy();
  //  this->audioframe->Destroy();
    this->Destroy(); // close the window, and get clear any resources used (eg, memory)
}

class MainApp : public wxApp {


    public:
        virtual bool OnInit();
};

bool MainApp::OnInit() {

    // create a new Notepad

    Notepad *main = new Notepad();
    main->Show(true); // show it

    // to make sure that there is no default ABCName
    main->ABCFileName = "";

   // main->myMidiPreview = new MidiPreview();
    main->myBrute = new Brute;

   // main->myaudioplayer = new AudioPlayer(main->myBrute, main->myMidiPreview);
    //main->myMidiTrackView =  new MidiTrackView(main->myBrute, 1);
    main->myaudioplayerAL = new AudioPlayerAL();
    main->myaudioplayerAL->Initialize(100, 100);

    // Make the BandView Window
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    main->frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxDC"), wxPoint(200,50), wxSize(1050,700));
    main->bandview = new BandView( (wxFrame*) main->frame, main->myBrute, main->myMidiTrackView, main->myaudioplayerAL);


    sizer->Add(main->bandview, 1, wxEXPAND);

    main->frame->SetSizer(sizer);

    main->frame->SetAutoLayout(true);
    main->frame->Show();



    return true;
}

// and lastly, we just have to implement our application!
IMPLEMENT_APP(MainApp)

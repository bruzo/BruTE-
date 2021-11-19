#include "stdio.h"
#include "string.h"
#include "brute.h"


int main(int argc, char** argv)
{
   // Invoke an Instance of the Brute-Class
   Brute myBrute;


   // classic midival equivalency
   if ( argc > 1)
      if ( strcmp( argv[1], "midival" ) == 0 )
      {
         // this is the standart midival functionality
         std::cout << "Emulating former midival.exe" << std::endl;

         char midiname[8] = "mid.mid";
         myBrute.LoadMidi(midiname);

         char outallname[12] = "out_txt.all";
         myBrute.ExportOutAll(outallname);

         char defaultconfig[11] = "out.config";
         myBrute.ExportDefaultConfig(defaultconfig);

         //std::cout << myBrute.m_Midi.size() << std::endl;
      }

   // classic remap equivalency
   if (argc > 1)
      if (strcmp( argv[1], "remap" ) == 0)
      {
         m_log.clear();

         std::cout << "Emulating former remap.exe" << std::endl;
         m_log << "Emulating former remap.exe" << std::endl;

         char midiname[8] = "mid.mid";
         myBrute.LoadMidi(midiname);
         m_log << "Midi loaded " << std::endl;

         char defaultconfig[12] = "out.config\0";
         myBrute.ImportConfig(defaultconfig);

         // in case it's wanted break up bended tones
         if ( myBrute.m_Mapping.m_dopitchbends ) myBrute.PitchBends();

         // this starts the tone quantization
         myBrute.GenerateQuantizedNotes();

         // this creates the reduced selection for the abctracks (alternate, split, durationsplit)
         myBrute.GenerateNoteSelection();

         // map the tones on the grid
         myBrute.MapToRegister();

         // break it into lists of chords with duration
         myBrute.GenerateRoughChordLists();

         // now we need to adjust Chords in time to get them to not have a missmatch if possible and also make sure they are
         // long enough
         myBrute.ChordJoinDurations();

         // now that we joined equal chords, we have to transfer duration to make the starts fit
         myBrute.CorrectMissmatch();

         // Check for too short tones and try to correct them!
         myBrute.CompensateEasy();

         // Make sure we really have it all!
         if (!myBrute.AllChordsOK()){
                std::cout << " we didn't catch everything " << std::endl;
                myBrute.CompensateEasy();
         } else {
             m_log << "Somehow we wiggled it all into place!" << std::endl;
         }

         myBrute.Check_for_too_long_tones();   // essentially break up chords that are too long into sustained ones

         // Pre-Generate duration string names
         myBrute.GenerateDurationNames();


         // Now we can export an ABC file
         char abcname[8] = "new.abc";
         myBrute.ExportABC(abcname);

         std::ofstream logfile;
         logfile.open("logfile.txt");
         logfile.clear();
         logfile << m_log.rdbuf();
         logfile.close();
      }
   return 0;
}

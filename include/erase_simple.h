
        former = m_chordlists[abctrack].begin();
        current = former;
        current++;
        next = current;
        next++;

        // first we do changes that don't affect starting times
        while ( current != m_chordlists[abctrack].end()--)
        {
           // the current duration is too short
           if (current->duration < 2.0)
           {
             if  (current->is_rest)
             {
                 // std::cout << "Removing Break" << current->duration << std::endl;
                 // this is a too short break, just delete it and add duration to former tone
                 former->duration = former->duration + current->duration;
                 m_chordlists[abctrack].erase(current);
                 current = former;
                 if (current!=m_chordlists[abctrack].end())  current++;
                 next = current;
                 if (next!=m_chordlists[abctrack].end()) next++;
             }
           }


           if (current->duration < 2.0)
           {
             if  ( (next->is_rest) )
             {
                 // std::cout << "Next is rest, Corrected" << std::endl;
                 // next break is long enough to compensate
                 if ( next->duration + current->duration >=4.0)
                 {
                     next->duration = next->duration - (2.0 - current->duration);
                     current->duration =2.0;
                 }
                 else
                 {
                     current->duration = current->duration + next->duration;
                     m_chordlists[abctrack].erase(next);
                     next = current;
                     if (next != m_chordlists[abctrack].end()) next ++;
                 }
             }
           }


           if (current->duration < 2.0)
           {
              // for better understanding write out all the chord info
              if (next->npitches.size()==0)
              {
                // std::cout << "Next chord has no new tone, corrected" << std::endl;

                if ( next->duration + current->duration >=4.0)
                {
                     next->duration = next->duration - (2.0 - current->duration);
                     current->duration =2.0;
                }
                else {
                     current->duration = current->duration + next->duration;
                     m_chordlists[abctrack].erase(next);
                     next = current;
                     if (next != m_chordlists[abctrack].end()) next ++;
                }
              }

           }
           former = current;
           current++;
           next = current;
           if ( current!= m_chordlists[abctrack].end()) next++;
        }

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/timer.hpp>

#include <forward_list>
#include <map>
#include <cassert>
#include<stdio.h>
#include <iostream>
using namespace std;

int main1()
{
//#ifdef NANA_ENABLE_AUDIO6

    
//audio
    nana::audio::player playerMi("Mi_Piano.wav");
    nana::threads::pool pool(1); //Only 1 thread
    /*slide 11 code:*/
    using namespace nana;

    //Define a form.
    form fm;

    //Define a label and display a text.
    label lab{ fm, "Hello, <bold blue size=16>Nana C++ Library</>" };
    lab.format(true);

    //Define a button and answer the click event.
    button btn{ fm, "Quit" };
    btn.events().click([&fm] {
        fm.close();
        });

    //Layout management
    /* Remove this code, and replace it with the following for slide 9*/
  /*
    fm.div("vert <><<><weight=80% text><>><><weight=24<><button><>><>");
    fm["text"] << lab;
    fm["button"] << btn;
    fm.collocate();
*/
    //new code for slide 9:
    
    button  redBtn{ fm,"Red" };
    redBtn.events().click([] { cout << "I was clicked" << std::endl; });
     redBtn.events().click([&] { playerMi.play(); });
     
// Timer
    timer myTimer(std::chrono::milliseconds(20000));
    myTimer.elapse([&] { fm.close(); });
    myTimer.start();
    redBtn.bgcolor(color(255, 128, 128));
    fm.div("vert <AA> <<RED><BB><><><>> <<><><><><>><> <<><weight=150% text><>><><weight=24<><button><>><>"); //This creates 3 slots
    fm["AA"] << lab;
    fm["BB"] << btn;
    fm["RED"] << redBtn;
    fm.collocate();
    
   
    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    exec();
//#endif  //NANA_ENABLE_AUDIO

    return 0;
}
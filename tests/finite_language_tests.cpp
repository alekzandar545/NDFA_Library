#include <iostream>
#include <cassert>
#include "../include/automaton/automaton.hpp"

void runFiniteLanguageTests() {
    // simple finite automaton without cycles
    {
        Automaton a;
        a.addState(false);
        a.addState(true);
        a.addTransition(0, 1, 'a');
        a.changeStart(0);

        assert(a.recognizesFiniteLanguage()); 
    }

    //automaton with cyclce
    {
        Automaton a;
        a.addState(false); 
        a.addState(false); 
        a.addState(true);  
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.addTransition(2, 0, 'a'); 
        a.changeStart(0);

        assert(!a.recognizesFiniteLanguage());  //language is infinite due to cycle
    }

    // cycle leading to end state
    {
        Automaton a;
        a.addState(false); 
        a.addState(true);
        a.addState(false); 
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.addTransition(2, 0, 'a');
        a.changeStart(0);
        a.totalize();
        assert(!a.recognizesFiniteLanguage());  //should be infinite due to cycle leading to end state
    }

    // path leading to end state
    {
        Automaton a;
        a.addState(false); 
        a.addState(false);       
        a.addState(true); 
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.changeStart(0);
        a.totalize();
        assert(a.recognizesFiniteLanguage());  //language is finite as there are no cycles
    }

    // Tmultiple end states
    {
        Automaton a;
        a.addState(false); 
        a.addState(true); 
        a.addState(true);
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.changeStart(0);

        assert(a.recognizesFiniteLanguage());  //finite language, no cycles
    }

    //multiple cycles
    {
        Automaton a;
        a.addState(false); // State 0
        a.addState(false); // State 1
        a.addState(true);  // State 2
        a.addState(false); // State 3
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.addTransition(2, 3, 'a');
        a.addTransition(3, 2, 'b'); //cycle between state 2 and 3
        a.changeStart(0);

        assert(!a.recognizesFiniteLanguage());  //infinite language due to cycle between state 2 and 3
    }

    // large automaton without cycles
    {
        Automaton a;
        a.addState(false); 
        a.addState(false); 
        a.addState(false); 
        a.addState(false); 
        a.addState(true);  
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.addTransition(2, 3, 'c');
        a.addTransition(3, 4, 'd');
        a.changeStart(0);

        assert(a.recognizesFiniteLanguage());  // finite language, no cycles
    }

    //epsilon transition to start state
    {
        Automaton a;
        a.addState(false); 
        a.addState(false); 
        a.addState(true);  
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.addTransition(2, 0, '@'); 
        a.changeStart(0);

        assert(!a.recognizesFiniteLanguage());  // infinite due to epsilon cycle
    }

    //empty automaton
    {
        Automaton a; 

        assert(a.recognizesFiniteLanguage());  //empty automaton is finite (no states)
    }

}

int main() {
    runFiniteLanguageTests();
    std::cout << "all tests passed!";
    return 0;
}

#include <iostream>
#include <cassert>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

void runKleeneStarTests() {
    // single state automaton
    {
        Automaton a;
        a.addState(true); 
        a.changeStart(0);

        Automaton starA = kleeneStar(a);

        assert(starA.getStatesCount() == 2);
        assert(starA.containsWord(""));
        assert(!starA.containsWord("a"));
    }

    // single transition automaton
    {
        Automaton a;
        a.addState(false); 
        a.addState(true); 
        a.addTransition(0, 1, 'a');
        a.changeStart(0);

        Automaton starA = kleeneStar(a);

        assert(starA.containsWord(""));
        assert(starA.containsWord("a"));
        assert(starA.containsWord("aa"));
        assert(starA.containsWord("aaa"));
        assert(!starA.containsWord("b")); 
        assert(!starA.containsWord("ab")); 
    }

    //multiple end states
    {
        Automaton a;
        a.addState(false);
        a.addState(true);  
        a.addState(true);  
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.changeStart(0);

        Automaton starA = kleeneStar(a);

        assert(starA.containsWord(""));
        assert(starA.containsWord("a"));
        assert(starA.containsWord("ab"));
        assert(starA.containsWord("abab"));
        assert(!starA.containsWord("abc"));
        assert(!starA.containsWord("b"));
    }

    // more complex automaton
    {
        Automaton a;
        a.addState(false);
        a.addState(false); 
        a.addState(false); 
        a.addState(true); 
        a.addTransition(0, 1, 'a');
        a.addTransition(1, 2, 'b');
        a.addTransition(2, 3, 'c');
        a.changeStart(0);

        Automaton starA = kleeneStar(a);

        assert(starA.containsWord(""));
        assert(starA.containsWord("abc"));
        assert(starA.containsWord("abcabc"));
        assert(starA.containsWord("abcabcabc"));
        assert(!starA.containsWord("ab"));
        assert(!starA.containsWord("aabc"));
    }

    // empty automaton
    {
        Automaton a; 

        Automaton starA = kleeneStar(a);

        assert(starA.getStatesCount() == 1); //adds a single state for \epsilon
        assert(starA.containsWord(""));
        assert(!starA.containsWord("a"));
        assert(!starA.containsWord("ab"));
    }

    //automaton with epsilon transitions
    {
        Automaton a;
        a.addState(false);
        a.addState(false);
        a.addState(true); 
        a.addTransition(0, 1, EPSILON); 
        a.addTransition(1, 2, 'a');
        a.changeStart(0);

        Automaton starA = kleeneStar(a);

        assert(starA.containsWord(""));
        assert(starA.containsWord("a"));
        assert(starA.containsWord("aa"));
        // assert(starA.containsWord("aaaaaaaaaaaa"));
        assert(!starA.containsWord("aaab"));
    }

}

int main(){
    runKleeneStarTests();
    std::cout << "all tests passed!";
}
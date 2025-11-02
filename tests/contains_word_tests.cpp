#include <cassert> 
#include <iostream>
#include <fstream>
#include "../include/automaton/automaton.hpp"

void testContainsWord() {
    //ndfa with one word
    {
        Automaton automata;
        automata.addState(false); 
        automata.addState(false); 
        automata.addState(true); 

        automata.addTransition(0, 1, 'a');
        automata.addTransition(1, 2, 'b');

        assert(automata.containsWord("ab"));
        assert(!automata.containsWord("a"));
        assert(!automata.containsWord("abc"));
        assert(!automata.containsWord(""));
    }

    //automata with multiple transitions
    {
        Automaton automata;
        automata.addState(false);
        automata.addState(false);
        automata.addState(true);  

        automata.addTransition(0, 1, 'a');
        automata.addTransition(1, 2, 'b');
        automata.addTransition(0, 2, 'c');

        assert(automata.containsWord("ab"));
        assert(automata.containsWord("c"));
        assert(!automata.containsWord("a"));
        assert(!automata.containsWord("abc"));

    }

    //automata with multiple paths ndfa
    {
        Automaton automata;
        automata.addState(false);
        automata.addState(false); 
        automata.addState(false); 
        automata.addState(true);  

        automata.addTransition(0, 1, 'a');
        automata.addTransition(0, 2, 'a');
        automata.addTransition(1, 3, 'b');
        automata.addTransition(2, 3, 'c');

        assert(automata.containsWord("ab"));
        assert(automata.containsWord("ac"));
        assert(!automata.containsWord("a"));
        assert(!automata.containsWord("abc"));
    }

    //empty automata
    {
        Automaton automata;
        assert(!automata.containsWord(""));
        assert(!automata.containsWord("a"));
    }

    //automata with single state as end state
    {
        Automaton automata;
        automata.addState(true);

        assert(automata.containsWord(""));
        assert(!automata.containsWord("a"));
    }

    //automata with cycles
    {
        Automaton automata;
        automata.addState(false); 
        automata.addState(false);
        automata.addState(true);  

        automata.addTransition(0, 1, 'a');
        automata.addTransition(1, 0, 'b');
        automata.addTransition(1, 2, 'c');

        assert(automata.containsWord("ac"));
        assert(automata.containsWord("abac"));
        assert(!automata.containsWord("abc"));
        assert(!automata.containsWord("a"));
    }
}

int main() {
    testContainsWord();
    return 0;
}

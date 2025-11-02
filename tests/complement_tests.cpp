#include <iostream>
#include <cassert>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

void testComplement() {
    try {
        //empty automaton
        Automaton emptyAutomaton;
        Automaton complementEmpty = complement(emptyAutomaton);
        assert(complementEmpty.getStatesCount() == 0);

        //single non accepting state
        Automaton singleNonAccepting;
        singleNonAccepting.addState(false); 
        singleNonAccepting.changeStart(0);
        Automaton complementSingleNonAccepting = complement(singleNonAccepting);
        assert(complementSingleNonAccepting.getStatesCount() == 1);
        assert(complementSingleNonAccepting.isFinalState(0));
        assert(complementSingleNonAccepting.containsWord("")); 

        //singe accepting state
        Automaton singleAccepting;
        singleAccepting.addState(true); 
        singleAccepting.changeStart(0);
        Automaton complementSingleAccepting = complement(singleAccepting);
        assert(complementSingleAccepting.getStatesCount() == 1);
        assert(!complementSingleAccepting.isFinalState(0));
        assert(!complementSingleAccepting.containsWord("")); 

        //two states
        Automaton twoStateAutomaton;
        twoStateAutomaton.addState(false); 
        twoStateAutomaton.addState(true);  
        twoStateAutomaton.addTransition(0, 1, 'a');
        twoStateAutomaton.addTransition(1, 0, 'b');
        twoStateAutomaton.changeStart(0);
        Automaton complementTwoState = complement(twoStateAutomaton);
        assert(complementTwoState.containsWord("b"));
        assert(!complementTwoState.containsWord("a")); 
        assert(complementTwoState.containsWord("bbb")); 

        //automaton with loops
        Automaton loopAutomaton;
        loopAutomaton.addState(false); 
        loopAutomaton.addState(true);  
        loopAutomaton.addTransition(0, 0, 'a');
        loopAutomaton.addTransition(0, 1, 'b');
        loopAutomaton.changeStart(0);
        Automaton complementLoop = complement(loopAutomaton);   
        assert(complementLoop.containsWord("aaa"));
        assert(!complementLoop.containsWord("b")); 
        assert(complementLoop.containsWord("abab")); 

        //totalized dfa
        Automaton totalizedDFA;
        totalizedDFA.addState(false); 
        totalizedDFA.addState(true); 
        totalizedDFA.addTransition(0, 1, 'a');
        totalizedDFA.addTransition(1, 0, 'b');
        totalizedDFA.changeStart(0);
        Automaton complementTotalized = complement(totalizedDFA);
        assert(complementTotalized.containsWord("ab")); 
        assert(complementTotalized.containsWord("")); 
        assert(complementTotalized.containsWord("aaa")); 

    } catch (const std::exception& ex) {
        std::cerr << "test failed with exception: " << ex.what() << std::endl;
    }
}

int main() {
    testComplement();
    std::cout << "all test passed!";
    return 0;
}

#include <iostream>
#include <cassert>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

void runDeterminizationTests() {
    try {
        //empty automaton
        Automaton emptyAutomaton;
        Automaton dfaEmpty;
        dfaEmpty.determinize();
        assert(emptyAutomaton.containsWord("") == dfaEmpty.containsWord(""));

        //single state automaton
        Automaton singleState;
        singleState.addState(true);
        singleState.changeStart(0);
        Automaton dfaSingleState = singleState;
        dfaSingleState.determinize();
        assert(singleState.containsWord("") == dfaSingleState.containsWord(""));

        //automaton with epsilon transitions
        Automaton epsilonAutomaton;
        epsilonAutomaton.addState(false); 
        epsilonAutomaton.addState(true);  
        epsilonAutomaton.addTransition(0, 1, '@');  
        epsilonAutomaton.changeStart(0);
        Automaton dfaEpsilon = epsilonAutomaton;
        dfaEpsilon.determinize();
        assert(epsilonAutomaton.containsWord("") == dfaEpsilon.containsWord(""));
        assert(epsilonAutomaton.containsWord("a") == dfaEpsilon.containsWord("a"));

        //automaton with multiple states and transitions
        Automaton multiStateAutomaton;
        multiStateAutomaton.addState(false);
        multiStateAutomaton.addState(false);
        multiStateAutomaton.addState(false); 
        multiStateAutomaton.addState(true);  
        multiStateAutomaton.addTransition(0, 1, 'a');
        multiStateAutomaton.addTransition(1, 2, '@');
        multiStateAutomaton.addTransition(2, 3, 'b');
        multiStateAutomaton.changeStart(0);
        Automaton dfaMultiState = multiStateAutomaton;
        dfaMultiState.determinize();
        assert(dfaMultiState.containsWord("ab"));
        assert(!dfaMultiState.containsWord("a"));
        assert(dfaMultiState.getStatesCount() == 3);
        assert(multiStateAutomaton.getStatesCount() == 4);
        assert(multiStateAutomaton.containsWord("ab") == dfaMultiState.containsWord("ab"));
        assert(multiStateAutomaton.containsWord("a") == dfaMultiState.containsWord("a"));

        // automaton with loops
        Automaton loopAutomaton;
        loopAutomaton.addState(true);  
        loopAutomaton.addState(false);
        loopAutomaton.addTransition(1, 1, 'a');
        loopAutomaton.addTransition(1, 0, 'b');
        loopAutomaton.changeStart(1);
        Automaton dfaLoop = loopAutomaton;
        dfaLoop.determinize();
        assert(loopAutomaton.containsWord("aaaaaaab"));
        assert(dfaLoop.containsWord("aaaaaaab"));
        assert(loopAutomaton.containsWord("aab") == dfaLoop.containsWord("aab"));
        assert(loopAutomaton.containsWord("a") == dfaLoop.containsWord("a"));

        // automaton with multiple end states
        Automaton multiEndAutomaton;
        multiEndAutomaton.addState(false); 
        multiEndAutomaton.addState(true);  
        multiEndAutomaton.addState(true);  
        multiEndAutomaton.addTransition(0, 1, 'a');
        multiEndAutomaton.addTransition(1, 2, 'b');
        multiEndAutomaton.changeStart(0);
        Automaton dfaMultiEnd = multiEndAutomaton;
        dfaMultiEnd.determinize();
        assert(multiEndAutomaton.containsWord("ab") == dfaMultiEnd.containsWord("ab"));
        assert(multiEndAutomaton.containsWord("a") == dfaMultiEnd.containsWord("a"));

        //automaton with self loopp start state
        Automaton selfLoopAutomaton;
        selfLoopAutomaton.addState(true); 
        selfLoopAutomaton.addTransition(0, 0, 'a'); 
        selfLoopAutomaton.changeStart(0);
        Automaton dfaSelfLoop = selfLoopAutomaton;
        dfaSelfLoop.determinize();
        assert(selfLoopAutomaton.containsWord("a") == dfaSelfLoop.containsWord("a"));
        assert(selfLoopAutomaton.containsWord("aa") == dfaSelfLoop.containsWord("aa"));

    } catch (const std::exception& ex) {
        std::cerr << "Test failed with exception: " << ex.what() << std::endl;
    }
}
void runLargeNfaTest() {
    try {
        Automaton largeNfa;

        largeNfa.addState(false);  
        largeNfa.addState(false);  
        largeNfa.addState(false); 
        largeNfa.addState(false);  
        largeNfa.addState(false);  
        largeNfa.addState(true);   

        largeNfa.changeStart(0);

        largeNfa.addTransition(0, 1, 'a');
        largeNfa.addTransition(1, 2, 'b');
        largeNfa.addTransition(2, 3, 'a');
        largeNfa.addTransition(3, 4, 'b');
        largeNfa.addTransition(4, 5, 'a'); 

        largeNfa.addTransition(0, 3, 'b');
        largeNfa.addTransition(1, 2, 'a');
        largeNfa.addTransition(2, 1, 'b');
        largeNfa.addTransition(4, 4, 'b'); 
        largeNfa.addTransition(3, 3, 'a'); 

        largeNfa.addTransition(1, 0, '@'); 
        largeNfa.addTransition(2, 3, '@');

        Automaton dfaLarge = largeNfa;
        dfaLarge.determinize();

        String test1 = "abab";
        String test2 = "aab";
        String test3 = "ababa";

        assert(largeNfa.containsWord(test1) == dfaLarge.containsWord(test1));
        assert(largeNfa.containsWord(test2) == dfaLarge.containsWord(test2));
        assert(largeNfa.containsWord(test3) == dfaLarge.containsWord(test3));

    } catch (const std::exception& ex) {
        std::cerr << "Test failed with exception: " << ex.what() << std::endl;
    }
}
int main() {
    runDeterminizationTests();
    runLargeNfaTest();
    std::cout << "all tests passeed!";
    return 0;
}

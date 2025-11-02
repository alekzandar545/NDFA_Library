#include <iostream>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

int main() {
    Automaton automaton1;
    automaton1.addState(true); 
    automaton1.addState(true);  
    automaton1.addTransition(0, 1, 'a'); 

    Automaton automaton2;
    automaton2.addState(false); 
    automaton2.addState(true);  
    automaton2.addTransition(0, 1, 'b');  

    Automaton concatenatedAutomaton = concatenate(automaton1, automaton2);

    String testWord = "ab";
    bool result = concatenatedAutomaton.containsWord(testWord);

    std::cout << (result ? "test passed!" : "test didnt pass");

    return 0;
}

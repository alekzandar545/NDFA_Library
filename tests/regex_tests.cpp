#include <iostream>
#include <fstream>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

int main() {
    //create automata manually and write regex tests
    Automaton automata1;
    automata1.addState(false);
    automata1.addState(true); 
    automata1.addTransition(0, 1, 'a');
    automata1.changeStart(0);

    std::cout << "test 1 (dfa with one transition 'a') regex: " << createRegex(automata1) << std::endl;

    Automaton automata3;
    automata3.addState(true); 
    automata3.addTransition(0, 0, 'a');
    automata3.changeStart(0);

    std::cout << "test 3 (automata for 'a*') regex: " << createRegex(automata3) << std::endl;

    Automaton automata4;
    automata4.addState(false);
    automata4.addState(false);
    automata4.addState(true); 
    automata4.addTransition(0, 1, 'a');
    automata4.addTransition(1, 2, 'b');
    automata4.changeStart(0);

    std::cout << "test 4 (automata for 'a.b') regex: " << createRegex(automata4) << std::endl;

    Automaton automata5;
    automata5.addState(false);
    automata5.addState(true);  
    automata5.addState(true); 
    automata5.addTransition(0, 1, 'a');
    automata5.addTransition(0, 2, 'b');
    automata5.changeStart(0);

    std::cout << "test 5 (automata for 'a+b') regex: " << createRegex(automata5) << std::endl;

    Automaton automata6;
    automata6.addState(true);  
    automata6.addState(false); 
    automata6.addState(false);
    automata6.addTransition(0, 1, 'a');
    automata6.addTransition(1, 2, 'b');
    automata6.addTransition(2, 0, '@');
    automata6.changeStart(0);

    automata6.determinize();
    std::cout << "test 6 (automata for '(a.b)*') regex: " << createRegex(automata6) << std::endl;

    //read automata from regex and recreating it tests
    Automaton automata7 = fromRegex("a");
    std::cout << "test 7 (automata for 'a') regex: " << createRegex(automata7) << std::endl;

    Automaton automata8 = fromRegex("a+b");
    std::cout << "test 8 (automata for 'a+b') regex: " << createRegex(automata8) << std::endl;

    Automaton automata9 = fromRegex("a.b");
    std::cout << "test 9 (automata for 'a.b') regex: " << createRegex(automata9) << std::endl;

    Automaton automata10 = fromRegex("a*");
    std::cout << "test 10 (automata for 'a*') regex: " << createRegex(automata10) << std::endl;

    Automaton automata11 = fromRegex("(a.b)* + c");
    std::cout << "test 11 (automata for '(a.b)* + c') regex: " << createRegex(automata11) << std::endl;

    return 0;

}

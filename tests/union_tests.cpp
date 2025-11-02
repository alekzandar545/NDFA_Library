#include <cassert>
#include <iostream>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

void testUnionize() {
    //union of two automata accepting "a" and "b"
    Automaton a1;
    a1.addState(false);
    a1.addState(true);  
    a1.addTransition(0, 1, 'a');

    Automaton a2;
    a2.addState(false); 
    a2.addState(true);  
    a2.addTransition(0, 1, 'b');

    Automaton a3 = unionize(a1, a2);

    // a3 should accept "a" and "b", but not "ab" or "ba"
    assert(a3.containsWord("a") == true);
    assert(a3.containsWord("b") == true);
    assert(a3.containsWord("ab") == false);
    assert(a3.containsWord("ba") == false);
    assert(a3.containsWord("") == false);

    // union of an automaton accepting "abc" and one accepting "def"
    Automaton a4;
    a4.addState(false);
    a4.addState(false);
    a4.addState(false); 
    a4.addState(true); 
    a4.addTransition(0, 1, 'a');
    a4.addTransition(1, 2, 'b');
    a4.addTransition(2, 3, 'c');
    a4.changeStart(0);
    
    Automaton a5;
    a5.addState(false); 
    a5.addState(false); 
    a5.addState(false); 
    a5.addState(true);  
    a5.addTransition(0, 1, 'd');
    a5.addTransition(1, 2, 'e');
    a5.addTransition(2, 3, 'f');
    a5.changeStart(0);

    Automaton a6 = unionize(a4, a5);

    // a6 should accept "abc" and "def", but not "abcd" or "cba"
    assert(a6.containsWord("abc") == true);
    assert(a6.containsWord("def") == true);
    assert(a6.containsWord("abcd") == false);
    assert(a6.containsWord("cba") == false);
    assert(a6.containsWord("") == false);


    //union with an empty automaton
    Automaton a7; 

    Automaton a8;
    a8.addState(false); 
    a8.addState(true);  
    a8.addTransition(0, 1, 'x'); 
    a8.changeStart(0);

    Automaton a9 = unionize(a7, a8);

    // a9 should behave like a8, as a7 is empty
    assert(a9.containsWord("x") == true);
    assert(a9.containsWord("y") == false);
    assert(a9.containsWord("") == false);

    //union of two automata accepting epsilon transitions
    Automaton a10;
    a10.addState(true);
    a10.changeStart(0);

    Automaton a11;
    a11.addState(true); 
    a11.changeStart(0);

    Automaton a12 = unionize(a10, a11);

    // a12 should accept an empty string because both automata accept epsilon
    assert(a12.containsWord("") == true);
    assert(a12.containsWord("a") == false);

}

int main() {
    testUnionize();
    std::cout << "all tests passed!";
    return 0;
}

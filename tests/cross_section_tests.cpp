#include <iostream>
#include <cassert>
#include "../include/automaton/automaton.hpp"

using namespace AutomataAlgorithms;

void testIntersection() {
    //basic Intersection Test
    Automaton a1, a2;
    a1.addState(true);
    a1.addState(false);
    a1.addTransition(0, 1, 'a');
    a1.addTransition(1, 0, 'b');
    a1.changeStart(0);

    a2.addState(true);
    a2.addState(false);
    a2.addTransition(0, 1, 'a');
    a2.addTransition(1, 0, 'b');
    a2.changeStart(0);

    Automaton result = intersection(a1, a2);
    assert(result.containsWord("ab")); 
    assert(!result.containsWord("ba"));  

    //no common word
    Automaton a3, a4;
    a3.addState(true);
    a3.addState(false);
    a3.addTransition(0, 1, 'a');
    a3.addTransition(1, 0, 'b');
    a3.changeStart(0);

    a4.addState(true);
    a4.addState(false);
    a4.addTransition(0, 1, 'x');
    a4.addTransition(1, 0, 'y');
    a4.changeStart(0);

    Automaton result2 = intersection(a3, a4);
    assert(!result2.containsWord("ab")); 
    assert(!result2.containsWord("xy"));


    //one automaton rejecting
    Automaton a5, a6;
    a5.addState(true);
    a5.addState(false);
    a5.addTransition(0, 1, 'a');
    a5.changeStart(0);

    a6.addState(false); 
    a6.changeStart(0);

    Automaton result3 = intersection(a5, a6);
    assert(!result3.containsWord("a"));

    //empty intersection test
    Automaton a7, a8;
    a7.addState(true);
    a7.addState(false);
    a7.addTransition(0, 1, 'a');
    a7.addTransition(1, 0, 'b');
    a7.changeStart(0);

    a8.addState(true);
    a8.addState(false);
    a8.addTransition(0, 1, 'c');
    a8.addTransition(1, 0, 'd');
    a8.changeStart(0);

    Automaton result4 = intersection(a7, a8);
    assert(!result4.containsWord("ab"));
    assert(!result4.containsWord("cd"));

    //intersection with common suffix
    Automaton a9, a10;
    a9.addState(true);
    a9.addState(false);
    a9.addTransition(0, 1, 'a');
    a9.addTransition(1, 0, 'b');
    a9.changeStart(0);

    a10.addState(true);
    a10.addState(false);
    a10.addTransition(0, 1, 'a');
    a10.addTransition(1, 0, 'b');
    a10.changeStart(0);

    Automaton result5 = intersection(a9, a10);
    assert(result5.containsWord("ababab"));
    assert(!result5.containsWord("ba"));

    //ideantical automata
    Automaton a11, a12;
    a11.addState(true);
    a11.addState(false);
    a11.addTransition(0, 1, 'a');
    a11.addTransition(1, 0, 'b');
    a11.changeStart(0);

    a12.addState(true);
    a12.addState(false);
    a12.addTransition(0, 1, 'a');
    a12.addTransition(1, 0, 'b');
    a12.changeStart(0);

    Automaton result6 = intersection(a11, a12);
    assert(result6.containsWord("ab")); 
    assert(!result6.containsWord("ba")); 


    //larger automata test
    Automaton a13, a14;
    a13.addState(true);
    a13.addState(true);
    a13.addState(true);
    a13.addTransition(0, 1, 'a');
    a13.addTransition(1, 2, 'd');
    a13.addTransition(2, 0, 'c');
    a13.changeStart(0);

    a14.addState(true);
    a14.addState(false);
    a14.addState(true);
    a14.addTransition(0, 1, 'a');
    a14.addTransition(1, 2, 'd');
    a14.addTransition(2, 0, 'e');
    a14.changeStart(0);

    Automaton result7 = intersection(a13, a14);
    assert(result7.containsWord("ad"));
    assert(!result7.containsWord("a"));
    assert(!result7.containsWord("ab"));
}

int main() {
    testIntersection();
    std::cout << "all tests passed!";
    return 0;
}

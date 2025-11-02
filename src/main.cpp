#include "../include/automaton/automaton.hpp"
#include "../libs/graphviz/include/graphviz/cgraph.h"
#include "../libs/graphviz/include/graphviz/gvc.h"

using namespace AutomataAlgorithms;

int main() {
    Automaton a, b;
    String regex = "(a.b.c.? + g)*";
    a = createAndSaveAutomaton(regex);
    std::ifstream stream("data/text.txt");
    checkRecognizedLines(a, stream);
    return 0;
}

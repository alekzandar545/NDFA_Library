#pragma once

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "../datastructures/string.hpp"
#include "../datastructures/vector.hpp"
#include "../datastructures/queue.hpp"
#include "../datastructures/stack.hpp"
#include "../datastructures/bitset.hpp"
#include "hash_structs.hpp"
#include "transition.hpp"

using State = unsigned;
static constexpr int EPSILON = '@';

class Automaton{
private:
    State startState;
    BitSet finalStates;
    Vector<Vector<Transition>> data;
public:
    Automaton();
    //UTIL------------------------------------------------------------
    void addState(const bool isEndState);
    void addFinalState(State state);
    void addTransition(const State from, const State to, const char tag);
    void changeStart(State newStartState);
    bool containsWord(const String& word) const;
    bool isFinalState(const State state) const;
    bool isDFA() const;
    bool recognizesEmptyLanguage() const;
    bool recognizesFiniteLanguage() const;
    bool recognizesAllWords() const;
    unsigned acceptedLines(const Automaton& a, std::ifstream& stream) const;
    Vector<State> epsilonClosure(State state) const;
    BitSet epsilonClosureBitSet(State state) const;
    //Setters   
    void setFinalState(State state, bool val) {finalStates[state] = val;}
    //SERIALIZATION-----------------------------------------------------
    static Automaton deserialize(std::ifstream& stream);
    void serialize(std::ofstream& stream) const;
    //VALIDATION--------------------------------------------------------
    void validate() const;
    //IMAGE_GENERATION--------------------------------------------------
    void convertToDOT() const;
    void rasterize(const String& str) const;
    //GETTERS-----------------------------------------------------------
    BitSet getAlphabet() const;
    const Vector<Vector<Transition>>& getData() const {return data;}
    const BitSet& getFinalStates() const {return finalStates;}
    unsigned getStatesCount() const;
    unsigned getFinalStatesCount() const;
    State getStartState() const;
    Vector<Transition> getTransitions(State state) const;
    //EXTRA ALGORITHMS-------------------------------------------------
    void determinize();
    void totalize(); 
};
namespace AutomataAlgorithms{
    //REGEX----------------------------------------------------------
    Automaton fromRegex(const String& regex);
    String createRegex(const Automaton& a); 
    //CONSTRUCTIONS-----------------------------------------------------
    Automaton intersection(const Automaton& a1, const Automaton& a2);
    Automaton concatenate(const Automaton& a1, const Automaton& a2);
    Automaton kleeneStar(const Automaton& a);
    Automaton unionize(const Automaton& a1, const Automaton& a2);
    Automaton complement(const Automaton& a);
    //OTHER---------------------------------------------------------
    Automaton createAndSaveAutomaton(const String& regex);
    void checkRecognizedLines(const Automaton& a, std::ifstream& stream);

}
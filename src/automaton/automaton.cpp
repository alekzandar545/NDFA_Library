#include "../../include/automaton/automaton.hpp"
#include "../../include/automaton/regex_utils.hpp"

using namespace AutomataAlgorithms;

Automaton::Automaton() : startState(0) {}
//UTIL------------------------------------------------------------
void Automaton::addState(const bool isFinalState){
    unsigned newSize = getStatesCount() + 1;
    data.resize(newSize);
    finalStates.resize(newSize, false);
    finalStates[newSize-1] = isFinalState;
}

void Automaton::addFinalState(State state){
    if(state >= getStatesCount() || state >= finalStates.size())
        throw std::out_of_range("No such state exists!");
    finalStates[state] = true;
}

void Automaton::addTransition(const State from, const State to, const char tag){
    if(from >= getStatesCount() || to >= getStatesCount())
        throw std::out_of_range("No such state!");
    data[from].append({from, to, tag});
}

void Automaton::changeStart(State newStartState){
    if (newStartState >= getStatesCount())
        throw std::out_of_range("No such state exists!");
    startState = newStartState;
}

bool Automaton::containsWord(const String& word) const{
    //empty automata got no words
    if(!getStatesCount())
        return word == false;
    Vector<State> currentStates = {epsilonClosure(startState)}; 
    //for each letter go through all the current states
    for (char c : word) {
        Vector<State> nextStates;
        for (State currState : currentStates){
            //get all elemets accessible through epsilon transitions
            Vector<State> currStateClosure = epsilonClosure(currState);
            for (State curr : currStateClosure)
            {
                //go through each transition coming out from each of those elements
                Vector<Transition> transitions = getTransitions(curr);
                for (const Transition& transition : transitions)
                    if (transition.tag == c) 
                        nextStates.append(transition.to);
            }
        }
        //nowhere to go
        if (nextStates.empty()) 
            return false;

        currentStates = nextStates;
    }

    //check last remaining states
    for (State state : currentStates)
        if (isFinalState(state)) 
            return true;
    return false;
}

bool Automaton::isFinalState(const State state) const{
    if(state >= finalStates.size())
        throw std::out_of_range("No such state exists!");
    return finalStates[state];
}

bool Automaton::recognizesEmptyLanguage() const{
    BitSet visited(getStatesCount());
    Queue<State> toVisit;

    //load start into queue
    toVisit.push(startState);
    visited[startState] = true;

    //standart bfs
    while (!toVisit.empty()) {
        State current = toVisit.front();
        toVisit.pop();

        //reachable end state means the automaton recognizes sth
        if (isFinalState(current))
            return false;

        //add unvisite to queue to explore transitions
        for (const Transition& transition : data[current]) {
            if (visited[transition.to] == false) {
                visited[transition.to] = true;
                toVisit.push(transition.to);
            }
        }
    }

    //didnt reach any final state
    return true;
}

bool Automaton::recognizesFiniteLanguage() const {
    //presense of * indicates that there is infinite repetition of sth
    String regex = createRegex(*this);
    for (char c : regex)
        if(c == '*')
            return false;
    return true;
}

bool Automaton::recognizesAllWords() const{
    //we will take the complment automata and check wether its language is empty ;3
    Automaton a = complement(*this);
    return !a.recognizesEmptyLanguage();
}

bool Automaton::isDFA() const {
    //empty automata is dfa, yes
    if(!getStatesCount())
        return true;
    //go through every state and check for inection and lack of epsilon transitions
    for (size_t i = 0; i < getStatesCount(); i++)
    {
        BitSet usedChars;
        for (const Transition& transition : data[i])   
        {
            if(transition.tag == EPSILON || usedChars[transition.tag] == true)
                return false;
            usedChars[transition.tag] = true;
        }
    }
    return true;
}


BitSet Automaton::getAlphabet() const{
    BitSet result;
    for (size_t i = 0; i < getStatesCount(); i++)
        for (const Transition& transition : data[i]){
            char tag = transition.tag;
            if(tag != EPSILON)//sparing the epsilon transitions
                result[tag] = true;
        }
    return result;
}

unsigned Automaton::acceptedLines(const Automaton& a, std::ifstream& stream) const{
    unsigned regognizedLines = 0;
    String line;
    char buffer[1024];
    while(stream.getline(buffer, sizeof(buffer))){
        line = buffer;
        if(a.containsWord(line))
            regognizedLines++;
    }
    return regognizedLines;
}
//SERIALIZATION-----------------------------------------------------
Automaton Automaton::deserialize(std::ifstream& stream){
    if(!stream)
        throw std::runtime_error("Failed to read from stream.");

    Automaton result;
    unsigned totalStates, totalFinalStates, totalTransitions;
    State startState;
    stream >> totalStates >> startState >> totalFinalStates >> totalTransitions;

    //input format validation (synthax check)
    if(startState >= totalStates || totalFinalStates > totalStates)
        throw std::out_of_range("Invalid input format!");
    
    result.data.resize(totalStates);
    result.finalStates.resize(totalStates, false);
    result.changeStart(startState);

    //read end states
    for (size_t i = 0; i < totalFinalStates; i++)
    {
        State state;
        stream >> state;
        if(state >= totalStates)
            throw std::out_of_range("State index is invalid!");
        result.addFinalState(state);
    }
    //read transitions
    for (size_t i = 0; i < totalTransitions; i++)
    {
        State from, to;
        char tag;
        stream >> from >> to >> tag;
        result.addTransition(from, to, tag);
    }

    result.validate();
    return result;
}

void Automaton::serialize(std::ofstream& stream) const {
    validate();

    if (!stream)
        throw std::runtime_error("Failed to write to stream.");

    stream << getStatesCount() << " " << startState << " ";
    stream << getFinalStatesCount() << " ";
    
    unsigned totalTransitions = 0;
    for (size_t i = 0; i < getStatesCount(); i++)
        totalTransitions += data[i].size();
    stream << totalTransitions << "\n";

    for (size_t i = 0; i < finalStates.size(); ++i)
        if (isFinalState(i))
            stream << i << " ";
    stream << "\n";

    for (size_t i = 0; i < getStatesCount(); i++)
        for (const Transition& transition : data[i])
            stream << transition.from << " " << transition.to << " " << transition.tag << "\n";
}
// VALIDATION--------------------------------------------------------
void Automaton::validate() const {
    //semantic validation (logic check)
    if(startState >= data.size())
        throw std::logic_error("Invalid start state");

    for (size_t i = 0; i < data.size(); ++i) {
        for (const Transition& t : data[i]) {
            if(t.from != i)
                throw std::logic_error("Transition source mismatch");
            if(t.to >= data.size())
                throw std::logic_error("Invalid transition target");
        }
    }
}
//IMAGE_GENERATION-----------------------------
void Automaton::convertToDOT() const{
    std::ofstream stream("data/automaton.dot");
    if (!stream) {
        throw std::runtime_error("Failed to create DOT file.");
    }

    stream << "digraph Automaton {\n";
    stream << "    rankdir=LR;\n"; 
    stream << "    node [shape=circle];\n";
    //start state marker
    stream << "    start [shape=plaintext, label=\"\"];\n";
    stream << "    start -> " << startState << ";\n";

    //marking end states
    for (size_t i = 0; i < finalStates.size(); ++i) 
        if (isFinalState(i)) 
            stream << "    " << i << " [shape=doublecircle];\n";

    //adding transitions
    for (size_t i = 0; i < getStatesCount(); ++i) {
        for (const Transition& transition : data[i]) {
            stream << "    " << transition.from << " -> " << transition.to 
                   << " [label=\"" << transition.tag << "\"];\n";
        }
    }

    stream << "}\n";
    stream.close();
}

void Automaton::rasterize(const String& str) const{
    convertToDOT();
    //path is relative to main.exe executable
    const String dotCommand = "libs\\graphviz\\bin\\dot.exe -Tpng data\\automaton.dot -o images\\" + str + ".png";
    int result = std::system(dotCommand.c_str());

    if (result == 0)
        std::cout << "DOT file successfully converted to automaton.png!\n";
    else
        std::cerr << "Error: Failed to run Graphviz command.\n";
}


//GETTERS---------------------------------------------------
unsigned Automaton::getStatesCount() const{return data.size();}

State Automaton::getStartState() const {return startState;}

Vector<Transition> Automaton::getTransitions(State state) const{
    Vector<Transition> res;
    Vector<State> epsilonClosureStates = epsilonClosure(state);
    for (State curr : epsilonClosureStates)
        for (const Transition& transition : data[curr])
            res.append(transition);

    return res;
}

Vector<State> Automaton::epsilonClosure(State state) const{

    Vector<State> res;
    //cannot get any closure in an automata with no states
    if(getStatesCount() == 0)
        return res;

    Queue<State> q;
    BitSet visited(getStatesCount()); 

    q.push(state);

    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        visited[curr] = true;
        
        for (const Transition& transition : data[curr])
            if (transition.tag == EPSILON && !visited[transition.to])
                q.push(transition.to);
    }
    //fill up the result with all the visited states
    for (size_t state = 0; state < visited.size(); state++)
        if(visited[state])
            res.append(state);
    
    return res;
}
BitSet Automaton::epsilonClosureBitSet(State state) const{

    //cannot get any closure in an automata with no states
    if(getStatesCount() == 0)
        return BitSet();

    Queue<State> q;
    BitSet visited(getStatesCount()); 

    q.push(state);

    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        visited[curr] = true;
        
        for (const Transition& transition : data[curr])
            if (transition.tag == EPSILON && !visited[transition.to])
                q.push(transition.to);
    }
    
    return visited;
}

unsigned Automaton::getFinalStatesCount() const{
    unsigned res = 0;
    for (size_t i = 0; i < finalStates.size(); i++)
        if(isFinalState(i)) res++;
    return res;
}
//DETERMIIZATION AND TOTALIZATION----------------------------------------------
void Automaton::determinize() {
    Automaton nfa = *this;
    //empty automaton doesnt need determination
    if(!nfa.getStatesCount())
        return;

    Automaton dfa;
    std::unordered_map<BitSet, State, bitset_hash> subsetToState; //mapping nfa states to dfa states
    Queue<BitSet> unprocessedSubsets; //here we process subsets
    BitSet startClosure = nfa.epsilonClosureBitSet(nfa.getStartState());
    
    //add start
    State dfaStartState = 0;
    dfa.addState(false); 
    dfa.changeStart(dfaStartState);
    subsetToState[startClosure] = dfaStartState;
    unprocessedSubsets.push(startClosure);
    
    //need to get the alphabet
    BitSet alphabet = nfa.getAlphabet();

    //bfs
    while (!unprocessedSubsets.empty()) {
        //extract curr subset
        BitSet currentSubset = unprocessedSubsets.front();
        unprocessedSubsets.pop();
        State currentDFAState = subsetToState[currentSubset];
        
        //check if the current dfa state should be end state
        for (State nfaState : currentSubset) {
            if (nfa.isFinalState(nfaState)) {
                dfa.addFinalState(currentDFAState);
                break;
            }
        }
        //check for each symbol
        for (unsigned char symbol : alphabet) {
            if (symbol == EPSILON) continue; // Skip epsilon transitions
            BitSet nextSubset;
            //get reachable states from currentSubset via symbol
            for (State nfaState : currentSubset) {
                for (const Transition& transition : nfa.getTransitions(nfaState)) {
                    if (transition.tag == symbol) {
                        Vector<State> closure = nfa.epsilonClosure(transition.to);
                        for (const State& state : closure)
                            nextSubset[state] = true;
                    }
                }
            }
            
            //no outgoing transitions from any of the elemets in currSubset
            if (nextSubset.none()) continue;
            
            //add newSubset if its not present as a state in the dfa 
            if (subsetToState.count(nextSubset) == 0) {
                State newDFAState = dfa.getStatesCount();
                dfa.addState(false); 
                subsetToState[nextSubset] = newDFAState;
                unprocessedSubsets.push(nextSubset);
            }
            
            //add the transition to the dfa
            dfa.addTransition(currentDFAState, subsetToState[nextSubset], symbol);
        }
    }
                
    *this = dfa;
}

void Automaton::totalize() {
    if (!isDFA()) 
        throw std::logic_error("Automata is not a DFA!");

    BitSet alphabet = getAlphabet();

    // create sink state if needed
    bool sinkStateCreated = false;
    State sinkState = getStatesCount(); // keep the index here in case we'll need it

    // go through each state and its transitions and see what tags were used
    for (size_t state = 0; state < getStatesCount(); ++state) {
        BitSet usedChars; // defaults to size 256

        for (const Transition& transition : data[state]) {
            usedChars[transition.tag] = true; // tracking used tags
        }

        // check for missing transitions
        for (unsigned char symbol : alphabet) {
            // add transition to sink state (if it exists)
            if (!usedChars[symbol]) {
                // create sink state in case it doesn't exist
                if (!sinkStateCreated) {
                    addState(false);
                    for (char s : alphabet)
                        addTransition(sinkState, sinkState, s);
                    sinkStateCreated = true;
                }
                // finally add the transition to the sink state
                addTransition(state, sinkState, symbol);
            }
        }
    }
}
#include "../../include/automaton/automaton.hpp"
#include "../../include/automaton/regex_utils.hpp"

namespace AutomataAlgorithms{
    //CONSTRUCTIONS-----------------------------------------------------
    Automaton intersection(const Automaton& a1, const Automaton& a2){
        Automaton result;
        std::unordered_map<std::pair<State, State>, State, pair_hash> stateMap; // Map to store state pairs and their indices
        Queue<std::pair<State, State>> stateQueue;
    
        State start1 = a1.getStartState();
        State start2 = a2.getStartState();
        std::pair<State, State> startPair = {start1, start2};
    
        //add starting pair
        stateMap[startPair] = 0; 
        result.addState(a1.isFinalState(start1) && a2.isFinalState(start2));
        result.changeStart(0);
        stateQueue.push(startPair);
    
        // standard bfs
        while (!stateQueue.empty()) {
            std::pair<State, State> curr = stateQueue.front();
            State s1 = curr.first, s2 = curr.second;
            stateQueue.pop();
    
            // Get transitions for both states
            Vector<Transition> transitions1 = a1.getTransitions(s1);
            Vector<Transition> transitions2 = a2.getTransitions(s2);
    
            // Go through all transitions
            for (Transition t1 : transitions1) {
                for (Transition t2 : transitions2) {
                    if (t1.tag == t2.tag) {//match tags
                        std::pair<State, State> nextPair = {t1.to, t2.to};
    
                        if (stateMap.count(nextPair) == 0) {//new state
                            State newMappedState = stateMap.size();
                            stateMap[nextPair] = newMappedState;
                            result.addState(a1.isFinalState(t1.to) && a2.isFinalState(t2.to));
                            stateQueue.push(nextPair);
                        }
                        //add tansitions
                        State nextIndex = stateMap[nextPair];
                        result.addTransition(stateMap[{s1, s2}], nextIndex, t1.tag);
                    }
                }
            }
        }
        return result;
    }
    
    Automaton concatenate(const Automaton& a1, const Automaton& a2) {
        Automaton result;
        //copy states into result
        for (size_t i = 0; i < a1.getStatesCount(); i++) 
            result.addState(false); //we dont want those end states
    
        size_t offset = a1.getStatesCount();
    
        for (size_t i = 0; i < a2.getStatesCount(); i++) 
            result.addState(a2.isFinalState(i)); //we want those end states
        
        //transfer all the transitions
        for (size_t i = 0; i < a1.getStatesCount(); i++) 
            for (const auto& transition : a1.getData()[i]) 
                result.addTransition(transition.from, transition.to, transition.tag);
    
        for (size_t i = 0; i < a2.getStatesCount(); i++) 
            for (const auto& transition : a2.getData()[i]) 
                result.addTransition(transition.from + offset, transition.to + offset, transition.tag);
    
        //connect a1 to a2 with an epsilon transition
        for (size_t i = 0; i < a1.getStatesCount(); i++) 
            if (a1.isFinalState(i))
                result.addTransition(i, a1.getStatesCount() + a2.getStartState(), EPSILON);  // epsilon transition to start of next automata
    
        //new start
        result.changeStart(a1.getStartState());
    
        return result;
    }
    
    Automaton kleeneStar(const Automaton& a) {
        Automaton result;
        //new start
        State newStartState = 0;
        result.addState(true); 
        //offset is 0 if base automata got no states
        size_t offset = a.getStatesCount() ? 1 : 0; 
        //copy other states and transitions
        for (size_t i = 0; i < a.getStatesCount(); i++) 
            result.addState(a.isFinalState(i)); //keep info
    
        for (size_t i = 0; i < a.getStatesCount(); i++) {
            Vector<Transition> currTransitions = a.getTransitions(i);
            for (const Transition& transition : currTransitions) 
                result.addTransition(transition.from + offset, transition.to + offset, transition.tag);
        }
        //epsilon transitions for end states
        for (size_t i = 0; i < a.getStatesCount(); i++) {
            if (a.isFinalState(i)) {
                //back to original start for repetition
                result.addTransition(i + offset, a.getStartState() + offset, EPSILON);
                //back to new start for termination
                result.addTransition(i + offset, newStartState, EPSILON);
            }
        }
        //connect starts
        result.addTransition(newStartState, a.getStartState() + offset, EPSILON);
    
        result.changeStart(newStartState);
        return result;
    }
    
    Automaton unionize(const Automaton& a1, const Automaton& a2){
        Automaton a3;
        State newStartState = 0;
        a3.addState(false);
    
        // copy states and transition
        for (size_t i = 0; i < a1.getStatesCount(); i++) 
            a3.addState(a1.isFinalState(i)); //copy end info
    
        for (size_t i = 0; i < a1.getStatesCount(); i++) 
            for (const Transition& transition : a1.getData()[i])
                a3.addTransition(transition.from + 1, transition.to + 1, transition.tag); // offset by 1
    
        //need offset for a2
        size_t offset = a1.getStatesCount();
        for (size_t i = 0; i < a2.getStatesCount(); i++) 
            a3.addState(a2.isFinalState(i)); //copy end state info
    
        for (size_t i = 0; i < a2.getStatesCount(); i++) 
            for (const Transition& transition : a2.getData()[i]) 
                a3.addTransition(transition.from + offset + 1, transition.to + offset + 1, transition.tag); // Offset by a1 state count + 1
    
        // add transition from new start to old starts
        a3.addTransition(newStartState, a1.getStartState() + 1, EPSILON);
        a3.addTransition(newStartState, a2.getStartState() + offset + 1, EPSILON);
    
        a3.changeStart(newStartState);
        return a3;
    }
    
    Automaton complement(const Automaton& a) {
        //determinize first
        Automaton res = a;
        if (!res.isDFA()) 
            res.determinize();
            
        //the totalize
        res.totalize();
    
        //swap end with non-end states
        for (size_t i = 0; i < res.getStatesCount(); i++)
            if(res.isFinalState(i))
                res.setFinalState(i, false);
            else
                res.setFinalState(i, true);
        
        return res;
    }
    
    Automaton fromRegex(const String& regex) {
        if (regex.empty())
            throw std::invalid_argument("regex is empty!");
        Stack<Automaton> operandStack;  
        Stack<char> operatorStack;
        
        int counter = 0;
        for (size_t i = 0; i < regex.size(); i++) {
            char c = regex[i];  
            if(c == ' ') //skip spaces
            continue;
            
            else if (isOperator(c)) { 
                //higher priority operators go first
                while (!operatorStack.empty() && getPriority(operatorStack.top()) >= getPriority(c)) 
                processOperator(operatorStack, operandStack);
                operatorStack.push(c);
            }
            else if (c == '(') {  
                operatorStack.push(c);
            }
            else if (c == ')') {  //process stack until (
                while (operatorStack.top() != '('){
                    processOperator(operatorStack, operandStack);
                }
                operatorStack.pop(); //pop the (
                }
                else { //add operand
                    // '/'adds next symbol to operandStack regardless of what it is
                    Automaton a;
                a.addState(false);  
                a.addState(true);
                BitSet transitionTags;
                if(c == '?'){ // '?' adds transition for every symbol of the alphabet
                    transitionTags = extractRegexAlphabet(regex);
                    if (transitionTags.none())
                        throw std::invalid_argument("the alphabet of this regex is empty");
                }
                else{    
                    if(c == '/' && (i+1) != regex.size()){
                        c = regex[++i];
                    }
                    transitionTags[c] = true;
                    
                }
                //add transition(s)
                for (char tag : transitionTags)
                    a.addTransition(0, 1, tag);
                
                operandStack.push(std::move(a));
            }
        }
    
        //process any remaining operators in the stack
        while (!operatorStack.empty())
            processOperator(operatorStack, operandStack);
        
        if (operandStack.size() != 1)
        throw std::runtime_error("Invalid regex: Operand stack does not contain a single result.");
        
        
        //the final automaton will be the only element left in the operand stack
        Automaton result = operandStack.top();
        operandStack.pop();
    
        result.determinize();
        return result;
    }
    //REGEX-------------------------------------------------------------
    String createRegex(const Automaton& a){
        Automaton dfa = a;
        if(!dfa.isDFA())
            dfa.determinize();
        
        State startState = dfa.getStartState();
        size_t n = dfa.getStatesCount();
        
        Vector<Vector<String>> regexTable(n, Vector<String>(n, ""));
        
        //populate regexTable with direct transitions
        for (size_t i = 0; i < n; i++) {
            for (const Transition& transition : dfa.getData()[i]) {
                if (!regexTable[transition.from][transition.to].empty()) 
                regexTable[transition.from][transition.to] += "+"; //union if there's already a transition
                regexTable[transition.from][transition.to] += transition.tag; // adding the transition label
            }
        }
        
        //apply the state elimination algorithm
        for (size_t k = 0; k < n; k++) {
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < n; j++) {
                    if (regexTable[i][k].empty() || regexTable[k][j].empty()) continue;
                    //handling self-loops
                    String loop = regexTable[k][k].empty() ? "" : "(" + regexTable[k][k] + ")*";
                    
                    //transition from i to j through k
                    String throughK = regexTable[i][k] + (loop.empty() ? "." : "." + loop + ".") + regexTable[k][j];
                    
                    // update regexTable[i][j] with union
                    if (!regexTable[i][j].empty())
                    regexTable[i][j] = "(" + regexTable[i][j] + "+" + throughK + ")";
                    else
                    regexTable[i][j] = throughK;
                }
            }
        }
        
        //combine all regexes leading from the start state to final states
        String result;
        for (size_t i = 0; i < n; i++) {
            if (dfa.isFinalState(i) && !regexTable[startState][i].empty()) {
                if (!result.empty()) 
                result += "+";
                result += regexTable[startState][i];
            }
        }
        // If the result is empty, there are no valid paths
        return result.empty() ? "∅" : result; // Use "∅" to represent no valid paths
    }
    
    //UTIL_ALGORITHMS-----------------------------------------
    Automaton createAndSaveAutomaton(const String& regex) {
        Automaton automaton = fromRegex(regex);
        automaton.rasterize("result");
    
        std::ofstream saveStream("data/save.txt");
        automaton.serialize(saveStream);
    
        return automaton;
    }
    //this has to go too
    void checkRecognizedLines(const Automaton& a, std::ifstream& stream) {
        unsigned recognizedLines = 0;
        char buffer[1024]; //temporary fixed-size buffer for reading lines
    
        while (stream.getline(buffer, sizeof(buffer))) { 
            // Process the line from the buffer
            String line(buffer);
            if (a.containsWord(line)) {
                recognizedLines++;
            }
        }
        std::cout << "Lines recognized by the automaton: " << recognizedLines << '\n';
    }
}

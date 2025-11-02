#include "../../include/automaton/regex_utils.hpp"

using namespace AutomataAlgorithms;

void processOperator(Stack<char>& operatorStack, Stack<Automaton>& operandStack) {
    char op = operatorStack.top();
    operatorStack.pop();
    Automaton a2 = operandStack.top();
    operandStack.pop();
    
    switch (op){
        case '.': {  
            Automaton a1 = operandStack.top();
            operandStack.pop();
            operandStack.push(concatenate(a1, a2));
            break;
        }
        case '+': {       
            Automaton a1 = operandStack.top();
            operandStack.pop();
            operandStack.push(unionize(a1, a2));
            break;
        }
        case '&': {  
            Automaton a1 = operandStack.top();
            operandStack.pop();
            operandStack.push(intersection(a1, a2));
            break;
        }
        case '*':
            operandStack.push(kleeneStar(a2));
            break;
    }
}

int getPriority(char op) {
    if (op == '*') return 3; 
    if (op == '.') return 2;  
    if (op == '+' || op == '&') return 1; 
    return 0;
}

BitSet extractRegexAlphabet(const String& regex){
    BitSet res;
    for (size_t i = 0; i < regex.size(); i++){
        char c = regex[i];

        if(isOperator(c) || c == '(' || c == ')' || c == '?' || c == ' ')
            continue;

        if(c == '/')
            c = regex[++i];
        res[c] = true;
    }
    return res;
}

bool isOperator(const char tag){
    switch (tag) {
        case '&': case '*': 
        case '+': case '.':
            return true;
        default:
            return false;
    }
}
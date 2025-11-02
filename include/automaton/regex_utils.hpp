#pragma once

#include "automaton.hpp" 

class Automaton; //forward declaration

void processOperator(Stack<char>& operatorStack, Stack<Automaton>& operandStack);
int getPriority(char op);
BitSet extractRegexAlphabet(const String& regex);
bool isOperator(const char ch);

g++ -c src/automaton/automaton.cpp -o build/automaton.o -Iinclude
g++ -c src/automaton/regex_utils.cpp -o build/regex_utils.o -Iinclude
g++ -c src/automaton/automaton_algorithms.cpp -o build/automaton_algorithms.o -Iinclude

ar rcs build/libautomaton.a build/automaton.o build/regex_utils.o build/automaton_algorithms.o
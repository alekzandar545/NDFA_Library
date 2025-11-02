g++ tests/regex_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/union_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/kleene_star_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/determinization_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/cross_section_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/contains_word_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/concatenation_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

g++ tests/complement_tests.cpp -Iinclude -Lbuild -lautomaton -o test.exe
call "test.exe"

if not exist build mkdir build
g++ src/main.cpp -Iinclude -Llibs -lautomaton -o main.exe
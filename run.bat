if not exist build mkdir build
call "create_library.bat"
call "compile.bat"
call "main.exe"
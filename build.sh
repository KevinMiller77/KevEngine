@echo off

echo Compiling...
g++ src/linuxmain.cpp -Iinclude -Llib -obin/linuxmain -lX11 -lGL -lGLU -lGLEW
echo Done compiling!
./bin/linuxmain run

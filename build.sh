@echo off

echo Compiling...
g++ src/linuxmain.cpp -Iinclude -Llib -obin/linuxmain -lX11 -lGL -lGLU -lGLEW
clear
echo Done compiling!
MESA_GL_VERSION_OVERRIDE=3.3 ./bin/linuxmain run

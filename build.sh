echo Compiling...
g++ src/linuxmain.cpp -Iinclude -Llib -o bin/linuxmain -lX11 -lGL -lGLU -lGLEW
echo Done compiling!
MESA_GL_VERSION_OVERRIDE=3.3 ./bin/linuxmain run

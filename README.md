# Just my future really
Welcome this beautiful game engine.

This is inteded as a learning project and hopefully the kickstart of my game development.

# What is currently supported?

At the moment the engine supports the following

  *  Layers -- Contain a renderer and the renderables to render each update. Contains a projection matrix
  *  Groups -- A renderable containing renderables. Contains a Model Matrix_
  *  Labels -- A string renderables
     *  Fonts! (and a font manager)  
  *  Texture manager
  *  Shader manager
  
# Using the example

1) *git clone https://KevinMiller77/KevEngine*
2) *cd KevEngine*
3) *./build*  __(Both windows and linux)__
4) *../bin/KevEngine* __(Both windows and linux)__

# Using KevEngine in your projects

1) *git clone https://KevinMiller77/KevEngine*
2) *cd KevEngine*
3) *./build AS_DEPENDANCY* __(Both windows and linux)__
4) Copy the files and directories inside of "KevEngine/out/" into your projects root dir.
5) Override the following members from the KevEngine class
   - OnGameStart()  Gets called once when you run the game and anytime to engine is restarted
   - Draw()         Gets called every frame
   - OnTick()       Gets called 60 times a second
   - ResetEngine()  Gets called when the engine takes in a restart event


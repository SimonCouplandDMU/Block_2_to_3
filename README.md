# Enhancement Week Activity Level 6 - blocks 2 to 3

## Getting Started

Run the buildVS2022Projects.bat file, either from the command line or by double clicking on it.  This will run the premake build system (an alternative to CMake) and create Application.sln.  You can open this file in VS2022 and start looking through the code.  Whenever you add files to your project I strongly recommend you rerun the buildVS2022Projects.bat file to make sure you have add the files correctly.  I'd also recommend you hit the "show all files" button in Visual Studio for both the Application and Engine projects.

## Simple 2D Game with Custom Shaders and ECS

This code is intended for students on CGP and DMU.  It relates to the shader and C++ work you've already done.  The code is in quite an old style and lacks the refinment of the modern C++ you been working with lately.  However, it has a basic 2D renderer with custom shaders which you can customise with things like post-processing effects or a particle system.  You can also use compute shaders for this work.  The code uses an ECS libary called EnTT. A number of simple components have been made for you and a version of the classic game Breakout is currently implemented using these components.  The Box2D physics library has also been included to give you good quality 2D physics. The presentation of rendered components is seperated into layers.  At the moment there are two layers.  The game layer holds the game related entities and renders the game world at a decent size. **Box2D use metres as units meaning a human character should be around 2 units high, hence the camera view of of 10.24 X 8.** The camera doesn't have to be fixed and could easily be an enitity with a script attached to control it. A simple data system has been supplied to allow you to hold adaa across layers, these can easily be extended with other type or refactored with templates.

## What Should You Do?

In small groups come up with an idea for or copy an existing 2D game which makes ideally use of physics.  I would recommend half the team focuses on gameplay and half on graphics.  It makes sense to make use of the physics engine provided.  Once you have an idea, read through the existing code in application and think about what enitities you'll need and what componenets these entities will need. This will give you a basic gameplay project backlog to start on. For the graphics you need decide for yourselves what you like to do and whether you can relaisacally achieve that, if not dial it back a bit.

Good luck!

# GameDev
Wrapper written around C++ for building SDL based items.

## Build
- Download the SDL2 package from [here](https://www.libsdl.org/download-2.0.php).
- Extract it to a location.
- Create a new project with the .cpp files under 'Source' and header files under 'Header'
- Add the include directory in the extracted location to 'Additional Include Directories'. 
	- For Visual Studio, this can be done under 'Properties' -> 'C/C++' -> 'General'
- Add the libs 'SDL2.lib' and 'SDL2main.lib' to the list of 'Additional dependencies'
	- For Visual Studio, this can be done under 'Properties' -> 'Linker' -> 'Input'
- Add the library folder to 'Additional library directories' so that the compiler can find out where SDL2.lib and SDL2main.lib resides.
	- For Visual Studio, this can be done under 'Properties' -> 'Linker' -> 'General'
- Finally copy the SDL2.dll available under the same library folder to your project location so that your project can link to this DLL.

## How to use
- Setup the build environment as mentioned above
- Include 'GameBase.h' and 'GameWindows.h'.
- Initialize main with object of GameBase such as below which will setup and teardown SDL for you.
	- `GameBase gb;`
- Create a GameWindow object which will handle SDL Window. 
	- `GameWindow gWin1(int top, int left, int width, int height, "Name for window")`
- Fill the window with a given color by calling fillWindowWithColor.
	- `gWin1.fillWindowWithColor(int red, int green, int blue);`
- Load a image onto the window based on path of image
	- `gWin1.loadImage(string pathToImage);`
- Update the window surface after all operations to reflect changes
	- `gWin1.updateWindowSurface();`
- Also pause execution by calling pause
	- `pause(int milliseconds);`
- To get the last event clicked, call getEvent which returns a value for enum GameEvents;
	- `gWin1.getEvent();`
 

## TODO
- Update Readme on using hardware rendering
- Update Readme on using SDL_image.h class
- Refactor code to remove redundant code
- Add more events like the letter WASD and QE.
- Also, add event handler support where one can pass a function for a specific event click instead of handling it explicitly.

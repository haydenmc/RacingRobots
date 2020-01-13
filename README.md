# Racing Robots!

## Building

0. Install [Build Tools for Visual Studio 2019](https://visualstudio.microsoft.com/downloads/) (located in "All Downloads" -> "Tools for Visual Studio 2019")
0. Download and extract [SDL 2 Development Libraries](https://www.libsdl.org/download-2.0.php), [SDL_image Development Libraries](https://www.libsdl.org/projects/SDL_image/), and [SDL_ttf Development Libraries](https://www.libsdl.org/projects/SDL_ttf/).
1. Open VS Command Prompt x64
2. `set SDLPATH=C:\Path\To\SDL\Root\Dir`
3. `set SDLIMAGEPATH=C:\Path\To\SDL_Image\Root\Dir`
4. `set SDLTTFPATH=C:\Path\To\SDL_TTF\Root\Dir`
5. `code .`
6. Create `bin` and `obj` dirs
7. Build (`Ctrl`+`Shift`+`B`)
8. Copy DLLs from `%SDLPATH%\lib` to the `bin` folder
9. Copy DLLs from `%SDLIMAGEPATH%\lib` to the `bin` folder
10. Copy DLLs from `%SDLTTFPATH%\lib` to the `bin` folder
11. Run
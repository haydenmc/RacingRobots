# Racing Robots!

## Building

0. Install [Build Tools for Visual Studio 2019](https://visualstudio.microsoft.com/downloads/) (located in "All Downloads" -> "Tools for Visual Studio 2019")
0. Download and extract [SDL 2 Development Libraries](https://www.libsdl.org/download-2.0.php), [SDL_image Development Libraries](https://www.libsdl.org/projects/SDL_image/), and [SDL_ttf Development Libraries](https://www.libsdl.org/projects/SDL_ttf/).
0. Clone [SDL2gfx](https://github.com/haydenmc/sdl2gfx)
1. Open VS Command Prompt x64
2. Build SDL2gfx with `windowsbuild.cmd`
3. `set SDLPATH=C:\Path\To\SDL\Root\Dir`
4. `set SDLIMAGEPATH=C:\Path\To\SDL_Image\Root\Dir`
5. `set SDLTTFPATH=C:\Path\To\SDL_TTF\Root\Dir`
6. `set SDLGFXPATH=C:\Path\To\SDL2GFX\Root\Dir`
7. `code .`
8. Create `bin` and `obj` dirs
9. Build (`Ctrl`+`Shift`+`B`)
10. Copy DLLs from `%SDLPATH%\lib` to the `bin` folder
11. Copy DLLs from `%SDLIMAGEPATH%\lib` to the `bin` folder
12. Copy DLLs from `%SDLTTFPATH%\lib` to the `bin` folder
13. Run
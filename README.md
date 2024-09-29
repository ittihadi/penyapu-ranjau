## Penyapu Ranjau

<!-- ![$(Game Title)](screenshots/screenshot000.png "$(Game Title)") -->

A collection of minesweeper games to pass the time made using the raylib framework

### Features

 - Multiple game modes, including:
     - Normal Minesweeper
     - Hexagon Minesweeper
 - Playable with keyboard only or mouse only

### Controls

Mouse:
 - Left Mouse Button to reveal the hovered cell
 - Right Mouse Button to flag the hovered cell
 - Middle Mouse Button to check the hovered cell

Keyboard:
 - Arrow Keys to move around pointer
 - Z to reveal hovered cell
 - X to flag hovered cell

<!-- ### Screenshots -->

<!-- _TODO: Show your game to the world, animated GIFs recommended!._ -->

### Developers

 - Ittihadi - Programmer, Artist
 <!-- - $(Developer 02) - $(Role/Tasks Developed) -->
 <!-- - $(Developer 03) - $(Role/Tasks Developed) -->

<!-- ### Links -->

<!--  - YouTube Gameplay: $(YouTube Link) -->
<!--  - itch.io Release: $(itch.io Game Page) -->
<!--  - Steam Release: $(Steam Game Page) -->

### Building

#### Visual Studio

- After extracting the zip or cloning from github, the parent folder `penyapu-ranjau` should exist in the same directory as `raylib`, so the folder structure should look like the following:
    - Some parent directory
        - `penyapu-ranjau`
            - This game project directory
        - `raylib`
            - The contents of https://github.com/raysan5/raylib
- If using Visual Studio, open `projects/VS2022/raylib-game-template.sln`
- Select on `raylib_game` in the solution explorer, then in the toolbar at the top, click `Project` > `Set as Startup Project`
- Now you're all set up!  Click `Local Windows Debugger` with the green play arrow and the project will run.

#### CMake

- Clone or download and extract the zip of this project
- Type the following command in the project root folder:

```sh
cmake -S . -B build
```

> if you want with debug symbols put the flag `-DCMAKE_BUILD_TYPE=Debug`

- After CMake configures the project, build it with:

```sh
cmake --build build
```

- Inside the build folder is another folder named `penyapu-ranjau` containing the executable and resources folder.

### License

This game sources are licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

<!-- $(Additional Licenses) -->

*Copyright (c) 2024 Ittihadi R (ittihadi)*

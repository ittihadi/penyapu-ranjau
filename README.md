## Penyapu Ranjau

<!-- ![$(Game Title)](screenshots/screenshot000.png "$(Game Title)") -->

A collection of minesweeper esque games to pass the time

<!-- ### Features -->

<!--  - $(Game Feature 01) -->
<!--  - $(Game Feature 02) -->
<!--  - $(Game Feature 03) -->

<!-- ### Controls -->

<!-- Keyboard: -->
<!--  - $(Game Control 01) -->
<!--  - $(Game Control 02) -->
<!--  - $(Game Control 03) -->

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

- Extract the zip of this project
- Type the follow command:

```sh
cmake -S . -B build
```

> if you want with debug symbols put the flag `-DCMAKE_BUILD_TYPE=Debug`

- After CMake config you project build:

```sh
cmake --build build
```

- Inside the build folder are another folder (named the same as the project name on CMakeLists.txt) with the executable and resources folder.

### License

This game sources are licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

<!-- $(Additional Licenses) -->

*Copyright (c) 2024 Ittihadi R (ittihadi)*

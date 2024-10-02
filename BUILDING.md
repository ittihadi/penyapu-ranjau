## Building

There are two ways to build this project, using Visual Studio or CMake

### Visual Studio

- After extracting the zip or cloning from github, the parent folder `penyapu-ranjau` should exist in the same directory as `raylib`, so the folder structure should look like the following:
    - Some parent directory
        - `penyapu-ranjau`
            - This game project directory
        - `raylib`
            - The contents of https://github.com/raysan5/raylib
- If using Visual Studio, open `projects/VS2022/raylib-game-template.sln`
- Select on `raylib_game` in the solution explorer, then in the toolbar at the top, click `Project` > `Set as Startup Project`
- Now you're all set up!  Click `Local Windows Debugger` with the green play arrow and the project will run.

### CMake

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


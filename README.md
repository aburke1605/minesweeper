# minesweeper

To compile on Ubuntu:
```bash
$ sudo apt-get install libsfml-dev
$ g++ -c src/main.cpp -o minesweeper.o
$ g++ minesweeper.o -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system
$ ./minesweeper
```

To set up SFML for working on Visual Studio:
 * download and extract SFML-2 from https://www.sfml-dev.org/download/sfml/2.6.2/ (64-bit)
 * copy the `lib/` and `include/` folders to the directory where your `.sln` file is located
 * in VS, change the **Solution Platform** to **x64** in the toolbar
 * build the solution (`Ctrl+Shift+B`) with **Solution Configuration** in both **Debug** and **Release** modes
   * this creates `x64/Debug/` and `x64/Release/` folders in your solution directory
 * copy:
   * the debug files (those with `-d` in the name) from the `bin/` folder of the downloaded SFML directory to `x64/Debug/`
   * the release files (the same files but without `-d`) to `x64/Release/`
   * `openal32.dll` to both `x64/Debug/` and `x64/Release/`
 * in VS:
   * right-click the solution in the **Solution Explorer** and select **Properites**
   * ensure **Configuration** is set to **All Configurations** and **Platform** to **All Platforms**
   * go to **Configuration Properties $\rightarrow$ C/C++ $\rightarrow$ General $\rightarrow$ Additional Include Directories $\rightarrow$ <Edit...>**, enter "`$(SolutionDir)\include`" and click **OK**
   * go to **Configuration Properties $\rightarrow$ Linker $\rightarrow$ General $\rightarrow$ Additional Library Directories $\rightarrow$ <Edit...>**, enter "`$(SolutionDir)\lib`" and click **OK**
   * go to **Configuration Properties $\rightarrow$ Linker $\rightarrow$ Input $\rightarrow$ Additional Dependencies $\rightarrow$ <Edit...>**, enter:
     *  "`sfml-system.lib;`"
     *  "`sfml-window.lib;`"
     *  "`sfml-graphics.lib;`"
     *  "`sfml-audio.lib;`"
     *  "`sfml-network.lib;`" \
    and click **OK** and **Apply**
   * change **Configuration** to **Debug**
   * go to **Configuration Properties $\rightarrow$ Linker $\rightarrow$ Input $\rightarrow$ Additional Dependencies $\rightarrow$ <Edit...>**, enter:
     *  "`sfml-system-d.lib;`"
     *  "`sfml-window-d.lib;`"
     *  "`sfml-graphics-d.lib;`"
     *  "`sfml-audio-d.lib;`"
     *  "`sfml-network-d.lib;`" \
    and click **OK** and **Apply**


It can also be compiled and ran in a browser using Emscripten with instructions below.

First install Emscripten:
```bash
$ git clone git@github.com:emscripten-core/emsdk.git
$ cd emsdk
$ ./emsdk install 3.1.67
$ ./emsdk activate 3.1.67
$ source ./emsdk_env.sh
```

Then get this fork of SFML:
```bash
$ git clone git@github.com:Zombieschannel/SFML.git
$ cd SFML
$ git switch SFML-2.6.x-EMCC
```

Build and install static SFML libraries somewhere (my `cmake` version is 3.24.0):
```bash
$ mkdir build && cd build
$ emcmake cmake .. -DBUILD_SHARED_LIBS=false
$ emmake make -j 8
$ cmake --install . --prefix=path/to/somewhere/SFML
```

and the debug libraries too:
```bash
$ emcmake cmake -DCMAKE_BUILD_TYPE=Debug .
$ emmake make -j 8
$ cmake --install . --prefix=path/to/somewhere/SFML
```


Now go back to this repo and build with the installed libraries: \
!!! NEED TO FIRST EDIT `CMakeLists.txt` TO UPDATE THE PATH TO SFML ON L46 !!!
```bash
$ cd path/to/minesweeper
$ mkdir build && cd build
$ emcmake cmake ..
$ emmake make
```

The compiled game can then be run in any browser, for example:
```bash
$ emrun Project.html --browser /mnt/c/Program\ Files\ \(x86\)/Microsoft/Edge/Application/msedge.exe
```

Do `$ emrun --list-browsers` to see a list of identified browsers on your machine

# Building with CMake

  - Install Qt Framework, install CMake. Create or add to existing environment variable CMAKE_PREFIX_PATH path to Qt root directory( for instance, if  you've installed  Qt on C drive - the root directory would be __C:/Qt__
  - Don't forget to install x32 or x64 compiler (for example  MSVC 2015/2017 )and add  it's path to environment variable PATH. 
  - Download sources and create folder __build__ with subfolders __x32__ and __x64__
## Configure x64 version
  - Navigate to folder __build/x64__ and open console/powershell. 
  - Configure project. Execute command for configure x64-debug version

```
   cmake -G "Visual Studio 15 2017 Win64"  ../.. -DCMAKE_PREFIX_PATH=PATH_TO_x64_COMPILER
``` 

## Configure x32 version
  - Navigate to folder __build/x32__ and execute

```
cmake -G "Visual Studio 15 2017" ../..-DCMAKE_PREFIX_PATH=PATH_TO_COMPILER
```
Where PATH_TO_COMPILER is full path to compiler's bin. For instance , command for msvc2015 and Qt 5.11.0 may be:
    
```
cmake -G "Visual Studio 15 2017" ../..-DCMAKE_PREFIX_PATH=C://Qt//5.11.0//msvc2015//
```

For x64 version, PATH_TO_x64_COMPILER may be:

```
cmake -G "Visual Studio 15 2017 Win64"  ../.. -DCMAKE_PREFIX_PATH=C://Qt//5.11.0//msvc2017_64//
```

## Build project
  - Commands must be executed in build directory (build/x32 or build/x64) after succesful configure project with CMake tool.
  - For builduing Debug version( builds by default ) execute command in directory:
 
```
cmake --build .
```
  - For building Release version execute:

```
cmake --build . --config Release
```



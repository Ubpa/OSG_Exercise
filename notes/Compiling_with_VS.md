# Windows

##Compiling with Visual Studio

> [Article Path](http://www.openscenegraph.org/index.php/documentation/platform-specifics/windows/37-visual-studio)

Follows are details on usage of OpenSceneGraph from source packages. These are useful if you want to always stay up to date with the newest OSG sources from the [github repository,](https://github.com/openscenegraph/OpenSceneGraph) or to use an OSG release that has no binaries. If you don't want this, you can probably use [precompiled binaries from the Downloads page](http://www.openscenegraph.org/index.php/download-section/stable-releases). 

Subpages:
[Help for compiling specific optional plugins](http://www.openscenegraph.org/index.php/documentation/platform-specifics/windows/38-visual-studio-plugins)
[Instructions when using older Visual Studio versions (6.0)](http://www.openscenegraph.org/index.php/documentation/platform-specifics/windows/39-older-visual-studio-versions)

### **Compiling with Visual Studio .NET**

(Note: These instructions are valid for Visual Studio .NET 2005 (8.0) and Visual Studio Express 2005 (see below), but they should also apply to Visual Studio .NET 2003 (7.0) or to Visual Studio .NET 2008 (9.0).)

### **Initial setup**

The project files are set up so that if you have the dependencies in the same base directory as the OpenSceneGraph sources, then it will find them. Thus, the suggested directory structure is:

```
\OpenSceneGraph-VERSION......replace VERSION by 2.8 or SVN or whatever
    \3rdParty................put the contents of the 3rdParty zip file in here
    \OpenSceneGraph
```

In the `OpenSceneGraph` directory, see [the Downloads page](http://www.openscenegraph.org/index.php/download-section) and download the sources for the version you're interested in, or check out the sources from the [github repository,](https://github.com/openscenegraph/OpenSceneGraph)

In the `3rdParty` directory, see [the Dependencies page](http://www.openscenegraph.org/index.php/download-section/dependencies) and download the dependencies for your platform. Place them so that the bin, lib etc. directories are directly under `OpenSceneGraph-VERSION\3rdParty` .

### **Generating Project & Solution files with CMake**

Once the sources and dependencies are in place you need to generate the Visual Studio solution and project files. This is done with CMake. Download it at <http://www.cmake.org/HTML/Download.html>.

Start the CMake GUI once it's installed, and select root `OpenSceneGraph` directory in the "Where is the source code" field. The same directory needs to be put into the "Where to build the binaries" field. If you like to do out-of-source builds, you can add `\build` to the end. Then click Configure.

You can then customize your build. The red lines in the CMake window indicate new variables that you may want to fill out or change, but most are optional. Some variables will be filled in automatically (such as `ACTUAL_3RDPARTY_DIR`, if you followed the directory structure above). I typically enable `BUILD_OSG_EXAMPLES` and **set `CMAKE_INSTALL_PREFIX` to the OpenSceneGraph directory** so that the binaries are installed in `OpenSceneGraph\bin`. You can also set it to somewhere else if you want to keep your source tree clean.

Note: In the permission-restricted environment of Windows Vista and later, do not set CMAKE_INSTALL_PREFIX to be a restricted folder like "Program Files". The make process will not be able to elevate permissions sufficiently to write to the destination, and will fail (typically while installing the first component, OpenThreads, with an error like "file INSTALL cannot copy file OpenThreads.dll").

Check if the dependencies you have are detected - if not fill in the variables manually. If you need to fill in some variables manually, you may need to show "Advanced" variables (with the drop-down at the top of the window) and make sure all relevant variables are set correctly for a given dependency. Any plugins or examples for which you don't have the dependencies will just not be part of the generated project files, which is cleaner than it was before (the projects would be there but just refuse to build, which resulted in lots of noise when building for things you knew would not build anyway).

Once your build configuration is to your liking, click Configure until the Generate button is enabled, then click that. Once it's done generating the project files, you can close CMake.

### **Building with Visual Studio**

Open the generated `OpenSceneGraph.sln` file, which will be in the directory you entered under "Where to build the binaries" (eg. `OpenSceneGraph\build`), with Visual Studio. Select your desired build type (Debug, Release, RelWithDebugInfo, MinSizeRel) and press F7 for "Build Solution". Assuming everything builds correctly, you can then right-click on the INSTALL project and build that, which will copy the compiled files to the correct directories (based on what you set `CMAKE_INSTALL_PREFIX` to). Before that, the compiled files all reside in the build directory, and I don't recommend you use them from there.

Just to reiterate: **Always build the INSTALL project**. The locations where the files are copied to as part of the INSTALL target are the correct locations from where you should use them (`bin\` for application executables and DLLs, `lib\` for libraries, `include\` for headers, and `share\OpenSceneGraph\bin\` for example executables). See "Environment variables" below for some tips to set up your build environment for your own project to use the files from the correct locations.

### **Notes**

#### COMPILATION TIME

A word of warning, **the first time you compile from source it will take some time**. After that, if you update an SVN checkout for example, it will **compile incrementally (only what changed)** so that's quite a bit faster.

#### ALWAYS REGENERATE AFTER UPDATES

**You should regenerate the project files with CMake each time you update from SVN or update to a newer snapshot of the source code.** That will make sure that a) any new build configuration options added to the CMake build files will be taken into account, and b) any new files will be included in the VS projects and compiled correctly. You can regenerate the build files by just opening the root `CMakeLists.txt` in the CMake GUI and setting the build directory to the same thing you had before (`OpenSceneGraph\build`, for example), that way any settings you had made will still be there. Just click Configure then Generate, open the `OpenSceneGraph.sln` and build.

#### FREETYPE PLUGIN

If have the 3rdparty libraries installed, the BUILD_OSG_PLUGINS is ON in your CMake file and the FREETYPE_LIBRARY_DEBUG path is found it might still happen that the project files for Freetype plugins or not built. Select "Show Advanced Values" in CMake and copy the directory found in FREETYPE_INCLUDE_DIR to FREETYPE_INCLUDE_DIR_freetype2 and FREETYPE_INCLUDE_DIR_ft2build.

#### CLEANUP THE CMAKE CACHE

Finally, note that from time to time, to see new settings, you will need to delete the CMakeCache.txt file in the `build` directory, which will also erase your settings... This should be rare though.

### Extensionless headers and syntax highlighting on Visual Studio 2003/2005/2008

In the OSG sources, in the `PlatformSpecifics\Windows` directory, there is a text file `VisualStudio_Syntax_Highlighting.txt` in which you can find instructions to get syntax highlighting on extensionless header files. It basically says:

Go to Tools-Options, then Text Editor-File Extension, check "Map Extensionless Files To" at the bottom and select "Microsoft Visual C++" in the list to the right.

### Starting a new project

There are two basic ways to start a new project using the OSG.

Create a new solution and project, and add the OSG libs as dependencies

Pros:

- Keeps everything separate, you can keep a tight control over the files in your project.
- If your own project is in SVN, it won't conflict with the OSG SVN.
- It's easy to distribute your project.

Cons:

- If you need to modify the OSG or look something up, you need to open the OSG's workspace/solution separately.

I normally start the project by copying `OpenSceneGraph\applications\osgViewer\osgViewer.cpp` into my new project's src directory, and compiling that. If that doesn't compile and run, there's a problem. See "Environment Variables" below for how to set up the compiler's include and library search paths easily.

### **Create a project directly in the OSG workspace / solution**

Pros:

- If you have to modify OSG itself for your project, the Visual Studio dependency check will recompile what is needed automatically.
- You can quickly switch from the project on which you're working to the OSG code itself.
- You can examine code for any src/example easily.

Cons:

- Your OSG workspace/solution will quickly become crowded once you start adding lots of your projects to it (as if it wasn't enough already...).
- When you regenerate the build files with CMake, you will have to re-add your project(s) to it.
- It's hard to separate your project from the OSG for distribution, so the other way is "cleaner".
- You can't keep your project in SVN if your OSG directories are also from SVN, unless you copy your project's files somewhere else, in which case why don't you just use the first method instead of having to do both?

I guess you can see that I don't recommend this way of doing. The OSG workspace/solution is already so big as it is, I think it's best to keep your mind uncluttered by creating a separate project for your own stuff. The rest of this guide is based on using the first option.

### **Environment variables**

If you select the first method, a way to simplify things and to make your project files work on multiple different machines is to use some standard environment variables. I use the following:

```
OSG_ROOT points to the base of the OSG file structure (the directory that contains include, src etc. subdirectories)
OSG_BIN_PATH = %OSG_ROOT%\bin
OSG_INCLUDE_PATH = %OSG_ROOT%\include
OSG_LIB_PATH = %OSG_ROOT%\lib
OSG_SAMPLES_PATH = %OSG_ROOT%\share\OpenSceneGraph\bin
OSG_FILE_PATH = ???\OpenSceneGraph-Data-X.X
```

Then, add `%OSG_BIN_PATH%` and `%OSG_SAMPLES_PATH%` to your `PATH` environment variable. That way, not only can you run examples easily, but the latest DLLs will always be found. When starting an application, Windows looks for the required DLLs first in the executable's directory, then in the `PATH`.

Make sure you restart Visual Studio if it was open when you added/changed these environment variables, so that it picks up te changes.

In your project's properties, use those environment variables to get Visual Studio to find the OSG libraries. Here are the settings I use:

```
Properties - C/C++ - General - Additional Include Directories = $(OSG_INCLUDE_PATH)
Properties - C/C++ - Preprocessor - Preprocessor Definitions = WIN32;_WIN32;NDEBUG
Properties - Linker - General - Additional Library Directories = $(OSG_LIB_PATH)
Properties - Linker - Input - Additional Dependencies = (any OSG library your project needs - for example: osg.lib osgGA.lib osgDB.lib osgViewer.lib osgText.lib osgUtil.lib OpenThreads.lib)
```

Remember to do the same thing in your project's Debug configuration, but add a `d` to the end of the OSG and OpenThreads library names (`osg.lib` becomes `osgd.lib` and so on). Also change `NDEBUG` to `_DEBUG` in the Preprocessor Definitions.

Once that's done, your project should be able to compile, link and run. If not, you can test your paths in a console (Start-Run, type `cmd`, press enter), by for example typing `echo %OSG_LIB_PATH%` or `dir %OSG_LIB_PATH%`. With those commands you should be able to see what is wrong.

### Important note about plugins

Once in a while, we get a message on the mailing list asking why the version number is added to the bin\osgPlugins directory name. Normally, the reason they ask is that after updating their copy of OSG, they had to modify their project files or their `PATH` to change the version number to point to the new directory.

There is **never** a need to add that directory to your library search paths or `PATH` environment variable. The OSG knows how to find the plugins by itself. In general, it will try to add `osgPlugins-<version>` to the directories in your `PATH` until it finds the right one. And since it knows its own version, it will find the right plugins directory.

If you had to add that directory to your `PATH`, for example in order to get examples to load the .osg files (cow.osg for example), that means that you didn't build the INSTALL target after compiling OSG. In that case, the plugins will reside in directories like `...\OpenSceneGraph\build\lib\osgPlugins-<version>\release`. So the problem is not the version added to the directory name, it's the `lib` instead of `bin`, and the `release` subdirectory. That's because CMake builds DLLs in the `lib` tree, and then the INSTALL target copies them to the `bin` tree, more specifically to `...\OpenSceneGraph\bin\osgPlugins-<version>`. And since `...\OpenSceneGraph\bin` is on your `PATH`, OSG will find them fine.

More generally, you should **never** have to put a reference to a subdirectory of the `build` directory into your environment variables. That is just a temporary location where things get built. Once the INSTALL target is run, the files will be in their final locations, which are `bin\` for application executables and DLLs, `lib\` for libraries, `include\` for headers, and `share\OpenSceneGraph\bin\` for the example executables.
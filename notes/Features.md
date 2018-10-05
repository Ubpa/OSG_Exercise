# Features

## Usage and Markets

The OpenSceneGraph is ==open source==, ==real-time== graphics middle-ware used by application developers in fields that range from visual simulation (flight, marine, vehicle, space simulator) to virtual and augmented reality, to medical and scientific visualisation, to education and games. 

## Cross Platform

The OpenSceneGraph is cross platform running on small devices such as embedded graphics platforms to phones, tablets that use OpenGL ES,  to laptops and desktops using OpenGL all the way up to dedicated image generator clusters used in full scale simulators and immersive 3D displays.

## Licensing

The OpenSceneGraph is published under the OpenSceneGraph Public License, which is a relaxation of the Less GNU Public License (==LGPL==) that permits usage in commercial application that require static linking or embed systems.

## Technology

The OpenSceneGraph is written in ==Standard C++==, taking advantage of the standard template library (==STL==) for containers.  The software uses ==the scene graph approach== to representing 3D worlds as a graph of node that logical and spatially group subgraphs for behaviour and high performance. 

==OpenGL 1.0 through to OpenGL 4.2, and OpenGL ES 1.1 and 2.0== are supported making it possible to support both old hardware and operating systems through to the latest mobile devices and all the features of cutting edge desktop graphics systems thanks to the software run time extension checking.

==Design Patterns== are used throughout the software making it easier to maintain and understand how our software works as well as providing a good example of usage. The software is kept ==modular and extensible== enabling end users to only utilize the components they need and to allow customisation when required.

The key strengths of OpenSceneGraph are its performance, scalability, portability and the productivity gains associated with using a fully featured scene graph, in more detail:

- **Performance**
  Supports ==view-frustum culling==, ==occlusion culling==, ==small feature culling==, Level Of Detail (==LOD==) nodes, ==OpenGL state sorting==, ==vertex arrays==, ==vertex buffer objects==, OpenGL ==Shader== Language and ==display lists== as part of the core scene graph. These together make the OpenSceneGraph one of the highest performance graphics toolkit available. The OpenSceneGraph also supports easy customization of the drawing process, such as implementation of Continuous Level of Detail (==CLOD==) meshes on top of the scene graph (see Virtual Terrain Project and Delta3D).

- **Productivity**
  The core scene graph ==encapsulates the majority of OpenGL functionality== including the latest extensions, provides ==rendering optimizations== such as culling and sorting, and ==a whole set of add-on libraries== which make it possible to develop high-performance graphics applications very rapidly. The application developer is freed to concentrate on content and how that content is controlled rather than low level coding. 

  Combining lessons learned from established scene graphs like Performer and Open Inventor, with modern software engineering methods like Design Patterns, along with a great deal of feedback early on in the development cycle, it has been possible to design a library that is clean and extensible. This has made it easy for users to adopt to the OpenSceneGraph and to integrate it with their own applications.

- **Database loaders**
  For reading and writing databases the database library (==osgDB==) adds support for a wide variety of database formats via ==an extensible dynamic plugin mechanism== - the distribution now includes 55 separate plugins for loading various 3D database and image formats. 

  ==3D database loaders== include COLLADA, LightWave (.lwo), Alias Wavefront (.obj), OpenFlight (.flt), TerraPage (.txp) including multi-threaded paging support, Carbon Graphics GEO (.geo), 3D Studio MAX (.3ds), Peformer (.pfb), AutoCAd? (.dxf), Quake Character Models (.md2). Direct X (.x), and Inventor Ascii 2.0 (.iv)/ VRML 1.0 (.wrl), Designer Workshop (.dw) and AC3D (.ac) and the native .osg ASCII format. 

  ==Image loaders== include .rgb, .gif, .jpg, .png, .tiff, .pic, .bmp, .dds (include compressed mip mapped imagery), .tga and quicktime (under OSX). 

  ==A full range of high quality, anti-aliased fonts== can also be loaded via the freetype plugin, and image based fonts can be loaded via the .txf plugin. 

  Users can also generate large scale geospatial (multi GB) terrain databases via the companion project (VirtualPlanetBuilder), and use the OpenSceneGraph's native database paging support to view these database.

- **Node Kits**

  The scene graph also has a set of Node Kits which are separate libraries that can be compiled in with your applications or loaded in at runtime. NodeKits available with OpenSceneGraph distribution are:

  - osgParticle - for particle systems
  - osgText - for high quality anti-aliased text
  - osgFX - special effects framework
  - osgShadow - shadow framework
  - osgManipulator - 3d interactive controls
  - osgSim - visual simulation centric effects
  - osgTerrain - terrain rendering
  - osgAnimation - character and rigid body animation
  - osgVolume - high quality volume rendering (with Dicom plugin for support of medical datasets)

- **Portability**
  The core scene graph has been designed to ==have minimal dependency on any specific platform==, requiring little more than Standard C++ and OpenGL. This has allowed the scene graph to be rapidly ported to a wide range of platforms - originally developed on IRIX, then ported to Linux, then to Windows, then FreeBSD, Mac OSX, Solaris, HP-UX, AIX, PlayStation2 and even iOS and Android! 

  The core scene graph library is completely ==windowing system independent==, which makes it easy for users to add their own window-specific libraries and applications on top. In the OpenSceneGraph distribution the osgViewer library provides native windowing support under Windows (Win32), Unices (X11) and OSX (Carbon). The osgViewer library can also be easily integrated with other windowing toolkits, such as Qt, GLUT, FLTK, SDL, WxWidget, Cocoa and MFC. Examples of integration with these toolkits are included in the OpenSceneGraph distribution.

- **Scalability**
  The scene graph will not only run on portables all the way up to high end multi-core, multi-gpu systems and cluster. This is possible because the core scene graph supports multiple graphics contexts for both OpenGL display lists and texture objects, and the cull and draw traversals have been designed to ==cache rendering data locally and use the scene graph almost entirely as a read-only operation==. This allows multiple ==cull-draw pairs== to run on multiple CPU's which are bound to multiple graphics subsystems. Support for multiple graphic context and multi-threading is all available out-of-the-box via osgViewer - all the examples in the distribution can run multi-threaded and multi-gpu.

- **Multi-language support**
  Java, Lua and Python bindings for the OpenSceneGraph are available as Community projects.
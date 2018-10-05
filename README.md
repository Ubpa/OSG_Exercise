# 一、介绍

## 1. OSG

>OSG中国首页：http://www.osgchina.org/index.php?option=com_content&view=featured&Itemid=435
>
>OSG英文首页：http://www.openscenegraph.org/

OpenSceneGraph是一个开源的三维引擎，被广泛的应用在可视化仿真、游戏、虚拟现实、科学计算、三维重建、地理信息、太空探索、石油矿产等领域。OSG采用标准C++和OpenGL编写而成，可运行在所有的Windows平台、OSX、GNU/Linux、IRIX、Solaris、HP-Ux、AIX、Android和FreeBSD 操作系统。OSG在各个行业均有着丰富的扩展，能够与使用OpenGL书写的引擎无缝的结合，使用国际上最先进的图形渲染技术，让每个用户都能站在巨人的肩上。

##2. 此项目

此项目是我关于OSG做的练习。

分为4部分

- QSG
- BG（未写）
- CB（未写）
- LearnOpenGL（未完成）

QSG、BG、CB是与OSG相关的三本书，书籍pdf和自带源码的下载链接如下

```
链接：https://pan.baidu.com/s/10ANhJ2l2TAU5S6mx93VSug 
提取码：2vwy
```

项目中关于QSG的部分，源码几乎直接来源于书自带的源码

LearnOpenGL是一个教程，介绍如下

>https://learnopengl-cn.github.io/
>
>欢迎来到OpenGL的世界。这个工程只是我([Joey de Vries](http://joeydevries.com/))的一次小小的尝试，希望能够建立起一个完善的OpenGL教学平台。无论你学习OpenGL是为了学业，找工作，或仅仅是因为兴趣，这个网站都将能够教会你**现代**(Core-profile) OpenGL从基础，中级，到高级的知识。LearnOpenGL的目标是使用易于理解的形式，使用清晰的例子，展现现代OpenGL的所有知识点，并与此同时为你以后的学习提供有用的参考。

此项目中关于LearnOpenGL的部分，代码是基于OSG自己写的，只是实现效果参考部分自LearnOpenGL。

# 二、使用方法

## 1. 环境配置

首先是 OSG 源码的项目配置，方法参考如下

```
http://www.openscenegraph.org/index.php/documentation/getting-started
```

接着只需要把此项目的 `data` 文件夹的路径添加到系统变量 `OSG_FILE_PATH` 中即可。

## 2. 建立工程

此项目支持 CMake，因此在**项目的根目录**执行以下命令即可

```bash
mkdir build
cd build
cmake ..
```

以下是 Windows 下的使用说明

打开 `build`文件夹 中的 `OSG_Exercise.sln`，执行 `INSTALL` 即可

生成的exe可执行文件会放在 `bin` 目录下
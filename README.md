# 一、介绍

## 1. OSG

>OSG中国首页：http://www.osgchina.org/index.php?option=com_content&view=featured&Itemid=435
>
>OSG英文首页：http://www.openscenegraph.org/
>
>OpenSceneGraph 是一个开源的三维引擎，被广泛的应用在可视化仿真、游戏、虚拟现实、科学计算、三维重建、地理信息、太空探索、石油矿产等领域。OSG采用标准C++和OpenGL编写而成，可运行在所有的Windows平台、OSX、GNU/Linux、IRIX、Solaris、HP-Ux、AIX、Android和FreeBSD 操作系统。OSG在各个行业均有着丰富的扩展，能够与使用OpenGL书写的引擎无缝的结合，使用国际上最先进的图形渲染技术，让每个用户都能站在巨人的肩上。

## 2. 此项目

### 2.1 介绍

此项目是我关于OSG做的练习。

分为4部分

- QSG
- BG（未写）
- CB（未写）
- LearnOpenGL（未完成）

---

QSG、BG、CB是与OSG相关的三本书，书籍pdf和自带源码的下载链接如下

```
链接：https://pan.baidu.com/s/10ANhJ2l2TAU5S6mx93VSug 
提取码：2vwy
```

项目中关于QSG的部分，源码几乎直接来源于书自带的源码

---

LearnOpenGL是一个教程，介绍如下

>https://learnopengl-cn.github.io/
>
>欢迎来到OpenGL的世界。这个工程只是我([Joey de Vries](http://joeydevries.com/))的一次小小的尝试，希望能够建立起一个完善的OpenGL教学平台。无论你学习OpenGL是为了学业，找工作，或仅仅是因为兴趣，这个网站都将能够教会你**现代**(Core-profile) OpenGL从基础，中级，到高级的知识。LearnOpenGL的目标是使用易于理解的形式，使用清晰的例子，展现现代OpenGL的所有知识点，并与此同时为你以后的学习提供有用的参考。

此项目中关于LearnOpenGL的部分，代码是基于OSG自己写的，只是实现效果参考部分自LearnOpenGL。

### 2.2 项目结构

```
/OSG_Exercise
	/CMakePredefinedTargets
		ALL_BUILD
		INSTALL
		ZERO_CHECK
	/LearnOpenGL
		/01_Introduction
			LO_01_01_CreateWindows
			LO_01_02_Triangle
			LO_01_03_SimpleScean
			LO_01_04_Shader
	/QSG
		QSG_01_Simple
		QSG_02_Viewer
		QSG_03_State
		QSG_04_TextureMapping
		QSG_05_Lighting
		QSG_06_Text
		QSG_07_Callback
		QSG_08_FindNode
		QSG_09_Picking
```

# 二、使用方法

此项目支持 CMake

以下是 Windows10 + vs 2017 的使用说明（其他搭配组合请自行尝试）

## 1. 环境配置

首先是 OSG 源码的项目配置，方法参考如下

```
http://www.openscenegraph.org/index.php/documentation/getting-started
```

接着设置一下环境变量

- 此项目的 `data` 文件夹的路径添加到系统变量 `OSG_FILE_PATH` 中。

- 设置环境变量 `OSG_3RDPATRY_PATH` ，添加第三方程序包的根目录路径

## 2. 建立工程

在**项目的根目录**执行以下命令

```bash
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" ..
```

打开 `build`文件夹 中的 `OSG_Exercise.sln`，右键`INSTALL` ，点击“生成”即可

生成的exe可执行文件会放在 `bin` 目录下
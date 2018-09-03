# EzGL

[![Build Status](https://travis-ci.org/ezaf/ezgl.svg?branch=master)](https://travis-ci.org/ezaf/ezgl)
[![GitHub Issues](https://img.shields.io/github/issues/ezaf/ezgl.svg)](https://github.com/ezaf/ezgl/issues)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://ezgl.ezaf.io)
[![License: zlib](https://img.shields.io/badge/license-zlib-blue.svg)](https://zlib.net/zlib_license.html)
<!--[![Contributors](https://img.shields.io/github/contributors/ezaf/ezgl.svg)](https://github.com/ezaf/ezgl/graphs/contributors)-->

A component-based, graphics API-agnostic game engine.



## About

The EzGL game engine allows for great flexibility and customizability through
it's ground-up, component-based architecture. Heck, the window and renderer
themselves are components! This unique design allows for EzGL to work with any
graphics API you desire such as SDL, OpenGL, or DirectX, assuming you or
someone else has written an EzGL plugin for that respective API. So far I have
written the SDL plugin; OpenGL/GLFW will come next.

EzGL's component-based architecture is also a boon for prototyping! No longer
do you have to keep recompiling every time you make a subtle change; much of
the design work is done entirely within json configuration files. For more
information, visit the [EzGL documentation website](http://ezgl.ezaf.io).



## License

Copyright (c) 2018 Kirk Lange <[github.com/kirklange](https://github.com/kirklange)>

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

# EzGL

[![Build Status](https://travis-ci.org/ezaf/ezgl.svg?branch=master)](https://travis-ci.org/ezaf/ezgl)
[![GitHub Issues](https://img.shields.io/github/issues/ezaf/ezgl.svg)](https://github.com/ezaf/ezgl/issues)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://ezgl.ezaf.io)
[![License: zlib](https://img.shields.io/badge/license-zlib-blue.svg)](https://zlib.net/zlib_license.html)
<!--[![Contributors](https://img.shields.io/github/contributors/ezaf/ezgl.svg)](https://github.com/ezaf/ezgl/graphs/contributors)-->

A component-based, graphics API-agnostic game engine.



## About

**Update Thu Aug 23:** The documentation is about 50% complete.

You may have noticed that the documentation is basically non-existent and full
of a lot of Lorem Ipsums. That is because this month (August) the engine has
undergone three major refactorings, the most recent one being on August 19th.
As far as I can tell, the engine shouldn't drastically change from now on, so
over the next couple weeks I'll be repaying all that technical debt.

In communicating the purpose of the EzGL game engine, I think it would help to
describe the purpose of the August 19th refactoring (EzSDL -> EzGL). For the
longest time I've been stagnating, only bothering to use SDL2. While I'll most
likely still implement my next semester's project in SDL2, I also want to learn
OpenGL/GLFW. What I thought would be really cool is if after I learn the ropes
of OpenGL I could write a drop-in replacement for the SDL2 component of the
game engine. Thus, over the weekend, I seperated out the component-based
foundation of EzGL from the SDL2-related code. Now, changing the graphics API
is as simple as changing `core.api` in the json configuration file! It is this
concept of dynamic loading and robust run-time customization that is at the
heart of EzGL.



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

/* main.cpp
Copyright (c) 2018 by Kirk Lange


Main function for ezsdl. None of this code is part of the engine itself.
Rather, treat this as an example or template for basing your future projects
off of.

TODO: move prefix documentation to some central window/engine class header (?)

Oregonian Notation (Kirk Lange's Apps Hungarian Notation)
===============================================================================
  u - public / visible namespace
  o - protected
  i - private / annonymous namespace
  s - static
  p - parameter
  r - return
  t - temporary holder value (use only if 'h' prefix does not apply)
  l - iterator (looper, hence 'l')
  h - push (as in said variable will be pushed to a cointainer or array)
  c - constant
  f - reference
  n - pointer / array
  v - value (use only if no other prefixes apply)
-------------------------------------------------------------------------------
> Append all applicable prefixes (except for 'v') in the order listed above.
> Whether to use 't' or 'v' can get a little hazy. Use your best judgement.
> "argc" and "argv" are sacred, otherwise, ALL arguments/parameters as well as
  ALL variables on both the stack and heap get prefixes.
> Common Examples
  > Obj& getObj(const int& pcfObjectID);
  > for (int lIndex=0; lIndex<vStr.length(); lIndex++) { ... }
===============================================================================

EZSDL is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

EZSDL is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*/

//#include ezsdl/
#include <stdio.h>



int main(int argc, char *argv[])
{
    printf("Hello world, I am ezsdl2!\n");

    return 0;
}

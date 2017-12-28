/* main.cpp
Copyright (c) 2018 by Kirk Lange

Main function for ezsdl. None of this code is part of the engine itself.
Rather, treat this as an example or template for basing your future projects
off of.

TODO: move prefix documentation to some central window/engine class header (?)

My Signature Variable Prefixes
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
*/

//#include ezsdl/
#include <cstdio>



int main(int argc, char *argv[])
{
    printf("Hello world, I am ezsdl2!\n");

    return 0;
}

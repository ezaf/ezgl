#!/bin/bash

###############################################################################
#### WARNING: Make sure you're calling this script from its own directory! ####
###############################################################################

# SOURCE-and-DIR-finding code from https://stackoverflow.com/a/246128/5890633
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
SOURCE=


function import
{
    # Import source, header, and dynamic library files
    for file in `ls *.c *.h *.cpp *.hpp *.dll *.so *.dylib`; do
        front=${file%%.*}
        # Don't import test files
        if [ $front != "tests" ] && [ $front != "test" ] && [ $front != "tst" ]; then
            dest=
            if [ ${file#*.} == "c" ] || [ ${file#*.} == "cpp" ]; then
                dest=$DIR/../src/$1
            elif [ ${file#*.} == "h" ] || [ ${file#*.} == "hpp" ]; then
                dest=$DIR/../include/$1
            elif [ ${file#*.} == "dll" ] || [ ${file#*.} == "so" ] || [ ${file#*.} == "dylib" ]; then
                dest=$DIR/../lib/$1
            fi
            # Clean or make directories before copying
            rm -f $dest$file
            mkdir -p $dest
            cp $DIR/$1$file $dest$file
        fi
    done

    # Recursively explore directories
    for dir in `ls -d */`; do
        # Ignore test folders
        if [ $dir != "tests/" ] && [ $dir != "test/" ]; then
            pushd $dir > /dev/null
            import $1$dir
            popd > /dev/null
        fi
    done
}


import

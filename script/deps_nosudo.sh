#!/bin/bash

sdl2_base="SDL2-2.0.8"
sdl2_image="SDL2_image-2.0.3"
sdl2_mixer="SDL2_mixer-2.0.2"
sdl2_ttf="SDL2_ttf-2.0.14"
sdl2_net="SDL2_net-2.0.1"

wget $(printf "https://www.libsdl.org/release/%s.tar.gz" $sdl2_base)
tar -xzf $(printf "%s.tar.gz" $sdl2_base)
pushd $(printf "%s" $sdl2_base) && ./configure --prefix="$HOME" && make && make install && popd

wget -q $(printf "https://www.libsdl.org/projects/SDL_image/release/%s.tar.gz" $sdl2_image)
wget -q $(printf "https://www.libsdl.org/projects/SDL_mixer/release/%s.tar.gz" $sdl2_mixer)
wget -q $(printf "https://www.libsdl.org/projects/SDL_ttf/release/%s.tar.gz" $sdl2_ttf)
wget -q $(printf "https://www.libsdl.org/projects/SDL_net/release/%s.tar.gz" $sdl2_net)
tar -xzf $(printf "%s.tar.gz" $sdl2_image)
tar -xzf $(printf "%s.tar.gz" $sdl2_mixer)
tar -xzf $(printf "%s.tar.gz" $sdl2_ttf)
tar -xzf $(printf "%s.tar.gz" $sdl2_net)
pushd $(printf "%s" $sdl2_image) && ./configure --prefix="$HOME" && make && make install && popd
pushd $(printf "%s" $sdl2_mixer) && ./configure --prefix="$HOME" && make && make install && popd
pushd $(printf "%s" $sdl2_ttf) && ./configure --prefix="$HOME" && make && make install && popd
pushd $(printf "%s" $sdl2_net) && ./configure --prefix="$HOME" && make && make install && popd

rm -rf SDL2*

if ! grep -q ~/lib/pkgconfig ~/.bashrc; then
    printf "\nexport PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:~/lib/pkgconfig\n" >> ~/.bashrc;
fi

#!/bin/bash

FREEGLUT_URL=https://github.com/dcnieho/FreeGLUT/archive/FG_2_8_0.tar.gz

mkdir -p /usr/local/src                        || exit 1
cd /usr/local/src	                       || exit 1
wget --no-check-certificate ${FREEGLUT_URL}    || exit 1 	
tar xvf FG_2_8_0.tar.gz	                       || exit 1 	
cd FreeGLUT-FG_2_8_0/freeglut                  || exit 1 	
./autogen.sh		                       || exit 1 	
./configure --prefix=/mingw                    || exit 1 	
make			                       || exit 1 	
make install		                       || exit 1 	



#!/bin/bash

FREEGLUT_URL=https://github.com/dcnieho/FreeGLUT/archive/FG_2_8_0.tar.gz
FREEGLUT_TAR=FG_2_8_0.tar.gz
FILE_UNTAR=FreeGLUT-FG_2_8_0/freeglut

mkdir -p /usr/local/src                                           || exit 1
cd /usr/local/src	                                          || exit 1
wget --no-check-certificate ${FREEGLUT_URL} -O ${FREEGLUT_TAR}    || exit 1 	
tar xvf ${FREEGLUT_TAR}	                                          || exit 1 	
cd ${FILE_UNTAR}                                                  || exit 1
./autogen.sh		                                          || exit 1 	
./configure --prefix=/mingw                                       || exit 1 	
make			                                          || exit 1 	
make install		                                          || exit 1 	



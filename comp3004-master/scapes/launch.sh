#!/bin/bash

FILE=scapes

if test -f "$FILE"; then
	./scapes
else
	export PATH=$PATH:~/Qt/5.13.0/gcc_64/bin
	qmake scapes.pro
	make
	./scapes
fi

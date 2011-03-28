#!/bin/sh
if [ `uname` == "Darwin" ]; then
	rm -rf gpuakf.app gpuakf.dmg
	qmake -spec macx-g++ -config release
	make
	macdeployqt gpuakf.app -dmg
else
	qmake -config release
	make
fi

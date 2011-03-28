#!/bin/sh
rm -rf gpuakf.app gpuakf.dmg
qmake -spec macx-g++ -config release
make
macdeployqt gpuakf.app -dmg

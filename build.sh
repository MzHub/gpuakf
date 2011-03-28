#!/bin/sh
rm -rf jkyprian-akf.app jkyprian-akf.dmg
qmake -spec macx-g++ -config release
make
macdeployqt jkyprian-akf.app -dmg

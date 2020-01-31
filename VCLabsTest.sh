#!/bin/bash
rm -f opencvtestapp
echo "compiling opencvtest.cpp"
g++ Panel.cpp -o opencvtestapp `pkg-config --cflags --libs opencv`
echo "Running opencvtest"
./opencvtestapp

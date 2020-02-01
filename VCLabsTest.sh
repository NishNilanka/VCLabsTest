#!/bin/bash
rm -f opencvtestapp
echo "compiling opencvtest.cpp"
g++ main.cpp stream.cpp FFmpegReader.cpp FFmpegWriter.cpp -o opencvtestapp `pkg-config --cflags --libs opencv` -lavformat -lavcodec -lswscale -lavutil -lz -pthread -lswresample -lvdpau -lva-drm -lva-x11 -lva -lvdpau -lX11 -llzma
echo "Running opencvtest"
./opencvtestapp Resources/Demo.mpeg 


#include <iostream>
#include <stdio.h>

#include "FFmpegReader.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You need to specify a media file.\n");
        return -1;
    }

    FFmpegReader *ffmpegReader = new FFmpegReader(argv[1]);
	ffmpegReader->initializeStream();
	ffmpegReader->showStreamInfo();
	ffmpegReader->findDecoder();
	ffmpegReader->processframe();

    return 0;




}








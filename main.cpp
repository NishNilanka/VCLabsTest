#include <iostream>
#include <stdio.h>

#include "streamDetails.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You need to specify a media file.\n");
        return -1;
    }

    streamDetails *streamDetail = new streamDetails(argv[1]);
	streamDetail->initializeStream();
	streamDetail->showStreamInfo();
	streamDetail->findDecoder();
	streamDetail->processframe();
	

    return 0;




}








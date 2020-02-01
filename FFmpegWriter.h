#include <iostream>
#include <stdio.h>
#include <ctime>
#include <locale>

#include "stream.h"

extern "C" {
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include "libavcodec/avcodec.h"
#include <libavutil/opt.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
#include <libavutil/mathematics.h>
}

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace cv;
using namespace std;

class FFmpegWriter : stream
{
	private:

	public:
		void writeVideo();

};

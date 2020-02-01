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

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#define mpeg CV_FOURCC('P','I','M','1')

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace std;
using namespace cv;

class FFmpegWriter : stream
{
	private:
		string outputFile;
		VideoWriter out;
		Mat bgr;

	public:
		FFmpegWriter(int, int, double, string);
		void writeVideo(Mat *);

};

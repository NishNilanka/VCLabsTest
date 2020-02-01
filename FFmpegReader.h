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

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace cv;
using namespace std;

class FFmpegReader : stream
{

	private:
		stream *streamObj;
		AVFormatContext *pFormatContext;
		AVCodec *pCodec;
		AVCodecParameters *pCodecParameters;
		AVCodec *pLocalCodec;
		int video_stream_index;
		AVCodecParameters *streamCodecParameters;
		AVFrame *pFrame, *pFrameRGB;
		AVCodecContext *pCodecCtx;
		void setTime();
		Mat resized;
		void resizeFrame(AVFrame*, AVFrame*);


	public:
		void logging(const char *fmt, ...);
		FFmpegReader(string mediaFile);
		int initializeStream();
		int showStreamInfo();
		AVCodec *findDecoder();
		int processframe();
	

};

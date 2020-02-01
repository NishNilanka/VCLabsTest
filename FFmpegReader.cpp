#include "FFmpegReader.h"

//call inherited function to create a stream
FFmpegReader::FFmpegReader(string mediaFile)
{
	setMediaFile(mediaFile);
	video_stream_index = 0;
}

//initialize all the containers, codecs and protocols
int FFmpegReader::initializeStream()
{
	pFormatContext = avformat_alloc_context();

	if (!pFormatContext)
    {
        logging("ERROR could not allocate memory for Format Context");
        return -1;
    }

    logging("opening the input file (%s) and loading format header", getMediaFile().c_str());

    if (avformat_open_input(&pFormatContext, (getMediaFile()).c_str(), NULL, NULL) != 0)
    {
        logging("ERROR could not open the file");
        return -1;
    }


    logging("format %s, duration %lld us, bit_rate %lld", pFormatContext->iformat->name, pFormatContext->duration, pFormatContext->bit_rate);

	return 0;
}

//start showing details of the video stream
int FFmpegReader::showStreamInfo()    
{
	logging("finding stream info from format");
    if (avformat_find_stream_info(pFormatContext,  NULL) < 0)
    {
        logging("ERROR could not get the stream info");
        return -1;
    }

	pCodecCtx = pFormatContext->streams[0]->codec;
    streamCodecParameters = pFormatContext->streams[0]->codecpar;
	logging("AVStream->format before open coded %s", pFormatContext->iformat->name);
    logging("AVStream->time_base before open coded %d/%d", pFormatContext->streams[0]->time_base.num, pFormatContext->streams[0]->time_base.den);
    logging("AVStream->r_frame_rate before open coded %d/%d", pFormatContext->streams[0]->r_frame_rate.num, pFormatContext->streams[0]->r_frame_rate.den);
    logging("AVStream->start_time %" PRId64, pFormatContext->streams[0]->start_time);
    logging("AVStream->duration %" PRId64, pFormatContext->streams[0]->duration);

	return 0;

}

//Find a proper decoder for the stream, prior to process the video
AVCodec *FFmpegReader::findDecoder()
{
	this->pLocalCodec = avcodec_find_decoder(streamCodecParameters->codec_id);
	if (pLocalCodec == NULL)
		return NULL;
	else	
		return pLocalCodec;
}


//
int FFmpegReader::processframe()
{

	pCodec =findDecoder();
	if(pCodec==NULL) return -15;

	if(avcodec_open2(pCodecCtx,pCodec,NULL) < 0) return -16;

	pFrame = av_frame_alloc();
	pFrameRGB = av_frame_alloc();

	if (!pFrame || !pFrameRGB)
	{
		logging("failed to allocated memory for AVFrame");
		return -1;
	}

	uint8_t *buffer;
	int numBytes;
	
	AVPixelFormat pFormat = AV_PIX_FMT_BGR24;
	numBytes = avpicture_get_size(pFormat,pCodecCtx->width,pCodecCtx->height) ;
	buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));
	avpicture_fill((AVPicture *) pFrameRGB,buffer,pFormat,pCodecCtx->width,pCodecCtx->height);

	int res;
	int frameFinished;
	AVPacket packet;

	while(res = av_read_frame(pFormatContext,&packet)>=0)
	{
		if(packet.stream_index == video_stream_index){
			avcodec_decode_video2(pCodecCtx,pFrame,&frameFinished,&packet);
			
			if(frameFinished){
				struct SwsContext * img_convert_ctx;
				img_convert_ctx = sws_getCachedContext(NULL,pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
				
				sws_scale(img_convert_ctx, ((AVPicture*)pFrame)->data, ((AVPicture*)pFrame)->linesize, 0, pCodecCtx->height, ((AVPicture *)pFrameRGB)->data, ((AVPicture *)pFrameRGB)->linesize);
				
				resizeFrame(pFrame, pFrameRGB);
				setTime();

				cv::imshow("display",resized);
				cvWaitKey(5);
				av_free_packet(&packet);
				sws_freeContext(img_convert_ctx);
			}
		}


		char c=(char)waitKey(25);
        if(c==27)
            break;
	}
	av_free_packet(&packet);
	avcodec_close(pCodecCtx);
	av_free(pFrame);
	av_free(pFrameRGB);
	avformat_close_input(&pFormatContext);

	return 0;
}

//Process decoded video stream with OpenCV (Resize frame) 
void FFmpegReader::resizeFrame(AVFrame *pFrame, AVFrame *pFrameRGB)
{
	Mat img(pFrame->height,pFrame->width,CV_8UC3,pFrameRGB->data[0]);
	Size size(pFrame->width/2, pFrame->height/2);
	resize(img, resized, size);
} 


//Get the current date and time and embedded into the video
void FFmpegReader::setTime()
{
	time_t timer;
    char buffer[26];
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	putText(resized, string(buffer), Point(5,50), FONT_HERSHEY_DUPLEX, 1, Scalar(0,0,0), 2);

}
	

void FFmpegReader::logging(const char *fmt, ...)
{
    va_list args;
    fprintf( stderr, "LOG: " );
    va_start( args, fmt );
    vfprintf( stderr, fmt, args );
    va_end( args );
    fprintf( stderr, "\n" );
}

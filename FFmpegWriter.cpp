#include "FFmpegWriter.h"

//frame writer is implemnted with OpenCV VideoWriter. Hence it is not possible to save the result file with the same encoding
FFmpegWriter::FFmpegWriter(int width, int height, double FPS, string format)
{
		out.open("output.mpeg4", CV_FOURCC('H','2','6','3'), FPS, Size(width, height/2));


}

//save output video into a file
void FFmpegWriter::writeVideo(Mat *frame)
{
	//cvtColor(*frame, bgr, CV_RGB2BGR);
	
	out << *frame;
	cv::imshow("Modified video", *frame);

}


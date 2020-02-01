#include "FFmpegWriter.h"

//frame writer is implemnted with OpenCV VideoWriter. Hence it is not possible to save the result file with the same encoding
FFmpegWriter::FFmpegWriter(int width, int height, double FPS, string format)
{
		out.open("output.avi", CV_FOURCC('I','4','2','0'), FPS, Size(width, height/2));


}

//save output video into a file
void FFmpegWriter::writeVideo(Mat *frame)
{
	//cvtColor(*frame, bgr, CV_RGB2BGR);
	
	out << *frame;
	cv::imshow("Modified video", *frame);

}


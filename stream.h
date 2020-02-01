#include <iostream>
#include <stdio.h>
#include <string>

extern "C" {
#include <libavformat/avformat.h>
}

using namespace std;


class stream
{

	private:
		string mediaFile;
		
	protected:
		string format;
		int frameRate;
			

	public:
		void setMediaFile(string);
		string getMediaFile();
		
};

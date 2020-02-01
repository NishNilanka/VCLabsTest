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
		
			

	public:
		void setMediaFile(string);
		string getMediaFile();
		
};

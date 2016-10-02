#ifndef UNSPLASH_WEI
#define UNSPLASH_WEI

#include<string>
#include<stdio.h>
#include<atomic>
#include"curl.h"

namespace unsplash
{
	class Unsplash_Wei
	{
	private:
		std::string sourceURL;
		CURL* curlIMG; // curl opinter to the web content
		CURLcode curlRes = CURLcode(0);// curl perform error code
		FILE* tempIMG; // pointer to the temp image file
		std::string tempImgDir; // temp image filename
		std::string picFolderDir; // image folder in which the liked wallpapers will be saved
		float refreshPeriod; // the wallpaper refresh interval, in hours
		int minMsec; // determine the minimal response time of the program, affects the resources hungry level
		std::atomic<bool> manualRefresh = false;  //https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
	public:

		//default constructor
		Unsplash_Wei();

		//constructor that initializes based on user commands
		Unsplash_Wei(float interval, std::string saveLoc, int wallpaperW, int wallpaperH);

		//set the url address for the Unsplash source
		void setURL(int width = 0, int height = 0);

		//get the wallpaper image from the given source url and save in the temp folder
		int getIMG();

		//set the wallpaper from the saved file in the temp folder
		int setWallpaper();

		//refresh the wallpaper setting process
		void loopExec(bool enableKeystroke);

		//detect user key stroke inputs. If the user manually changes the wallpaper, restart the loopExec thread
		void enableKeystrokeCombo();

	}; // end of class definition
}

#endif
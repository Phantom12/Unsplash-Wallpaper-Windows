#ifndef UNSPLASH_WEI_OLD
#define UNSPLASH_WEI_OLD

#include<string>
#include<stdio.h>
#include<atomic>
#include"curl.h"

namespace unsplash
{
	class Unsplash_Wei_old
	{
	protected:
		std::string sourceURL;
		std::string imgURL; //imgURL is sourceURL appended with resolution info
		CURL* curlIMG; // curl opinter to the web content
		CURLcode curlRes = CURLcode(0);// curl perform error code
		FILE* tempIMG; // pointer to the temp image file
		std::string tempImgDir; // temp image filename
		std::string picFolderDir; // image folder in which the liked wallpapers will be saved
		float refreshPeriod; // the wallpaper refresh interval, in hours
		int minMsec; // determine the minimal response time of the program, affects the resources hungry level
		int WIDTH, HEIGHT; // the width and height of the of the screen resolution
		std::atomic<bool> manualRefresh = false;  //https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
	public:

		//default constructor
		Unsplash_Wei_old();

		//constructor that initializes based on user commands
		Unsplash_Wei_old(float interval, std::string saveLoc, int wallpaperW, int wallpaperH);

		//set the wallpaper size
		void setRes(const int width = 0, const int height = 0);

		//set the default save location for the liked images
		void setDefaultSaveLoc();

		//set the url address for the Unsplash source
		void setURL();

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
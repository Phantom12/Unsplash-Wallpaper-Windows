#ifndef UNSPLASH_WEI
#define UNSPLASH_WEI

#include<string>
#include<stdio.h>
#include<atomic>
#include"curl.h"
#include<ShObjIdl.h>
#include <VersionHelpers.h>

namespace unsplash
{
	class Unsplash_Wei
	{
	protected:
		std::string sourceURL;
		CURL* curlIMG; // curl opinter to the web content
		CURLcode curlRes = CURLcode(0);// curl perform error code
		FILE* tempIMG; // pointer to the temp image file
		std::string tempImgDir; // temp image filename
		std::string picFolderDir; // image folder in which the liked wallpapers will be saved
		float refreshPeriod; // the wallpaper refresh interval, in hours
		int minMsec; // determine the minimal response time of the program, affects the resource hungry level
		int WIDTH, HEIGHT; // the width and height of the of the screen resolution
		std::atomic<bool> manualRefresh = false;  //https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
		IDesktopWallpaper* pDesktopWallpaper = NULL; //newer version of functionality that allows finer control of setting wallpapers 
		//http://amin-ahmadi.com/2015/12/07/how-to-change-desktop-background-image-in-c/
		//https://blogs.msdn.microsoft.com/matthew_van_eerde/2012/10/10/changing-the-desktop-wallpaper-using-idesktopwallpaper/
		bool differentWallpaperPerMonitor;
		UINT32 monitorIdx = 0; // indicate the current monitor to change wallpaper if differentWallpaperPerMonitor==true

	public:
		//default constructor
		Unsplash_Wei();

		//constructor that initializes based on user commands
		Unsplash_Wei(float interval, std::string saveLoc, int wallpaperW, int wallpaperH);

		//default destructor
		~Unsplash_Wei();

		//set the wallpaper size
		void setRes(const int width = 0, const int height = 0);

		//set the default save location for the liked images
		void setDefaultSaveLoc();

		//set the url address for the Unsplash source
		void setURL();

		//get the wallpaper image from the given source url and save in the temp folder
		int getIMG();

		//set the wallpaper from the saved file in the temp folder
		int setWallpaper(const LPWSTR* const monitorID = NULL);

		//refresh the wallpaper setting process
		void loopExec(bool enableKeystroke);

		//detect user key stroke inputs. If the user manually changes the wallpaper, restart the loopExec thread
		void enableKeystrokeCombo();

	}; // end of class definition
}

#endif
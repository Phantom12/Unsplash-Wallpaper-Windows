#include"Unsplash_Wei.h"
#include<thread>
#include<time.h>
#include"curl.h"
#include<fstream>
#include<iostream>
#include<Windows.h>
#include<shlobj.h>

//#pragma comment(lib, "shell32.lib")

unsplash::Unsplash_Wei::Unsplash_Wei()
{
	//curl_global_init(CURL_GLOBAL_DEFAULT);

	//initialize the temp image file 
	char tempFolder[256], picFolder[256];
	GetTempPath(256, tempFolder);
	tempImgDir = tempFolder;
	tempImgDir += "UnsplashTemp.jpg";
	
	//default auto refresh interval
	refreshPeriod = 1.f;
	
	//initialize the program's working frequency
	minMsec = 50;
	
	//default wallpaper save location
	SHGetFolderPath(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, picFolder);
	picFolderDir = picFolder;
	picFolderDir += "\\Unsplash\\";
	std::string createFolderCMD = "mkdir " + picFolderDir;
	system(createFolderCMD.c_str());
	//printf("%s", picFolderDir);

	//set the source url with auto-determined wallpaper size
	this->setURL();
}

//unsplash::Unsplash_Wei::Unsplash_Wei(float interval, std::string saveLoc, int wallpaperW, int wallpaperH) :Unsplash_Wei()
//{
//}

unsplash::Unsplash_Wei::Unsplash_Wei(float interval, std::string saveLoc, int wallpaperW, int wallpaperH)
{
	//initialize the temp image file 
	char tempFolder[256], picFolder[256];
	GetTempPath(256, tempFolder);
	tempImgDir = tempFolder;
	tempImgDir += "UnsplashTemp.jpg";

	//default auto refresh interval
	refreshPeriod = interval;

	//initialize the program's working frequency
	minMsec = 50;

	//create wallpaper save folder
	picFolderDir = saveLoc;
	std::string createFolderCMD = "mkdir " + picFolderDir;
	system(createFolderCMD.c_str());

	//set the source url with given wallpaper size
	this->setURL(wallpaperW, wallpaperH);
}

void unsplash::Unsplash_Wei::setURL(int width, int height)
{
	//printf("%d\n", GetSystemMetrics(SM_CXSCREEN));
	sourceURL = "https://source.unsplash.com/featured/";
	if (!(width*height))
	{
		width = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);
	}
	sourceURL += std::to_string(width);
	sourceURL += "x";
	sourceURL += std::to_string(height);
	//sourceURL = "https://source.unsplash.com/featured/3840x2160";
	printf("%s", sourceURL);
}

int unsplash::Unsplash_Wei::getIMG()
{
	tempIMG = fopen(tempImgDir.c_str(), "wb");
	if (tempIMG == NULL)
	{
		printf("Error: unable to open the temp image file\n");
		return -1;
	}

	curlIMG = curl_easy_init();

	curl_easy_setopt(curlIMG, CURLOPT_URL, sourceURL);
	curl_easy_setopt(curlIMG, CURLOPT_WRITEDATA, tempIMG);
	//curl_easy_setopt(curlIMG, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(curlIMG, CURLOPT_FOLLOWLOCATION, 1L);

	curlRes = curl_easy_perform(curlIMG);

	curl_easy_cleanup(curlIMG);
	fclose(tempIMG);
	
	if (curlRes)
	{
		printf("Error: unable to grab the image from the web address\n");
		return -1;
	}

	printf("image grabbed\n");
	return 0;
}

int unsplash::Unsplash_Wei::setWallpaper()
{
	if (!SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)tempImgDir.c_str(), 0))
	{
		printf("Error: unable to set the wallpaper\n");
		return -1;
	}

	printf("wallpaper set\n");
	return 0;
}

void unsplash::Unsplash_Wei::loopExec(bool enableKeystroke)
{
	float refreshMsec, retryMsec, waitMsec;
	if (enableKeystroke)
	{
		std::thread keyStrokeDetectThread(&unsplash::Unsplash_Wei::enableKeystrokeCombo, this);
		while (true)
		{
			// redefine the two waiting time every iteration to lay the ground work for future change of refresh time while program running.
			refreshMsec = refreshPeriod * 3600 * 1000;
			retryMsec = min(refreshPeriod * 3600 * 1000, 5 * 1000); // if failed, retry every 5s unless the default refresh interval is smaller.

			if (this->getIMG() || this->setWallpaper())
				waitMsec = retryMsec;
			else
				waitMsec = refreshMsec;

			//seems an odd choice to restart the thread in the next run, but seems the only way to resolve the bug that quick manual refresh twice causes blackscreen
			if (!keyStrokeDetectThread.joinable())
				keyStrokeDetectThread = std::thread(&unsplash::Unsplash_Wei::enableKeystrokeCombo, this);

			for (int i = 0; i < waitMsec / minMsec; i++)
			{
				if (!manualRefresh)
					Sleep(minMsec);
				else
				{
					keyStrokeDetectThread.join();
					keyStrokeDetectThread.~thread();
					manualRefresh = false;
					//keyStrokeDetectThread = std::thread(&unsplash::Unsplash_Wei::enableKeystrokeCombo, this);
					break;
				}
			} // end of for
		} // end of while
	}
	else
	{
		while (true)
		{
			// redefine the two waiting time every iteration to lay the ground work for future change of refresh time while program running.
			refreshMsec = refreshPeriod * 3600 * 1000;
			retryMsec = min(refreshPeriod * 3600 * 1000, 5 * 1000); // if failed, retry every 5s unless the default refresh interval is smaller.

			if (this->getIMG() || this->setWallpaper())
				waitMsec = retryMsec;
			else
				waitMsec = refreshMsec;

			Sleep(waitMsec);
		}
	} // end of if(enableKeystroke)
}

void unsplash::Unsplash_Wei::enableKeystrokeCombo()
{
	//std::thread loopExec_thread(&unsplash::Unsplash_Wei::loopExec,this); //http://stackoverflow.com/questions/10998780/stdthread-calling-method-of-class
	while (true)
	{
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(0x53) & 0x8000)) // save the current wallpaper
		{
			printf("save wallpaper command detected\n");
			time_t tNow = time(NULL);
			struct tm* timeinfo = localtime(&tNow);
			char timeStr[256];
			memset(timeStr, 0, 256);
			strftime(timeStr, 256, "%y%m%d%H%M%S", timeinfo);
			//printf("%s", picFolderDir + timeStr + ".jpg");
			std::ifstream src(tempImgDir, std::ios::in | std::ios::binary);
			std::ofstream dst(picFolderDir + "Unsplash_" + timeStr + ".jpg", std::ios::out | std::ios::binary);
			//std::ofstream dst("d:\\dss.jpg", std::ios::out | std::ios::binary);
			/*if (dst.is_open())
				printf("dst stream has been opened\n");
			else
				printf("%s", picFolderDir + timeStr + ".jpg");*/
			dst << src.rdbuf();
			src.close();
			dst.close();
		}
		else if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(0x4E) & 0x8000)) // manually refresh the wallpaper
		{
			printf("manual refresh detected\n");
			//loopExec_thread.detach(); // savior. Important!
			//loopExec_thread.~thread(); // seems the program crashes if in the middle of getIMG or setWallpaper

			//safer to tell the thread to "go kill yourself"
			manualRefresh = true;
			return;
			// have a weird problem that if the user refresh again b4 last manual refresh image shows up, the screen went black
			// actually it doesn't matter which one is called as the new thread, the problem persists
			/*loopExec_thread.join();
			loopExec_thread.~thread();
			printf("thread terminated\n");
			manualRefresh = false;
			loopExec_thread=std::thread(&unsplash::Unsplash_Wei::loopExec, this);*/
		}
		Sleep(minMsec);
	}	
}
#include"Unsplash_Wei.h"
#include<thread>
#include<time.h>
#include"curl.h"
#include<fstream>
#include<iostream>
#include<Windows.h>
#include<shlobj.h>
#include<comdef.h>
#include<QString>

//#pragma comment(lib, "shell32.lib")

unsplash::Unsplash_Wei::Unsplash_Wei()
{
	//curl_global_init(CURL_GLOBAL_DEFAULT);

	differentWallpaperPerMonitor = IsWindows8OrGreater() ? true : false;// if the OS version is not lower than Windows 8, enable different Wallpapers for different monitors

	//initialize the temp image file 
	char tempFolder[256];
	GetTempPathA(256, tempFolder); // must specify the ASCII versions of the windows API with the suffix -A, as Qt declares UNICODE in preprocessor
	/*std::fstream logFileStream;
	logFileStream.open("log.txt", std::fstream::out);
	logFileStream << tempFolder << std::endl;
	logFileStream.close();*/
	tempImgDir = tempFolder;
	tempImgDir += "UnsplashTemp.jpg";
	
	//default auto refresh interval
	refreshPeriod = 1.f;
	
	//initialize the program's working frequency
	minMsec = 50;
	
	//default wallpaper save location
	this->setDefaultSaveLoc();

	//set the source url with auto-determined wallpaper size
	this->setRes();
}

//unsplash::Unsplash_Wei::Unsplash_Wei(float interval, std::string saveLoc, int wallpaperW, int wallpaperH) :Unsplash_Wei()
//{
//}

unsplash::Unsplash_Wei::Unsplash_Wei(float interval, std::string saveLoc, int wallpaperW, int wallpaperH)
{
	differentWallpaperPerMonitor = IsWindows8OrGreater() ? true : false;

	//initialize the temp image file 
	char tempFolder[256], picFolder[256];
	GetTempPathA(256, tempFolder);
	/*std::fstream logFileStream;
	logFileStream.open("log.txt", std::fstream::out);
	logFileStream << tempFolder << std::endl;
	logFileStream.close();*/
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
	this->setRes(wallpaperW, wallpaperH);
}

unsplash::Unsplash_Wei::~Unsplash_Wei()
{
	delete curlIMG, tempIMG, pDesktopWallpaper;
	curlIMG = NULL;
	tempIMG = NULL;
	pDesktopWallpaper = NULL;
}

void unsplash::Unsplash_Wei::setRes(const int width, const int height)
{
	WIDTH = width;
	HEIGHT = height;
}

void unsplash::Unsplash_Wei::setDefaultSaveLoc()
{
	char picFolder[256];
	SHGetFolderPathA(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, picFolder);
	picFolderDir = picFolder;
	picFolderDir += "\\Unsplash\\";
	std::string createFolderCMD = "mkdir " + picFolderDir;
	picFolderDir = QString(picFolderDir.c_str()).replace("\\", "/").toStdString(); //for syntax consistency, use backslash
	system(createFolderCMD.c_str());
	//printf("%s", picFolderDir);
}

void unsplash::Unsplash_Wei::setURL()
{
	//printf("%d\n", GetSystemMetrics(SM_CXSCREEN));
	sourceURL = "https://source.unsplash.com/featured/";

	if (WIDTH*HEIGHT)
	{
		sourceURL += std::to_string(WIDTH);
		sourceURL += "x";
		sourceURL += std::to_string(HEIGHT);
	}
	else if (!differentWallpaperPerMonitor)
	{
		sourceURL += std::to_string(GetSystemMetrics(SM_CXSCREEN));
		sourceURL += "x";
		sourceURL += std::to_string(GetSystemMetrics(SM_CYSCREEN));
		
		/*std::fstream logFileStream;
		logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
		logFileStream << sourceURL.c_str() << std::endl;
		logFileStream.close(); */
	}
	else
	{
		RECT dispRect;
		LPWSTR monitorID[256];
		memset(monitorID, 0, 256);
		long lclWidth, lclHeight;
		HRESULT hr = pDesktopWallpaper->GetMonitorDevicePathAt(monitorIdx, monitorID);
		if (FAILED(hr))
		{
			lclWidth = GetSystemMetrics(SM_CXSCREEN);
			lclHeight = GetSystemMetrics(SM_CYSCREEN);
		}
		else
		{
			hr = pDesktopWallpaper->GetMonitorRECT(*monitorID, &dispRect);
			if (FAILED(hr))
			{
				lclWidth = GetSystemMetrics(SM_CXSCREEN);
				lclHeight = GetSystemMetrics(SM_CYSCREEN);
			}
			else
			{
				lclWidth = dispRect.right - dispRect.left;
				lclHeight = dispRect.bottom - dispRect.top;
			}// end of if GetMonitorRECT failed
		}// end of if GetMonitorDevicePathAt failed

		sourceURL += std::to_string(lclWidth);
		sourceURL += "x";
		sourceURL += std::to_string(lclHeight);

		/*std::fstream logFileStream;
		logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
		logFileStream << sourceURL.c_str() << std::endl;
		logFileStream.close();*/
	}
	
	//sourceURL = "https://source.unsplash.com/featured/3840x2160";
	//printf("%s", sourceURL.c_str()); // not recommended
	std::cout << sourceURL << std::endl;
}

int unsplash::Unsplash_Wei::getIMG()
{
	this->setURL();
	tempIMG = fopen(tempImgDir.c_str(), "wb");
	if (tempIMG == NULL)
	{
		printf("Error: unable to open the temp image file\n");
		return -1;
	}

	curlIMG = curl_easy_init();

	curl_easy_setopt(curlIMG, CURLOPT_URL, sourceURL.c_str());
	curl_easy_setopt(curlIMG, CURLOPT_WRITEDATA, tempIMG);
	//curl_easy_setopt(curlIMG, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(curlIMG, CURLOPT_FOLLOWLOCATION, 1);

	curlRes = curl_easy_perform(curlIMG);

	curl_easy_cleanup(curlIMG);
	fclose(tempIMG);

	/*std::fstream logFileStream;
	logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
	logFileStream << sourceURL.c_str() << std::endl;
	logFileStream << tempImgDir.c_str() << std::endl;
	logFileStream << curlRes << std::endl;
	logFileStream.close();*/
	
	if (curlRes)
	{
		std::cout << curlRes;
		printf("Error: unable to grab the image from the web address\n");
		return -1;
	}

	printf("image grabbed\n");
	return 0;
}

int unsplash::Unsplash_Wei::setWallpaper(const LPWSTR* const monitorID)
{
	if (differentWallpaperPerMonitor)
	{
		std::wstring wTempImgDir = std::wstring(tempImgDir.begin(), tempImgDir.end());
		HRESULT hr = pDesktopWallpaper->SetWallpaper(*monitorID, wTempImgDir.c_str());
		if (FAILED(hr))
		{
			printf("Error: unable to set the wallpaper\n");
			return -1;
		}
	}
	else
	{
		if (!SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)tempImgDir.c_str(), 0))
		{
			printf("Error: unable to set the wallpaper\n");
			/*std::fstream logFileStream;
			logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
			logFileStream << "Error: unable to set the wallpaper\n";
			logFileStream << tempImgDir.c_str() << std::endl;
			logFileStream.close();*/
			return -1;
		}
	}
	
	printf("wallpaper set\n");
	return 0;
}

void unsplash::Unsplash_Wei::loopExec(bool enableKeystroke)
{
	HRESULT hrInitilize = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);// https://msdn.microsoft.com/en-us/library/ms809971.aspx
	if (FAILED(hrInitilize))
	{
		printf("CoInitializeEx failed\n");
		return;
	}
	hrInitilize = CoCreateInstance(__uuidof(DesktopWallpaper), NULL, CLSCTX_ALL, IID_PPV_ARGS(&pDesktopWallpaper));
	if (FAILED(hrInitilize))
	{
		printf("CoCreateInstance failed\n");
		return;
	}

	LPWSTR monitorID[256];
	memset(monitorID, 0, 256);
	//UINT32 monitorIdx = 0;
	UINT32 totalMonitor = 0;
	RECT displayRect;

	float refreshMsec, retryMsec, waitMsec;
	if (enableKeystroke)
	{
		std::thread keyStrokeDetectThread(&unsplash::Unsplash_Wei::enableKeystrokeCombo, this);
		while (true)
		{
			if (differentWallpaperPerMonitor)
			{
				hrInitilize = pDesktopWallpaper->GetMonitorDevicePathCount(&totalMonitor);
				/*std::fstream logFileStream;
				logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
				logFileStream << totalMonitor << std::endl;
				logFileStream.close();*/
				if (FAILED(hrInitilize))
				{
					printf("get monitor number failed\n");
					monitorID[0] = L"\0";
				}

				if (monitorIdx >= totalMonitor) monitorIdx = 0;
				/*logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
				logFileStream << monitorIdx << std::endl;
				logFileStream.close();*/
				hrInitilize = pDesktopWallpaper->GetMonitorDevicePathAt(monitorIdx, monitorID);
				/*logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
				logFileStream << monitorID << std::endl;
				logFileStream.close();*/
				//monitorID[0] = L"\0";
				//if (monitorIdx==1) monitorID[0] = L"\0";
				if (FAILED(hrInitilize))
				{
					printf("get monitor ID failed\n");

					//_com_error err(hrInitilize);
					/*logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
					logFileStream << hrInitilize << std::endl;
					logFileStream.close();*/
					monitorID[0] = L"\0"; // refresh all the monitors with the same wallpaper
					//return;
				}
				else
				{
					pDesktopWallpaper->GetMonitorRECT(*monitorID, &displayRect);
					if ((displayRect.bottom - displayRect.top)*(displayRect.right - displayRect.left)==0) //detect possible detached monitors
					{
						monitorIdx++;
						continue;
					}
				}

			} // end of if (differentWallpaperPerMonitor)
			else
				monitorID[0] = L"\0";
			
			// redefine the two waiting time every iteration to lay the ground work for future change of refresh time while program running.
			refreshMsec = refreshPeriod * 3600 * 1000;
			retryMsec = min(refreshPeriod * 3600 * 1000, 5 * 1000); // if failed, retry every 5s unless the default refresh interval is smaller.

			if (this->getIMG() || this->setWallpaper(monitorID))
				waitMsec = retryMsec;
			else
			{
				waitMsec = refreshMsec;
				monitorIdx++;
			}

			/*std::fstream logFileStream;
			logFileStream.open("log.txt", std::fstream::out | std::fstream::app);
			logFileStream << refreshPeriod << std::endl;
			logFileStream << waitMsec << std::endl;
			logFileStream.close();*/

			//seems an odd choice to restart the thread in the next run, but seems the only way to resolve the bug that quick manual refresh twice causes blackscreen
			if (!keyStrokeDetectThread.joinable())
				keyStrokeDetectThread = std::thread(&unsplash::Unsplash_Wei::enableKeystrokeCombo, this);

			for (int i = 0; i < waitMsec / minMsec; i++)
			{
				if (!manualRefresh)
					Sleep(minMsec);
				else
				{
					//keyStrokeDetectThread.join();
					keyStrokeDetectThread.detach(); // modify to accomodate the GUI version which introduces the manual refresh button
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
			if (differentWallpaperPerMonitor)
			{
				hrInitilize = pDesktopWallpaper->GetMonitorDevicePathCount(&totalMonitor);
				if (FAILED(hrInitilize))
				{
					printf("get monitor number failed\n");
					monitorID[0] = L"\0";
				}

				if (monitorIdx >= totalMonitor) monitorIdx = 0;
				hrInitilize = pDesktopWallpaper->GetMonitorDevicePathAt(monitorIdx, monitorID);
				if (FAILED(hrInitilize))
				{
					printf("get monitor ID failed\n");
					monitorID[0] = L"\0";
					//return;
				}
				else
				{
					pDesktopWallpaper->GetMonitorRECT(*monitorID, &displayRect);
					if ((displayRect.bottom - displayRect.top)*(displayRect.right - displayRect.left)==0)
					{
						monitorIdx++;
						continue;
					}
				}
			} //end of if (differentWallpaperPerMonitor)
			else
				monitorID[0] = L"\0";

			// redefine the two waiting time every iteration to lay the ground work for future change of refresh time while program running.
			refreshMsec = refreshPeriod * 3600 * 1000;
			retryMsec = min(refreshPeriod * 3600 * 1000, 5 * 1000); // if failed, retry every 5s unless the default refresh interval is smaller.

			if (this->getIMG() || this->setWallpaper(monitorID))
				waitMsec = retryMsec;
			else
			{
				waitMsec = refreshMsec;
				monitorIdx++;
			}

			Sleep(waitMsec);
		}
	} // end of if(enableKeystroke)

	CoUninitialize();
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
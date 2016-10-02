#include<iostream>
#include<fstream>
#include<chrono>
#include<time.h>
#include<algorithm>
#include"Unsplash_Wei.h"
// windows socket headers need to be ahead of Windows.h! WTF? http://stackoverflow.com/questions/22517036/socket-errors-cant-get-functions-in-winsock2-h
#include<Windows.h>
#include<shlobj.h>
#include<ShellScalingApi.h>

std::string instructions = 
"Wallpapers obtained from https://source.unsplash.com/ \n\n"
"Keystroke commands:\n"
"Crtl + Alt + N: manual refresh the wallpaper\n"
"Crtl + Alt + S: save the current wallpaper\n\n"
"Usage: UnsplashWallpaper [OPTIONS]\n"
"	None	Auto refreshes every 1 hour. Saved wallpapaers are stored in User/Pictures/Unsplash. Wallpaper size is based on the main screen resolution.\n"
"	--help	display the program usage instructions.\n"
"	'auto refresh interval (in hour)'\n"
"	'auto refresh interval (in hour)' 'wallpaper save location (eg. C:\\Unsplash\\)'\n"
"	'auto refresh interval (in hour)' 'wallpaper save location' 'wallpaper width' 'wallpaper height'\n"
;

int main(int argc, char** argv)
{
	FreeConsole(); // hide the terminal window
	SetProcessDPIAware(); // otherwise the screen resolution returned by GetSystemMetrics is scaled by the scaling factor 
	
	//std::cout << std::atoi("x1080");
	//std::string a;
	//std::cin >> a;
	////scanf("%s", &a);
	//fflush(stdin);
	//std::cout << a;
	//std::string createFolderCMD = "mkdir " + a;
	//system(createFolderCMD.c_str());

	unsplash::Unsplash_Wei* Unsplash;

	float timeInterval = 1.f;
	char picFolder[256];
	SHGetFolderPath(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, picFolder);
	std::string saveLoc = picFolder;
	saveLoc += "\\Unsplash\\";
	int wallpaperW = 0, wallpaperH = 0;

	bool inputCheck = true;
	switch (argc)
	{
	case 1:
		//Unsplash = new unsplash::Unsplash_Wei();
		break;
	case 2: // http://stackoverflow.com/questions/7044574/about-the-braces-in-case-statement-in-switch
	{
		std::string singleOp = argv[1];
		std::transform(singleOp.begin(), singleOp.end(), singleOp.begin(), ::tolower); // http://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
		if (!strcmp(singleOp.c_str(), "--help"))
		{
			printf("%s\n", instructions);
			//printf("Press Enter to exit\n");
			fflush(stdin);
			//getchar();
			return 1;
		}
		else
		{
			try
			{
				timeInterval = std::stof(singleOp);
			}
			catch (std::exception e)
			{
				inputCheck = false;
			}
		}
		break;
	}
	case 3:
		try
		{
			timeInterval = std::stof(argv[1]);
			saveLoc = argv[2];
			saveLoc += "\\"; // incase the user doesn't end the folder name with "\"
		}
		catch (std::exception e)
		{
			inputCheck = false;
		}
		break;
	case 5:
		try
		{
			timeInterval = std::stof(argv[1]);
			saveLoc = argv[2];
			saveLoc += "\\";
			wallpaperW = std::stoi(argv[3]);
			wallpaperH = std::stoi(argv[4]);
		}
		catch (std::exception e)
		{
			inputCheck = false;
		}
		break;
	default:
		inputCheck = false;
	}

	if (!inputCheck)
	{
		std::cout << "Wrong inputs. type --help to check the input formats\n";
		return -1;
	}

	Unsplash = new unsplash::Unsplash_Wei(timeInterval, saveLoc, wallpaperW, wallpaperH);
	Unsplash->loopExec(true);

	delete Unsplash;

	/*unsplash::Unsplash_Wei Unsplash;
	Unsplash.setURL();*/

	/*Unsplash.getIMG();
	Unsplash.setWallpaper();*/
	//Unsplash.loopExec(true);

	/*using namespace std::chrono;
	system_clock::time_point today = system_clock::now();
	time_t tt;
	tt = system_clock::to_time_t(today);
	std::cout << "today is: " << ctime(&tt);*/

	//time_t tNow = time(NULL);
	//std::cout << "today is: " << ctime(&tNow);
	//struct tm* timeinfo = localtime(&tNow);
	//char timeStr[256];
	//strftime(timeStr, 256, "%y%m%d%H%M%S", timeinfo);
	//std::cout << timeStr<<std::endl;

	//getchar();

	return 0;
}
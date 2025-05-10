#include <Windows.h>
#include <string>
#include <urlmon.h>
#include <ShlObj.h>
#include <ctime>
#include <shellapi.h>
#include <iostream>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shell32.lib")

int main() {
	// allocating buffer for temp path 
	char temppath[MAX_PATH];
	GetTempPathA(MAX_PATH, temppath);

	// using unixtime, to prevent caching otherwise for a more commercial way setup cdn and hashing...
	std::time_t unixTime = std::time(nullptr);

	std::string appname = "app.exe";

	// downloadURL example: http://127.0.0.1:8401/
	std::string downloadURL = "http://127.0.0.1:8401/" + appname + "?t=" + std::to_string(unixTime);
	char fullPath[MAX_PATH];
	snprintf(fullPath, MAX_PATH, "%s%s", temppath, appname.c_str());

	HRESULT result = URLDownloadToFileA(nullptr, downloadURL.c_str(), fullPath, 0, nullptr);

	if (FAILED(result)) {
		MessageBoxA(NULL, "Failed to download loader.", "Error", MB_OK | MB_ICONERROR);
	}
     
	// setting up struct
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si); 

	// just ctrl and click on createprocess for more info
	BOOL success = CreateProcessA(
		fullPath, // file path
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	);

	// now just waiting for object and closing handle
	if (success) {
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		MessageBoxA(NULL, "Failed to start loader", "Error", MB_OK | MB_ICONERROR);
	}

}





#include "FileManager.hpp"

#include "StringHandler.hpp"
#include <Windows.h>
#include <stdio.h>
#include "Log.hpp"

//TODO: Add support for other platforms

std::vector<std::string> FileManager::getFilesInFolder(std::string folder)
{
	std::vector<std::string> list;

	std::string CWD = getCWD();
	std::string path = CWD;

	if (folder != "") path += "/" + folder;

	HANDLE dirHandle = NULL;
	WIN32_FIND_DATA fileHandle;
	std::string winPath(path + "/" + std::string("*"));
	if ((dirHandle = FindFirstFile(winPath.c_str(), &fileHandle)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (std::string(fileHandle.cFileName) == ".") continue;
			if (std::string(fileHandle.cFileName) == "..") continue;

			std::string filename = path + "/" + fileHandle.cFileName;

			Log("Found file: %s", filename.c_str());

			list.push_back(filename);
		} while (FindNextFile(dirHandle, &fileHandle) != false);
		FindClose(dirHandle);
	}
	else Log("ERROR: Unable to open directory: %s", path.c_str());

	return list;
}

std::string FileManager::getCWD()
{
	std::string CWD;

	char buffer[MAX_PATH];
	CWD = ((GetCurrentDirectory(MAX_PATH, buffer) > 0) ? std::string(buffer) : std::string(""));

	return CWD;
}

std::string FileManager::getFileNameWithoutExt(std::string filename)
{
	std::vector<std::string> parts = StringHandler::explode(filename, "/");
	std::string newFilename = parts[parts.size() - 1];

	parts = StringHandler::explode(newFilename, ".");
	newFilename = parts[0];
	return newFilename;
}

std::string FileManager::getFileNameExt(std::string filename)
{
	std::vector<std::string> parts = StringHandler::explode(filename, ".");

	return (parts.size() <= 1 ? "" : parts[parts.size() - 1]);
}
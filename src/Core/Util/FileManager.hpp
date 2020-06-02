#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

class FileManager
{
public:
	//TODO: Maybe add setter and getter for contents of file?
	//static bool setContents(std::string filename, std::string content, bool relative = true);
	//static std::string getContents(std::string filename, bool relative = true);

  //TODO: Make these functions work across platforms
	//static std::vector<std::string> getFilesInFolder(std::string folder);
	//static std::string getCWD();

	static std::string getFileNameWithoutExt(std::string filename);

	static std::string getFileNameExt(std::string filename);
};

#endif

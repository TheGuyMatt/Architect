#ifndef STRINGHANDLER_HPP
#define STRINGHANDLER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class StringHandler
{
public:
	static std::string Int(int x);
	static std::string Float(float x);
	static std::string Double(double x);
	static std::string Char(char* x);

	static int toInt(const std::string& String);
	static float toFloat(const std::string& String);
	static double toDouble(const std::string& String);

	static std::vector<std::string> explode(std::string str, const std::string& separator);
};

#endif
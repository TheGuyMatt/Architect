#include "StringHandler.hpp"

std::string StringHandler::Int(int x)
{
	std::ostringstream o;

	o << x;

	return o.str();
}

std::string StringHandler::Float(float x)
{
	std::ostringstream o;

	o << x;

	return o.str();
}

std::string StringHandler::Double(double x)
{
	std::ostringstream o;

	o << x;

	return o.str();
}

std::string StringHandler::Char(char* x)
{
	std::string o = x;

	return o;
}

int StringHandler::toInt(const std::string& String)
{
	if (String == "") return 0;

	int x;
	std::stringstream strStream(String);
	strStream >> x;
	return x;
}

float StringHandler::toFloat(const std::string& String)
{
	if (String == "") return 0;

	float x;
	std::stringstream strStream(String);
	strStream >> x;
	return x;
}

double StringHandler::toDouble(const std::string& String)
{
	if (String == "") return 0;

	double x;
	std::stringstream strStream(String);
	strStream >> x;
	return x;
}

std::vector<std::string> StringHandler::explode(std::string str, const std::string& separator)
{
	std::vector<std::string> results;

	int found;
	found = str.find_first_of(separator);
	while (found != std::string::npos)
	{
		if (found > 0) results.push_back(str.substr(0, found));

		str = str.substr(found + 1);
		found = str.find_first_of(separator);
	}

	if (str.length() > 0) results.push_back(str);

	return results;
}
/**
 * Author: rodrigo
 * 2015
 */
#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <vector>
#include <boost/algorithm/string.hpp>

Config::Config()
{
	level = NONE;
	radius = 0.002;
}

Config::~Config()
{
}

void Config::load(const string &_filename)
{
	string line;
	ifstream inputFile;
	inputFile.open(_filename.c_str(), fstream::in);
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			// Parse string line
			vector<string> tokens;
			istringstream iss(line);
			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

			parse(tokens[0], tokens[1]);
		}
		inputFile.close();
	}
	else
		cout << "Unable to open input: " << _filename;
}

void Config::parse(const string _key, const string _value)
{
	if (_key.compare("ballRadius") == 0)
		getInstance()->radius = atof(_value.c_str());
	else if (_key.compare("debug") == 0)
	{
		if (boost::iequals(_value, "low"))
			getInstance()->level = LOW;
		else if (boost::iequals(_value, "medium"))
			getInstance()->level = MEDIUM;
		else if (boost::iequals(_value, "high"))
			getInstance()->level = HIGH;
		else
			getInstance()->level = NONE;
	}
}

double Config::getBallRadius()
{
	return getInstance()->radius;
}

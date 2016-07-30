#include <vector>
#include <string>
#include <sstream>

#include "serverParser.h"
#include "serverWeatherData.h"

Parser::Parser(WeatherDataProtected& temperatures) :
	temperatures(temperatures) {}

void Parser::operator()(std::string& data) {
	if (!data.compare("End")) return;
	
	std::stringstream ss(data);
	std::string city;
	int day, temp;
	
	ss >> day;
	ss >> temp;
	ss >> city;
	
	temperatures.push_value(day, new WeatherValue(temp, city));
}

Parser::~Parser() {}

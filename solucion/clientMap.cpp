#include <utility>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "clientMap.h"

MapWeather::MapWeather(int day, int temp, std::string city) {
	this->day = day;
	this->value = std::make_pair(temp, city);
}

std::string MapWeather::str() {
	std::stringstream ss;
	ss << this->day << " ";
	ss << this->value.first << " ";
	ss << this->value.second << "\n";
	return ss.str();
}

MapWeather::~MapWeather() {}

MapWeather* Map::operator()(std::string& line) {
	std::stringstream ss(line);
	std::string city;
	int day, temp;
	
	ss >> city;
	ss >> temp;
	ss >> day;
	
	return new MapWeather(day, temp, city);
}

Map::~Map() {}

#ifndef MAP_H
#define MAP_H

#include <utility>
#include <string>

class MapWeather {
	private:
		unsigned int day;
		std::pair <int, std::string> value;
	
	public:
		MapWeather(int day, int temp, std::string city);
		std::string str();
		~MapWeather();
};

class Map {
	public:
		MapWeather* operator()(std::string& line);
		~Map();
};

#endif // MAP_H

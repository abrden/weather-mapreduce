#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "serverWeatherData.h"

class Parser {
	private:
		WeatherDataProtected& temperatures;
	
	public:
		explicit Parser(WeatherDataProtected& temperatures);
		void operator()(std::string& data);
		~Parser();
};

#endif // PARSER_H

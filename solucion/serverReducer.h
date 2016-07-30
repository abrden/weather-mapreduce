#ifndef REDUCER_H
#define REDUCER_H

#include <string>
#include <vector>
#include <utility>

#include "commonThread.h"
#include "serverWeatherData.h"

class ValueCmp {
	public:
		bool operator()(const WeatherValue* a, const WeatherValue* b);
};

class Reducer : public Thread {
	private:
		int day;
		std::vector <WeatherValue*>& values;
		WeatherResultsProtected& results;

		void save_result(int temp, std::string cities);
		
	public:
		Reducer(int day, std::vector <WeatherValue*>& values, 
		WeatherResultsProtected& results);
		void run();
		~Reducer();
};

#endif // REDUCER_H

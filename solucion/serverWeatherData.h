#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include <map>
#include <vector>
#include <string>
#include <utility>

#include "commonThread.h"

class WeatherValue {
	private:
		int temperature;
		std::string city;
		
	public:
		WeatherValue(int temperature, std::string city);
		int get_temperature() const;
		std::string get_city() const;
		~WeatherValue();
};

class WeatherData {
	private:
		std::map <int, std::vector <WeatherValue*> > data;
		
	public:
		WeatherData();
		std::vector<int> get_days();
		std::vector <WeatherValue*>& get_value(int day);
		void push_value(int day, WeatherValue* value);
		~WeatherData();
};

class WeatherDataProtected {
	private:
		Mutex m;
		WeatherData data;
		
	public:
		WeatherDataProtected();
		std::vector<int> get_days();
		std::vector <WeatherValue*>& get_value(int day);
		void push_value(int day, WeatherValue* value);
		~WeatherDataProtected();
};

class WeatherResults {
	private:
		std::vector <std::string> results;
	
	public:
		WeatherResults();
		std::string& get_day_result(int day);
		void set_day_result(int day, std::string result);
		~WeatherResults();
};

class WeatherResultsProtected {
	private:
		Mutex m;
		WeatherResults results;
	
	public:
		WeatherResultsProtected();
		std::string& get_day_result(int day);
		void set_day_result(int day, std::string result);
		~WeatherResultsProtected();
};

#endif // WEATHER_DATA_H

#include <map>
#include <vector>
#include <string>
#include <utility>

#include "serverWeatherData.h"
#include "commonThread.h"

#define DAYS_IN_A_MONTH 31

WeatherValue::WeatherValue(int temperature, std::string city) :
 temperature(temperature), city(city) {}

int WeatherValue::get_temperature() const {
	return this->temperature;
}

std::string WeatherValue::get_city() const {
	return this->city;
}

WeatherValue::~WeatherValue() {}

WeatherData::WeatherData() {}

typedef std::map <int, std::vector <WeatherValue*> >::iterator data_it;

std::vector<int> WeatherData::get_days() {
	std::vector<int> days;
	for (data_it it = this->data.begin(); it != this->data.end(); ++it)
		days.push_back(it->first);
	return days;
}

std::vector <WeatherValue*>& WeatherData::get_value(int day) {
	return this->data[day];
}

void WeatherData::push_value(int day, WeatherValue* value) {
	this->data[day].push_back(value);
}

WeatherData::~WeatherData() {
	for (data_it it = this->data.begin(); it != this->data.end(); ++it)
		for (unsigned int i = 0; i < it->second.size(); ++i)
			delete it->second[i];
}

WeatherDataProtected::WeatherDataProtected() {}

std::vector<int> WeatherDataProtected::get_days() {
	return this->data.get_days();
}

std::vector <WeatherValue*>& WeatherDataProtected::get_value(int day) {
	return this->data.get_value(day);
}

void WeatherDataProtected::push_value(int day, WeatherValue* value) {
	Lock l(this->m);
	this->data.push_value(day, value);
}

WeatherDataProtected::~WeatherDataProtected() {}

WeatherResults::WeatherResults() : results(DAYS_IN_A_MONTH) {}

std::string& WeatherResults::get_day_result(int day) {
	return this->results[day - 1];
}

void WeatherResults::set_day_result(int day, std::string result) {
	this->results[day - 1] = result;
}

WeatherResults::~WeatherResults() {}
		
WeatherResultsProtected::WeatherResultsProtected() {}

std::string& WeatherResultsProtected::get_day_result(int day) {
	return this->results.get_day_result(day);
}

void WeatherResultsProtected::set_day_result(int day, std::string result) {
	Lock l(this->m);
	this->results.set_day_result(day, result);
}

WeatherResultsProtected::~WeatherResultsProtected() {}

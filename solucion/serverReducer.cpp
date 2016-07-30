#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

#include "serverReducer.h"
#include "commonThread.h"


bool ValueCmp::operator()(const WeatherValue* a, const WeatherValue* b) {
	return a->get_temperature() > b->get_temperature() || 
	((a->get_temperature() == b->get_temperature()) && 
	(a->get_city() < b->get_city()));
}

Reducer::Reducer(int day, std::vector <WeatherValue*>& values, 
WeatherResultsProtected& results) : 
day(day), values(values), results(results) {}

void Reducer::save_result(int temp, std::string cities) {
	std::stringstream ss;
	ss << this->day << ": " << cities << " (" << temp << ")\n";
	this->results.set_day_result(this->day, ss.str());
}

void Reducer::run() {
	std::sort(this->values.begin(), this->values.end(), ValueCmp());
	
	int max_temp = this->values[0]->get_temperature();
	std::stringstream cities;
	cities << this->values[0]->get_city();

	for (unsigned int i = 1; i < this->values.size(); i++) {
		WeatherValue* tie_temp = this->values[i];

		if (max_temp == tie_temp->get_temperature()) {
			cities << "/" << tie_temp->get_city();
		} else {
			break;
		}
	}
	
	this->save_result(max_temp, cities.str());
}

Reducer::~Reducer() {}

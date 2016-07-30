#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>

#include "serverWeatherServer.h"
#include "commonAddrInfo.h"
#include "serverWeatherData.h"
#include "serverAcceptor.h"
#include "serverParser.h"

#define END_ID_LEN 4
#define MAX_CANT_THREADS 4

WeatherServer::WeatherServer(Socket& server, const char* port) :
server(server) {
	ServerAddrInfo info(port);
	this->server(info());
	this->server.bind_and_listen(info());
}

void WeatherServer::receive_weather_data() {
	QuitProtected quit;
	Acceptor acceptor(this->server, this->temperatures, quit);
	acceptor.start();
	while(!quit())
		if (getchar() == 'q') quit.switch_to_true();
	this->server.shutdown();
	acceptor.join();
}

void WeatherServer::launch_reducers() {
	std::vector<int> keys = this->temperatures.get_days();
	for (unsigned int i = 0; i < keys.size(); ++i) {
		this->reducers.push_back(
			new Reducer(keys[i], this->temperatures.get_value(keys[i]), 
			this->results));
	}
	

	for (unsigned int i = 0;
		i < (this->reducers.size() + MAX_CANT_THREADS);
		i += MAX_CANT_THREADS) {
		for (unsigned int j = i;
			j < (i + MAX_CANT_THREADS) && j < this->reducers.size();
			++j)
			this->reducers[j]->start();
			
		for (unsigned int j = i;
			j < (i + MAX_CANT_THREADS) && j < this->reducers.size();
			++j)
			this->reducers[j]->join();
	}
}

void WeatherServer::print_results() {
	for (unsigned int i = 1; i <= this->reducers.size(); ++i) {
		std::cout << this->results.get_day_result(i);
	}
}

void WeatherServer::operator()() {
	this->receive_weather_data();
	this->launch_reducers();
	this->print_results();
}

WeatherServer::~WeatherServer() {
	for (unsigned int i = 0; i < this->reducers.size(); i++)
		delete this->reducers[i];
}

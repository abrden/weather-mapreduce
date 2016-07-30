#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

#include "clientWeatherClient.h"
#include "commonAddrInfo.h"
#include "commonSocket.h"
#include "clientMap.h"

#define END_ID_LEN 4

WeatherClient::WeatherClient(Socket& client, const char* hostname, 
const char* port) : client(client) {
	struct addrinfo* ptr;
	bool connected = false;
	ClientAddrInfo info(hostname, port);
	
	for (ptr = info(); ptr != NULL && connected == false; ptr = ptr->ai_next) {
		this->client(ptr);
		try {
			this->client.connect(ptr);
		} catch (const SocketError &e) {
			if (ptr->ai_next) 
				continue;
			else 
				throw;
		}
		connected = true;
	}
}

void WeatherClient::send_map_result(MapWeather* data) {
	std::string result = data->str();
	this->client.send(result.c_str(), sizeof(char) * result.length());
}

void WeatherClient::send_map_results_end() {
	std::string end_id = "End\n";
	this->client.send(end_id.c_str(), sizeof(char) * END_ID_LEN);
}

void WeatherClient::operator()() {
	std::string line;
	Map map;
	MapWeather* result;
	
	while (std::getline(std::cin, line)) {
		if (!line.compare("")) continue;
		
		result = map(line);
		send_map_result(result);
		delete result;
	}
	send_map_results_end();
}

WeatherClient::~WeatherClient() {
	this->client.shutdown();
}

#ifndef WEATHER_CLIENT_H
#define WEATHER_CLIENT_H

#include "commonSocket.h"
#include "clientMap.h"

class WeatherClient {
	private:
		Socket& client;
		
		void send_map_result(MapWeather* data);
		void send_map_results_end();
	
	public:
		WeatherClient(Socket& client, const char* hostname, const char* port);
		void operator()();
		~WeatherClient();
};

#endif // WEATHER_CLIENT_H

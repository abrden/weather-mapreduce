#ifndef WEATHER_SERVER_H
#define WEATHER_SERVER_H

#include <vector>

#include "commonSocket.h"
#include "serverReducer.h"
#include "serverWeatherData.h"

class WeatherServer {
	private:
		Socket& server;
		WeatherDataProtected temperatures;
		std::vector <Reducer*> reducers;
		WeatherResultsProtected results;
		
		void receive_weather_data();
		void launch_reducers();
		void print_results();
		
	public:
		WeatherServer(Socket& server, const char* port);
		void operator()();
		~WeatherServer();
};

#endif // WEATHER_SERVER_H

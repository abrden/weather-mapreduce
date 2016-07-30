#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <vector>
#include <string>

#include "commonSocket.h"
#include "commonThread.h"
#include "serverWeatherData.h"

class Receiver : public Thread {
	private:
		Socket peer;
		WeatherDataProtected& temperatures;
		
	public:
		Receiver(int peers_fd, WeatherDataProtected& temperatures);
		void run();
		~Receiver();
};

class QuitProtected {
	private:
		Mutex m;
		bool quit;
	
	public:
		QuitProtected();
		void switch_to_true();
		bool operator()();
		~QuitProtected();
};

class Acceptor : public Thread {
	private:
		Socket& server;
		std::vector <Receiver*> receivers;
		WeatherDataProtected& temperatures;
		QuitProtected& quit;
		
	public:
		Acceptor(Socket& server, WeatherDataProtected& temperatures, 
		QuitProtected& quit);
		void run();
		~Acceptor();
};

#endif // ACCEPTOR_H

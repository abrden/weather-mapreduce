#include <vector>
#include <string>
#include <sstream>

#include "serverAcceptor.h"
#include "commonThread.h"
#include "commonSocket.h"
#include "serverParser.h"
#include "serverWeatherData.h"

Receiver::Receiver(int peers_fd, WeatherDataProtected& temperatures) :
 peer(peers_fd), temperatures(temperatures) {}

void Receiver::run() {
	Parser parser(this->temperatures);
	char c;
	std::stringstream ss;
	std::string data;
		
	while (data.compare("End")) {
		ss.str("");
			
		this->peer.receive(&c, sizeof(char));
		while (c != '\n') {
			ss << c;
			this->peer.receive(&c, sizeof(char));
		}
			
		data = ss.str();
		parser(data);
	}
}

Receiver::~Receiver() {
	peer.shutdown();
}

QuitProtected::QuitProtected() {
	this->quit = false;
}
void QuitProtected::switch_to_true() {
	Lock l(this->m);
	this->quit = true;
}

bool QuitProtected::operator()() {
	Lock l(this->m);
	return this->quit;
}

QuitProtected::~QuitProtected() {}

Acceptor::Acceptor(Socket& server, WeatherDataProtected& temperatures, 
QuitProtected& quit) : server(server), temperatures(temperatures), quit(quit) {}

void Acceptor::run() {
	int peers_fd;
	Receiver* receiver;
	while (!this->quit()) {
		try {
			peers_fd = this->server.accept();
		} catch (const SocketError &e) {
			continue;
		}
		
		receiver = new Receiver(peers_fd, this->temperatures);
		receiver->start();
		this->receivers.push_back(receiver);
	}
}

Acceptor::~Acceptor() {
	for (unsigned int i = 0; i < this->receivers.size(); ++i) {
		this->receivers[i]->join();
		delete this->receivers[i];
	}
}

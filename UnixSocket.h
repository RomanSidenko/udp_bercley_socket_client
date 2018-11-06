#ifndef UNIXSOCKET_H
#define UNIXSOCKET_H
#include "AbstractSocket.h"
class UnixSocket :
	public AbstractSocket
{
public:
	UnixSocket();
	~UnixSocket();

	bool connectToHost(const std::string& hostName, const unsigned short hostPort) override;
	void disconnect() override;
	unsigned long readData(char* buf, size_t bufferSize) override;
	bool writeData(char* data, size_t bufferSize) override;
	bool sendCommand(uint8_t command) override; ///realizaciya!!
	int reciveCommand(char* commandBuffer) override; ///realizaciya!!

private:
	bool setNonBlockingMode();
	bool openSocket(sockaddr_in& address) override;
};

#endif  // UNIXSOCKET_H


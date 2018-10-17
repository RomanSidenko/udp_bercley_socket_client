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
	unsigned long readData(char* buf, unsigned long bufSize) override;
	bool writeData(char* data, unsigned long dataSize) override;

private:
	bool setNonBlockingMode();
	bool openSocket() override;
	bool bindingSocket(sockaddr_in& address) override;
};

#endif  // UNIXSOCKET_H


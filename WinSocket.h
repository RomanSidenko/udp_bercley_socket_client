#ifndef WINSOCKET_H
#define WINSOCKET_H
#include "AbstractSocket.h"

class WinSocket :public AbstractSocket
{
public:

	explicit WinSocket();
	~WinSocket();

	bool connectToHost(const std::string& hostName, const unsigned short hostPort) override;
	void disconnect() override;
	unsigned long readData(char* buf, unsigned long bufSize) override;
	bool writeData(char* data, unsigned long dataSize) override;

private:
	int init();
	bool setNonBlockingMode();
	bool openSocket() override;
	bool bindingSocket(sockaddr_in& address) override;
	
	
	
};
#endif // WINSOCKET_H


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
	unsigned long readData(char* buf, size_t bufferSize) override;
	bool writeData(char* data, size_t bufferSize) override;
	bool sendCommand(uint8_t command) override;
	int reciveCommand(char* commandBuffer) override;

private:
	int init();
	bool setNonBlockingMode();
	bool openSocket(sockaddr_in& address) override;
	int m_counter;
	
};
#endif // WINSOCKET_H


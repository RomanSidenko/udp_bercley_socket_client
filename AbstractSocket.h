#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H
#include <string>

class sockaddr_in;
class AbstractSocket
{
public:
	AbstractSocket();
	virtual ~AbstractSocket();

	virtual bool connectToHost(const std::string& hostName, const unsigned short hostPort) = 0;
	virtual void disconnect() = 0;
	virtual unsigned long readData(char* buf, size_t bufferSize) = 0;
	virtual bool writeData(char* data, size_t bufferSize) = 0;
	



protected:
	int m_descriptor;
	sockaddr_in* m_address;

	virtual bool openSocket(sockaddr_in& address) = 0;
	int getSocketDescriptor() const { return m_descriptor; }


};

#endif // ABSTRACTSOCKET_H
#ifndef SOCKET_H
#define SOCKET_H
#include <iostream>


class AbstractSocket;

class Socket
{
public:
	
	Socket();
	~Socket();
	bool connectToHost(const std::string& hostName, const unsigned short hostPort);
	void disconnect();
	
	unsigned long readData(char* buf, size_t bufferSize);
	bool writeData(char* data, size_t bufferSize);

private:
	AbstractSocket* m_socket;
	
};
#endif  //SOCKET_H


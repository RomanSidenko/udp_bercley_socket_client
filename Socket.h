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
	
	unsigned long readData(char* buf, unsigned long bufSize);
	bool writeData(char* data, unsigned long dataSize);

private:
	AbstractSocket* m_socket;
	void setBufferSize(unsigned long bufSize);
	unsigned long getBuferSize();
	
};
#endif  //SOCKET_H


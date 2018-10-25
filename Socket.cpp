#include "Socket.h"
//#if defined  _WIN32
#include "WinSocket.h"
//#else
//#include "UnixSocket.h"
//#endif



Socket::Socket() 
{
//#if defined  _WIN32
	m_socket = new WinSocket;
//#else
//	AbstractSocket*socket = new UnixSocket;
//#endif

}


Socket::~Socket()
{
	disconnect();
}

bool Socket::connectToHost(const std::string & hostName, const unsigned short hostPort)
{
	return false;
}

void Socket::disconnect()
{
	m_socket->disconnect();
}

unsigned long Socket::readData(char* buf, size_t bufferSize)
{
	return m_socket->readData(buf, bufferSize);
}

bool Socket::writeData(char * data, size_t bufferSize)
{
	return m_socket->writeData(data, bufferSize);
}


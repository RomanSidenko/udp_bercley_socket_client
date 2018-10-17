#include "Socket.h"
//#if defined  _WIN32
#include "WinSocket.h"
//#else
//#include "UnixSocket.h"
//#endif



Socket::Socket() 
{
//#if defined  _WIN32
	AbstractSocket* m_socket = new WinSocket;
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

unsigned long Socket::readData(char* buf, unsigned long bufSize)
{
	return m_socket->readData(buf, bufSize);
}

bool Socket::writeData(char * data, unsigned long dataSize)
{
	return m_socket->writeData(data, dataSize);
}

void Socket::setBufferSize(unsigned long bufSize)
{
	m_socket->setBufferSize(bufSize);
}

unsigned long Socket::getBuferSize()
{
	return m_socket->getBuferSize();
}

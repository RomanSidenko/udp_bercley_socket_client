#include "UnixSocket.h"
#include <iostream>


#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>


#define DEFAULT_PORT 12345

UnixSocket::UnixSocket()
{
	sockaddr_in m_address;
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	m_address.sin_port = htons(DEFAULT_PORT);
	if (!openSocket())
		std::cout << "socket not open" << std::endl;
	else
		std::cout << "Descriptor " << getSocketDescriptor() << std::endl;
	listen(m_descriptor, 5);
}


UnixSocket::~UnixSocket()
{
	disconnect();
}

bool UnixSocket::connectToHost(const std::string & hostName, const unsigned short hostPort)
{
	return false;
}

void UnixSocket::disconnect()
{
	close(m_descriptor);
}

bool UnixSocket::bindingSocket(sockaddr_in & address)
{
	if (bind(m_descriptor, (const sockaddr*)& address, sizeof(sockaddr_in)) < 0)
	{
		return false;
		///add error handling
	}
	return false;
}

unsigned long UnixSocket::readData(char* buf, unsigned long bufSize)
{
	int received_bytes = -1;
	while (true)
	{
		unsigned char packetData[256];
		unsigned int maximumPacketSize = sizeof(packetData);

		sockaddr_in from;
		int fromLength = sizeof(from);

		received_bytes = recvfrom(m_descriptor, (char*)packetData, maximumPacketSize, 0, (sockaddr*)&from, &fromLength);

		if (received_bytes <= 0)
			break;
		else
			std::cout << "packet" << packetData;

		unsigned int fromAddress = ntohl(from.sin_addr.s_addr);
		unsigned int fromPort = ntohs(from.sin_port);
	}
	return received_bytes;
}

bool UnixSocket::writeData(char * data, unsigned long dataSize)
{
	int sent_bytes = sendto(m_descriptor, (const char*)data, dataSize, 0, (sockaddr*)& m_address, sizeof(sockaddr_in));
	if (sent_bytes != dataSize)
	{
		return false;
		std::cout << "failed to send packet" << std::endl;
		///add error handling
	}
	return true;
}


bool UnixSocket::setNonBlockingMode()
{
	int nonBlocking = 1;
	if (fcntl(m_descriptor, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
	{
		return false;
	}
	return false;
}

bool UnixSocket::openSocket()
{
	m_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if ((m_descriptor < 0) || (!bindingSocket(*m_address)) || (!setNonBlockingMode()))
	{
		return false;
		///add error handing open socket
	}
	return true;

}

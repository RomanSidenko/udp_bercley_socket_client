#include "WinSocket.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <cstdlib>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT 12345


WinSocket::WinSocket()
{
	sockaddr_in m_address;
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	m_address.sin_port = htons(DEFAULT_PORT);

	if (!openSocket(m_address))
		std::cout << "socket not open" << std::endl;
	else
		std::cout << "Descriptor " << getSocketDescriptor() << std::endl;
}


WinSocket::~WinSocket()
{
	disconnect();
}

bool WinSocket::connectToHost(const std::string& hostName, const unsigned short hostPort)
{
	return false;
}

void WinSocket::disconnect()
{
	closesocket(m_descriptor);
	WSACleanup();
}

unsigned long WinSocket::readData(char* buf, size_t bufferSize)
{
	int receivedBytes = -1;
	sockaddr_in from;
	int fromLength = sizeof(from);

	while (true)
	{
		receivedBytes = recvfrom(m_descriptor, buf, static_cast<int>(bufferSize), 0, (sockaddr*)&from, &fromLength);
		if (receivedBytes <= 0)
			break;
	}
	//unsigned int fromAddress = ntohl(from.sin_addr.s_addr);
	//unsigned int fromPort = ntohs(from.sin_port);
	return receivedBytes;
}

bool WinSocket::writeData(char* data, size_t bufferSize)
{
	int sent_bytes = sendto(m_descriptor, data, static_cast<int>(bufferSize), 0, (sockaddr*)& m_address, sizeof(sockaddr_in));
	if (sent_bytes != bufferSize)
	{
		return false;
		std::cout << "failed to send packet" << std::endl;
		///add error handling
	}
	return true;
}

bool WinSocket::sendCommand(uint8_t command)
{
	char commBuffer[8];
	_itoa(command, commBuffer, 10);
	sockaddr_in m_address;
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	m_address.sin_port = htons(DEFAULT_PORT);
	int sent_bytes = sendto(m_descriptor, commBuffer, sizeof(commBuffer), 0, (sockaddr*)& m_address, sizeof(sockaddr_in));
	if (sent_bytes != sizeof(commBuffer))
	{
		std::cout << "failed to send command" << WSAGetLastError() << std::endl;
		disconnect();
		return false;
	}
	return true;
}

int WinSocket::reciveCommand(char* commandBuffer)
{
	int receivedBytes = -1;
	sockaddr_in from;
	int fromLength = static_cast<int>(sizeof(from));

	receivedBytes = recvfrom(m_descriptor, commandBuffer, strlen(commandBuffer) /*its size is 8 bytes sizeof(int8_t)*/, 0, (sockaddr*)&from, &fromLength);
	return receivedBytes;
}

int WinSocket::init()
{
	WSADATA wsaData;
	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsaData)))
	{
		std::cout <<"Error in init(): " << WSAGetLastError()<<std::endl;
		return false;
	}
	return true;
}

bool WinSocket::setNonBlockingMode()
{
	DWORD nonBlocking = 1;
	if (ioctlsocket(m_descriptor, FIONBIO, &nonBlocking) != 0)
	{
		std::cout << "Error in setNonBlockingMode(): " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool WinSocket::openSocket(sockaddr_in& address)
{
	init();
	m_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if ((m_descriptor == INVALID_SOCKET) || (!setNonBlockingMode()))
	{
		std::cout << "Error in openSocket(): " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;

}

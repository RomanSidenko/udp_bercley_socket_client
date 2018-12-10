#include "FileManager.h"
#include <iostream>



FileManager::FileManager()
	: m_fileName()
	, m_fileSize(0)
	, m_bufferSize(0)
	, m_pos(0)
{
	
}


FileManager::~FileManager()
{
	closeStream();
}

std::string FileManager::getFileName() const
{
	return m_fileName;
}


bool FileManager::readFile(std::string& fileName)
{
	try
	{
		m_in.open(fileName.c_str(), std::ios::binary);
		if (!m_in.is_open())
		{
			std::cout << "File is not open" << std::endl;
			return false;
		}
		else
		{
			m_fileSize = m_in.seekg(0, std::ios::end).tellg();
			m_in.seekg(0, std::ios::beg);
			setFileName(fileName);
			setFileNameSize(strlen(fileName.c_str()));
		}
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return false;
	}
	
	return true;
}

bool FileManager::writeFile(char* buffer, std::string fileName = std::string())
{
	if (fileName.empty() && !m_fileName.empty())
		fileName = m_fileName;
	if (!m_out.is_open())
	{
		m_out.open(fileName, std::ios::binary);
		if (!m_out.is_open())
		{
			std::cout << "File is not open" << std::endl;
			return false;
		}
			
		else
		{
			m_out.write(buffer, sizeof(buffer));
			m_pos += sizeof(buffer);
		}
	}
	else
	{
		m_out.write(buffer, sizeof(buffer));
		m_pos += sizeof(buffer);
	}
	return true;
}

size_t FileManager::getFileSize() const
{
	return m_fileSize;
}

void FileManager::setFileSize(size_t fileSize)
{
	m_fileSize = fileSize;
}

size_t FileManager::getBufferSize() const
{
	if (m_bufferSize == 0)
		return 1024;
	return m_bufferSize;
}

void FileManager::setFileNameSize(size_t fileNameSize)
{
	m_fileNameSize = fileNameSize;
}

size_t FileManager::getFileNameSize() const
{
	return m_fileNameSize;
}

void FileManager::setFileName(char * fileName)
{
	m_fileName = fileName;
}

void FileManager::setFileName(std::string & fileName)
{
	m_fileName = fileName;
}

void FileManager::setBufferSize(size_t size)
{
	m_bufferSize = size;
}

char* FileManager::getBuffer()
{
	char buffer[1024];
	memset(&buffer, 0, sizeof(buffer));
	m_in.read(buffer, sizeof(buffer));
	if (m_in.eof())
		setBufferSize(std::abs(m_pos - static_cast<std::streamsize>(m_fileSize)));
	else
	{
		m_pos = m_in.tellg();
		m_in.seekg(m_pos);
		setBufferSize(sizeof(buffer));
	}
	return buffer;
}

std::streampos FileManager::getPos()
{
	return m_pos;
}

void::FileManager::closeStream()
{
	m_in.close();
}

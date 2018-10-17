#include "FileManager.h"
#include <iostream>

#define DEFAULT_FILE_NAME "resivedFile.txt"

FileManager::FileManager()
	: m_fileName()
	, m_fileSize(0)
	, m_buffer(nullptr)
	, m_in(nullptr)
	, m_out(nullptr)
{
	
}


FileManager::~FileManager()
{
	delete[] m_buffer;
}

std::string FileManager::getFileName() const
{
	return m_fileName;
}

void FileManager::setFileName(std::string& fileName)
{
	m_fileName = fileName;
}

bool FileManager::readFile(std::string& fileName)
{
	const char* array = fileName.c_str();
	if ((m_in = fopen(array, "rb")) == NULL)
	{
		std::cout << "File is not open" << std::endl;
		return false;
	}
	setFileName(fileName);
	getFileSize();
	if (!formBuffer())
	{
		std::cout << "Buffer not formed" << std::endl;
		return false;

	}
	return true;
}

bool FileManager::writeFile(char* buffer, std::string fileName = std::string())
{
	if (fileName.empty() && !m_fileName.empty())
		fileName = m_fileName;
	const char* name = fileName.c_str();
	m_out = fopen(name, "wb");
	size_t bufferSize = sizeof(buffer);
	size_t outPutSize = fwrite(buffer, 1, bufferSize, m_out);
	fclose(m_out);
	if(bufferSize != outPutSize)
		return false;
	return true;
}

bool FileManager::writeFile(std::vector<char> data, std::string fileName = std::string())
{
	if (fileName.empty() && !m_fileName.empty())
		fileName = m_fileName;
	else
		fileName = DEFAULT_FILE_NAME;
	const char* name = fileName.c_str();
	m_out = fopen(name, "wb");
	size_t bufferSize = sizeof(data);
	size_t outPutSize = fwrite(data.data(), sizeof data[0], bufferSize, m_out);
	fclose(m_out);
	if (bufferSize != outPutSize)
		return false;
	return true;
}

bool FileManager::formBuffer()
{
	size_t sizeRead;
	allocMemoryForBuff(m_buffer, m_fileSize);
	while (!feof(m_in))
	{
		sizeRead = fread(m_buffer, 1, sizeof(m_buffer), m_in);
	}
	if (sizeRead <= 0 || sizeRead != m_fileSize)
	{
		///error
		return false;
	}
	return true;
}

unsigned long FileManager::getFileSize()
{
	fseek(m_in, 0, SEEK_END);							// set the position to the end of the file
	m_fileSize = ftell(m_in);                           // get the size in bytes
	rewind(m_in);										// set the internal file position indicator to the beginning of the file.
	return m_fileSize;
}

char * FileManager::getBuffer() const
{
	return m_buffer;
}

bool FileManager::allocMemoryForBuff(char * buffer, unsigned long fileSize)
{
	m_buffer = new char[fileSize];  ///char[fileSize+1] ??????
	//m_buffer = (char*)malloc(sizeof(char) * m_fileSize);   //c style
	if (m_buffer == NULL)
	{
		std::cout << "Memory malloc for bufer error" << std::endl;
		return false;
	}
	return true;
}

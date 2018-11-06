#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <fstream>


class FileManager
{
public:
	FileManager();
	~FileManager();

	enum Commands
	{
		comSendFileName = 0,
		comSendFileNameSize,
		comSendFileSize,
		comSendFile
	};

	std::string getFileName() const;
	
	bool readFile(std::string& fileName);
	bool writeFile(char* buffer, std::string fileName);
	size_t getFileSize() const;
	void setFileSize(size_t fileSize);
	size_t getBufferSize() const;
	void setFileNameSize(size_t fileNameSize);
	size_t getFileNameSize() const;
	void setFileName(char* fileName);
	void setFileName(std::string& fileName);
	char* getBuffer();
	std::streampos getPos();
	void closeStream();

	

private:
	std::string m_fileName;
	size_t m_fileSize;
	size_t m_bufferSize;
	size_t m_fileNameSize;
	std::streampos m_pos;
	std::ifstream m_in;
	std::ofstream m_out;

	void setBufferSize(size_t size);
	
};

#endif  //FILEMANAGER


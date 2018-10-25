#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <fstream>


class FileManager
{
public:
	FileManager();
	~FileManager();

	std::string getFileName() const;
	
	bool readFile(const std::string& fileName);
	bool writeFile(char* buffer, std::string fileName);
	std::streamsize getFileSize();
	size_t getBufferSize() const;
	char* getBuffer();
	std::streampos getPos();
	void closeStream();
	

private:
	std::string m_fileName;
	std::streamsize m_fileSize;
	size_t m_bufferSize;
	std::streampos m_pos;
	std::ifstream m_in;
	std::ofstream m_out;
	void setFileName(const std::string& fileName);
	void setBufferSize(size_t size);
	
};

#endif  //FILEMANAGER


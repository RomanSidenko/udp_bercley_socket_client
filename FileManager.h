#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <cstdio>
#include <vector>


//#define DEFULT_FILE_NAME_SIZE 50
class FileManager
{
public:
	FileManager();
	~FileManager();

	std::string getFileName() const;
	
	bool readFile(std::string& fileName);
	bool writeFile(char* buffer, std::string fileName);
	bool writeFile(std::vector<char> data, std::string filename);
	unsigned long getFileSize();
	char* getBuffer() const;
	

private:
	std::string m_fileName;
	unsigned long m_fileSize;
	char* m_buffer;
	FILE* m_in;
	FILE* m_out;

	bool allocMemoryForBuff(char* buffer, unsigned long fileSize);
	bool formBuffer();
	void setFileName(std::string& fileName);
	
};

#endif  //FILEMANAGER


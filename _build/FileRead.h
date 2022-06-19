#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileRead
{
public:
	static std::vector< std::string > file_read(const char* filepath)
	{
		std::vector<std::string> dataReturn;
		std::fstream file(filepath, std::ios::in);
		std::string singleLine;
		while (file >> singleLine)
		{

			dataReturn.push_back(singleLine);
		}
		file.close();
		return dataReturn;
	}
	static void file_write(std::vector<std::string> data, const char* filepath)
	{
		std::ifstream file(filepath,std::ios::out);
		


	}
};

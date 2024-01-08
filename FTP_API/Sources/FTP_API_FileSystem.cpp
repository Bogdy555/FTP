#include "../Headers/FTP_API.hpp"



#ifdef _WIN32



bool FTP_API::FileSystem::ListFiles(const char* _Folder, std::vector<std::string>& _FileNames)
{

	if (!_Folder || _Folder[0] == '\0')
	{
		return false;
	}

	_FileNames.clear();

	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA((_Folder + std::string("*")).c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	do 
	{
		if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
		{
			_FileNames.push_back(findFileData.cFileName);
		}
	} while (FindNextFileA(hFind, &findFileData) != 0);

	FindClose(hFind);
	return true;
}

bool FTP_API::FileSystem::SaveFile(const char* _FileName, const size_t _FileLength, const uint8_t* _FileData)
{
	if (!_FileName || _FileName[0] == '\0') {
		return false;
	}

	HANDLE hFile = CreateFileA(_FileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	if (!_FileLength) {
		CloseHandle(hFile);
		return true;
	}

	DWORD bytesWritten;
	if (!WriteFile(hFile, _FileData, (DWORD)(_FileLength), &bytesWritten, NULL) || bytesWritten != _FileLength) {
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);

	return true;
}

bool FTP_API::FileSystem::LoadFile(const char* _FileName, size_t& _FileLength, BytesBuffer& _FileData)
{
	if (!_FileName || _FileName[0] == '\0') 
	{
		return false;
	}

	HANDLE hFile = CreateFileA(_FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		_FileLength = 0;
		return false;
	}

	_FileLength = GetFileSize(hFile, NULL);
	if (_FileLength == INVALID_FILE_SIZE) 
	{
		CloseHandle(hFile);
		_FileLength = 0;
		return false;
	}

	if (!_FileLength)
	{
		CloseHandle(hFile);
		return true;
	}

	_FileData = new uint8_t[_FileLength];

	if (!_FileData) 
	{
		CloseHandle(hFile);
		_FileLength = 0;
		return false;
	}

	DWORD bytesRead;
	if (!ReadFile(hFile, _FileData, (DWORD)(_FileLength), &bytesRead, NULL) || bytesRead != _FileLength) 
	{
		CloseHandle(hFile);
		delete[] _FileData;
		_FileLength = 0;
		return false;
	}

	CloseHandle(hFile);

	return true;
}



#endif



#ifdef __unix__



bool FTP_API::FileSystem::ListFiles(const char* _Folder, std::vector<std::string>& _FileNames)
{
	if (!_Folder || _Folder[0] == '\0')
	{
		return false;
	}

	DIR* dir = opendir(_Folder);
	if (!dir)
	{
		return false;
	}

	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			_FileNames.push_back(entry->d_name);
		}
	}

	closedir(dir);

	return true;
}

bool FTP_API::FileSystem::SaveFile(const char* _FileName, const size_t _FileLength, const uint8_t* _FileData)
{
	if (!_FileName || _FileName[0] == '\0')
	{
		return false;
	}

	int fd = open(_FileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		return false;
	}

	if (!_FileLength)
	{
		close(fd);
		return true;
	}

	ssize_t bytesWritten = write(fd, _FileData, _FileLength);
	if (bytesWritten != _FileLength)
	{
		close(fd);
		return false;
	}

	close(fd);

	return true;

}

bool FTP_API::FileSystem::LoadFile(const char* _FileName, size_t& _FileLength, BytesBuffer& _FileData)
{
	if (!_FileName || _FileName[0] == '\0')
	{
		return false;
	}

	int fd = open(_FileName, O_RDONLY);
	if (fd == -1)
	{
		_FileLength = 0;
		return false;
	}

	struct stat st;
	if (fstat(fd, &st) == -1)
	{
		close(fd);
		_FileLength = 0;
		return false;
	}

	_FileLength = st.st_size;

	if (!_FileLength)
	{
		close(fd);
		return true;
	}

	_FileData = new uint8_t[_FileLength];

	if (!_FileData)
	{
		close(fd);
		_FileLength = 0;
		return false;
	}

	size_t bytesRead = read(fd, _FileData, _FileLength);
	if (bytesRead != _FileLength)
	{
		close(fd);
		delete[] _FileData;
		_FileData = nullptr;
		_FileLength = 0;
		return false;
	}

	close(fd);

	return true;

}



#endif

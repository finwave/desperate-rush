#pragma once

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <zip.h>

namespace fs = std::filesystem;

class CZipManager
{
public:

	CZipManager(void);
	~CZipManager(void);

	void Initialize();

	void UnpackMasterZipFileWithName(const char* zipFileName);
	void UnpackMasterZipFileWithTarget(const char* sourceZipFile, const char* targetName);
	void UnpackChildZipFile(const char* zipFileName);

	bool IsExistResourceFolder(std::string childPath);
	bool IsExistResourceFile(std::string childPath);

	std::string GetResourceFilePath(const char* childPath);
	inline std::string GetDataPath() { return this->m_sDataPath; }

private:

	std::string GetWorkingDir();
	void CreateFolder(const fs::path dirPath);
	void ExtractFile(struct zip_file* file, struct zip_stat fileInfo);

	bool IsCharPartOf(const char* target, const char* matcher);

	const char* PASSWORD = "mf8p_LWs*j";

	std::string m_sApplicationPath;
	std::string m_sDataPath;
	std::string m_sFullResourceFilePath;

	// only for debug purposes
	const bool m_bIsDebugOutput = false;
};
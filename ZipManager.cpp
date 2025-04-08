#include "ZipManager.h"

CZipManager::CZipManager(void)
{
    
}

CZipManager::~CZipManager(void)
{
}

void CZipManager::Initialize()
{
    m_sApplicationPath = GetWorkingDir();

    fs::current_path(fs::temp_directory_path());
    CreateFolder("desperate_rush");

    m_sDataPath = fs::temp_directory_path().generic_string();
    m_sDataPath += "desperate_rush/";

    if (m_bIsDebugOutput)
    {
        std::cout << m_sDataPath << std::endl;
    }
}

void CZipManager::UnpackMasterZipFileWithName(const char* zipFileName)
{
    struct zip* archive;
    struct zip_file* file;
    struct zip_stat fileInfo;

    int i, len;

    // Step 1: Initialize the zip archive

    const fs::path applicationPath = fs::path(m_sApplicationPath, std::locale(""));
    fs::current_path(applicationPath);

    if ((archive = zip_open(zipFileName, 0, NULL)) == NULL) {
        std::cerr << "Failed to open the zip file." << std::endl;
        return;
    }

    zip_set_default_password(archive, PASSWORD);

    // Step 2: Extract all the packed zip files

    const fs::path dataPath = fs::path(m_sDataPath, std::locale(""));
    fs::current_path(dataPath);

    zip_int64_t numOfEntries = zip_get_num_entries(archive, 0);

    for (i = 0; i < numOfEntries; i++)
    {
        if (zip_stat_index(archive, i, 0, &fileInfo) == 0)
        {
            len = strlen(fileInfo.name);

            if (fileInfo.name[len - 1] == '/')
            {
                std::string dir = m_sDataPath + fileInfo.name;
                const fs::path dirPath = fs::path(dir, std::locale(""));
                CreateFolder(dirPath);
            }
            else
            {
                file = zip_fopen_index(archive, i, 0);

                if (file)
                {
                    ExtractFile(file, fileInfo);
                    zip_fclose(file);
                }
            }
        }
    }

    // Step 3: Close the zip archive

    zip_close(archive);
}

void CZipManager::UnpackMasterZipFileWithTarget(const char* sourceZipFile, const char* targetName)
{
    struct zip* archive;
    struct zip_file* file;
    struct zip_stat fileInfo;

    int i, len;

    // Step 1: Initialize the zip archive

    const fs::path applicationPath = fs::path(m_sApplicationPath, std::locale(""));
    fs::current_path(applicationPath);

    if ((archive = zip_open(sourceZipFile, 0, NULL)) == NULL) {
        std::cerr << "Failed to open the zip file." << std::endl;
        return;
    }

    zip_set_default_password(archive, PASSWORD);

    // Step 2: Extract all the packed zip files

    const fs::path dataPath = fs::path(m_sDataPath, std::locale(""));
    fs::current_path(dataPath);

    zip_int64_t numOfEntries = zip_get_num_entries(archive, 0);

    for (i = 0; i < numOfEntries; i++)
    {
        if (zip_stat_index(archive, i, 0, &fileInfo) == 0)
        {
            if (IsCharPartOf(fileInfo.name, targetName))
            {
                len = strlen(fileInfo.name);

                if (fileInfo.name[len - 1] == '/')
                {
                    std::string dir = m_sDataPath + fileInfo.name;
                    const fs::path dirPath = fs::path(dir, std::locale(""));
                    CreateFolder(dirPath);
                }
                else
                {
                    file = zip_fopen_index(archive, i, 0);

                    if (file)
                    {
                        ExtractFile(file, fileInfo);
                        zip_fclose(file);
                    }
                }
            }
        }
    }

    // Step 3: Close the zip archive

    zip_close(archive);
}

void CZipManager::UnpackChildZipFile(const char* zipFileName)
{
    struct zip* archive;
    struct zip_file* file;
    struct zip_stat fileInfo;

    int i, len;

    // Step 1: Initialize the zip archive

    const fs::path dataPath = fs::path(m_sDataPath, std::locale(""));
    fs::current_path(dataPath);

    if ((archive = zip_open(zipFileName, 0, NULL)) == NULL) {
        std::cerr << "Failed to open the zip file." << std::endl;
        return;
    }

    // Step 2: Extract all the packed zip files

    zip_int64_t numOfEntries = zip_get_num_entries(archive, 0);

    for (i = 0; i < numOfEntries; i++)
    {
        if (zip_stat_index(archive, i, 0, &fileInfo) == 0)
        {
            len = strlen(fileInfo.name);

            if (fileInfo.name[len - 1] == '/')
            {
                std::string dir = m_sDataPath + fileInfo.name;
                const fs::path dirPath = fs::path(dir, std::locale(""));
                CreateFolder(dirPath);
            }
            else
            {
                file = zip_fopen_index(archive, i, 0);

                if (file)
                {
                    ExtractFile(file, fileInfo);
                    zip_fclose(file);
                }
            }
        }
    }

    // Step 3: Close and remove the zip archive

    zip_close(archive);
    remove(zipFileName);
}

std::string CZipManager::GetWorkingDir()
{
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    return std::string(buf) + '\\';
}

void CZipManager::CreateFolder(const fs::path dirPath)
{
    fs::create_directory(dirPath);
}

bool CZipManager::IsExistResourceFolder(std::string childPath)
{
    /*
    std::string dir = m_sDataPath + childPath;
    const fs::path dirPath = fs::path(dir, std::locale(""));
    return fs::is_directory(dirPath);
    */

    // Always make sure when playing the game,
    // that the game logic is unpacking all the resource files.
    return false;
}

bool CZipManager::IsExistResourceFile(std::string childPath)
{
    /*
    std::string dir = m_sDataPath + childPath;
    const fs::path dirPath = fs::path(dir, std::locale(""));
    return fs::exists(dirPath);
    */

    // Always make sure when playing the game,
    // that the game logic is unpacking all the resource files.
    return false;
}

void CZipManager::ExtractFile(struct zip_file* file, struct zip_stat fileInfo)
{
    std::string filePath = m_sDataPath + fileInfo.name;
    std::ofstream outfile(filePath, std::ofstream::binary);

    if (!outfile)
    {
        return;
    }

    char buf[100];
    int len;
    long long sum = 0;

    while (sum != fileInfo.size)
    {
        len = zip_fread(file, buf, 100);

        if (len < 0)
        {
            break;
        }

        outfile.write(buf, len);
        sum += len;
    }

    if (m_bIsDebugOutput)
    {
        std::cout << "File created: " << filePath << std::endl;
    }

    outfile.close();
}

std::string CZipManager::GetResourceFilePath(const char* childPath)
{
    std::string stringChildPath = childPath;
    m_sFullResourceFilePath = m_sDataPath + stringChildPath;
    return m_sFullResourceFilePath;
}

// Source: https://stackoverflow.com/questions/27090069/check-if-a-string-of-type-char-contains-another-string
bool CZipManager::IsCharPartOf(const char* target, const char* matcher)
{
    int i = 0;
    int j = 0;

    while (target[i] != '\0')
    {
        if (target[i] == matcher[j])
        {
            int init = i;

            while ((target[i] == matcher[j]) && (matcher[j] != '\0'))
            {
                j++;
                i++;
            }

            if (matcher[j] == '\0')
            {
                return true;
            }

            j = 0;
        }

        i++;
    }

    return false;
}
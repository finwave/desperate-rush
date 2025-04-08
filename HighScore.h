#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <stdio.h>

#include "HighScoreItem.h"

#define ENCRYPTION_FORMULA	(int) Byte + 107
#define	DECRYPTION_FORMULA	(int) Byte - 107

namespace fs = std::filesystem;

class CHighScore
{
public:

	CHighScore(void);
	~CHighScore(void);

	/**
	 * IsEmpty
	 * @return member m_bEmpty
	 */
	inline bool IsEmpty() { return m_bEmpty; }

	/**
	 * GetScores
	 * @return member m_vHighScores
	 */
	inline std::vector<CHighScoreItem> GetScores() { return m_vHighScores; }

	void Load();
	void Save();
	void SortScores();
	bool IsHighScore(int iNewScore);

	void AddHighScore();
	void AddHighScore(std::string strName, int iLevel, int iScore, float fTime);

	inline std::string GetNewName() { return this->m_strNewName; }
	inline int GetNewLevel() { return this->m_iNewLevel; }
	inline int GetNewScore() { return this->m_iNewScore; }
	inline float GetNewTime() { return this->m_fNewTime; }

	inline void SetNewName(std::string strName) { this->m_strNewName = strName; }
	inline void SetNewLevel (int iLevel) { this->m_iNewLevel = iLevel; }
	inline void SetNewScore (int iScore) { this->m_iNewScore = iScore; }
	inline void SetNewTime (float fTime) { this->m_fNewTime = fTime; }

private:

	int EncryptFile(std::string fileName, std::string newFileName);
	int DecryptFile(std::string fileName, std::string newFileName);

	bool IsExistResourceFile(std::string childPath);

	int StringToInt(const std::string& s);
	float StringToFloat(const std::string& s);

	std::string m_sDataPath;
	std::string m_strDataFile;
	std::string m_strTempFile;

	bool m_bEmpty;
	
	std::vector<CHighScoreItem> m_vHighScores;
	std::string m_strNewName;
	int m_iNewLevel;
	int m_iNewScore;
	float m_fNewTime;

	// Descending date sorting function
	struct SDescendingSort
	{	
		bool operator()(CHighScoreItem rpStart, CHighScoreItem rpEnd)
		{
			return rpStart.GetScore() > rpEnd.GetScore();
		}
	};
};
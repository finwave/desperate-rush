#pragma once

#include <string>

class CHighScoreItem
{
public:
	CHighScoreItem(void);
	virtual ~CHighScoreItem(void);

	inline std::string GetName() {return m_strName; }
	inline int GetLevel() {return m_iLevel; }
	inline int GetScore() {return m_iScore; }
	inline float GetTime() {return m_fTime; }

	inline void SetName(std::string strName) { this->m_strName = strName; }
	inline void SetLevel(int iLevel) { this->m_iLevel = iLevel; }
	inline void SetScore(int iScore) { this->m_iScore = iScore; }
	inline void SetTime (float fTime) { this->m_fTime = fTime; }

private:
	std::string			m_strName;
	int					m_iLevel;
	int					m_iScore;
	float				m_fTime;
};
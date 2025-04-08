#include "HighScore.h"

CHighScore::CHighScore(void)
{
	this->m_sDataPath = fs::temp_directory_path().generic_string();
	this->m_sDataPath += "desperate_rush/";

	this->m_strDataFile = "highscores.dat";
	this->m_strTempFile = "temp.dat";

	this->m_bEmpty = false;
	this->m_iNewLevel = 0;
	this->m_iNewScore = 0;
	this->m_fNewTime = 0.0f;
}

CHighScore::~CHighScore(void)
{
	this->m_vHighScores.clear();
}

void CHighScore::Load(void)
{
	int lineData;
	char nextChar;
	std::string strOutput;
	std::wstring wStrOutput;

	CHighScoreItem scoreEntry;

	if(IsExistResourceFile(this->m_strDataFile))
	{
		std::string pathDataFile = m_sDataPath + this->m_strDataFile;
		std::string pathTempFile = m_sDataPath + this->m_strTempFile;

		// rename original file, it becomes temp file
		rename(pathDataFile.c_str(), pathTempFile.c_str());
		// decrypt temp file, decrypted file will be saved using original name
		DecryptFile(pathTempFile, pathDataFile);
		// remove temp file, we don't need it anymore
		remove(pathTempFile.c_str());

		std::ifstream fileIn;
		fileIn.open(pathDataFile.c_str(), std::ios::binary);

		// file opened successfully
		if(fileIn.is_open() && !(fileIn.bad()))
		{
			lineData = 1;
			this->m_vHighScores.clear();

			// file not reached end
			while(!fileIn.eof())
			{
				// get the next character from file
				nextChar = fileIn.get();

				// reads name data from the current line of the file
				if(lineData == 1)
				{
					if(nextChar != '\t')
					{
						strOutput = strOutput + nextChar;
					}

					else
					{
						scoreEntry.SetName(strOutput);
						strOutput.clear();
						lineData++;
					}
				}
				// reads score data from the current line of the file
				else if(lineData == 2)
				{
					if(nextChar != '\t')
					{
						strOutput = strOutput + nextChar;
					}

					else
					{
						scoreEntry.SetScore(StringToInt(strOutput));
						strOutput.clear();
						lineData++;
					}
				}
				// reads level data from the current line of the file
				else if(lineData == 3)
				{
					if(nextChar != '\t')
					{
						strOutput = strOutput + nextChar;
					}

					else
					{
						scoreEntry.SetLevel(StringToInt(strOutput));
						strOutput.clear();
						lineData++;
					}
				}
				// reads time data from the current line of the file
				else if(lineData == 4)
				{
					if(nextChar != '\n')
					{
						strOutput = strOutput + nextChar;
					}

					else
					{
						scoreEntry.SetTime(StringToFloat(strOutput));
						strOutput.clear();
						
						// puts scoreEntry object into the end of a vector
						m_vHighScores.push_back(scoreEntry);

						lineData = 1;
					}
				}
			}

			fileIn.close();
			this->m_bEmpty = false;
		}
		else
		{
			this->m_bEmpty = true;
		}

		// rename original file, it becomes temp file
		rename(pathDataFile.c_str(), pathTempFile.c_str());
		// encrypt temp file, encrypted file will be saved using original name
		EncryptFile(pathTempFile, pathDataFile);
		// remove temp file, we don't need it anymore
		remove(pathTempFile.c_str());
	}
	else
	{
		this->m_bEmpty = true;
	}
}

void CHighScore::Save()
{
	// we don't have existing highscores
	if (this->m_vHighScores.size() <= 0)
	{
		return;
	}

	std::ofstream fileOut;

	std::string pathDataFile = m_sDataPath + this->m_strDataFile;
	std::string pathTempFile = m_sDataPath + this->m_strTempFile;

	// first decrypt the file before writing to it
	if(IsExistResourceFile(this->m_strDataFile))
	{
		// rename original file, it becomes temp file
		rename(pathDataFile.c_str(), pathTempFile.c_str());
		// decrypt temp file, decrypted file will be saved using original name
		DecryptFile(pathTempFile, pathDataFile);
		// remove temp file, we don't need it anymore
		remove(pathTempFile.c_str());
	}

	// highscore data will be written as a binary file
	fileOut.open(pathDataFile.c_str(), std::ios::trunc | std::ios::binary);

	// file opened successfully
	if(fileOut.is_open())
	{
		std::stringstream stream;

		std::string strName = "";
		std::string strScore = "";
		std::string strLevel = "";
		std::string strTime = "";

		int iSize = this->m_vHighScores.size();

		for(int i = 0; i < iSize; i++)
		{
			strName = this->m_vHighScores[i].GetName();

			stream << this->m_vHighScores[i].GetScore();
			stream >> strScore;

			stream.clear();

			stream << this->m_vHighScores[i].GetLevel();
			stream >> strLevel;

			stream.clear();

			stream << this->m_vHighScores[i].GetTime();
			stream >> strTime;

			stream.clear();

			fileOut.write(strName.c_str(), strName.length());
			fileOut<<"\t";
			fileOut.write(strScore.c_str(), strScore.length());
			fileOut<<"\t";
			fileOut.write(strLevel.c_str(), strLevel.length());
			fileOut<<"\t";
			fileOut.write(strTime.c_str(), strTime.length());
			fileOut<<"\n";
		}

		fileOut.close();
	}

	// rename original file, it becomes temp file
	rename(pathDataFile.c_str(), pathTempFile.c_str());
	// encrypt temp file, encrypted file will be saved using original name
	EncryptFile(pathTempFile, pathDataFile);
	// remove temp file, we don't need it anymore
	remove(pathTempFile.c_str());
}

void CHighScore::SortScores(void)
{
	sort(m_vHighScores.begin(), m_vHighScores.end(), SDescendingSort());
}

bool CHighScore::IsHighScore(int iNewScore)
{
	bool bHighscore = false;

	// no existing highscores
	if( this->m_bEmpty )
	{
		bHighscore = true;
	}
	else
	{
		int iSize = this->m_vHighScores.size();

		// less than max number of highscores
		// so automaticly a new highscore
		if(iSize < 10)
		{
			bHighscore = true;
		}
		// max number of highscores
		else
		{
			// sort scores to descending order
			this->SortScores();

			// let's see if the new score is bigger 
			// than the current lowest highscore
			if(iNewScore > this->m_vHighScores[iSize-1].GetScore())
			{
				bHighscore = true;

				// let's delete the last score in the order
				// since it's the smallest one (descending order)
				// erases the 10th element
				this->m_vHighScores.erase(this->m_vHighScores.begin() + 9);
			}
		}
	}

	return bHighscore;
}

void CHighScore::AddHighScore()
{
	CHighScoreItem scoreEntry;

	scoreEntry.SetName(m_strNewName);
	scoreEntry.SetScore(m_iNewScore);
	scoreEntry.SetLevel(m_iNewLevel);
	scoreEntry.SetTime(m_fNewTime);

	this->m_vHighScores.push_back(scoreEntry);
}

void CHighScore::AddHighScore(	std::string strName,
								int iLevel,
								int iScore,
								float fTime)
{
	CHighScoreItem scoreEntry;

	scoreEntry.SetName(strName);
	scoreEntry.SetScore(iScore);
	scoreEntry.SetLevel(iLevel);
	scoreEntry.SetTime(fTime);

	this->m_vHighScores.push_back(scoreEntry);
}

int CHighScore::EncryptFile(std::string fileName, std::string newFileName)
{
	std::ifstream inFile;	// This is the file that we're going to encrypt and read
	std::ofstream outFile;	// Once we encrypt the file, this is it's new location

	char Byte;			// This is the FILENAME's byte, we'll add 25 to this later

	///////////////////////////////////////////////////////////////
	// Before we continue:
	// std::ios:: in		-	 Used for reading a file
	// std::ios::out		-	 Used for writing a file
	// std::ios::binary	-	 Used for reading or writing binary files
	///////////////////////////////////////////////////////////////

	inFile.open(fileName.c_str(), std::ios::in | std::ios::binary);		// We read this file in binary mode
	outFile.open(newFileName.c_str(), std::ios::out | std::ios::binary);	// And we write the file in binary mode

	// eof() stands for End Of File, so while we are still reading the file, continue
	while(!inFile.eof())	
	{
		// Remember we need to change a byte so we add 25 to it
		char NewByte;
		
		//////////////////////////////////////////////////
		// NOTE: Only use the .put() and .get() in loops	
		// because it only reads 1 Byte at a time!						
		//////////////////////////////////////////////////

		// Out old byte is recieved from the file
		Byte = inFile.get();	

		// If the file that we are reading has an error, turn 0
		if (inFile.fail())		
			return 0;
		//Remember our Encryption Formula above?
		//Our new byte is recieved from it, see above
		NewByte = ENCRYPTION_FORMULA;	
		// This simple puts the new byte, into the new file!
		outFile.put(NewByte);
	}

	// We have to be neat so we close both the file that we're reading
	// and the file that we're writing
	inFile.close();		// (File to read)
	outFile.close();	// (File to write)

	return 1; // Success!
}

int CHighScore::DecryptFile(std::string fileName, std::string newFileName)
{
	std::ifstream inFile;
	std::ofstream outFile;

	char Byte;

	inFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
	outFile.open(newFileName.c_str(), std::ios::out | std::ios::binary);

	while(!inFile.eof())	
	{
		char NewByte;
		
		Byte = inFile.get();	

		if (inFile.fail())		
			return 0;
									  /////////////////////////////////////////////////////
		NewByte = DECRYPTION_FORMULA; // New Line! We just change the ENCRYPTION_FORMULA
									  // to DECRYPTION_FORMULA, see above
									  /////////////////////////////////////////////////////
		outFile.put(NewByte);
	}

	inFile.close();
	outFile.close();

	return 1;
}

bool CHighScore::IsExistResourceFile(std::string childPath)
{
	std::string dir = m_sDataPath + childPath;
	const fs::path dirPath = fs::path(dir, std::locale(""));
	return fs::exists(dirPath);
}

int CHighScore::StringToInt(const std::string& s)
{
	int x;
	std::istringstream i(s);

	i >> x;
	return x;
}

float CHighScore::StringToFloat(const std::string& s)
{
	float x;
	std::istringstream i(s);

	i >> x;
	return x;
}

#include "TextUtils.h"
#include "Config.h"

CConfig::CConfig(void)
{
	this->m_sApplicationPath = GetWorkingDir();

	this->m_bSuccess = false;

	this->m_iVolumeMusic = 0;
	this->m_iVolumeSoundEffect = 0;

	this->m_strUp = new char[4];
	this->m_strDown = new char[4];
	this->m_strLeft = new char[4];
	this->m_strRight = new char[4];
	this->m_strFireMode = new char[4];
	this->m_strMinigun = new char[4];
	this->m_strCannon = new char[4];
	this->m_strBlast = new char[4];

	this->m_iUp = 0;
	this->m_iDown = 0;
	this->m_iLeft = 0;
	this->m_iRight = 0;
	this->m_iFireMode = 0;
	this->m_iMinigun = 0;
	this->m_iCannon = 0;
	this->m_iBlast = 0;
}

CConfig::~CConfig(void)
{
	if (this->m_strUp)
	{
		delete[] this->m_strUp;
		this->m_strUp = NULL;
	}
	if (this->m_strDown)
	{
		delete[] this->m_strDown;
		this->m_strDown = NULL;
	}
	if (this->m_strLeft)
	{
		delete[] this->m_strLeft;
		this->m_strLeft = NULL;
	}
	if (this->m_strRight)
	{
		delete[] this->m_strRight;
		this->m_strRight = NULL;
	}
	if (this->m_strFireMode)
	{
		delete[] this->m_strFireMode;
		this->m_strFireMode = NULL;
	}
	if (this->m_strMinigun)
	{
		delete[] this->m_strMinigun;
		this->m_strMinigun = NULL;
	}
	if (this->m_strCannon)
	{
		delete[] this->m_strCannon;
		this->m_strCannon = NULL;
	}
	if (this->m_strBlast)
	{
		delete[] this->m_strBlast;
		this->m_strBlast = NULL;
	}
}

std::string CConfig::GetWorkingDir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

std::string CConfig::ReadNextConfigValue()
{
	std::string strData = "";
	char nextChar = this->m_FileStreamIn.get();

	while (nextChar != '\n')
	{
		strData += nextChar;
		nextChar = this->m_FileStreamIn.get();
	}

	return strData;
}

void CConfig::Load(void)
{
	this->m_bSuccess = false;

	const fs::path applicationPath = fs::path(m_sApplicationPath, std::locale(""));
	fs::current_path(applicationPath);

	char nextChar;
	std::string strData;

	bool readLine = false;
	int iLineIndex = 1;

	this->m_FileStreamIn.open("config.cfg");

	// file exists
	if (this->m_FileStreamIn.is_open() && !(this->m_FileStreamIn.bad()))
	{
		// file not reached end
		while (!this->m_FileStreamIn.eof())
		{
			// get the next character from file
			nextChar = this->m_FileStreamIn.get();

			// next character is '='
			if (nextChar == '=')
			{
				readLine = true;
			}

			// read rest of the data from the current line
			if (readLine)
			{
				switch (iLineIndex)
				{
				case 1:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						this->m_iVolumeMusic = atoi(strData.c_str());
					}
					else
					{
						this->m_iVolumeMusic = 100;
					}

					break;

				case 2:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						this->m_iVolumeSoundEffect = atoi(strData.c_str());
					}
					else
					{
						this->m_iVolumeSoundEffect = 100;
					}

					break;

				case 3:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						this->m_eAntialiasing = (eANTIALIASING)atoi(strData.c_str());
					}
					else
					{
						DefaultAntialiasingParameter();
					}

					break;

				case 4:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						this->m_eSpecularLighting = (eSPECULAR_LIGHTING)atoi(strData.c_str());
					}
					else
					{
						this->m_eSpecularLighting = eSPECULAR_LIGHTING_ON;
					}

					break;

				case 5:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strUp = TextUtils::ConstCharToChar(charData, this->m_strUp);
					}

					break;

				case 6:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strDown = TextUtils::ConstCharToChar(charData, this->m_strDown);
					}

					break;

				case 7:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strLeft = TextUtils::ConstCharToChar(charData, this->m_strLeft);
					}

					break;

				case 8:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strRight = TextUtils::ConstCharToChar(charData, this->m_strRight);
					}

					break;

				case 9:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strFireMode = TextUtils::ConstCharToChar(charData, this->m_strFireMode);
					}

					break;

				case 10:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strMinigun = TextUtils::ConstCharToChar(charData, this->m_strMinigun);
					}

					break;

				case 11:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strCannon = TextUtils::ConstCharToChar(charData, this->m_strCannon);
					}

					break;

				case 12:

					strData = ReadNextConfigValue();

					if (strData.size() > 0)
					{
						const char* charData = strData.c_str();
						this->m_strBlast = TextUtils::ConstCharToChar(charData, this->m_strBlast);
					}

					break;
				}

				readLine = false;
				iLineIndex++;
			}
		}

		this->m_FileStreamIn.close();

		// checks if loaded values are valid
		CheckAll();
		SetVkeys();

		this->m_bSuccess = true;
	}
	// create a default 'config.cfg' file
	else
	{
		DefaultAll();
	}
}

void CConfig::Save(void)
{
	const fs::path applicationPath = fs::path(m_sApplicationPath, std::locale(""));
	fs::current_path(applicationPath);

	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file opened successfully
	if (fileOut.is_open())
	{
		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "GAME CONFIGURATION";
		fileOut << "\n\n";
		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "AUDIO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "music=";
		fileOut << this->m_iVolumeMusic;
		fileOut << "\n";
		fileOut << "sound effect=";
		fileOut << this->m_iVolumeSoundEffect;
		fileOut << "\n\n";
		fileOut << "VIDEO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "antialiasing=";
		fileOut << this->m_eAntialiasing;
		fileOut << "\n";
		fileOut << "specular lighting=";
		fileOut << this->m_eSpecularLighting;
		fileOut << "\n\n";
		fileOut << "CONTROLS";
		fileOut << "\n";
		fileOut << "--------";
		fileOut << "\n\n";
		fileOut << "up=";
		fileOut << this->m_strUp[0];
		fileOut << this->m_strUp[1];
		fileOut << this->m_strUp[2];
		fileOut << this->m_strUp[3];
		fileOut << "\n";
		fileOut << "down=";
		fileOut << this->m_strDown[0];
		fileOut << this->m_strDown[1];
		fileOut << this->m_strDown[2];
		fileOut << this->m_strDown[3];
		fileOut << "\n";
		fileOut << "left=";
		fileOut << this->m_strLeft[0];
		fileOut << this->m_strLeft[1];
		fileOut << this->m_strLeft[2];
		fileOut << this->m_strLeft[3];
		fileOut << "\n";
		fileOut << "right=";
		fileOut << this->m_strRight[0];
		fileOut << this->m_strRight[1];
		fileOut << this->m_strRight[2];
		fileOut << this->m_strRight[3];
		fileOut << "\n";
		fileOut << "fire mode=";
		fileOut << this->m_strFireMode[0];
		fileOut << this->m_strFireMode[1];
		fileOut << this->m_strFireMode[2];
		fileOut << this->m_strFireMode[3];
		fileOut << "\n";
		fileOut << "minigun=";
		fileOut << this->m_strMinigun[0];
		fileOut << this->m_strMinigun[1];
		fileOut << this->m_strMinigun[2];
		fileOut << this->m_strMinigun[3];
		fileOut << "\n";
		fileOut << "cannon=";
		fileOut << this->m_strCannon[0];
		fileOut << this->m_strCannon[1];
		fileOut << this->m_strCannon[2];
		fileOut << this->m_strCannon[3];
		fileOut << "\n";
		fileOut << "bomb=";
		fileOut << this->m_strBlast[0];
		fileOut << this->m_strBlast[1];
		fileOut << this->m_strBlast[2];
		fileOut << this->m_strBlast[3];
		fileOut << "\n";

		fileOut.close();
		m_bSuccess = true;

		SetVkeys();
	}
	else
	{
		m_bSuccess = false;
	}
}

void CConfig::CheckAll()
{
	CheckAudio();
	CheckAntialiasing();
	CheckSpecularLighting();
	CheckControls();
}

void CConfig::DefaultAll(void)
{
	DefaultAudio();
	DefaultAntialiasing();
	DefaultSpecularLighting();
	DefaultControls();

	SetVkeys();

	m_bSuccess = true;
}

void CConfig::DefaultAudio()
{
	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if (fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "GAME CONFIGURATION";
		fileOut << "\n\n";
		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "AUDIO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "music=100";
		fileOut << "\n";
		fileOut << "sound effect=100";
		fileOut << "\n\n";
		fileOut << "VIDEO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "antialiasing=";
		fileOut << this->m_eAntialiasing;
		fileOut << "\n";
		fileOut << "specular lighting=";
		fileOut << this->m_eSpecularLighting;
		fileOut << "\n\n";
		fileOut << "CONTROLS";
		fileOut << "\n";
		fileOut << "--------";
		fileOut << "\n\n";
		fileOut << "up=";
		fileOut << this->m_strUp;
		fileOut << "\n";
		fileOut << "down=";
		fileOut << this->m_strDown;
		fileOut << "\n";
		fileOut << "left=";
		fileOut << this->m_strLeft;
		fileOut << "\n";
		fileOut << "right=";
		fileOut << this->m_strRight;
		fileOut << "\n";
		fileOut << "fire mode=";
		fileOut << this->m_strFireMode;
		fileOut << "\n";
		fileOut << "minigun=";
		fileOut << this->m_strMinigun;
		fileOut << "\n";
		fileOut << "cannon=";
		fileOut << this->m_strCannon;
		fileOut << "\n";
		fileOut << "blast=";
		fileOut << this->m_strBlast;
		fileOut << "\n";

		fileOut.close();

		// sets default values to member variables
		this->m_iVolumeMusic = 100;
		this->m_iVolumeSoundEffect = 100;

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::DefaultAntialiasingParameter()
{
	this->m_eAntialiasing = eANTIALIASING::eANTIALIASING_0X;

	if (this->m_dwMaxAntialiasing >= 8)
	{
		this->m_eAntialiasing = eANTIALIASING::eANTIALIASING_8X;
	}
	else if (this->m_dwMaxAntialiasing >= 6)
	{
		this->m_eAntialiasing = eANTIALIASING::eANTIALIASING_6X;
	}
	else if (this->m_dwMaxAntialiasing >= 4)
	{
		this->m_eAntialiasing = eANTIALIASING::eANTIALIASING_4X;
	}
	else if (this->m_dwMaxAntialiasing >= 2)
	{
		this->m_eAntialiasing = eANTIALIASING::eANTIALIASING_2X;
	}
}

void CConfig::DefaultAntialiasing()
{
	DefaultAntialiasingParameter();

	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if (fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "GAME CONFIGURATION";
		fileOut << "\n\n";
		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "AUDIO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "music=";
		fileOut << this->m_iVolumeMusic;
		fileOut << "\n";
		fileOut << "sound effect=";
		fileOut << this->m_iVolumeSoundEffect;
		fileOut << "\n\n";
		fileOut << "VIDEO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "antialiasing=";
		fileOut << this->m_eAntialiasing;
		fileOut << "\n";
		fileOut << "specular lighting=";
		fileOut << this->m_eSpecularLighting;
		fileOut << "\n\n";
		fileOut << "CONTROLS";
		fileOut << "\n";
		fileOut << "--------";
		fileOut << "\n\n";
		fileOut << "up=";
		fileOut << this->m_strUp;
		fileOut << "\n";
		fileOut << "down=";
		fileOut << this->m_strDown;
		fileOut << "\n";
		fileOut << "left=";
		fileOut << this->m_strLeft;
		fileOut << "\n";
		fileOut << "right=";
		fileOut << this->m_strRight;
		fileOut << "\n";
		fileOut << "fire mode=";
		fileOut << this->m_strFireMode;
		fileOut << "\n";
		fileOut << "minigun=";
		fileOut << this->m_strMinigun;
		fileOut << "\n";
		fileOut << "cannon=";
		fileOut << this->m_strCannon;
		fileOut << "\n";
		fileOut << "blast=";
		fileOut << this->m_strBlast;
		fileOut << "\n";

		fileOut.close();

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::DefaultSpecularLighting()
{
	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if (fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "GAME CONFIGURATION";
		fileOut << "\n\n";
		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "AUDIO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "music=";
		fileOut << this->m_iVolumeMusic;
		fileOut << "\n";
		fileOut << "sound effect=";
		fileOut << this->m_iVolumeSoundEffect;
		fileOut << "\n\n";
		fileOut << "VIDEO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "antialiasing=";
		fileOut << this->m_eAntialiasing;
		fileOut << "\n";
		fileOut << "specular lighting=1";
		fileOut << "\n\n";
		fileOut << "CONTROLS";
		fileOut << "\n";
		fileOut << "--------";
		fileOut << "\n\n";
		fileOut << "up=";
		fileOut << this->m_strUp;
		fileOut << "\n";
		fileOut << "down=";
		fileOut << this->m_strDown;
		fileOut << "\n";
		fileOut << "left=";
		fileOut << this->m_strLeft;
		fileOut << "\n";
		fileOut << "right=";
		fileOut << this->m_strRight;
		fileOut << "\n";
		fileOut << "fire mode=";
		fileOut << this->m_strFireMode;
		fileOut << "\n";
		fileOut << "minigun=";
		fileOut << this->m_strMinigun;
		fileOut << "\n";
		fileOut << "cannon=";
		fileOut << this->m_strCannon;
		fileOut << "\n";
		fileOut << "blast=";
		fileOut << this->m_strBlast;
		fileOut << "\n";

		fileOut.close();

		// sets default values to member variables
		this->m_eSpecularLighting = eSPECULAR_LIGHTING_ON;

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::DefaultControls()
{
	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if (fileOut.is_open())
	{
		// writes default control values to 'config.cfg' file

		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "GAME CONFIGURATION";
		fileOut << "\n\n";
		fileOut << "*******************";
		fileOut << "\n\n";
		fileOut << "AUDIO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "music=";
		fileOut << this->m_iVolumeMusic;
		fileOut << "\n";
		fileOut << "sound effect=";
		fileOut << this->m_iVolumeSoundEffect;
		fileOut << "\n\n";
		fileOut << "VIDEO";
		fileOut << "\n";
		fileOut << "-----";
		fileOut << "\n\n";
		fileOut << "antialiasing=";
		fileOut << this->m_eAntialiasing;
		fileOut << "\n";
		fileOut << "specular lighting=";
		fileOut << this->m_eSpecularLighting;
		fileOut << "\n\n";
		fileOut << "CONTROLS";
		fileOut << "\n";
		fileOut << "--------";
		fileOut << "\n\n";
		fileOut << "up=0x26";
		fileOut << "\n";
		fileOut << "down=0x28";
		fileOut << "\n";
		fileOut << "left=0x25";
		fileOut << "\n";
		fileOut << "right=0x27";
		fileOut << "\n";
		fileOut << "fire mode=0x10";
		fileOut << "\n";
		fileOut << "minigun=0x11";
		fileOut << "\n";
		fileOut << "cannon=0x0D";
		fileOut << "\n";
		fileOut << "blast=0x20";
		fileOut << "\n";

		fileOut.close();

		// sets default values to member variables

		this->m_strUp = TextUtils::ConstCharToChar("0x26", this->m_strUp);
		this->m_strDown = TextUtils::ConstCharToChar("0x28", this->m_strDown);
		this->m_strLeft = TextUtils::ConstCharToChar("0x25", this->m_strLeft);
		this->m_strRight = TextUtils::ConstCharToChar("0x27", this->m_strRight);
		this->m_strFireMode = TextUtils::ConstCharToChar("0x10", this->m_strFireMode);
		this->m_strMinigun = TextUtils::ConstCharToChar("0x11", this->m_strMinigun);
		this->m_strCannon = TextUtils::ConstCharToChar("0x0D", this->m_strCannon);
		this->m_strBlast = TextUtils::ConstCharToChar("0x20", this->m_strBlast);

		SetVkeys();

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::CheckAudio()
{
	if ((this->m_iVolumeMusic < 0) || (this->m_iVolumeMusic > 100))
	{
		this->DefaultAudio();
	}
	else if ((this->m_iVolumeSoundEffect < 0) || (this->m_iVolumeSoundEffect > 100))
	{
		this->DefaultAudio();
	}
}

void CConfig::CheckAntialiasing()
{
	if ((this->m_eAntialiasing < 0) || (this->m_eAntialiasing > 4))
	{
		this->DefaultAntialiasing();
	}
}

void CConfig::CheckSpecularLighting()
{
	if ((this->m_eSpecularLighting < 0) || (this->m_eSpecularLighting > 1))
	{
		this->DefaultSpecularLighting();
	}
}

void CConfig::CheckControls()
{
	this->m_strUp = TextUtils::SubstrFromChar(this->m_strUp, 4);
	this->m_strDown = TextUtils::SubstrFromChar(this->m_strDown, 4);
	this->m_strLeft = TextUtils::SubstrFromChar(this->m_strLeft, 4);
	this->m_strRight = TextUtils::SubstrFromChar(this->m_strRight, 4);
	this->m_strFireMode = TextUtils::SubstrFromChar(this->m_strFireMode, 4);
	this->m_strMinigun = TextUtils::SubstrFromChar(this->m_strMinigun, 4);
	this->m_strCannon = TextUtils::SubstrFromChar(this->m_strCannon, 4);
	this->m_strBlast = TextUtils::SubstrFromChar(this->m_strBlast, 4);

	bool bValid = true;

	// checks next control value if still valid

	if (!this->m_keyReference.CheckValidValue(this->m_strUp))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strDown))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strLeft))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strRight))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strFireMode))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strMinigun))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strCannon))
	{
		bValid = false;
	}

	if (!this->m_keyReference.CheckValidValue(this->m_strBlast))
	{
		bValid = false;
	}

	if (!bValid)
	{
		this->DefaultControls();
	}
}

void CConfig::RemoveDuplicate(int iButton)
{
	switch (iButton)
	{
	// compare up to others
	case 1:

		if ((m_strUp[2] == m_strDown[2]) &&
			(m_strUp[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strUp[2] == m_strLeft[2]) &&
			(m_strUp[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strUp[2] == m_strRight[2]) &&
			(m_strUp[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strUp[2] == m_strFireMode[2]) &&
			(m_strUp[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strUp[2] == m_strMinigun[2]) &&
			(m_strUp[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strUp[2] == m_strCannon[2]) &&
			(m_strUp[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if ((m_strUp[2] == m_strBlast[2]) &&
			(m_strUp[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare down to others
	case 2:

		if ((m_strDown[2] == m_strUp[2]) &&
			(m_strDown[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strDown[2] == m_strLeft[2]) &&
			(m_strDown[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strDown[2] == m_strRight[2]) &&
			(m_strDown[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strDown[2] == m_strFireMode[2]) &&
			(m_strDown[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strDown[2] == m_strMinigun[2]) &&
			(m_strDown[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strDown[2] == m_strCannon[2]) &&
			(m_strDown[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if ((m_strDown[2] == m_strBlast[2]) &&
			(m_strDown[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare left to others
	case 3:

		if ((m_strLeft[2] == m_strUp[2]) &&
			(m_strLeft[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strLeft[2] == m_strDown[2]) &&
			(m_strLeft[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strLeft[2] == m_strRight[2]) &&
			(m_strLeft[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strLeft[2] == m_strFireMode[2]) &&
			(m_strLeft[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strLeft[2] == m_strMinigun[2]) &&
			(m_strLeft[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strLeft[2] == m_strCannon[2]) &&
			(m_strLeft[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if ((m_strLeft[2] == m_strBlast[2]) &&
			(m_strLeft[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare right to others
	case 4:

		if ((m_strRight[2] == m_strUp[2]) &&
			(m_strRight[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strRight[2] == m_strDown[2]) &&
			(m_strRight[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strRight[2] == m_strLeft[2]) &&
			(m_strRight[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strRight[2] == m_strFireMode[2]) &&
			(m_strRight[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strRight[2] == m_strMinigun[2]) &&
			(m_strRight[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strRight[2] == m_strCannon[2]) &&
			(m_strRight[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if ((m_strRight[2] == m_strBlast[2]) &&
			(m_strRight[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare fire mode to others
	case 5:

		if ((m_strFireMode[2] == m_strUp[2]) &&
			(m_strFireMode[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strFireMode[2] == m_strDown[2]) &&
			(m_strFireMode[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strFireMode[2] == m_strLeft[2]) &&
			(m_strFireMode[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strFireMode[2] == m_strRight[2]) &&
			(m_strFireMode[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strFireMode[2] == m_strMinigun[2]) &&
			(m_strFireMode[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strFireMode[2] == m_strCannon[2]) &&
			(m_strFireMode[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if ((m_strFireMode[2] == m_strBlast[2]) &&
			(m_strFireMode[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare minigun to others
	case 6:

		if ((m_strMinigun[2] == m_strUp[2]) &&
			(m_strMinigun[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strMinigun[2] == m_strDown[2]) &&
			(m_strMinigun[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strMinigun[2] == m_strLeft[2]) &&
			(m_strMinigun[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strMinigun[2] == m_strRight[2]) &&
			(m_strMinigun[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strMinigun[2] == m_strFireMode[2]) &&
			(m_strMinigun[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strMinigun[2] == m_strCannon[2]) &&
			(m_strMinigun[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if ((m_strMinigun[2] == m_strBlast[2]) &&
			(m_strMinigun[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare cannon to others
	case 7:

		if ((m_strCannon[2] == m_strUp[2]) &&
			(m_strCannon[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strCannon[2] == m_strDown[2]) &&
			(m_strCannon[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strCannon[2] == m_strLeft[2]) &&
			(m_strCannon[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strCannon[2] == m_strRight[2]) &&
			(m_strCannon[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strCannon[2] == m_strFireMode[2]) &&
			(m_strCannon[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strCannon[2] == m_strMinigun[2]) &&
			(m_strCannon[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strCannon[2] == m_strBlast[2]) &&
			(m_strCannon[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare bomb to others
	case 8:

		if ((m_strBlast[2] == m_strUp[2]) &&
			(m_strBlast[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if ((m_strBlast[2] == m_strDown[2]) &&
			(m_strBlast[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if ((m_strBlast[2] == m_strLeft[2]) &&
			(m_strBlast[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if ((m_strBlast[2] == m_strRight[2]) &&
			(m_strBlast[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if ((m_strBlast[2] == m_strFireMode[2]) &&
			(m_strBlast[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if ((m_strBlast[2] == m_strMinigun[2]) &&
			(m_strBlast[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if ((m_strBlast[2] == m_strCannon[2]) &&
			(m_strBlast[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		break;
	}
}

bool CConfig::IsInputButtonEmpty(void)
{
	bool empty = false;

	if (IsInputButtonEmpty(m_strUp))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strDown))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strLeft))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strRight))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strFireMode))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strMinigun))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strCannon))
	{
		empty = true;
	}
	else if (IsInputButtonEmpty(m_strBlast))
	{
		empty = true;
	}

	return empty;
}

bool CConfig::IsInputButtonEmpty(char* inputButton)
{
	if ((inputButton[2] == ' ') && (inputButton[3] == ' '))
	{
		return true;
	}

	return false;
}

void CConfig::SetVkeys(void)
{
	this->m_iUp = HexStringToInt(GetStrUp());
	this->m_iDown = HexStringToInt(GetStrDown());
	this->m_iLeft = HexStringToInt(GetStrLeft());
	this->m_iRight = HexStringToInt(GetStrRight());
	this->m_iFireMode = HexStringToInt(GetStrMode());
	this->m_iMinigun = HexStringToInt(GetStrMinigun());
	this->m_iCannon = HexStringToInt(GetStrCannon());
	this->m_iBlast = HexStringToInt(GetStrBlast());
}

long CConfig::HexStringToInt(char* strHex)
{
	return strtol(strHex, NULL, 16);
}

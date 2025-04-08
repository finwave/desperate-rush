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

	this->Load();
}

CConfig::~CConfig(void)
{
	if(this->m_strUp)
	{
		delete [] this->m_strUp;
		this->m_strUp = NULL;
	}
	if(this->m_strDown)
	{
		delete [] this->m_strDown;
		this->m_strDown = NULL;
	}
	if(this->m_strLeft)
	{
		delete [] this->m_strLeft;
		this->m_strLeft = NULL;
	}
	if(this->m_strRight)
	{
		delete [] this->m_strRight;
		this->m_strRight = NULL;
	}
	if(this->m_strFireMode)
	{
		delete [] this->m_strFireMode;
		this->m_strFireMode = NULL;
	}
	if(this->m_strMinigun)
	{
		delete [] this->m_strMinigun;
		this->m_strMinigun = NULL;
	}
	if(this->m_strCannon)
	{
		delete [] this->m_strCannon;
		this->m_strCannon = NULL;
	}
	if(this->m_strBlast)
	{
		delete [] this->m_strBlast;
		this->m_strBlast = NULL;
	}
}

std::string CConfig::GetWorkingDir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

void CConfig::Load(void)
{
	const fs::path applicationPath = fs::path(m_sApplicationPath, std::locale(""));
	fs::current_path(applicationPath);

	char nextChar;
	char* strData = NULL;
	bool readLine = false;
	int iLineIndex = 1;
	int i = 0;

	this->m_bSuccess = false;

	std::ifstream fileIn;
	fileIn.open("config.cfg");

	// file exists
	if(fileIn.is_open() && !(fileIn.bad()))
	{
		strData = new char[3];

		// file not reached end
		while(!fileIn.eof())
		{
			// get the next character from file
			nextChar = fileIn.get();

			// next character is '='
			if(nextChar == '=')
			{
				readLine = true;
			}

			// read rest of the data from the current line
			if(readLine)
			{
				switch(iLineIndex)
				{
					case 1:

						strData = new char[100];
						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							strData[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						this->m_iVolumeMusic = atoi(strData);

						delete [] strData;
						strData = NULL;

						i = 0;

						break;

					case 2:

						strData = new char[100];
						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							strData[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						this->m_iVolumeSoundEffect = atoi(strData);

						delete [] strData;
						strData = NULL;

						i = 0;

						break;

					case 3:

						strData = new char[100];
						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							strData[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						this->m_eAntialiasing = (eANTIALIASING)atoi(strData);

						delete [] strData;
						strData = NULL;

						i = 0;

						break;

					case 4:

						strData = new char[100];
						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							strData[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						this->m_eSpecularLighting = (eSPECULAR_LIGHTING)atoi(strData);

						delete [] strData;
						strData = NULL;

						i = 0;

						break;

					case 5:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strUp[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 6:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strDown[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 7:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strLeft[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 8:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strRight[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 9:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strFireMode[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 10:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strMinigun[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 11:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strCannon[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;

					case 12:

						nextChar = fileIn.get();

						while(nextChar != '\n')
						{
							this->m_strBlast[i] = nextChar;
							nextChar = fileIn.get();
							i++;
						}

						i = 0;

						break;
				}

				readLine = false;
				iLineIndex++;
			}
		}

		fileIn.close();

		// checks if loaded values are valid
		this->CheckAudio();
		this->CheckAntialiasing();
		this->CheckSpecularLighting();
		this->CheckControls();

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
	if(fileOut.is_open())
    {
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"GAME CONFIGURATION";
		fileOut<<"\n\n";
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"AUDIO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"music=";
		fileOut<<this->m_iVolumeMusic;
		fileOut<<"\n";
		fileOut<<"sound effect=";
		fileOut<<this->m_iVolumeSoundEffect;
		fileOut<<"\n\n";
		fileOut<<"VIDEO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"antialiasing=";
		fileOut<<this->m_eAntialiasing;
		fileOut<<"\n";
		fileOut<<"specular lighting=";
		fileOut<<this->m_eSpecularLighting;
		fileOut<<"\n\n";
		fileOut<<"CONTROLS";
		fileOut<<"\n";
		fileOut<<"--------";
		fileOut<<"\n\n";
		fileOut<<"up=";
		fileOut<<this->m_strUp[0];
		fileOut<<this->m_strUp[1];
		fileOut<<this->m_strUp[2];
		fileOut<<this->m_strUp[3];
		fileOut<<"\n";
		fileOut<<"down=";
		fileOut<<this->m_strDown[0];
		fileOut<<this->m_strDown[1];
		fileOut<<this->m_strDown[2];
		fileOut<<this->m_strDown[3];
		fileOut<<"\n";
		fileOut<<"left=";
		fileOut<<this->m_strLeft[0];
		fileOut<<this->m_strLeft[1];
		fileOut<<this->m_strLeft[2];
		fileOut<<this->m_strLeft[3];
		fileOut<<"\n";
		fileOut<<"right=";
		fileOut<<this->m_strRight[0];
		fileOut<<this->m_strRight[1];
		fileOut<<this->m_strRight[2];
		fileOut<<this->m_strRight[3];
		fileOut<<"\n";
		fileOut<<"fire mode=";
		fileOut<<this->m_strFireMode[0];
		fileOut<<this->m_strFireMode[1];
		fileOut<<this->m_strFireMode[2];
		fileOut<<this->m_strFireMode[3];
		fileOut<<"\n";
		fileOut<<"minigun=";
		fileOut<<this->m_strMinigun[0];
		fileOut<<this->m_strMinigun[1];
		fileOut<<this->m_strMinigun[2];
		fileOut<<this->m_strMinigun[3];
		fileOut<<"\n";
		fileOut<<"cannon=";
		fileOut<<this->m_strCannon[0];
		fileOut<<this->m_strCannon[1];
		fileOut<<this->m_strCannon[2];
		fileOut<<this->m_strCannon[3];
		fileOut<<"\n";
		fileOut<<"bomb=";
		fileOut<<this->m_strBlast[0];
		fileOut<<this->m_strBlast[1];
		fileOut<<this->m_strBlast[2];
		fileOut<<this->m_strBlast[3];
		fileOut<<"\n";

		fileOut.close();
		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::DefaultAll(void)
{
	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if(fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"GAME CONFIGURATION";
		fileOut<<"\n\n";
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"AUDIO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"music=85";
		fileOut<<"\n";
		fileOut<<"sound effect=100";
		fileOut<<"\n\n";
		fileOut<<"VIDEO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"antialiasing=0";
		fileOut<<"\n";
		fileOut<<"specular lighting=0";
		fileOut<<"\n\n";
		fileOut<<"CONTROLS";
		fileOut<<"\n";
		fileOut<<"--------";
		fileOut<<"\n\n";
		fileOut<<"up=0x26";
		fileOut<<"\n";
		fileOut<<"down=0x28";
		fileOut<<"\n";
		fileOut<<"left=0x25";
		fileOut<<"\n";
		fileOut<<"right=0x27";
		fileOut<<"\n";
		fileOut<<"fire mode=0x10";
		fileOut<<"\n";
		fileOut<<"minigun=0x11";
		fileOut<<"\n";
		fileOut<<"cannon=0x0D";
		fileOut<<"\n";
		fileOut<<"blast=0x20";
		fileOut<<"\n";

		fileOut.close();

		// sets default values to member variables

		this->m_iVolumeMusic = 85;
		this->m_iVolumeSoundEffect = 100;

		this->m_eAntialiasing = eANTIALIASING_0X;
		this->m_eSpecularLighting = eSPECULAR_LIGHTING_OFF;

		this->m_strUp[0] = '0';
		this->m_strUp[1] = 'x';
		this->m_strUp[2] = '2';
		this->m_strUp[3] = '6';

		this->m_strDown[0] = '0';
		this->m_strDown[1] = 'x';
		this->m_strDown[2] = '2';
		this->m_strDown[3] = '8';

		this->m_strLeft[0] = '0';
		this->m_strLeft[1] = 'x';
		this->m_strLeft[2] = '2';
		this->m_strLeft[3] = '5';

		this->m_strRight[0] = '0';
		this->m_strRight[1] = 'x';
		this->m_strRight[2] = '2';
		this->m_strRight[3] = '7';

		this->m_strFireMode[0] = '0';
		this->m_strFireMode[1] = 'x';
		this->m_strFireMode[2] = '1';
		this->m_strFireMode[3] = '0';

		this->m_strMinigun[0] = '0';
		this->m_strMinigun[1] = 'x';
		this->m_strMinigun[2] = '1';
		this->m_strMinigun[3] = '1';

		this->m_strCannon[0] = '0';
		this->m_strCannon[1] = 'x';
		this->m_strCannon[2] = '0';
		this->m_strCannon[3] = 'D';

		this->m_strBlast[0] = '0';
		this->m_strBlast[1] = 'x';
		this->m_strBlast[2] = '2';
		this->m_strBlast[3] = '0';

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::DefaultAudio()
{
	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if(fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"GAME CONFIGURATION";
		fileOut<<"\n\n";
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"AUDIO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"music=85";
		fileOut<<"\n";
		fileOut<<"sound effect=100";
		fileOut<<"\n\n";
		fileOut<<"VIDEO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"antialiasing=";
		fileOut<<this->m_eAntialiasing;
		fileOut<<"\n";
		fileOut<<"specular lighting=";
		fileOut<<this->m_eSpecularLighting;
		fileOut<<"\n\n";
		fileOut<<"CONTROLS";
		fileOut<<"\n";
		fileOut<<"--------";
		fileOut<<"\n\n";
		fileOut<<"up=";
		fileOut<<this->m_strUp;
		fileOut<<"\n";
		fileOut<<"down=";
		fileOut<<this->m_strDown;
		fileOut<<"\n";
		fileOut<<"left=";
		fileOut<<this->m_strLeft;
		fileOut<<"\n";
		fileOut<<"right=";
		fileOut<<this->m_strRight;
		fileOut<<"\n";
		fileOut<<"fire mode=";
		fileOut<<this->m_strFireMode;
		fileOut<<"\n";
		fileOut<<"minigun=";
		fileOut<<this->m_strMinigun;
		fileOut<<"\n";
		fileOut<<"cannon=";
		fileOut<<this->m_strCannon;
		fileOut<<"\n";
		fileOut<<"blast=";
		fileOut<<this->m_strBlast;
		fileOut<<"\n";

		fileOut.close();

		// sets default values to member variables
		this->m_iVolumeMusic = 85;
		this->m_iVolumeSoundEffect = 100;

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::DefaultAntialiasing()
{
	std::ofstream fileOut;
	fileOut.open("config.cfg");

	// file created successfully
	if(fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"GAME CONFIGURATION";
		fileOut<<"\n\n";
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"AUDIO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"music=";
		fileOut<<this->m_iVolumeMusic;
		fileOut<<"\n";
		fileOut<<"sound effect=";
		fileOut<<this->m_iVolumeSoundEffect;
		fileOut<<"\n\n";
		fileOut<<"VIDEO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"antialiasing=0";
		fileOut<<"\n";
		fileOut<<"specular lighting=";
		fileOut<<this->m_eSpecularLighting;
		fileOut<<"\n\n";
		fileOut<<"CONTROLS";
		fileOut<<"\n";
		fileOut<<"--------";
		fileOut<<"\n\n";
		fileOut<<"up=";
		fileOut<<this->m_strUp;
		fileOut<<"\n";
		fileOut<<"down=";
		fileOut<<this->m_strDown;
		fileOut<<"\n";
		fileOut<<"left=";
		fileOut<<this->m_strLeft;
		fileOut<<"\n";
		fileOut<<"right=";
		fileOut<<this->m_strRight;
		fileOut<<"\n";
		fileOut<<"fire mode=";
		fileOut<<this->m_strFireMode;
		fileOut<<"\n";
		fileOut<<"minigun=";
		fileOut<<this->m_strMinigun;
		fileOut<<"\n";
		fileOut<<"cannon=";
		fileOut<<this->m_strCannon;
		fileOut<<"\n";
		fileOut<<"blast=";
		fileOut<<this->m_strBlast;
		fileOut<<"\n";

		fileOut.close();

		// sets default values to member variables
		this->m_eAntialiasing = eANTIALIASING_0X;

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
	if(fileOut.is_open())
	{
		// writes all default values to 'config.cfg' file

		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"GAME CONFIGURATION";
		fileOut<<"\n\n";
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"AUDIO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"music=";
		fileOut<<this->m_iVolumeMusic;
		fileOut<<"\n";
		fileOut<<"sound effect=";
		fileOut<<this->m_iVolumeSoundEffect;
		fileOut<<"\n\n";
		fileOut<<"VIDEO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"antialiasing=";
		fileOut<<this->m_eAntialiasing;
		fileOut<<"\n";
		fileOut<<"specular lighting=0";
		fileOut<<"\n\n";
		fileOut<<"CONTROLS";
		fileOut<<"\n";
		fileOut<<"--------";
		fileOut<<"\n\n";
		fileOut<<"up=";
		fileOut<<this->m_strUp;
		fileOut<<"\n";
		fileOut<<"down=";
		fileOut<<this->m_strDown;
		fileOut<<"\n";
		fileOut<<"left=";
		fileOut<<this->m_strLeft;
		fileOut<<"\n";
		fileOut<<"right=";
		fileOut<<this->m_strRight;
		fileOut<<"\n";
		fileOut<<"fire mode=";
		fileOut<<this->m_strFireMode;
		fileOut<<"\n";
		fileOut<<"minigun=";
		fileOut<<this->m_strMinigun;
		fileOut<<"\n";
		fileOut<<"cannon=";
		fileOut<<this->m_strCannon;
		fileOut<<"\n";
		fileOut<<"blast=";
		fileOut<<this->m_strBlast;
		fileOut<<"\n";

		fileOut.close();

		// sets default values to member variables
		this->m_eAntialiasing = eANTIALIASING_0X;

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
	if(fileOut.is_open())
	{
		// writes default control values to 'config.cfg' file

		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"GAME CONFIGURATION";
		fileOut<<"\n\n";
		fileOut<<"*******************";
		fileOut<<"\n\n";
		fileOut<<"AUDIO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"music=";
		fileOut<<this->m_iVolumeMusic;
		fileOut<<"\n";
		fileOut<<"sound effect=";
		fileOut<<this->m_iVolumeSoundEffect;
		fileOut<<"\n\n";
		fileOut<<"VIDEO";
		fileOut<<"\n";
		fileOut<<"-----";
		fileOut<<"\n\n";
		fileOut<<"antialiasing=";
		fileOut<<this->m_eAntialiasing;
		fileOut<<"\n";
		fileOut<<"specular lighting=";
		fileOut<<this->m_eSpecularLighting;
		fileOut<<"\n\n";
		fileOut<<"CONTROLS";
		fileOut<<"\n";
		fileOut<<"--------";
		fileOut<<"\n\n";
		fileOut<<"up=0x26";
		fileOut<<"\n";
		fileOut<<"down=0x28";
		fileOut<<"\n";
		fileOut<<"left=0x25";
		fileOut<<"\n";
		fileOut<<"right=0x27";
		fileOut<<"\n";
		fileOut<<"fire mode=0x10";
		fileOut<<"\n";
		fileOut<<"minigun=0x11";
		fileOut<<"\n";
		fileOut<<"cannon=0x0D";
		fileOut<<"\n";
		fileOut<<"blast=0x20";
		fileOut<<"\n";

		fileOut.close();

		// sets default values to member variables

		this->m_strUp[0] = '0';
		this->m_strUp[1] = 'x';
		this->m_strUp[2] = '2';
		this->m_strUp[3] = '6';

		this->m_strDown[0] = '0';
		this->m_strDown[1] = 'x';
		this->m_strDown[2] = '2';
		this->m_strDown[3] = '8';

		this->m_strLeft[0] = '0';
		this->m_strLeft[1] = 'x';
		this->m_strLeft[2] = '2';
		this->m_strLeft[3] = '5';

		this->m_strRight[0] = '0';
		this->m_strRight[1] = 'x';
		this->m_strRight[2] = '2';
		this->m_strRight[3] = '7';

		this->m_strFireMode[0] = '0';
		this->m_strFireMode[1] = 'x';
		this->m_strFireMode[2] = '1';
		this->m_strFireMode[3] = '0';

		this->m_strMinigun[0] = '0';
		this->m_strMinigun[1] = 'x';
		this->m_strMinigun[2] = '1';
		this->m_strMinigun[3] = '1';

		this->m_strCannon[0] = '0';
		this->m_strCannon[1] = 'x';
		this->m_strCannon[2] = '0';
		this->m_strCannon[3] = 'D';

		this->m_strBlast[0] = '0';
		this->m_strBlast[1] = 'x';
		this->m_strBlast[2] = '2';
		this->m_strBlast[3] = '0';

		m_bSuccess = true;
	}

	else
	{
		m_bSuccess = false;
	}
}

void CConfig::CheckAudio()
{
	if(	(this->m_iVolumeMusic < 0) || 
		(this->m_iVolumeMusic > 100))
	{
		this->DefaultAudio();
	}
	if(	(this->m_iVolumeSoundEffect < 0) || 
		(this->m_iVolumeSoundEffect > 100))
	{
		this->DefaultAudio();
	}
}

void CConfig::CheckAntialiasing()
{
	if(	(this->m_eAntialiasing < 0) || 
		(this->m_eAntialiasing > 4))
	{
		this->DefaultAntialiasing();
	}
}

void CConfig::CheckSpecularLighting()
{
	if(	(this->m_eSpecularLighting < 0) || 
		(this->m_eSpecularLighting > 1))
	{
		this->DefaultSpecularLighting();
	}
}

void CConfig::CheckControls()
{
	bool bValid = true;

	// checks next control value if still valid

	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strUp))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strDown))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strLeft))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strRight))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strFireMode))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strMinigun))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strCannon))
		{
			bValid = false;
		}
	}
	if(bValid)
	{
		if(!this->m_keyReference.CheckValidValue(this->m_strBlast))
		{
			bValid = false;
		}
	}

	if(!bValid)
	{
		this->DefaultControls();
	}
}

void CConfig::RemoveDuplicate(int iButton)
{
	switch(iButton)
	{
	// compare up to others
	case 1:

		if(	(m_strUp[2] == m_strDown[2]) && 
			(m_strUp[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strUp[2] == m_strLeft[2]) && 
			(m_strUp[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strUp[2] == m_strRight[2]) && 
			(m_strUp[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strUp[2] == m_strFireMode[2]) && 
			(m_strUp[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strUp[2] == m_strMinigun[2]) && 
			(m_strUp[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strUp[2] == m_strCannon[2]) && 
			(m_strUp[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if(	(m_strUp[2] == m_strBlast[2]) && 
			(m_strUp[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare down to others
	case 2:

		if(	(m_strDown[2] == m_strUp[2]) && 
			(m_strDown[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strDown[2] == m_strLeft[2]) && 
			(m_strDown[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strDown[2] == m_strRight[2]) && 
			(m_strDown[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strDown[2] == m_strFireMode[2]) && 
			(m_strDown[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strDown[2] == m_strMinigun[2]) && 
			(m_strDown[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strDown[2] == m_strCannon[2]) && 
			(m_strDown[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if(	(m_strDown[2] == m_strBlast[2]) && 
			(m_strDown[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare left to others
	case 3:

		if(	(m_strLeft[2] == m_strUp[2]) && 
			(m_strLeft[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strLeft[2] == m_strDown[2]) && 
			(m_strLeft[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strLeft[2] == m_strRight[2]) && 
			(m_strLeft[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strLeft[2] == m_strFireMode[2]) && 
			(m_strLeft[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strLeft[2] == m_strMinigun[2]) && 
			(m_strLeft[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strLeft[2] == m_strCannon[2]) && 
			(m_strLeft[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if(	(m_strLeft[2] == m_strBlast[2]) && 
			(m_strLeft[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare right to others
	case 4:

		if(	(m_strRight[2] == m_strUp[2]) && 
			(m_strRight[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strRight[2] == m_strDown[2]) && 
			(m_strRight[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strRight[2] == m_strLeft[2]) && 
			(m_strRight[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strRight[2] == m_strFireMode[2]) && 
			(m_strRight[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strRight[2] == m_strMinigun[2]) && 
			(m_strRight[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strRight[2] == m_strCannon[2]) && 
			(m_strRight[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if(	(m_strRight[2] == m_strBlast[2]) && 
			(m_strRight[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare fire mode to others
	case 5:

		if(	(m_strFireMode[2] == m_strUp[2]) && 
			(m_strFireMode[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strFireMode[2] == m_strDown[2]) && 
			(m_strFireMode[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strFireMode[2] == m_strLeft[2]) && 
			(m_strFireMode[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strFireMode[2] == m_strRight[2]) && 
			(m_strFireMode[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strFireMode[2] == m_strMinigun[2]) && 
			(m_strFireMode[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strFireMode[2] == m_strCannon[2]) && 
			(m_strFireMode[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if(	(m_strFireMode[2] == m_strBlast[2]) && 
			(m_strFireMode[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare minigun to others
	case 6:

		if(	(m_strMinigun[2] == m_strUp[2]) && 
			(m_strMinigun[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strMinigun[2] == m_strDown[2]) && 
			(m_strMinigun[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strMinigun[2] == m_strLeft[2]) && 
			(m_strMinigun[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strMinigun[2] == m_strRight[2]) && 
			(m_strMinigun[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strMinigun[2] == m_strFireMode[2]) && 
			(m_strMinigun[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strMinigun[2] == m_strCannon[2]) && 
			(m_strMinigun[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		if(	(m_strMinigun[2] == m_strBlast[2]) && 
			(m_strMinigun[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare cannon to others
	case 7:

		if(	(m_strCannon[2] == m_strUp[2]) && 
			(m_strCannon[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strCannon[2] == m_strDown[2]) && 
			(m_strCannon[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strCannon[2] == m_strLeft[2]) && 
			(m_strCannon[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strCannon[2] == m_strRight[2]) && 
			(m_strCannon[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strCannon[2] == m_strFireMode[2]) && 
			(m_strCannon[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strCannon[2] == m_strMinigun[2]) && 
			(m_strCannon[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strCannon[2] == m_strBlast[2]) && 
			(m_strCannon[3] == m_strBlast[3]))
		{
			m_strBlast[2] = ' ';
			m_strBlast[3] = ' ';
		}

		break;

	// compare bomb to others
	case 8:

		if(	(m_strBlast[2] == m_strUp[2]) && 
			(m_strBlast[3] == m_strUp[3]))
		{
			m_strUp[2] = ' ';
			m_strUp[3] = ' ';
		}

		if(	(m_strBlast[2] == m_strDown[2]) && 
			(m_strBlast[3] == m_strDown[3]))
		{
			m_strDown[2] = ' ';
			m_strDown[3] = ' ';
		}

		if(	(m_strBlast[2] == m_strLeft[2]) && 
			(m_strBlast[3] == m_strLeft[3]))
		{
			m_strLeft[2] = ' ';
			m_strLeft[3] = ' ';
		}

		if(	(m_strBlast[2] == m_strRight[2]) && 
			(m_strBlast[3] == m_strRight[3]))
		{
			m_strRight[2] = ' ';
			m_strRight[3] = ' ';
		}

		if(	(m_strBlast[2] == m_strFireMode[2]) && 
			(m_strBlast[3] == m_strFireMode[3]))
		{
			m_strFireMode[2] = ' ';
			m_strFireMode[3] = ' ';
		}

		if(	(m_strBlast[2] == m_strMinigun[2]) && 
			(m_strBlast[3] == m_strMinigun[3]))
		{
			m_strMinigun[2] = ' ';
			m_strMinigun[3] = ' ';
		}

		if(	(m_strBlast[2] == m_strCannon[2]) && 
			(m_strBlast[3] == m_strCannon[3]))
		{
			m_strCannon[2] = ' ';
			m_strCannon[3] = ' ';
		}

		break;
	}
}

bool CConfig::ButtonEmpty(void)
{
	bool empty = false;

	if(	(m_strUp[2] == ' ') && 
		(m_strUp[3] == ' '))
	{
		empty = true;
	}

	else if((m_strDown[2] == ' ') && 
			(m_strDown[3] == ' '))
	{
		empty = true;
	}

	else if((m_strLeft[2] == ' ') && 
			(m_strLeft[3] == ' '))
	{
		empty = true;
	}

	else if((m_strRight[2] == ' ') && 
			(m_strRight[3] == ' '))
	{
		empty = true;
	}

	else if((m_strFireMode[2] == ' ') && 
			(m_strFireMode[3] == ' '))
	{
		empty = true;
	}

	else if((m_strMinigun[2] == ' ') && 
			(m_strMinigun[3] == ' '))
	{
		empty = true;
	}

	else if((m_strCannon[2] == ' ') && 
			(m_strCannon[3] == ' '))
	{
		empty = true;
	}

	else if((m_strBlast[2] == ' ') && 
			(m_strBlast[3] == ' '))
	{
		empty = true;
	}

	return empty;
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
	long int value = strtol(strHex, NULL, 16);
	return value;
}

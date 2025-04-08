#pragma once

#include "windows.h"
#include <stdlib.h>
#include <tchar.h>
#include <malloc.h>
#include <fstream>
#include <filesystem>

// scan code / virtual-key code reference class
#include "KeyReference.h"

namespace fs = std::filesystem;

class CConfig
{
public:

	enum eANTIALIASING
	{
		eANTIALIASING_0X,
		eANTIALIASING_2X,
		eANTIALIASING_4X,
		eANTIALIASING_6X,
		eANTIALIASING_8X
	};

	enum eSPECULAR_LIGHTING
	{
		eSPECULAR_LIGHTING_OFF,
		eSPECULAR_LIGHTING_ON
	};

	CConfig(void);
	~CConfig(void);

	inline bool IsSuccess() { return this->m_bSuccess; }

	inline int GetVolumeMusic() { return this->m_iVolumeMusic; }
	inline void SetVolumeMusic(int iVolume) { this->m_iVolumeMusic = iVolume; }

	inline int GetVolumeSoundEffect() { return this->m_iVolumeSoundEffect; }
	inline void SetVolumeSoundEffect(int iVolume) { this->m_iVolumeSoundEffect = iVolume; }

	inline char* GetStrUp() { return this->m_strUp; }
	inline char* GetStrDown() { return this->m_strDown; }
	inline char* GetStrLeft() { return this->m_strLeft; }
	inline char* GetStrRight() { return this->m_strRight; }
	inline char* GetStrMode() { return this->m_strFireMode; }
	inline char* GetStrMinigun() { return this->m_strMinigun; }
	inline char* GetStrCannon() { return this->m_strCannon; }
	inline char* GetStrBlast() { return this->m_strBlast; }

	inline int GetVkeyUp() { return this->m_iUp; }
	inline int GetVkeyDown() { return this->m_iDown; }
	inline int GetVkeyLeft() { return this->m_iLeft; }
	inline int GetVkeyRight() { return this->m_iRight; }
	inline int GetVkeyMode() { return this->m_iFireMode; }
	inline int GetVkeyMinigun() { return this->m_iMinigun; }
	inline int GetVkeyCannon() { return this->m_iCannon; }
	inline int GetVkeyBlast() { return this->m_iBlast; }

	inline void SetStrUp(char* strUp) { this->m_strUp = strUp; }
	inline void SetStrDown(char* strDown) { this->m_strDown = strDown; }
	inline void SetStrLeft(char* strLeft) { this->m_strLeft = strLeft; }
	inline void SetStrRight(char* strRight) { this->m_strRight = strRight; }
	inline void SetStrFireMode(char* strFireMde) { this->m_strFireMode = strFireMde; }
	inline void SetStrMinigun(char* strMinigun) { this->m_strMinigun = strMinigun; }
	inline void SetStrCannon(char* strCannon) { this->m_strCannon = strCannon; }
	inline void SetStrBlast(char* strBlast) { this->m_strBlast = strBlast; }

	void Load();
	void Save();
	void DefaultControls();

	/**
	 * CheckDuplicate
	 * checks if a control button value described by given parameter
	 * is the same as any other current control button value
	 * if so changes that other button value to empty
	 * @param button describes which control is in question (up, down, ...)
	 */
	void RemoveDuplicate(int button);

	bool ButtonEmpty(void);

	/**
	 * SetVkey
	 * sets member values (integer) describing virtual-keys of player controls
	 */
	void SetVkeys(void);

	inline eANTIALIASING GetAntialiasing() { return this->m_eAntialiasing; }
	inline void SetAntialiasing(eANTIALIASING eAntialiasing) { this->m_eAntialiasing = eAntialiasing; }

	inline eSPECULAR_LIGHTING GetSpecularLighting() { return this->m_eSpecularLighting; }
	inline void SetSpecularLighting(eSPECULAR_LIGHTING eSpecularLighting) { this->m_eSpecularLighting = eSpecularLighting; }

private:

	std::string GetWorkingDir();

	void DefaultAll();
	void DefaultAudio();
	void DefaultAntialiasing();
	void DefaultSpecularLighting();

	void CheckAudio();
	void CheckAntialiasing();
	void CheckSpecularLighting();
	void CheckControls();

	/**
	 * HexStringToInt
	 * @return int value of hex string
	 */
	long HexStringToInt(char* strHex);

	// key codes reference
	CKeyReference		m_keyReference;

	eANTIALIASING		m_eAntialiasing;
	eSPECULAR_LIGHTING	m_eSpecularLighting;

	std::string			m_sApplicationPath;
	bool				m_bSuccess;

	// members holding music and sound effect volume values
	int					m_iVolumeMusic;
	int					m_iVolumeSoundEffect;

	// members holding hex values of game cotrols 
	char*				m_strUp;
	char*				m_strDown;
	char*				m_strLeft;
	char*				m_strRight;
	char*				m_strFireMode;
	char*				m_strMinigun;
	char*				m_strCannon;
	char*				m_strBlast;

	// members holding integer values of game cotrols (int vKey)
	long int			m_iUp;
	long int			m_iDown;
	long int			m_iLeft;
	long int			m_iRight;
	long int			m_iFireMode;
	long int			m_iMinigun;
	long int			m_iCannon;
	long int			m_iBlast;
};
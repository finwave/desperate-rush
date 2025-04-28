#pragma once

// MESH COUNT
#define MESH_MENUS_SHIPS									7
#define MESH_MENUS_TEXT										36

// SPRITE COUNT
#define SPRITE_MENUS										136

// MULTI-PART SPRITES
#define SPRITE_LOADING_BAR									327
#define SPRITE_MENUS_AUDIO_BAR								100

//#define MENU_CREDITS

#include "Sprite.h"
#include "SpriteScrolling.h"
#include "XFileContainer.h"

#include "Resources.h"

// Forward declaration
class CTheApp;

class CResourceMenus : public CResources
{
public:

	CResourceMenus();

	virtual void Init(CTheApp* pApp, CZipManager* pZipManager);

	virtual void Release();
	virtual HRESULT Load();

	HRESULT LoadSpriteLoadingScreen();

	/* LOADING SCREEN */

	inline CSprite* GetSpriteLoadingBar() { return this->m_pSpriteLoadingBar; }
	inline CSprite* GetSpriteLoadingScreen() { return this->m_pSpriteLoadingScreen; }

	/* MENUS */

#ifdef MENUS_PLANET
	inline CXFileContainer& GetMeshMenusPlanet() { return m_MeshMenusPlanet; }
#endif

	// letters
	inline CXFileContainer& GetMeshLetterA() { return m_MeshLetterA; }
	inline CXFileContainer& GetMeshLetterB() { return m_MeshLetterB; }
	inline CXFileContainer& GetMeshLetterC() { return m_MeshLetterC; }
	inline CXFileContainer& GetMeshLetterD() { return m_MeshLetterD; }
	inline CXFileContainer& GetMeshLetterE() { return m_MeshLetterE; }
	inline CXFileContainer& GetMeshLetterF() { return m_MeshLetterF; }
	inline CXFileContainer& GetMeshLetterG() { return m_MeshLetterG; }
	inline CXFileContainer& GetMeshLetterH() { return m_MeshLetterH; }
	inline CXFileContainer& GetMeshLetterI() { return m_MeshLetterI; }
	inline CXFileContainer& GetMeshLetterJ() { return m_MeshLetterJ; }
	inline CXFileContainer& GetMeshLetterK() { return m_MeshLetterK; }
	inline CXFileContainer& GetMeshLetterL() { return m_MeshLetterL; }
	inline CXFileContainer& GetMeshLetterM() { return m_MeshLetterM; }
	inline CXFileContainer& GetMeshLetterN() { return m_MeshLetterN; }
	inline CXFileContainer& GetMeshLetterO() { return m_MeshLetterO; }
	inline CXFileContainer& GetMeshLetterP() { return m_MeshLetterP; }
	inline CXFileContainer& GetMeshLetterQ() { return m_MeshLetterQ; }
	inline CXFileContainer& GetMeshLetterR() { return m_MeshLetterR; }
	inline CXFileContainer& GetMeshLetterS() { return m_MeshLetterS; }
	inline CXFileContainer& GetMeshLetterT() { return m_MeshLetterT; }
	inline CXFileContainer& GetMeshLetterU() { return m_MeshLetterU; }
	inline CXFileContainer& GetMeshLetterV() { return m_MeshLetterV; }
	inline CXFileContainer& GetMeshLetterW() { return m_MeshLetterW; }
	inline CXFileContainer& GetMeshLetterX() { return m_MeshLetterX; }
	inline CXFileContainer& GetMeshLetterY() { return m_MeshLetterY; }
	inline CXFileContainer& GetMeshLetterZ() { return m_MeshLetterZ; }

	// numbers
	inline CXFileContainer& GetMeshNumber0() { return m_MeshNumber0; }
	inline CXFileContainer& GetMeshNumber1() { return m_MeshNumber1; }
	inline CXFileContainer& GetMeshNumber2() { return m_MeshNumber2; }
	inline CXFileContainer& GetMeshNumber3() { return m_MeshNumber3; }
	inline CXFileContainer& GetMeshNumber4() { return m_MeshNumber4; }
	inline CXFileContainer& GetMeshNumber5() { return m_MeshNumber5; }
	inline CXFileContainer& GetMeshNumber6() { return m_MeshNumber6; }
	inline CXFileContainer& GetMeshNumber7() { return m_MeshNumber7; }
	inline CXFileContainer& GetMeshNumber8() { return m_MeshNumber8; }
	inline CXFileContainer& GetMeshNumber9() { return m_MeshNumber9; }

	// credits
#ifdef MENU_CREDITS
	inline CSprite* GetSpriteCreditsBackLayer() { return this->m_pSpriteCreditsBackLayer; }
	inline CSpriteScrolling* GetSpriteCreditsText() { return this->m_pSpriteCreditsText; }
#endif

	// load cycle
	inline bool IsMasterZipFileLoaded() { return (m_bZipFileStepLoaded && !m_bipFileStepWaited); }

	// SPRITES

	// Menus

	void RenderMenuTextHighlight(int posY);
	void RenderMenuTextHighlight(int posX, int posY);

	CSpriteScrolling* m_pSpriteMenuStarsBack;
	CSpriteScrolling* m_pSpriteMenuStarsFront;

	CSprite* m_pSpriteMenuBackground;

	CSprite* m_pSpriteMenuTextHighlightLong;
	CSprite* m_pSpriteMenuTextHighlightShort;

	CSprite* m_pSpriteMenuTitleMain;
	CSprite* m_pSpriteMenuTitleHighscore;

	CSprite* m_pSpriteMenuMain;
	CSprite* m_pSpriteMenuOptions;
	CSprite* m_pSpriteMenuInput;
	CSprite* m_pSpriteMenuAudio;
	CSprite* m_pSpriteMenuDisplay;
	CSprite* m_pSpriteMenuHighscore;

	CSprite* m_pSpriteVideoAntialiasingBarBorder;
	CSprite* m_pSpriteVideoAntialiasingBar2x;
	CSprite* m_pSpriteVideoAntialiasingBar46x;
	CSprite* m_pSpriteVideoAntialiasingBar8x;

	CSprite* m_pSpriteArrowInput;
	CSprite* m_pSpriteArrowAntialiasingNormalLeft;
	CSprite* m_pSpriteArrowAntialiasingNormalRight;
	CSprite* m_pSpriteArrowAntialiasingGlowLeft;
	CSprite* m_pSpriteArrowAntialiasingGlowRight;
	CSprite* m_pSpriteArrowAntialiasingHideLeft;
	CSprite* m_pSpriteArrowAntialiasingHideRight;

	CSprite* m_pSpriteSpecularLightingOn;
	CSprite* m_pSpriteSpecularLightingOnGlow;
	CSprite* m_pSpriteSpecularLightingOff;
	CSprite* m_pSpriteSpecularLightingOffGlow;

	CSprite* m_pSpriteMessageInputEmpty;
	CSprite* m_pSpriteMessageInputKey;
	CSprite* m_pSpriteMessageRestart;
	CSprite* m_pSpriteMessageOK1;
	CSprite* m_pSpriteMessageOK2;

	CSprite* m_pSpriteAudioBarBorder;
	CSprite* m_pSpriteAudioBarMeter;

	CSprite* m_pSpriteVersion;
	CSprite* m_pSpriteCursor;

#ifdef MENU_CREDITS
	CSprite* m_pSpriteCreditsBackLayer;
	CSpriteScrolling* m_pSpriteCreditsText;
#endif

#ifdef MENUS_FOG
	CSpriteScrolling* m_pSpriteFogBack;
	CSpriteScrolling* m_pSpriteFogFront;
#endif

private:

	// LOAD METHODS

	HRESULT LoadMeshMenusShips();
	HRESULT LoadMeshMenusText();
	HRESULT LoadSpriteMenus();

	// AFTER-LOAD METHODS

	void InitMeshMenus();
	void InitMeshMenusPlayer();
	void InitMeshMenusEnemies();
	void InitMeshMenusBosses();

	// LOAD CYCLE

	bool m_bZipFileStepLoaded;
	bool m_bipFileStepWaited;
	bool m_bIsLoadingScreenSprites;
	bool m_bMenusShipsLoaded;
	bool m_bMenusTextLoaded;

	// SPRITE DEPTH

	float m_fDepthMenuText;
	float m_fDepthMenuHighlight;

	// SPRITE DIMENSIONS

	const int SPRITE_WIDTH_MENU_TEXT_HIGHLIGHT_LONG = 353;
	const int SPRITE_WIDTH_MENU_TEXT_HIGHLIGHT_SHORT = 148;
	const int SPRITE_HEIGHT_MENU_TEXT_HIGHLIGHT = 60;

	// MESHES

	// Menus

	CXFileContainer		m_MeshMenusPlanet;

	CXFileContainer		m_MeshLetterA;
	CXFileContainer		m_MeshLetterB;
	CXFileContainer		m_MeshLetterC;
	CXFileContainer		m_MeshLetterD;
	CXFileContainer		m_MeshLetterE;
	CXFileContainer		m_MeshLetterF;
	CXFileContainer		m_MeshLetterG;
	CXFileContainer		m_MeshLetterH;
	CXFileContainer		m_MeshLetterI;
	CXFileContainer		m_MeshLetterJ;
	CXFileContainer		m_MeshLetterK;
	CXFileContainer		m_MeshLetterL;
	CXFileContainer		m_MeshLetterM;
	CXFileContainer		m_MeshLetterN;
	CXFileContainer		m_MeshLetterO;
	CXFileContainer		m_MeshLetterP;
	CXFileContainer		m_MeshLetterQ;
	CXFileContainer		m_MeshLetterR;
	CXFileContainer		m_MeshLetterS;
	CXFileContainer		m_MeshLetterT;
	CXFileContainer		m_MeshLetterU;
	CXFileContainer		m_MeshLetterV;
	CXFileContainer		m_MeshLetterW;
	CXFileContainer		m_MeshLetterX;
	CXFileContainer		m_MeshLetterY;
	CXFileContainer		m_MeshLetterZ;

	CXFileContainer		m_MeshNumber0;
	CXFileContainer		m_MeshNumber1;
	CXFileContainer		m_MeshNumber2;
	CXFileContainer		m_MeshNumber3;
	CXFileContainer		m_MeshNumber4;
	CXFileContainer		m_MeshNumber5;
	CXFileContainer		m_MeshNumber6;
	CXFileContainer		m_MeshNumber7;
	CXFileContainer		m_MeshNumber8;
	CXFileContainer		m_MeshNumber9;

	// SPRITES

	// Loading Screen

	CSprite* m_pSpriteLoadingScreen;
	CSprite* m_pSpriteLoadingBar;
};
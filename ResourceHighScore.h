#pragma once

 // MESH COUNT
#define MESH_HIGHSCORE		3

// SPRITE COUNT
#define SPRITE_HIGHSCORE	6

#include "Sprite.h"
#include "SpriteScrolling.h"
#include "XFileContainer.h"

#include "Resources.h"

// Forward declaration
class CTheApp;

class CResourceHighScore : public CResources
{
public:

	CResourceHighScore();

	virtual void Init(CTheApp* pApp, CZipManager* pZipManager);

	virtual void Release();
	virtual HRESULT Load();

	/* HIGHSCORE */

	inline CXFileContainer& GetMeshHighscoreShipPlayer() { return m_MeshHighscoreShipPlayer; }
	inline CXFileContainer& GetMeshHighscoreBulletPlayerMinigun() { return m_MeshHighscoreBulletPlayerMinigun; }
	inline CXFileContainer& GetMeshHighscoreLetterWheel() { return m_MeshHighscoreLetterWheel; }

	// background stars
	inline CSpriteScrolling* GetSpriteHighscoresStarsBack() { return this->m_pSpriteHighscoresStarsBack; }
	inline CSpriteScrolling* GetSpriteHighscoresStarsFront() { return this->m_pSpriteHighscoresStarsFront; }
	// highscore text
	inline CSprite* GetSpriteHighscoresText() { return this->m_pSpriteHighscoresText; }
	// select box
	inline CSprite* GetSpriteHighscoresSelectBox() { return this->m_pSpriteHighscoresSelectBox; }
	// player afterburn
	inline CSprite* GetSpriteHighscoresPlayerAfterburn() { return this->m_pSpriteHighscoresPlayerAfterburn; }

private:

	// LOAD METHODS

	HRESULT LoadMeshHighscore();
	HRESULT LoadSpriteHighscore();

	// MESHES

	CXFileContainer m_MeshHighscoreShipPlayer;
	CXFileContainer m_MeshHighscoreBulletPlayerMinigun;
	CXFileContainer m_MeshHighscoreLetterWheel;

	// SPRITES

	CSpriteScrolling* m_pSpriteHighscoresStarsBack;
	CSpriteScrolling* m_pSpriteHighscoresStarsFront;

	CSprite* m_pSpriteHighscoresText;
	CSprite* m_pSpriteHighscoresSelectBox;
	CSprite* m_pSpriteHighscoresPlayerAfterburn;
};
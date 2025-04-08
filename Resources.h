/**
 * Holds 3d meshes and 2d sprites in memory.
 */

#pragma once

// MODEL TYPES
#define MODEL_TYPE_SHIP_FIRST								1
#define MODEL_TYPE_PLAYER									1
#define MODEL_TYPE_ENEMY									2
#define MODEL_TYPE_BOSS										3
#define MODEL_TYPE_SHIP_LAST								3
#define MODEL_TYPE_BULLET_FIRST								4
#define MODEL_TYPE_BULLET_PLAYER							4
#define MODEL_TYPE_BULLET_PLAYER_CHECK						5
#define MODEL_TYPE_BULLET_DRONE								6
#define MODEL_TYPE_BULLET_SNIPER							7
#define MODEL_TYPE_BULLET_ROLLER							8
#define MODEL_TYPE_BULLET_VANGUARD							9
#define MODEL_TYPE_BULLET_BOSS_1_LASER						10
#define MODEL_TYPE_BULLET_BOSS_1_SCATTER					11
#define MODEL_TYPE_BULLET_LAST								11
#define MODEL_TYPE_ASTEROID									12
#define MODEL_TYPE_TEXT										13
#define MODEL_TYPE_HIGHSCORE_PLAYER							14

// Loading cycle pause times
#define LOAD_STEPS_WAIT_DEFAULT								50
#define LOAD_STEPS_WAIT_GAME								100

#include <vector>
#include <map>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "Sprite.h"
#include "XFileContainer.h"

// Forward declaration
class CTheApp;
class CZipManager;

class CResources
{
public:

	/* MODELS */

	static int MODEL_GAME_PLAYER_FRAME;
	static int MODEL_GAME_PLAYER_MINIGUN;
	static int MODEL_GAME_ENEMY_DRONE_1;
	static int MODEL_GAME_ENEMY_DRONE_2;
	static int MODEL_GAME_ENEMY_DRONE_3;
	static int MODEL_GAME_ENEMY_DRONE_4;
	static int MODEL_GAME_ENEMY_DRONE_5;
	static int MODEL_GAME_ENEMY_SNIPER_1;
	static int MODEL_GAME_ENEMY_SNIPER_2;
	static int MODEL_GAME_ENEMY_SNIPER_3;
	static int MODEL_GAME_ENEMY_SNIPER_4;
	static int MODEL_GAME_ENEMY_SNIPER_5;
	static int MODEL_GAME_ENEMY_ROLLER_1;
	static int MODEL_GAME_ENEMY_ROLLER_2;
	static int MODEL_GAME_ENEMY_ROLLER_3;
	static int MODEL_GAME_ENEMY_ROLLER_4;
	static int MODEL_GAME_ENEMY_ROLLER_5;
	static int MODEL_GAME_ENEMY_VANGUARD_1;
	static int MODEL_GAME_ENEMY_VANGUARD_2;
	static int MODEL_GAME_ENEMY_VANGUARD_3;
	static int MODEL_GAME_ENEMY_VANGUARD_4;
	static int MODEL_GAME_ENEMY_VANGUARD_5;
	static int MODEL_GAME_BOSS_1_FRAME;
	static int MODEL_GAME_BOSS_1_CORE;
	static int MODEL_GAME_BOSS_1_LASER_LEFT;
	static int MODEL_GAME_BOSS_1_LASER_RIGHT;
	static int MODEL_GAME_BOSS_1_SCATTER;
	static int MODEL_GAME_BOSS_1_CANNON;
	static int MODEL_GAME_BULLET_PLAYER_MINIGUN;
	static int MODEL_GAME_BULLET_DRONE;
	static int MODEL_GAME_BULLET_SNIPER;
	static int MODEL_GAME_BULLET_ROLLER;
	static int MODEL_GAME_BULLET_VANGUARD;
	static int MODEL_GAME_BULLET_BOSS_1_LASER;
	static int MODEL_GAME_BULLET_BOSS_1_SCATTER;
	static int MODEL_GAME_ASTEROID_BIG_1;
	static int MODEL_GAME_ASTEROID_BIG_2;
	static int MODEL_GAME_ASTEROID_BIG_3;
	static int MODEL_GAME_ASTEROID_BIG_4;
	static int MODEL_GAME_ASTEROID_BIG_5;
	static int MODEL_GAME_ASTEROID_MEDIUM_1;
	static int MODEL_GAME_ASTEROID_MEDIUM_2;
	static int MODEL_GAME_ASTEROID_MEDIUM_3;
	static int MODEL_GAME_ASTEROID_MEDIUM_4;
	static int MODEL_GAME_ASTEROID_MEDIUM_5;
	static int MODEL_GAME_ASTEROID_SMALL_1;
	static int MODEL_GAME_ASTEROID_SMALL_2;
	static int MODEL_GAME_ASTEROID_SMALL_3;
	static int MODEL_GAME_ASTEROID_SMALL_4;
	static int MODEL_GAME_ASTEROID_SMALL_5;
	static int MODEL_GAME_TEXT_SCORE;

	/* SPRITES */

	static int SPRITE_GAME_BULLET_FIRST;
	static int SPRITE_GAME_BULLET_PLAYER_MINIGUN_FRONT;
	static int SPRITE_GAME_BULLET_PLAYER_MINIGUN_LEFT;
	static int SPRITE_GAME_BULLET_PLAYER_MINIGUN_RIGHT;
	static int SPRITE_GAME_BULLET_DRONE;
	static int SPRITE_GAME_BULLET_SNIPER;
	static int SPRITE_GAME_BULLET_ROLLER;
	static int SPRITE_GAME_BULLET_VANGUARD;
	static int SPRITE_GAME_BULLET_BOSS_1_LASER_DOWN;
	static int SPRITE_GAME_BULLET_BOSS_1_LASER_LEFT;
	static int SPRITE_GAME_BULLET_BOSS_1_LASER_RIGHT;
	static int SPRITE_GAME_BULLET_BOSS_1_SCATTER;
	static int SPRITE_GAME_BULLET_LAST;
	static int SPRITE_HIGHSCORE_BULLET_FIRST;
	static int SPRITE_HIGHSCORE_BULLET_PLAYER_MINIGUN;
	static int SPRITE_HIGHSCORE_BULLET_LAST;

	CResources();
	~CResources();

	virtual void Init(CTheApp* pApp, CZipManager* pZipManager);

	virtual void Release();
	virtual HRESULT Load() = 0;

	inline bool IsInitialized() { return this->m_bInitialized; }
	inline bool IsResourcesLoaded() { return this->m_bResourcesLoaded; }

	inline bool IsLoadWaitCycle() { return this->m_bIsLoadWaitCycle; }
	inline void SetLoadWaitCycle(bool value) { this->m_bIsLoadWaitCycle = value; }
	inline int GetStepsMax() { return this->m_iMeshStepsMax + this->m_iSpriteStepsMax; }

	LPCTSTR GetUnpackedResourceFilePath(const char* childPath);

	void SetMeshFilePath(const char* childPath);
	void SetSpriteFilePath(const char* childPath);

	/** MESH GETTERS **/

	LPD3DXMESH GetMesh(int index);
	std::vector<D3DMATERIAL9*> GetMaterial(int index);
	std::vector<LPDIRECT3DTEXTURE9> GetTexture(int index);

	/** SPRITE GETTERS **/

	CSprite GetSprite(int index);

protected:

	LPDIRECT3DDEVICE9 m_pDevice;

	CTheApp* m_pApp;
	CZipManager* m_pZipManager;

	int m_iResourcesLoadStepCounter;
	bool m_bInitialized;

	std::string m_sFullResourceFilePath;
	std::wstring m_tempResourceFilePath;

	// LOAD METHODS

	HRESULT LoadGameObject(std::string fileName, int mapKey, int modelType);
	HRESULT LoadGameEnemyObject(std::string fileName, int mapKey, int modelType);

	// AFTER-LOAD METHODS

	void RotatePlayer(LPD3DXMESH mesh);
	void RotateEnemy(LPD3DXMESH mesh);

	void SetMeshData(CXFileContainer xFile, int mapKey, int modelType);
	void SetSpriteData(CSprite sprite, int mapKey);

	D3DMATERIAL9* InitMaterial(D3DMATERIAL9* material, int mapKey, int modelType);
	LPD3DXMESH SetPivotPoint(LPD3DXMESH mesh, int modelType);

	// MAPS

	std::map<int, LPD3DXMESH>						m_MapMesh;
	std::map<int, std::vector<D3DMATERIAL9*>>		m_MapMaterial;
	std::map<int, std::vector<LPDIRECT3DTEXTURE9>>	m_MapTexture;
	std::map <int, CSprite>							m_MapSprite;

	// LOAD CYCLE

	int m_iMeshSteps;
	int m_iSpriteSteps;
	int m_iMeshStepsMax;
	int m_iSpriteStepsMax;

	bool m_bIsLoadWaitCycle;
	bool m_bResourcesLoaded;

private:

	// LOAD METHODS

	CXFileContainer LoadMeshObject(std::string fileName, int mapKey, int modelType);
};
#include "GameSettings.h"

// SOUND VOLUME (0.0f - 1.0f)

float CGameSettings::VOLUME_MUSIC_GAME_OVER = 0.85f;

float CGameSettings::VOLUME_PLAYER_MINIGUN_SHOOT = 0.9f;
float CGameSettings::VOLUME_PLAYER_MINIGUN_TURN = 0.9f;
float CGameSettings::VOLUME_PLAYER_CANNON = 0.93f;
float CGameSettings::VOLUME_PLAYER_BLAST = 0.93f;
float CGameSettings::VOLUME_PLAYER_VELOCITY_AFTERBURN = 0.8f;

float CGameSettings::VOLUME_ENEMY_SHOOT_ROLLER = 1.0f;

float CGameSettings::VOLUME_BOSS_SCATTER = 0.88f;
float CGameSettings::VOLUME_BOSS_LASER = 0.94f;
float CGameSettings::VOLUME_BOSS_CANNON = 0.9f;

float CGameSettings::VOLUME_BOSS_CHAIN_EXPLOSION_MIN = 0.8f;
float CGameSettings::VOLUME_BOSS_CHAIN_EXPLOSION_MAX = 1.0f;

// BACKGROUND SCROLLING

float CGameSettings::SCROLLING_PLAYER_VELOCITY_MAX = 130.0f;

float CGameSettings::SCROLLING_BACKGROUND_TOP_MIN = 0.0f;
float CGameSettings::SCROLLING_BACKGROUND_TOP_MAX = 8.0f;

float CGameSettings::SCROLLING_EXPLOSION_MIN = 1.0f;
float CGameSettings::SCROLLING_EXPLOSION_MAX = 6.0f;

// PLAYER

int CGameSettings::PLAYER_LIVES = 3;
int CGameSettings::PLAYER_HEALTH = 100;
float CGameSettings::PLAYER_WIDTH = 23.0f;
float CGameSettings::PLAYER_HEIGHT = 34.0f;
float CGameSettings::PLAYER_SPEED = 125.0f;
float CGameSettings::PLAYER_MAX_VELOCITY = 1.75f * CGameSettings::PLAYER_SPEED;

int CGameSettings::PLAYER_CANNON_ENERGY_MAX = 200;
int CGameSettings::PLAYER_CANNON_DAMAGE = 75;
float CGameSettings::PLAYER_CANNON_SPEED = 280.0f;
float CGameSettings::PLAYER_CANNON_TIMER = 14.0f;

float CGameSettings::PLAYER_BLAST_ACTIVE_DURATION = 0.8f;
float CGameSettings::PLAYER_BLAST_BEAM_DURATION = 0.05f;
int CGameSettings::PLAYER_BLAST_BEAM_COUNT = 4;

int CGameSettings::PLAYER_BLAST_DAMAGE = 100;
int CGameSettings::PLAYER_BLAST_AMOUNT = 3;

float CGameSettings::PLAYER_SHIP_ENTER_POS_X = 0.0f;
float CGameSettings::PLAYER_SHIP_ENTER_POS_Y = -250.0f;
float CGameSettings::PLAYER_SHIP_START_POS_Y = -105.0f;

// WEAPONS

float CGameSettings::PLAYER_BULLET_WIDTH = 2.0f;
float CGameSettings::PLAYER_BULLET_HEIGHT = 2.0f;

float CGameSettings::ENEMY_DRONE_BULLET_WIDTH = 5.5f;
float CGameSettings::ENEMY_DRONE_BULLET_HEIGHT = 5.5f;
float CGameSettings::ENEMY_DRONE_BULLET_SPEED = 400.0f;
int CGameSettings::ENEMY_DRONE_BULLET_DAMAGE = 4;
int CGameSettings::ENEMY_DRONE_SHIP_DAMAGE = 50;

float CGameSettings::ENEMY_SNIPER_BULLET_WIDTH = 2.8f;
float CGameSettings::ENEMY_SNIPER_BULLET_HEIGHT = 10.0f;
float CGameSettings::ENEMY_SNIPER_BULLET_SPEED = 450.0f;
int CGameSettings::ENEMY_SNIPER_BULLET_DAMAGE = 6;
int CGameSettings::ENEMY_SNIPER_SHIP_DAMAGE = 60;

float CGameSettings::ENEMY_ROLLER_BULLET_WIDTH = 2.5f;
float CGameSettings::ENEMY_ROLLER_BULLET_HEIGHT = 2.5f;
float CGameSettings::ENEMY_ROLLER_BULLET_SPEED = 120.0f;
int CGameSettings::ENEMY_ROLLER_BULLET_DAMAGE = 3;
int CGameSettings::ENEMY_ROLLER_SHIP_DAMAGE = 70;

float CGameSettings::ENEMY_GUARD_BULLET_WIDTH = 3.5f;
float CGameSettings::ENEMY_GUARD_BULLET_HEIGHT = 3.5f;
float CGameSettings::ENEMY_GUARD_BULLET_SPEED = 250.0f;
int CGameSettings::ENEMY_GUARD_BULLET_DAMAGE = 6;
int CGameSettings::ENEMY_GUARD_SHIP_DAMAGE = 80;

float CGameSettings::ENEMY_BOSS_LASER_BULLET_WIDTH = 5.0f;
float CGameSettings::ENEMY_BOSS_LASER_BULLET_HEIGHT = 5.0f;
float CGameSettings::ENEMY_BOSS_LASER_BULLET_SPEED = 230.0f;
int CGameSettings::ENEMY_BOSS_LASER_BULLET_DAMAGE = 3;

float CGameSettings::ENEMY_BOSS_SCATTER_BULLET_WIDTH = 2.5f;
float CGameSettings::ENEMY_BOSS_SCATTER_BULLET_HEIGHT = 2.5f;
float CGameSettings::ENEMY_BOSS_SCATTER_BULLET_SPEED = 180.0f;
int CGameSettings::ENEMY_BOSS_SCATTER_BULLET_DAMAGE = 5;

float CGameSettings::ENEMY_BOSS_CANNON_BULLET_SPEED = 220.0f;
int CGameSettings::ENEMY_BOSS_CANNON_BULLET_DAMAGE = 200;

// ENEMIES

int CGameSettings::ENEMY_DRONE_HEALTH = 15;
float CGameSettings::ENEMY_DRONE_WIDTH = 21.0f;
float CGameSettings::ENEMY_DRONE_HEIGHT = 28.0f;
float CGameSettings::ENEMY_DRONE_LAUNCH_SPEED = 95.0f;
float CGameSettings::ENEMY_DRONE_LAUNCH_SHOOT_TIME = 0.2f;
float CGameSettings::ENEMY_DRONE_STRIKE_SPEED = 260.0f;
float CGameSettings::ENEMY_DRONE_STRIKE_SHOOT_TIME = 0.35f;
float CGameSettings::ENEMY_DRONE_ENTER_DURATION = 0.005625f;
float CGameSettings::ENEMY_DRONE_FLEE_DURATION = 0.67f * CGameSettings::ENEMY_DRONE_ENTER_DURATION;

int CGameSettings::ENEMY_SNIPER_HEALTH = 25;
float CGameSettings::ENEMY_SNIPER_WIDTH = 26.0f;
float CGameSettings::ENEMY_SNIPER_HEIGHT = 35.0f;
float CGameSettings::ENEMY_SNIPER_LAUNCH_SPEED = 90.0f;
float CGameSettings::ENEMY_SNIPER_LAUNCH_SHOOT_TIME = 0.25f;
float CGameSettings::ENEMY_SNIPER_STRIKE_SPEED = 200.0f;
float CGameSettings::ENEMY_SNIPER_STRIKE_SHOOT_TIME = 0.45f;
float CGameSettings::ENEMY_SNIPER_ENTER_DURATION = 0.00525f;
float CGameSettings::ENEMY_SNIPER_FLEE_DURATION = 0.67f * CGameSettings::ENEMY_SNIPER_ENTER_DURATION;

int CGameSettings::ENEMY_ROLLER_HEALTH = 50;
float CGameSettings::ENEMY_ROLLER_WIDTH = 50.0f;
float CGameSettings::ENEMY_ROLLER_HEIGHT = 50.0f;
float CGameSettings::ENEMY_ROLLER_LAUNCH_SPEED = 70.0f;
float CGameSettings::ENEMY_ROLLER_LAUNCH_SHOOT_TIME = 0.4f;
float CGameSettings::ENEMY_ROLLER_STRIKE_SPEED = 150.0f;
float CGameSettings::ENEMY_ROLLER_STRIKE_SHOOT_TIME = 0.8f;
float CGameSettings::ENEMY_ROLLER_ENTER_DURATION = 0.0065625f;
float CGameSettings::ENEMY_ROLLER_FLEE_DURATION = 0.67f * CGameSettings::ENEMY_ROLLER_ENTER_DURATION;

int CGameSettings::ENEMY_GUARD_HEALTH = 70;
float CGameSettings::ENEMY_GUARD_WIDTH = 10.0f;
float CGameSettings::ENEMY_GUARD_HEIGHT = 10.0f;
float CGameSettings::ENEMY_GUARD_LAUNCH_SPEED = 60.0f;
float CGameSettings::ENEMY_GUARD_LAUNCH_SHOOT_TIME = 0.4f;
float CGameSettings::ENEMY_GUARD_STRIKE_SPEED = 120.0f;
float CGameSettings::ENEMY_GUARD_STRIKE_SHOOT_TIME = 1.2f;
float CGameSettings::ENEMY_GUARD_ENTER_DURATION = 0.0065625f;
float CGameSettings::ENEMY_GUARD_FLEE_DURATION = 0.67f * CGameSettings::ENEMY_GUARD_ENTER_DURATION;

float CGameSettings::ENEMY_STRIKE_SPEED_MULTIPLIER_MIN = 0.95f;
float CGameSettings::ENEMY_STRIKE_SPEED_MULTIPLIER_MAX = 1.0f;

// BOSSES

float CGameSettings::BOSS_WARNING_START_TIME = 0.05f;
float CGameSettings::BOSS_WARNING_END_TIME = 0.05f;

float CGameSettings::ENEMY_BOSS_FRAME_WIDTH = 85.0f;
float CGameSettings::ENEMY_BOSS_FRAME_HEIGHT = 123.0f;
int CGameSettings::ENEMY_BOSS_FRAME_HEALTH = 2000;
float CGameSettings::ENEMY_BOSS_FRAME_SPEED = 70.0f;
float CGameSettings::ENEMY_BOSS_FRAME_SHOOT_TIME = 1.0f;

float CGameSettings::ENEMY_BOSS_LASER_WIDTH = 60.0f;
float CGameSettings::ENEMY_BOSS_LASER_HEIGHT = 60.0f;
int CGameSettings::ENEMY_BOSS_LASER_HEALTH = 600;

float CGameSettings::ENEMY_BOSS_SCATTER_WIDTH = 25.0f;
float CGameSettings::ENEMY_BOSS_SCATTER_HEIGHT = 25.0f;
int CGameSettings::ENEMY_BOSS_SCATTER_HEALTH = 400;
float CGameSettings::ENEMY_BOSS_SCATTER_SPEED = 100.0f;
float CGameSettings::ENEMY_BOSS_SCATTER_SHOOT_TIME = 4.5f;
int CGameSettings::ENEMY_BOSS_SCATTER_SHOOT_AMOUNT_MAX = 40;

float CGameSettings::ENEMY_BOSS_CANNON_SHOOT_TIME = 4.0f;

// OBSTACLES

float CGameSettings::BIG_ASTEROID_WIDTH = 74.0f;
float CGameSettings::BIG_ASTEROID_HEIGHT = 45.0f;

float CGameSettings::MEDIUM_ASTEROID_WIDTH = 50.0f;
float CGameSettings::MEDIUM_ASTEROID_HEIGHT = 36.0f;

float CGameSettings::SMALL_ASTEROID_WIDTH = 20.0f;
float CGameSettings::SMALL_ASTEROID_HEIGHT = 15.0f;

float CGameSettings::OSTACLE_SPEED_DEPTH_1 = 35.0f;
float CGameSettings::OSTACLE_SPEED_DEPTH_2 = 15.0f;
float CGameSettings::OSTACLE_SPEED_DEPTH_3 = 11.0f;
float CGameSettings::OSTACLE_SPEED_DEPTH_4 = 7.0f;
float CGameSettings::OSTACLE_SPEED_DEPTH_5 = 3.0f;

// SHIPS COMMON VALUES

float CGameSettings::SHIP_AFTERBURN_FLICKER_SHOW_DURATION = 0.015f;
float CGameSettings::SHIP_AFTERBURN_FLICKER_HIDE_DURATION = 0.025f;

// UI ELEMENTS

float CGameSettings::UI_NUMBER_WIDTH = 7.0f;
float CGameSettings::UI_NUMBER_HEIGHT = 10.0f;

int CGameSettings::UI_PLAYER_LIVES_BASE_POS_X = 29;
int CGameSettings::UI_PLAYER_LIVES_BASE_POS_Y = 29;
int CGameSettings::UI_PLAYER_LIVES_NUMBER_POS_X = CGameSettings::UI_PLAYER_LIVES_BASE_POS_X + 66;
int CGameSettings::UI_PLAYER_LIVES_NUMBER_POS_Y = CGameSettings::UI_PLAYER_LIVES_BASE_POS_Y + 13;

int CGameSettings::UI_PLAYER_BLAST_BASE_POS_X = 661;
int CGameSettings::UI_PLAYER_BLAST_BASE_POS_Y = 29;
int CGameSettings::UI_PLAYER_BLAST_NUMBER_POS_X = CGameSettings::UI_PLAYER_BLAST_BASE_POS_X + 66;
int CGameSettings::UI_PLAYER_BLAST_NUMBER_POS_Y = CGameSettings::UI_PLAYER_BLAST_BASE_POS_Y + 13;

int CGameSettings::UI_PLAYER_HEALTH_BAR_POS_X = 148;
int CGameSettings::UI_PLAYER_HEALTH_BAR_POS_Y = 29;
int CGameSettings::UI_PLAYER_HEALTH_FILL_POS_X = CGameSettings::UI_PLAYER_HEALTH_BAR_POS_X + 5;
int CGameSettings::UI_PLAYER_HEALTH_FILL_POS_Y = CGameSettings::UI_PLAYER_HEALTH_BAR_POS_Y + 3;

int CGameSettings::UI_PLAYER_CANNON_BAR_POS_X = 148;
int CGameSettings::UI_PLAYER_CANNON_BAR_POS_Y = 57;
int CGameSettings::UI_PLAYER_CANNON_FILL_POS_X = CGameSettings::UI_PLAYER_CANNON_BAR_POS_X + 5;
int CGameSettings::UI_PLAYER_CANNON_FILL_POS_Y = CGameSettings::UI_PLAYER_CANNON_BAR_POS_Y + 3;

float CGameSettings::UI_LEVEL_TITLE_APPEAR_DURATION = 0.5f;
float CGameSettings::UI_LEVEL_TITLE_STAY_DURATION = 0.5f;
float CGameSettings::UI_LEVEL_TITLE_DISAPPEAR_DURATION = 0.35f;

// EXTRA VISUAL EFFECTS

bool CGameSettings::EFFECT_PLAYER_BLAST_LIGHT = false;

float CGameSettings::GetObstacleSpeed(int depth)
{
	switch (depth)
	{
	case 2:
		return CGameSettings::OSTACLE_SPEED_DEPTH_2;
	case 3:
		return CGameSettings::OSTACLE_SPEED_DEPTH_3;
	case 4:
		return CGameSettings::OSTACLE_SPEED_DEPTH_4;
	case 5:
		return CGameSettings::OSTACLE_SPEED_DEPTH_5;
	default:
		return CGameSettings::OSTACLE_SPEED_DEPTH_1;
	}
}

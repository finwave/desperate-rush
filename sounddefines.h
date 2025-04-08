/**
 * Holds all the sound defines.
 */

#pragma once

#include <iostream>
#include <tchar.h>

// NUM_WAVES defines total number of wave files to load
#define NUM_WAVES							64
#define FIRST_DUPLICATE_SOUND				17

// single sound

#define SOUND_MENU_START					0
#define SOUND_GAME_OVER						1
#define SOUND_GAIN_LIFE						2
#define SOUND_BOSS_INTRO_WARNING			3
#define SOUND_PLAYER_ENTER					4
#define SOUND_PLAYER_ENTER_AFTERBURN		5
#define SOUND_PLAYER_LEAVE_AFTERBURN		6
#define SOUND_PLAYER_MINIGUN_TURN_FRONT		7
#define SOUND_PLAYER_MINIGUN_TURN_DIAGONAL	8
#define SOUND_SHOOT_PLAYER_BLAST			9
#define SOUND_SHOOT_PLAYER_CANNON_CHARGE	10
#define SOUND_SHOOT_PLAYER_CANNON_BEAM		11
#define SOUND_SHOOT_BOSS_1_CANNON_CHARGE	12
#define SOUND_SHOOT_BOSS_1_CANNON_SHOOT		13
#define SOUND_EXPLOSION_PLAYER				14
#define SOUND_EXPLOSION_BOSS_PART			15
#define SOUND_EXPLOSION_BOSS_BIG			16

// duplicate sound

#define SOUND_MENU_SELECT					17
#define SOUND_MENU_OPTION					18
#define SOUND_MENU_BACK						19
#define SOUND_ENEMY_ENTER_AFTERBURN			20
#define SOUND_ENEMY_LEAVE_AFTERBURN			21
#define SOUND_ENEMY_STRIKE_AFTERBURN_1		22
#define SOUND_ENEMY_STRIKE_AFTERBURN_2		23
#define SOUND_ENEMY_STRIKE_AFTERBURN_3		24
#define SOUND_ENEMY_STRIKE_AFTERBURN_4		25
#define SOUND_SHOOT_PLAYER_MINIGUN_1		26
#define SOUND_SHOOT_PLAYER_MINIGUN_2		27
#define SOUND_SHOOT_DRONE_1					28
#define SOUND_SHOOT_DRONE_2					29
#define SOUND_SHOOT_SNIPER_1				30
#define SOUND_SHOOT_SNIPER_2				31
#define SOUND_SHOOT_ROLLER_1				32
#define SOUND_SHOOT_ROLLER_2				33
#define SOUND_SHOOT_ROLLER_3				34
#define SOUND_SHOOT_ROLLER_4				35
#define SOUND_SHOOT_BOSS_1_LASER_SMALL_1	36
#define SOUND_SHOOT_BOSS_1_LASER_SMALL_2	37
#define SOUND_SHOOT_BOSS_1_LASER_SMALL_3	38
#define SOUND_SHOOT_BOSS_1_LASER_SMALL_4	39
#define SOUND_SHOOT_BOSS_1_SCATTER_1		40
#define SOUND_SHOOT_BOSS_1_SCATTER_2		41
#define SOUND_SHOOT_BOSS_1_SCATTER_3		42
#define SOUND_SHOOT_BOSS_1_SCATTER_4		43
#define SOUND_HIT_PLAYER_1					44
#define SOUND_HIT_PLAYER_2					45
#define SOUND_HIT_ENEMY_1					46
#define SOUND_HIT_ENEMY_2					47
#define SOUND_HIT_BOSS_1					48
#define SOUND_HIT_BOSS_2					49
#define SOUND_EXPLOSION_DRONE_1				50
#define SOUND_EXPLOSION_DRONE_2				51
#define SOUND_EXPLOSION_DRONE_3				52
#define SOUND_EXPLOSION_DRONE_4				53
#define SOUND_EXPLOSION_SNIPER_1			54
#define SOUND_EXPLOSION_SNIPER_2			55
#define SOUND_EXPLOSION_SNIPER_3			56
#define SOUND_EXPLOSION_SNIPER_4			57
#define SOUND_EXPLOSION_ROLLER_1			58
#define SOUND_EXPLOSION_ROLLER_2			59
#define SOUND_EXPLOSION_ROLLER_3			60
#define SOUND_EXPLOSION_ROLLER_4			61
#define SOUND_EXPLOSION_BOSS_CHAIN_1		62
#define SOUND_EXPLOSION_BOSS_CHAIN_2		63

// define sound filenames
//const std::string waveFilenames[NUM_WAVES][MAX_PATH] =
const std::string waveFilenames[NUM_WAVES] =
{
	// single sound

	"sound/menu_start.wav",
	"sound/game_over.wav",
	"sound/gain_life.wav",
	"sound/boss_warning.wav",
	"sound/player_enter.wav",
	"sound/player_enter_afterburn.wav",
	"sound/player_leave_afterburn.wav",
	"sound/player_minigun_turn_front.wav",
	"sound/player_minigun_turn_diagonal.wav",
	"sound/shoot_player_blast.wav",
	"sound/shoot_player_cannon_charge.wav",
	"sound/shoot_player_cannon_beam.wav",
	"sound/shoot_boss_1_cannon_charge.wav",
	"sound/shoot_boss_1_cannon_shoot.wav",
	"sound/explosion_player.wav",
	"sound/explosion_boss_part.wav",
	"sound/explosion_boss_big.wav",

	// duplicate sound

	"sound/menu_select.wav",
	"sound/menu_option.wav",
	"sound/menu_back.wav",
	"sound/enemy_enter_afterburn.wav",
	"sound/enemy_leave_afterburn.wav",
	"sound/enemy_strike_afterburn_1.wav",
	"sound/enemy_strike_afterburn_2.wav",
	"sound/enemy_strike_afterburn_3.wav",
	"sound/enemy_strike_afterburn_4.wav",
	"sound/shoot_player_minigun_1.wav",
	"sound/shoot_player_minigun_2.wav",
	"sound/shoot_drone_1.wav",
	"sound/shoot_drone_2.wav",
	"sound/shoot_sniper_1.wav",
	"sound/shoot_sniper_2.wav",
	"sound/shoot_roller_1.wav",
	"sound/shoot_roller_2.wav",
	"sound/shoot_roller_3.wav",
	"sound/shoot_roller_4.wav",
	"sound/shoot_boss_1_laser_small_1.wav",
	"sound/shoot_boss_1_laser_small_2.wav",
	"sound/shoot_boss_1_laser_small_3.wav",
	"sound/shoot_boss_1_laser_small_4.wav",
	"sound/shoot_boss_1_scatter_1.wav",
	"sound/shoot_boss_1_scatter_2.wav",
	"sound/shoot_boss_1_scatter_3.wav",
	"sound/shoot_boss_1_scatter_4.wav",
	"sound/hit_player_1.wav",
	"sound/hit_player_2.wav",
	"sound/hit_enemy_1.wav",
	"sound/hit_enemy_2.wav",
	"sound/hit_boss_1.wav",
	"sound/hit_boss_2.wav",
	"sound/explosion_drone_1.wav",
	"sound/explosion_drone_2.wav",
	"sound/explosion_drone_3.wav",
	"sound/explosion_drone_4.wav",
	"sound/explosion_sniper_1.wav",
	"sound/explosion_sniper_2.wav",
	"sound/explosion_sniper_3.wav",
	"sound/explosion_sniper_4.wav",
	"sound/explosion_roller_1.wav",
	"sound/explosion_roller_2.wav",
	"sound/explosion_roller_3.wav",
	"sound/explosion_roller_4.wav",
	"sound/explosion_boss_chain_1.wav",
	"sound/explosion_boss_chain_2.wav"
};
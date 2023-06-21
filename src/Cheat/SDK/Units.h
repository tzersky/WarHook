#pragma once
#include "../Includes.h"
#include "../Utils/Math.h"
#include <array>
#include <unordered_set>
#include <string>

class Player
{
	enum GuiState : std::uint8_t
	{
		NONE = 0,
		MENU = 1,
		ALIVE = 2,
		DEAD = 3,
		SPEC = 6,
		LIMBO = 8,
		LOADING = 10
	};

public:
	char pad_0000[176]; //0x0000
	char Name[32]; //0x00B0
	char pad_00D0[1064]; //0x00D0
	uint8_t GuiState; //0x04F8
	char pad_04F9[511]; //0x04F9
	class Unit* OwnedUnit; //0x06F8


	bool IsAlive() const noexcept
	{
		return GuiState == GuiState::ALIVE;
	}

	bool IsDead() const noexcept
	{
		return GuiState == GuiState::DEAD;
	}

	bool IsinHangar() const noexcept
	{
		return GuiState == GuiState::MENU;
	}
};


class Unit
{
	enum UnitState : std::uint8_t {
		ALIVE = 0,
		DEAD = 2,
	};

public:
	char pad_0000[480]; //0x0000
	Vector3 BBMin; //0x01E0
	Vector3 BBMax; //0x01EC
	char pad_01F8[688]; //0x01F8
	char* UnitName; //0x04A8
	char pad_04B0[688]; //0x04B0
	uint8_t VisualReload; //0x0760
	char pad_0761[539]; //0x0761
	Matrix3x3 RotationMatrix; //0x097C
	Vector3 Position; //0x09A0
	char pad_09AC[1496]; //0x09AC
	float InvulTimer; //0x0F84
	char pad_0F88[32]; //0x0F88
	bool Invulnerable; //0x0FA8
	char pad_0FA9[223]; //0x0FA9
	uint8_t UnitState; //0x1088
	char pad_1089[15]; //0x1089
	class Player* PlayerInfo; //0x1098
	char pad_10A0[64]; //0x10A0
	uint8_t TeamNum; //0x10E0
	char pad_10E1[15]; //0x10E1
	class Info* UnitInfo; //0x10F0



	bool IsAlive() const noexcept
	{
		return UnitState == UnitState::ALIVE;
	}

	bool IsDead() const noexcept
	{
		return UnitState == UnitState::DEAD;
	}
};

class Info
{
public:
	char* unitName; //0x0000
	char* modelName; //0x0008
	char* modelPath; //0x0010
	char* FullName; //0x0018
	char* ShortName; //0x0020
	char pad_0028[8]; //0x0028
	char* unitType; //0x0030
	char pad_0038[428]; //0x0038
	float ZoomMulti; //0x01E4
	float AlternateMulti; //0x01E8
	char pad_01EC[16]; //0x01EC
	float ShadowMulti; //0x01FC


	bool isPlane() {
		static const std::unordered_set<std::string> planeTypes = { "exp_bomber", "exp_assault", "exp_fighter" };
		return planeTypes.find(unitType) != planeTypes.end();
	}

	bool isDummy() {
		static const std::unordered_set<std::string> dummyTypes = { "exp_fortification", "exp_structure", "exp_aaa", "dummy_plane", "exp_bridge", "exp_zero", "exp_ca_ship"};
		return dummyTypes.find(unitType) != dummyTypes.end();
	}
};

class EntList {
public:
	Player* players[64];
};

class Units {
public:
	std::array<Unit*, 500U> units;
};

class UnitList {
public:
	Units* unitList;
};
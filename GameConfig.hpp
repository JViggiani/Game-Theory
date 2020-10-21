#pragma once

namespace Config
{

	struct GameConfig
	{
		GameConfig();
		~GameConfig() = default;

		int _bothCooperate;
		int _bothCheat;
		int _cooperate;
		int _cheat;

		unsigned int _mistakeChance;
	};

}
#pragma once

namespace Config
{

	struct RewardConfig
	{
		RewardConfig() = default;
		~RewardConfig() = default;

		int _bothCooperate;
		int _bothCheat;
		int _cooperate;
		int _cheat;
	};

}
#pragma once

#include <mutex>
#include <iostream>

#include "Player.hpp"
#include "RoundResults.hpp"
#include "Decision.hpp"
#include "RewardConfig.hpp"

//JOSH should this be a singleton? consider..
class Machine
{

    /**
     * The Machine is a thread safe Singleton which returns the results of player decisions
     */
private:
    static Machine* pinstance_;
    static std::mutex mutex_;

protected:
    Machine();

    ~Machine() = default;

public:
    /**
     * Singletons should not be cloneable.
     */
    Machine(Machine& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Machine&) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. It gaurantees that only one instance is ever made.
     */
    static Machine* GetInstance();

    // Returns the results of player decisions
    //JOSH consider replacing input players with just decisions? hmm..
    RoundResults processRound(std::shared_ptr<Player> aPlayer1, std::shared_ptr<Player> aPlayer2);

private:
    //This config should never change during execution of the program. It should only be read once at startup
    RewardConfig _rewardConfig;
};


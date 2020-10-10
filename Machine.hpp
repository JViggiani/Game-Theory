#pragma once

#include <mutex>

#include "Player.hpp"
#include "RoundResults.hpp"

class Machine
{

    /**
     * The Machine is a thread safe Singleton which returns the results of player decisions
     */
private:
    static Machine* pinstance_;
    static std::mutex mutex_;

protected:
    Machine() = default;

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
    RoundResults processEvent(std::shared_ptr<Player> aPlayer1, std::shared_ptr<Player> aPlayer2)
    {
        RoundResults aRoundResults;
        return aRoundResults;
    }
};


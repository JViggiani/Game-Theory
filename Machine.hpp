#pragma once

#include <mutex>
#include <iostream>

#include "Player.hpp"
#include "RoundResults.hpp"
#include "eDecisionType.hpp"
#include "GameConfig.hpp"

//JOSH should this be Core or Implementation? Consider...
namespace Core
{

    //! The Machine is a thread safe Singleton which returns the results of player decisions
    class Machine
    {
    public:
        /// Constructors and Destructors ///

        //! Singletons should not be cloneable.
        Machine(Machine& other) = delete;

        //! Deleted move constructor
        Machine(Machine&&) = delete;

        /// Operators ///

        //! Singletons should not be assignable.
        void operator=(const Machine&) = delete;

        //! Singletons should not be moveable.
        Machine& operator=(Machine&&) = delete;

        /// Functions ///

        //! This is the static method that controls the access to the singleton instance. It gaurantees that only one instance is ever made.
        static Machine* GetInstance();

        // Returns the results of player decisions based upon input game results so far
        Data::RoundResults processRound(const std::shared_ptr<Player>& aPlayer1, const std::shared_ptr<Player>& aPlayer2, const Data::GameResults& aGameResults);

    protected:
        /// Constructors and Destructors ///

        //! Can only be constructed from GetInstance()
        Machine() = default;

        //! Cannot be destroyed from outside of class
        ~Machine() = default;

    private:
        //This config should never change during execution of the program. It should only be read once at startup
        Config::GameConfig _gameConfig;

        static Machine* pinstance_;
        static std::mutex mutex_;
    };

}
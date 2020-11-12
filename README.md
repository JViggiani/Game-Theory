# Game-Theory

*Why do friends become enemies, even in peacetime? Why do enemies become friends, even in wartime?*

In World War I, soldiers from enemy lines, against explicit orders of their officers, crossed no man's land and gathered to bury their dead, exchange gifts and play games. Enemies became friends. 

After World War II, the world's emergent allied superpowers - the United States and the Soviet Union - stood over the rubble. The next fifty years would be defined by espionage, proxy wars and the ever-looming threat of nuclear armageddon between the two powers and their spheres. Friends became enemies. 

This project aims to use game theory principles to explain how trust can evolve in social ecosystems, and how distrust can fester. 

# The Premise

Two "players" face a "machine". In front of them is a "decision": cheat or co-operate. Depending on the combination of choices, rewards (or penalties!) are distributed to both players. 

Each player has a "personality", which will determine how they will make their decision. 

The players play this in "rounds" as a "game". This is a repeated set of decisions made by both players, and players may make decisions based upon the last set of decisions. It is possible for a player to make a mistake and make a decision which they did not intend to make. In reality, this represents miscommunications and blunders. At the end, each player is given the sum total of their rewards. 

There are a pool of players with various personalities who each play against each other player in a set of games. This is the tournament. The tourement happens in a cycle of three steps: play, eliminate, evolve. After everyone has played against everyone, the tournament is allowed to evolve. The bottom players with the least rewards are eliminated and the top players are allowed to reproduce.

This process is repeated a number of times, and when the number is reached, the resulting player distribution is printed to the log file. 

The user has control over configuration aspects of the tournament, such as mistake chance in a game, number of rounds in a game, number of evolutions in the tournament, and number of eliminations in an iteration. Which "unsuccessful" behaviours disappear, and which ones are allowed to perpetuate? How does this change with different configurations?

# Installing

This was created with Visual Studio 2019. See: https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2019 for cloning instructions. 

# The Personalities

Personality | Description
------------ | -------------
Cheater | Always cheats.
Cooperator | Always cooperates.
Copycat | Always does what the other player did last round.
Vengeful | Cooperates by default. If the other player cheats, even once, starts always cheating. 
Copykitten | Behaves like copycat, but only cheats if the other player cheats twice in a row or more. 
MeanCopycat | Behaves like copycat, but cheats on the last round. 
Random | 50% likely to cheat, 50% likely to cooperate. 
WinStayLoseSwitch | Cooperates by default. Switches decision based on whether it "won" last round (ie got more or equal coins to the other player). If it won, it sticks with the same decision. Otherwise, it switches to the opposite decision.

# The Config

The user has control over many aspects of the tournament. This can be found in TournamentConfig.ini

Logging config:

Item | Description
------------ | -------------
Severity | Trace levels of 0-5, displaying varying amounts of information. 0 - trace, 1 - debug, 2 - info, 3 - warning, 4 - error, 5 - fatal. The user should be aware that a lower logging level significantly slows down the program. 
LogFileName | The name of the log file to write to.
LogFileDirectory | The directory to write the log file to.

Tournament config:

Item | Description
------------ | -------------
Evolutions | The number of tournament cycles to play, evolve and eliminate. 
Rounds | The number of decisions made in a game by both players. 
EliminationEvolutions | The number of players to both evolve and eliminate. This is the same to maintain a stable population.

Player config:

This is simply the initial list of players with different types of personality. It will evolve over time. 

Game config:

Item | Description
------------ | -------------
BothCheat | The reward given to players if they both cheat.
BothCooperate | The reward given to players if they both cooperate.
Cooperate | The reward given to the player who cooperates while the other player cheated. 
Cheat | The reward given to the player who cheats while the other player cooperated. 
MistakeChance | The percentage likelyhood that a player will make a mistake on any given decision. 

# The Findings 

Game theory shows us that we need three things to evolve trust:

1. Repeat interactions: You need knowledge of a possible future repeat interaction before trust can evolve. Cooperative personalities reproduce more when the number of rounds in a game is high. 
2. Possible win-wins: You have to be playing a "non-zero-sum" game. Cooperative personalities reproduce more when the BothCooperate reward is sufficient. 
3. Low miscommunication: If the level of miscommunication between players is too high, trust breaks down. When there is a little bit of miscommunication present, the personalities who assume malice, like Vengeful and Copycat, perform worse than those who give a second chance, like Copykitten. 

The evolution of mistrust or trust is defined entirely by the game itself. The environment can act against the evolution of trust, and no one player has the power to change the game. We are products of our environment, and the results are highly deterministic. 

However, we are each other's environment, and in reality individuals often do have the power to change the rules of the game. Do what you can to evolve trust in your social environment: build lasting relationships, find win-wins and communicate clearly. 

# Further Reading

* https://en.wikipedia.org/wiki/The_Evolution_of_Cooperation
* https://www.scientificamerican.com/article/game-theory-calls-cooperation-into-question1/


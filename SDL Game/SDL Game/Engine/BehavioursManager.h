#pragma once

#include <vector>

class Behaviour;

class BehavioursManager
{
public:
	static void update();
	static void subscribeBehaviour(Behaviour* behaviour);
	static void unsubscribeBehaviour(Behaviour* behaviour);

private:
	BehavioursManager();
	static std::vector<Behaviour*> behaviours;
};


#pragma once

#include "Time.h"
#include "Random.h"

#include <notcurses/notcurses.h>

struct Raindrop 
{
    float x;
    float y;
    float speed;
};

struct SimSpec
{
	int speed;
	int rainDensity;
	int speedRange;
	bool showDebug = 0;
	std::string dropChars = "|:.";
	int targetFrameTime;
};

class Simulation
{
	public:
		Simulation(SimSpec s);
		~Simulation();

		void run();
		int getDropCount();
		char getDropChar(const Raindrop &drop);
		std::tuple<int,int,int> getDropColor(const Raindrop &drop);

	private:
		SimSpec spec;
		int refScreenSurface = 80 * 25;
		bool running;
		Random rng;

		notcurses *nc = nullptr;
		ncplane *plane = nullptr;
		unsigned int width, height;

		std::vector<Raindrop> drops;

		void handleEvents();
		void update(Timestep dt);

		void render(Timestep dt);
		void renderRain(Timestep dt);
		void renderText(Timestep dt);

		void initNC();
		void initSim();
};

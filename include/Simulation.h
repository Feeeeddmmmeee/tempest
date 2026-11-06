#pragma once

struct SimSpec
{
	int speed;
	int numDrops;
};

class Simulation
{
	public:
		Simulation(SimSpec spec);
		void run();

	private:
		SimSpec spec;
};

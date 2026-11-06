#include "Simulation.h"
#include "Utils.h"

#include <notcurses/notcurses.h>

Simulation::Simulation(SimSpec spec) : spec(spec)
{
	TEMPEST_LOG("Initializing the simulation with the following settings:");
	TEMPEST_LOG("\tSpeed: "<<spec.speed);
	TEMPEST_LOG("\tDrop count: "<<spec.numDrops);
}

void Simulation::run()
{

}

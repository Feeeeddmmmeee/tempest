/*
	   ⠀⠀⠀⠀⠀⠀⣀⡤⠖⠒⠦⢀⠀⠀⠀⠀⠀⠀
	⠀⠀⠀⠀⢀⡴⣲⠶⠞⠅⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀
	⠀⢀⠴⠊⠁⠛⠇⠀⠀⠀⠀⠀⠀⠀⠀⠸⠒⠒⠦⡀⠀
	⣰⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⡄
	⢻⠀⠐⠀⠀⣀⡀⠁⠂⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⢀⠇
	⠀⠙⠒⠒⢴⡻⣿⣤⡄⢵⡶⣶⢠⣀⣀⣴⠷⠾⠞⠋⠀
	⠀⠀/⠀⠀⠙⠛⠋⠀/⠀⠙⠛⠛⠛⠋/⠀⠀⠀⠀⠀
	    /      /  /

	 /ᐠ - ˕ -マ ᶻ 𝗓 𐰁

   Made with <3 by Feeeeddmmmeee

*/

#include "InputParser.h"
#include "Simulation.h"

#include <cstdlib>
#include <iostream>

#ifndef TEMPEST_VERSION
#define TEMPEST_VERSION "unknown"
#endif

void usage(const char *prog)
{
	std::cout
		<<prog<<" - Terminal rain simulator\n\n"
		<<"USAGE:\n"
		<<"\t"<<prog<<" [OPTIONS]\n\n"
		<<"OPTIONS:\n"
		<<"\t-h, --help      Display help information\n"
		<<"\t-v, --version   Display version information\n";
}

void version(const char *prog)
{
	std::cout<<prog<<" "<<TEMPEST_VERSION<<std::endl;
}

int main(int argc, char *argv[])
{
	InputParser parser(argc, argv);
	std::string raw;
	SimSpec spec;

	if(parser.has("--help") || parser.has("-h"))
	{
		usage(argv[0]);
		return EXIT_SUCCESS;
	}

	if(parser.has("--version") || parser.has("-v"))
	{
		version(argv[0]);
		return EXIT_SUCCESS;
	}

	raw = parser.getOr("100", "--speed", "-s");
	try { spec.speed = std::stoi(raw); }
	catch (...) 
	{
		std::cerr<<"Failed to parse value given to --speed: "<<raw<<", it must be a number!"<<std::endl;
		return EXIT_FAILURE;
	}

	raw = parser.getOr("100", "--drops", "-d");
	try { spec.numDrops = std::stoi(raw); }
	catch (...) 
	{
		std::cerr<<"Failed to parse value given to --drops: "<<raw<<", it must be a number!"<<std::endl;
		return EXIT_FAILURE;
	}

	Simulation sim(spec);
	sim.run();

	return EXIT_SUCCESS;
}

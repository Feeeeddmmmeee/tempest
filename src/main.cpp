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
		<<"A thunderstorm simulation in your terminal!\n\n"
		<<"Usage:\n"
		<<"  "<<prog<<" [options]\n\n"
		<<"Options:\n"
		<<"  -h, --help                  Display help information\n"
		<<"  -v, --version               Display version information\n"
		<<"  -t, --debug                 Render debug information (press d to toggle)\n"
		<<"  -d, --drops <density>       Controls how strong the rain will be\n"
		<<"  -s, --speed <value>         Sets the average raindrop speed\n"
		<<"  -r, --range <value>         Controls how much drops can deviate from the average speed\n"
		<<"  -c, --chars <string>        Specifies the characters to be used for raindrops\n"
		<<"  -f, --frame-delay <ms>   Controls the target amount of ms between simulation steps/frames\n"
		;
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

	if(parser.has("--debug") || parser.has("-t"))
	{
		spec.showDebug = 1;
	}

	raw = parser.getOr("70", "--speed", "-s");
	try { spec.speed = std::stoi(raw); }
	catch (...) 
	{
		std::cerr<<"Failed to parse value given to --speed: "<<raw<<", it must be a number!"<<std::endl;
		return EXIT_FAILURE;
	}

	raw = parser.getOr("100", "--drops", "-d");
	try { spec.rainDensity = std::stoi(raw); }
	catch (...) 
	{
		std::cerr<<"Failed to parse value given to --drops: "<<raw<<", it must be a number!"<<std::endl;
		return EXIT_FAILURE;
	}

	raw = parser.getOr("30", "--range", "-r");
	try { spec.speedRange = std::stoi(raw); }
	catch (...) 
	{
		std::cerr<<"Failed to parse value given to --range: "<<raw<<", it must be a number!"<<std::endl;
		return EXIT_FAILURE;
	}

	raw = parser.getOr("15", "--frame-delay", "-f");
	int delay;
	try { delay = std::stoi(raw); }
	catch (...) 
	{
		std::cerr<<"Failed to parse value given to --fps: "<<raw<<", it must be a number!"<<std::endl;
		return EXIT_FAILURE;
	}
	spec.targetFrameTime = delay;

	spec.dropChars = parser.getOr("|:.", "--chars", "-c");

	Simulation sim(spec);
	sim.run();

	return EXIT_SUCCESS;
}

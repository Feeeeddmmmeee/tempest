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

#include <cstdlib>
#include <iostream>

#ifdef DEBUG
#define LOG(msg) std::cout<<msg<<std::endl
#else
#define LOG(msg)
#endif

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
		<<"\t-h, --help      Display help info\n"
		<<"\t-v, --version   Display version information\n";
}

void version(const char *prog)
{
	std::cout<<prog<<" "<<TEMPEST_VERSION<<std::endl;
}

int main(int argc, char *argv[])
{
	InputParser parser(argc, argv);

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
}

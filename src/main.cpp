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

#include <iostream>

#ifdef DEBUG
#define LOG(msg) std::cout<<msg<<std::endl
#else
#define LOG(msg)
#endif

int main()
{
	std::cout<<"Hello, World!"<<std::endl;
	LOG("secret!");
}

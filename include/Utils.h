#pragma once

#include <cstring>
#include <cstdlib>
#include <iostream>

#ifdef TEMPEST_DEBUG
#define TEMPEST_LOG(msg) std::cout<<msg<<std::endl
#else
#define TEMPEST_LOG(msg)
#endif

#define TEMPEST_ERR(msg) std::cerr<<std::strerror(errno)<<std::endl<<msg<<", "\
	<<__FILE__<<":"<<__LINE__<<std::endl; exit(EXIT_FAILURE)

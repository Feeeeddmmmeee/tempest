#pragma once

#include <random>

class Random
{
	public:
		Random() : rng(time(NULL)) {}
		Random(unsigned int seed) : rng(seed) {}

		int integer(int min, int max)
		{
			std::uniform_int_distribution dist(min, max);
			return dist(rng);
		}

		int integerGauss(int min, int max)
		{
			std::binomial_distribution dist(min, max);
			return dist(rng);
		}

		double real(double min, double max)
		{
			std::uniform_real_distribution dist(min, max);
			return dist(rng);
		}

		double realGauss(double min, double max)
		{
			std::normal_distribution dist(min, max);
			return dist(rng);
		}

	private:
		std::mt19937 rng;
};

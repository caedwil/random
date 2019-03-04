// A single-file library for generating random numbers using the C++
// random library. The goal is to provide a simpler syntax for 
// generating random numbers without the verbosity of the regular C++
// library.

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
public:
	// Generates a pseudo-random integer in the range [min, max].
	static int get(int min, int max) {
		return generate<std::uniform_int_distribution, int>(min, max);
	}

	// Generates a pseudo-random unsigned integer in the range [min, max].
	static unsigned int get(unsigned int min, unsigned int max) {
		return generate<std::uniform_int_distribution, unsigned int>(min, max);
	}

	// Generates a pseudo-random double in the range [min, max).
	static double get(double min, double max) {
		return generate<std::uniform_real_distribution, double>(min, max);
	}

	// Generates a pseudo-random float in the range [min, max).
	static float get(float min, float max) {
		return generate<std::uniform_real_distribution, float>(min, max);
	}
private:
	// Used to seed the random number generator.
	static std::random_device device;

	// The random number generator. In this case, it is based on the 
	// Mersenne Twister implementation.
	static std::mt19937 rng;

	// Generates a random number using the specified distribution type
	// and the specified minimum and maximum values.
	template <template<typename> class Distribution, typename T>
	static T generate(T min, T max) {
		// Declare the distribution as static so that it can be reused
		// by subsequent calls to this function if the minimum or
		// maximum values have not changed.
		static Distribution<T> distribution;

		// If the minimum or maximum values have changed, generate a
		// new distribution. Otherwise leave the current distribution
		// unchanged.
		if (distribution.min() != min || distribution.max() != max) {
			distribution = Distribution<T>(min, max);
		}

		// Generate a random number using the current distribution.
		return distribution(rng);
	}

	// Declaring the constructor as 'private' to prevent instantiation.
	Random() {}
};

// Define the random device and, specifically, the random number
// generator so that they can be used.
std::random_device Random::device;
std::mt19937 Random::rng(Random::device());

#endif
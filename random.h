// A single-file library for generating random numbers using the C++
// random library. The goal is to provide a simpler syntax for 
// generating random numbers without the verbosity of the regular C++
// library.

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

template <class Engine = std::mt19937>
class Random {
public:
	// Initialise the randomisation engine using an instance of random
	// device.
	Random() {
		engine = Engine(std::random_device()());
	}

	// Generates a pseudo-random integer in the range [min, max].
	int operator()(int min, int max) {
		return generate<std::uniform_int_distribution, int>(min, max);
	}

	// Generates a pseudo-random unsigned integer in the range [min, max].
	unsigned int operator()(unsigned int min, unsigned int max) {
		return generate<std::uniform_int_distribution, unsigned int>(min, max);
	}

	// Generates a pseudo-random float in the range [min, max).
	float operator()(float min, float max) {
		return generate<std::uniform_real_distribution, float>(min, max);
	}

	// Generates a pseudo-random double in the range [min, max).
	double operator()(double min, double max) {
		return generate<std::uniform_real_distribution, double>(min, max);
	}
private:
	// The randomisation engine.
	Engine engine;

	// Generate a random number using the specified distribution type
	// and the specified minimum and maximum values.
	template <template<typename> class Distribution, typename T>
	T generate(T min, T max) {
		// Declare the distribution as static so that it can be reused
		// by subsequent calls to this function if the minimum and 
		// maximum values have not changed.
		static Distribution<T> distribution;

		// If the minimum or maximum values have changed, generate a
		// new distribution. Otherwise, leave the current distribution
		// unchanged.
		if (distribution.min() != min || distribution.max() != max) {
			distribution = Distribution<T>(min, max);
		}

		// Generate a random number using the current distribution.
		return distribution(engine);
	}
};

#endif
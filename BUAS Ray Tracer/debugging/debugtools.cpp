#include "debugtools.h"

#include "../math/MathLibrary.h"
#include <stdio.h>
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"

namespace brt
{
#pragma region printing
	void debugtools::print_matrix(mat4 matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%.2f,\t%.2f,\t%.2f,\t%.2f\n", matrix.m[4 * i + 0], matrix.m[4 * i + 1], matrix.m[4 * i + 2], matrix.m[4 * i + 3]);
		}
	}

	void debugtools::print_vector(vec3 vec)
	{
		printf("(%.2f,\t%.2f,\t%.2f)\n", vec.m_X, vec.m_Y, vec.m_Z);
	}
#pragma endregion

#pragma region profiling
	std::vector<debugprofiletimerdata> debugtools::timers;
	std::unique_ptr<sf::Clock> debugtools::m_clock;

	const float debugtools::get_elapsed_time()
	{
		sf::Time t = m_clock->getElapsedTime();
		return t.asSeconds();
	}

	void debugtools::start_profile_timer(std::string name)
	{
		if (!m_clock)
		{
			m_clock = std::make_unique<sf::Clock>();
		}
		timers.push_back(debugprofiletimerdata(name, get_elapsed_time()));
	}

	const float debugtools::end_and_measure_profile_timer(std::string name)
	{
		auto i = std::begin(timers);
		while (i != std::end(timers))
		{
			if (i->m_name == name)
			{
				float time = get_elapsed_time() - i->m_starttime;
				timers.erase(i);
				return time;
			}
		}
		return -1.f;
	}
#pragma endregion
}
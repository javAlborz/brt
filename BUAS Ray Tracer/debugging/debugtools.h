#pragma once
#include <vector>
#include <memory.h>
#include "debugprofiletimerdata.h"

namespace sf
{
	class Clock;
}

class mat4;
class vec3;

namespace brt
{
	class debugtools
	{
	public:
		debugtools();
		~debugtools();

		static void print_matrix(mat4 matrix);
		static void print_vector(vec3 vec);

		static void matrix_tests();
		static void vector_tests();

		static void start_profile_timer(std::string name);
		static const float end_and_measure_profile_timer(std::string name);

	private:
		static const float get_elapsed_time();

	private:
		static std::vector<debugprofiletimerdata> timers;
		static std::unique_ptr<sf::Clock> m_clock;
	};
}
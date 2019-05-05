#include "debugtools.h"

#include "../math/MathLibrary.h"
#include <stdio.h>
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"

namespace brt
{
	std::vector<debugprofiletimerdata> debugtools::timers;
	std::unique_ptr<sf::Clock> debugtools::m_clock;

	debugtools::debugtools()
	{
	}


	debugtools::~debugtools()
	{
	}

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

	void debugtools::matrix_tests()
	{
		mat4 a = mat4(
			2, 4, 2, 7,
			9, 1, 4, 5,
			9, 8, 4, 6,
			2, 2, 4, 9);
		mat4 b = mat4(
			9, 3, 6, 7,
			1, 1, 4, 6,
			8, 9, 3, 4,
			9, 9, 7, 8);
		printf("matrix multiplication:\n");
		mat4 product = a * b;
		print_matrix(product);

		printf("\n");
		mat4 projectionTest = mat4::projection(10.f, 1.6f, 1.f, 100.f);
		printf("projection matrix:\n");
		print_matrix(projectionTest);

		printf("\n");
		printf("determinant test %.2f\n", a.determinant());

		printf("\n");
		mat4 inv = a.inverse();
		printf("inverse matrix of a:\n");
		print_matrix(inv);

		// lookat matrix doesn't work yet
		printf("\n");
		mat4 lookAt = mat4::lookat(vec3(0.f, 0.f, 0.f), vec3(3.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
		printf("lookat matrix:\n");
		print_matrix(lookAt);
	}

	void debugtools::vector_tests()
	{
		vec3 a(1.f, 2.f, 3.f);
		vec3 b(3.f, -1.f, 2.f);
		printf("||a|| * ||b|| = %.2f\n", a.length() * b.length());
		printf("a * b: ");
		print_vector(vec3(a.m_X * b.m_X, a.m_Y * b.m_Y, a.m_Z * b.m_Z));

		printf("\n");
		print_vector(a.cross(b));
	}

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
}
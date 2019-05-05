#pragma once
#include "SFML/Graphics.hpp"

#define COLOR_ELEMENTS_COUNT 4
#define HSVCOLOR_ELEMENTS_COUNT 3
#define HSLCOLOR_ELEMENTS_COUNT 3

namespace brt
{
	struct hsvcolor
	{
#pragma warning(push)
#pragma warning(disable : 4201)
		union
		{
			struct
			{
				float m_h;
				float m_s;
				float m_v;
			};
			float c[HSVCOLOR_ELEMENTS_COUNT];
		};
#pragma warning(pop)

		hsvcolor(float h, float s, float b);
	};

	struct hslcolor
	{
#pragma warning(push)
#pragma warning(disable : 4201)
		union
		{
			struct
			{
				float m_h;
				float m_s;
				float m_l;
			};
			float c[HSLCOLOR_ELEMENTS_COUNT];
		};
#pragma warning(pop)

		hslcolor(float h, float s, float l);
	};

	struct color // not reusing vector class because vector class has some operators that don't make sense for color
	{
#pragma warning(push)
#pragma warning(disable : 4201)
		union {
			struct
			{
				float m_r;
				float m_g;
				float m_b;
				float m_a;
			};
			float c[COLOR_ELEMENTS_COUNT];
		};
#pragma warning(pop)

		color();
		color(float r, float g, float b);
		color(float r, float g, float b, float a);
		explicit color(sf::Color col);
		explicit color(hsvcolor col);
		explicit color(hslcolor col);

		color& operator=(const color& rhs);
		color& operator=(const hsvcolor &rhs);
		color& operator=(const hslcolor &rhs);

		color& operator+=(const color &rhs);
		color& operator-=(const color &rhs);
		color& operator*=(float rhs);
		color& operator/=(float rhs);

		float operator[](int index) const;
		float& operator[](int index);

		sf::Color to_sf_color() const;

		static color white() { return color(255.f, 255.f, 255.f); }
	};

	color operator+(const color &lhs, const color &rhs);
	color operator-(const color &lhs, const color &rhs);
	color operator*(const color &lhs, float rhs);
	color operator/(const color &lhs, float rhs);
}
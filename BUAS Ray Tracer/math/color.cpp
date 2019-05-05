#include "color.h"

#include <assert.h>

#include "MathLibrary.h"
#include <algorithm> // std::clamp

namespace brt
{
	color::color()
	{
		for (int i = 0; i < COLOR_ELEMENTS_COUNT; i++)
		{
			c[i] = 0.f;
		}
	}
	color::color(float r, float g, float b)
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = 255.f;
	}

	color::color(float r, float g, float b, float a)
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}

	color::color(sf::Color col)
	{
		m_r = static_cast<float>(col.r);
		m_g = static_cast<float>(col.g);
		m_b = static_cast<float>(col.b);
		m_a = static_cast<float>(col.a);
	}

	color::color(hsvcolor col)
	{
		*this = col;
	}

	color::color(hslcolor col)
	{
		*this = col;
	}

	color & color::operator=(const color & rhs)
	{
		for (int i = 0; i < COLOR_ELEMENTS_COUNT; i++)
		{
			c[i] = rhs.c[i];
		}
		return *this;
	}

	color & color::operator=(const hsvcolor & rhs)
	{
		// https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
		float      hh, p, q, t, ff;
		long        i;
		color         out;

		if (rhs.m_s <= 0.0f) {       // < is bogus, just shuts up warnings
			out.m_r = rhs.m_v;
			out.m_g = rhs.m_v;
			out.m_b = rhs.m_v;
		}
		hh = rhs.m_h;
		if (hh >= 360.0f) hh = 0.0f;
		hh /= 60.0f;
		i = static_cast<long>(hh);
		ff = hh - i;
		p = rhs.m_v * (1.0f - rhs.m_s);
		q = rhs.m_v * (1.0f - (rhs.m_s * ff));
		t = rhs.m_v * (1.0f - (rhs.m_s * (1.0f - ff)));

		switch (i)
		{
		case 0:
			out.m_r = rhs.m_v;
			out.m_g = t;
			out.m_b = p;
			break;
		case 1:
			out.m_r = q;
			out.m_g = rhs.m_v;
			out.m_b = p;
			break;
		case 2:
			out.m_r = p;
			out.m_g = rhs.m_v;
			out.m_b = t;
			break;

		case 3:
			out.m_r = p;
			out.m_g = q;
			out.m_b = rhs.m_v;
			break;
		case 4:
			out.m_r = t;
			out.m_g = p;
			out.m_b = rhs.m_v;
			break;
		case 5:
		default:
			out.m_r = rhs.m_v;
			out.m_g = p;
			out.m_b = q;
			break;
		}

		*this = out;
		return *this;
	}

	float HueToRGB(float v1, float v2, float vH)
	{
		if (vH < 0)
			vH += 1.f;

		if (vH > 1)
			vH -= 1.f;

		if ((6 * vH) < 1.f)
			return (v1 + (v2 - v1) * 6.f * vH);

		if ((2.f * vH) < 1.f)
			return v2;

		if ((3.f * vH) < 2.f)
			return (v1 + (v2 - v1) * ((2.0f / 3.f) - vH) * 6.f);

		return v1;
	}

	color & color::operator=(const hslcolor & rhs)
	{
		// https://www.programmingalgorithms.com/algorithm/hsl-to-rgb?lang=C%2B%2B

		float r, g, b;
		if (rhs.m_s == 0)
		{
			r = g = b = (rhs.m_l * 255.f);
		}
		else
		{
			float v1, v2;
			float hue = (float)rhs.m_h / 360.f;

			v2 = (rhs.m_l < 0.5) ? (rhs.m_l * (1 + rhs.m_s)) : ((rhs.m_l + rhs.m_s) - (rhs.m_l * rhs.m_s));
			v1 = 2 * rhs.m_l - v2;

			r = 255.f * HueToRGB(v1, v2, hue + (1.f / 3.f));
			g = 255.f * HueToRGB(v1, v2, hue);
			b = 255.f * HueToRGB(v1, v2, hue - (1.f / 3.f));
		}

		*this = color(r, g, b);
		return *this;
	}

	float color::operator[](int index) const
	{
		assert(index < COLOR_ELEMENTS_COUNT);
		return c[index];
	}

	float & color::operator[](int index)
	{
		assert(index < COLOR_ELEMENTS_COUNT);
		return c[index];
	}

	sf::Color color::to_sf_color() const
	{
		return sf::Color(
			static_cast<sf::Uint8>(std::clamp(m_r, 0.f, 255.f)),
			static_cast<sf::Uint8>(std::clamp(m_g, 0.f, 255.f)),
			static_cast<sf::Uint8>(std::clamp(m_b, 0.f, 255.f)),
			static_cast<sf::Uint8>(std::clamp(m_a, 0.f, 255.f)));
	}

	/// doesn't add alpha values to each other, just returns a color with alpha 255
	color & color::operator+=(const color & rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	/// doesn't subtract alpha values from each other, just returns a color with alpha 255
	color & color::operator-=(const color & rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	/// doesn't multiply alpha values with each other, just returns a color with alpha 255
	color & color::operator*=(float rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	/// doesn't devide alpha values with each other, just returns a color with alpha 255
	color & color::operator/=(float rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	/// doesn't add alpha values to each other, just returns a color with alpha 255
	color operator+(const color & lhs, const color & rhs)
	{
		return color(lhs.m_r + rhs.m_r, lhs.m_g + rhs.m_g, lhs.m_b + rhs.m_b);
	}

	/// doesn't subtract alpha values from each other, just returns a color with alpha 255
	color operator-(const color & lhs, const color & rhs)
	{
		return color(lhs.m_r - rhs.m_r, lhs.m_g - rhs.m_g, lhs.m_b - rhs.m_b);
	}

	/// doesn't multiply alpha values with each other, just returns a color with alpha 255
	brt::color operator*(const color &lhs, float rhs)
	{
		return color(lhs.m_r * rhs, lhs.m_g * rhs, lhs.m_b * rhs);
	}

	/// doesn't devide alpha values with each other, just returns a color with alpha 255
	color operator/(const color & lhs, float rhs)
	{
		return color(lhs.m_r / rhs, lhs.m_g / rhs, lhs.m_b / rhs);
	}

	hsvcolor::hsvcolor(float h, float s, float v)
	{
		m_h = h;
		m_s = s;
		m_v = v;
	}

	hslcolor::hslcolor(float h, float s, float l)
	{
		m_h = h;
		m_s = s;
		m_l = l;
	}
}
#pragma once
#include "SFML/Graphics.hpp"

enum MTYPE
{
	MTYPE_NONE = 0,
	MTYPE_DEFAULT,
	MTYPE_PROCCHECKERBOARD,
	MTYPE_METAL,
	MTYPE_COUNT
};

namespace brt
{
	struct material
	{
		material() = default;

		MTYPE m_mattype;

		// TODO: recieve shadows option
	};
}
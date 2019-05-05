#pragma once
enum class MTYPE
{
	NONE = 0,
	DEFAULT,
	PROCCHECKERBOARD,
	COUNT
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
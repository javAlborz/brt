#pragma once
#include <string>

namespace brt
{
	struct debugprofiletimerdata
	{
		debugprofiletimerdata(std::string name, float starttime) : m_name(name), m_starttime(starttime)
		{

		}

		std::string m_name;
		float m_starttime;
	};
}
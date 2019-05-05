#include "boundingvolume.h"

#include "../../../ray/intersection.h"

namespace brt
{
	boundingvolume::boundingvolume(const vec3 & pos, std::shared_ptr<sceneobject> volume) : sceneobject(pos, nullptr), m_volume(volume)
	{
	}

	vec3 boundingvolume::get_normal_at(const vec3 & point) const
	{
		return m_cachedintersection.object->get_normal_at(point);
	}

	bool boundingvolume::has_intersection(const vec3& origin, const vec3& dir, intersection& info)
	{
		intersection discardedinfo;
		if (m_volume->has_intersection(origin, dir, discardedinfo)) // if there is intersection with the object itself
		{
			float mindist = std::numeric_limits<float>::infinity();
			for (unsigned int i = 0; i < m_objects.size(); i++) // check which objects in volume have intersection
			{
				intersection curobjinter;
				if (m_objects[i]->has_intersection(origin, dir, curobjinter) && curobjinter.distance < mindist)
				{
					mindist = curobjinter.distance;
					info = curobjinter;
				}
			}
			if (info.hasintersection)
			{
				m_mat = info.object->get_object_material();
				m_cachedintersection = info;
				return true;
			}
		}
		return false;
	}

	void boundingvolume::add_object(std::shared_ptr<sceneobject> obj)
	{
		m_objects.push_back(obj);
	}
}
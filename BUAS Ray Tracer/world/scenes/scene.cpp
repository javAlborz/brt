#include "scene.h"

#include "../objects/sceneobject.h"

#include "../lights/light.h"

#include "../../rendering/camera.h"

#include "../../ray/intersection.h"
#include "../../ray/ray.h"

namespace brt
{
	scene::scene(raytracer* application) : m_raytracer(application)
	{
	}

	scene::~scene()
	{
		delete m_camera;
	}

	std::vector<sceneobject*> scene::get_objects() const
	{
		return m_objects;
	}

	std::vector<std::shared_ptr<light>> scene::get_lights() const
	{
		return m_lights;
	}

	camera * scene::get_camera() const
	{
		return m_camera;
	}

	void scene::update(float deltat)
	{
		// currently it's only needed to call update on the camera, later on I might change this to call update on all entities
		m_camera->update(deltat);
	}

	brt::intersection scene::check_for_intersection(const ray& r) const
	{
		intersection result;
		std::vector<intersection> intersections;

		float disttoclosestobj = std::numeric_limits<float>::max();
		for (sceneobject* sceneobj : m_objects)
		{
			intersection inter;

#if 1
 			vec3 o = sceneobj->get_transformation_matrix().inverse_transform_vector(r.origin);
 			vec3 d = sceneobj->get_transformation_matrix().inverse_transform_direction(r.direction);
#else
			vec3 o = (r.origin);
			vec3 d = (r.direction);
#endif
			if (sceneobj->has_intersection(o, d, inter))
			{
				if (inter.distance < disttoclosestobj)
				{
					result = inter;
					result.hasintersection = true;
					disttoclosestobj = inter.distance;
				}
			}
		}

		return result;
	}

	void scene::destroy_scene()
	{
		while (m_objects.size() > 0)
		{
			sceneobject* curobj = m_objects[0];
			m_objects.erase(m_objects.begin());
			delete curobj;
		}
	}
}
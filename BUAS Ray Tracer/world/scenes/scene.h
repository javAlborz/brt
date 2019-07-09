#pragma once
#include <vector>
#include <memory>

namespace brt
{
	class raytracer;
	class sceneobject;
	class light;
	class camera;
	struct intersection;
	struct ray;

	class scene
	{
	public:
		scene(raytracer* application);
		~scene();

		std::vector<sceneobject*> get_objects() const;
		std::vector<std::shared_ptr<light>> get_lights() const;
		camera* get_camera() const;

		virtual void update(float deltat);

		intersection check_for_intersection(const ray& r) const;

	protected:
		virtual void destroy_scene();

	protected:
		raytracer* m_raytracer;

		std::vector<sceneobject*> m_objects;
		std::vector<std::shared_ptr<light>> m_lights;
		camera* m_camera;
	};
}
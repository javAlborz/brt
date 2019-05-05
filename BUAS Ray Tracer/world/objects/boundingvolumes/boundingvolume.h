#pragma once
#include "../sceneobject.h"
#include "../../../ray/intersection.h"

namespace brt
{
	class boundingvolume : public sceneobject
	{
	public:
		boundingvolume(const vec3& pos, std::shared_ptr<sceneobject> volume);
		
		virtual vec3 get_normal_at(const vec3& point) const override;
		virtual bool has_intersection(const vec3& origin, const vec3& dir, intersection& info) override;

		void add_object(std::shared_ptr<sceneobject> obj);

	private:
		std::shared_ptr<sceneobject> m_volume;

		std::vector<std::shared_ptr<sceneobject>> m_objects;

		intersection m_cachedintersection;
	};
}
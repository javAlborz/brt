#include "sceneacceleration.h"

#include "../objects/sceneobject.h"
#include "../objects/sphere.h"
#include "../objects/plane.h"

#include "../lights/light.h"
#include "../lights/pointlight.h"

#include "../../rendering/materials/material.h"
#include "../../rendering/materials/materialdefault.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../raytracer.h"
#include "../../math/color.h"
#include "../objects/boundingvolumes/boundingvolume.h"

namespace brt
{
	sceneacceleration::sceneacceleration(raytracer * application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	sceneacceleration::~sceneacceleration()
	{
		destroy_scene();
	}

	void sceneacceleration::build_scene()
	{
		// camera
		vec3 lookatpos(0.f, 2.f, 0.f);
		vec3 campos(0.f, 6.f, 20.f);

		m_camera = new camera(lookatpos, campos, vec3::up());

		//const int totalspheres = 1000;
		const int treechildren = 10;
		
		// spheres
#if 1	// if bounding volumes
		// this way the tree is build top down, and only works with this specific set, this is ok in this situation though, this is to demo the acceleration structure

		float radius0 = 8.f;
		vec3 p0;
		boundingvolume* bv0 = new boundingvolume(p0, std::make_shared<sphere>(p0, radius0, nullptr));
		m_objects.push_back(bv0);
		for (int i = 0; i < treechildren; i++)
		{
			float radius1 = 2.f;
			vec3 p1 = mathlibrary::random_point_in_unit_sphere() * (radius0 - radius1 / 2.f) + p0;
			std::shared_ptr<boundingvolume> bv2 = std::make_shared<boundingvolume>(boundingvolume(p1, std::make_shared<sphere>(p1, radius1, nullptr)));
			bv0->add_object(bv2);
			for (int j = 0; j < treechildren; j++)
			{
				float radius2 = 0.5f;
				vec3 p2 = mathlibrary::random_point_in_unit_sphere() * (radius1 - radius2 / 2.f) + p1;
				std::shared_ptr<boundingvolume> bv3 = std::make_shared<boundingvolume>(boundingvolume(p2, std::make_shared<sphere>(p2, radius2, nullptr)));
				bv0->add_object(bv3);
				for (int k = 0; k < treechildren; k++)
				{
					color col = color(hslcolor(mathlibrary::random_float_gen(0.f, 360.f), mathlibrary::random_float_gen(0.27f, 0.95f), mathlibrary::random_float_gen(0.65f, 0.75f))); // create nice pastel like color
					std::shared_ptr<material> s1mat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(col, SPECEGGSHELL, color(150, 150, 150)));

					float radius3 = 0.1f;
					vec3 p3 = mathlibrary::random_point_in_unit_sphere() * (radius2 - radius3 / 2.f) + p2;
					bv3->add_object(std::make_shared<sphere>(p3, radius3, s1mat));
				}
			}
		}
#else
		float radius0 = 8.f;
		vec3 p0;
		for (int i = 0; i < treechildren; i++)
		{
			float radius1 = 2.f;
			vec3 p1 = mathlibrary::random_point_in_unit_sphere() * (radius0 - radius1 / 2.f) + p0;
			for (int j = 0; j < treechildren; j++)
			{
				float radius2 = 0.5f;
				vec3 p2 = mathlibrary::random_point_in_unit_sphere() * (radius1 - radius2 / 2.f) + p1;
				for (int k = 0; k < treechildren; k++)
				{
					color col = color(hslcolor(mathlibrary::random_float_gen(0.f, 360.f), mathlibrary::random_float_gen(0.27f, 0.95f), mathlibrary::random_float_gen(0.65f, 0.75f))).to_sf_color(); // create nice pastel like color
					std::shared_ptr<material> s1mat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(col, SPECEGGSHELL, color(150, 150, 150)));

					float radius3 = 0.1f;
					vec3 p3 = mathlibrary::random_point_in_unit_sphere() * (radius2 - radius3 / 2.f) + p2;
					m_objects.push_back(new sphere(p3, radius3, s1mat));
				}
			}
		}
#endif

		// plane
		//std::shared_ptr<material> planemat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(sf::Color(200, 200, 200), SPECNONE));
		//m_objects.push_back(new plane(vec3(0.f, 0.f, 0.f), vec3(0.0f, 1.f, 0.f), planemat));

		// light
		m_lights.push_back(std::static_pointer_cast<light>(std::make_shared<pointlight>(vec3(1.f, 20.f, 0.f), color::white(), 1.f)));

		// triangle test
		//vec3 verts[3] = { vec3(2.f, 0.f, -0.f), vec3(0.f, 2.f, -1.f), vec3(0.f, 0.f, 0.f) };
		//m_objects.push_back(new triangle(vec3(0.f, 0.f, 0.f), sf::Color(228, 182, 2), verts));
	}
}
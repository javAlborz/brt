#include "scenetest.h"

#include "../objects/sceneobject.h"
#include "../objects/sphere.h"
#include "../objects/plane.h"
#include "../objects/triangle.h"
#include "../objects/quadrilateral.h"

#include "../lights/light.h"
#include "../lights/pointlight.h"

#include "../../rendering/materials/material.h"
#include "../../rendering/materials/materialdefault.h"
#include "../../rendering/materials/materialproccheckerboard.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../raytracer.h"
#include "../../math/color.h"

#include "../objects/aabb.h"
#include "../../debugging/debugtools.h"

#define SCREEN_WIDTH 340.f
#define SCREEN_HEIGHT 180.f

namespace brt
{
	scenetest::scenetest(raytracer * application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	scenetest::~scenetest()
	{
		destroy_scene();
	}

	void scenetest::build_scene()
	{
		// camera
		vec3 lookatpos(0.f, 2.f, -5.f);
		vec3 campos(4.f, 3.f, 3.f);

		m_camera = new camera(lookatpos, campos, vec3::up(), SCREEN_WIDTH, SCREEN_HEIGHT);
		m_raytracer->get_renderer()->set_resolution(static_cast<unsigned int>(SCREEN_WIDTH), static_cast<unsigned int>(SCREEN_HEIGHT));

		// oriented bounding box
		vec3 corner1 = vec3(-0.5f, -0.75f, -0.5f);
		vec3 corner2 = vec3(0.5f, 0.75f, 0.5f);
		vec3 bounds[2] = { corner1, corner2 };

		sf::Color col2 = color(hslcolor(200.f, 0.7f, 0.7f)).to_sf_color();
		std::shared_ptr<material> aabbmat2 = std::static_pointer_cast<material>(std::make_shared<materialdefault>(col2, SPECNONE));
		m_objects.push_back(new aabb(vec3(), bounds, aabbmat2));
		sceneobject* obj = m_objects[m_objects.size() - 1];
		
		obj->rotation += vec3(M_PI / -5.f, 0.f, 0.f);
		obj->position += vec3(1.f, 1.f, -8.f);

		m_objects.push_back(new aabb(vec3(), bounds, aabbmat2));
		sceneobject* obj2 = m_objects[m_objects.size() - 1];
		obj2->rotation += vec3(M_PI / 7.f, 0.f, 0.f);
		obj2->position += vec3(1.f, 1.f, -5.f);

		// plane
		std::shared_ptr<material> planemat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(sf::Color(200, 200, 200), SPECNONE));
		m_objects.push_back(new plane(vec3(0.f, 0.f, 0.f), vec3(0.0f, 1.f, 0.f), planemat));

		// light
		m_lights.push_back(std::static_pointer_cast<light>(std::make_shared<pointlight>(vec3(1.f, 20.f, 0.f), color::white(), 1.f)));

		// triangle test
		//vec3 verts[3] = { vec3(2.f, 0.f, -0.f), vec3(0.f, 2.f, -1.f), vec3(0.f, 0.f, 0.f) };
		//m_objects.push_back(new triangle(vec3(0.f, 0.f, 0.f), sf::Color(228, 182, 2), verts));
	}
}
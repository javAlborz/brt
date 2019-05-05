#include "sceneboxes.h"

#include "../objects/sceneobject.h"
#include "../objects/plane.h"
#include "../objects/quadrilateral.h"
#include "../objects/aabb.h"
#include "../objects/sphere.h"

#include "../lights/light.h"
#include "../lights/pointlight.h"
#include "../lights/directionallight.h"

#include "../../rendering/materials/material.h"
#include "../../rendering/materials/materialdefault.h"
#include "../../rendering/materials/materialproccheckerboard.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../RayTracer.h"
#include "../../math/color.h"
#include "../objects/boundingvolumes/boundingvolume.h"
#include <memory>

#define SCREEN_WIDTH 340.f
#define SCREEN_HEIGHT 180.f

namespace brt
{
	sceneboxes::sceneboxes(raytracer * application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	sceneboxes::~sceneboxes()
	{
		destroy_scene();
	}

	void sceneboxes::build_scene()
	{
		// camera
		vec3 lookatpos(0.f, 2.f, -10.f);
		vec3 campos(0.f, 9.f, 14.f);
		// 		vec3 lookatpos(0.f, 2.f, -10.f);
		// 		vec3 campos(0.f, 20.f, -9.5f); // this doesn't work when z=-10 ???
		m_camera = new camera(lookatpos, campos, vec3::up(), SCREEN_WIDTH, SCREEN_HEIGHT);
		m_raytracer->get_renderer()->set_resolution(static_cast<unsigned int>(SCREEN_WIDTH), static_cast<unsigned int>(SCREEN_HEIGHT));

		// metal sphere
		std::shared_ptr<material> metalspheremat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(color(50, 50, 50), 5.f, color(160, 160, 160), 0.8f));
		m_objects.push_back(new sphere(vec3(0.f, 1.f, -10.5f), 1.f, metalspheremat));

		// acceleration or not
#if 0
		// boxes
		const int amountofboxes = 800; // TODO: move elsewhere
		const float r = M_PI / 12.f; // maxrotamount
		for (int i = 0; i < amountofboxes; i++)
		{
			vec3 bottomcenterofbox = find_box_pos();

			float sizex = mathlibrary::random_float_gen(0.2f, 1.5f), sizey = mathlibrary::random_float_gen(1.0f, 3.f), sizez = mathlibrary::random_float_gen(0.2f, 1.5f);

			sf::Color col = color(hslcolor(mathlibrary::random_float_gen(0.f, 360.f), mathlibrary::random_float_gen(0.27f, 0.95f), mathlibrary::random_float_gen(0.65f, 0.75f) )).to_sf_color();
			std::shared_ptr<material> aabbmat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(col, SPECNONE));
			m_objects.push_back(new aabb(vec3(sizex, sizey, sizez), aabbmat));
			float rotx = mathlibrary::random_float_gen(-r, r), roty = mathlibrary::random_float_gen(-r, r), rotz = mathlibrary::random_float_gen(-r, r);
			m_objects[m_objects.size() - 1]->transform *= mat4::rotateX(rotx) * mat4::rotateY(roty) * mat4::rotateZ(rotz);
			m_objects[m_objects.size() - 1]->transform *= mat4::translate(bottomcenterofbox + vec3(0.f, sizey * 0.3f, 0.f));
		}

#else
		const int amountofgroups = 10;
		const float allround = (2.f * M_PI);
		for (int i = 0; i < amountofgroups; i++)
		{
			float dirtobuildin = static_cast<float>(i) * allround / static_cast<float>(amountofgroups);
			spawn_group(dirtobuildin, 24);
			spawn_group(dirtobuildin, 40);
		}
#endif

		// plane
		std::shared_ptr<material> planemat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(color(200, 200, 200), SPECNONE));
		m_objects.push_back(new plane(vec3(0.f, 0.f, 0.f), vec3(0.0f, 1.f, 0.f), planemat));

		// light
		m_lights.push_back(std::static_pointer_cast<light>(std::make_shared<pointlight>(vec3(7.f, 20.f, 8.f), color::white(), 1.f)));
	}

	void sceneboxes::spawn_group(float raddir, float disttocenter)
	{
		const int amountingroup = 10;
		const float r = M_PI / 12.f; // maxrotamount

		const vec3 center(0.f, 0.f, -10.f); // TODO: move elsewhere
		
		vec3 boundingcenterpos(
			center.m_X + cos(raddir) * disttocenter,
			center.m_Y,
			center.m_Z + sin(raddir) * disttocenter);

		const float maxdist = 8.f;
		

		vec3 bvpos = boundingcenterpos + vec3(0, 2, 0) - vec3(maxdist / 2, 0, maxdist / 2);
#if 0
		// material
 		sf::Color col = color(hslcolor(mathlibrary::random_float_gen(0.f, 360.f), mathlibrary::random_float_gen(0.27f, 0.95f), mathlibrary::random_float_gen(0.65f, 0.75f))).to_sf_color();
 		std::shared_ptr<material> aabbmat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(col, SPECNONE));
		aabb* box = new aabb(vec3(maxdist, 4, maxdist), aabbmat);
		m_objects.push_back(box);
		box->transform *= mat4::translate(bvpos);

#else
 		// boundingbox
		std::shared_ptr<aabb> vol = std::make_shared<aabb>(vec3(maxdist, 4, maxdist), nullptr);
 		boundingvolume* bv0 = new boundingvolume(bvpos, vol);
 		//bv0->transform *= mat4::translate(bvpos);
		vol->position += bvpos;
 		m_objects.push_back(bv0);
 
 		for (int i = 0; i < amountingroup; i++)
 		{
 			// material
			color col = color(hslcolor(mathlibrary::random_float_gen(0.f, 360.f), mathlibrary::random_float_gen(0.27f, 0.95f), mathlibrary::random_float_gen(0.65f, 0.75f)));
 			std::shared_ptr<material> aabbmat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(col, SPECNONE));
 			
 			// box
 			float sizex = mathlibrary::random_float_gen(0.2f, 1.5f), sizey = mathlibrary::random_float_gen(1.0f, 3.f), sizez = mathlibrary::random_float_gen(0.2f, 1.5f);
 			std::shared_ptr<aabb> box = std::make_shared<aabb>(vec3(sizex, sizey, sizez), aabbmat);
 			bv0->add_object(box);
 			
 			// rotation
 			float rotx = mathlibrary::random_float_gen(-r, r), roty = mathlibrary::random_float_gen(-r, r), rotz = mathlibrary::random_float_gen(-r, r);
 			box->rotation += vec3(rotx, roty, rotz);
 			
 			// position
 			//vec3 bottomcenterofbox = boundingcenterpos + vec3(mathlibrary::random_float_gen(-maxdist, maxdist), 0, mathlibrary::random_float_gen(-maxdist, maxdist));
			//box->transform *= mat4::translate(bottomcenterofbox + vec3(0.f, sizey * 0.3f, 0.f));
			box->position += boundingcenterpos;
		}
#endif
	}

	vec3 sceneboxes::find_box_pos() // TODO: possibly change this to have a more equal spread over plane, by e.g. working from inside out and not placing more than a certain number of cubes in one area
	{
		float dirtobuildin = mathlibrary::random_float_gen(0.f, 2.f * M_PI);
		float distfromcenter = mathlibrary::random_float_gen(10.f, 50.f);

		const vec3 center(0.f, 0.f, -10.f); // TODO: move elsewhere

		return vec3(
			center.m_X + cos(dirtobuildin) * distfromcenter,
			center.m_Y,
			center.m_Z + sin(dirtobuildin) * distfromcenter);
	}
}
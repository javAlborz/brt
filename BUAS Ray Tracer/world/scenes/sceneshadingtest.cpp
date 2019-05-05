#include "sceneshadingtest.h"

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

#define SCREEN_WIDTH 340.f
#define SCREEN_HEIGHT 180.f

namespace brt
{
	sceneshadingtest::sceneshadingtest(raytracer * application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	sceneshadingtest::~sceneshadingtest()
	{
		destroy_scene();
	}

	void sceneshadingtest::build_scene()
	{
	}
}
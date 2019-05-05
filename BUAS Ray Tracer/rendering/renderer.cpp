#include "renderer.h"

#include <SFML/Graphics.hpp>

#include "../raytracer.h"

#include "camera.h"

#include "materials/materialproccheckerboard.h"
#include "materials/materialdefault.h"

#include "../debugging/debugtools.h"

#include "../ray/ray.h"
#include "../ray/intersection.h"

#include "../math/color.h"

#include "../world/entity.h"

#include "../world/scenes/scene.h"

#include "../world/lights/light.h"
#include "../world/lights/pointlight.h"
#include "../world/lights/directionallight.h"

#include "../world/objects/sceneobject.h"
#include "../world/objects/plane.h"
#include "../world/objects/aabb.h"

#define TO_F(i) static_cast<float>(i)

// these can be overwritten by specific scenes
#define DEFAULT_SCREEN_WIDTH 340.f
#define DEFAULT_SCREEN_HEIGHT 180.f
#define DEFAULT_MAX_CALCULATE_SHADING_RECURSIONS 10

#define SHADOW_BIAS 0.0001f
#define IMAGE_SCALING 1 // TODO: fix this

namespace brt
{
	renderer::renderer(raytracer* app) :
		m_application(app)
	{
		m_window = new sf::RenderWindow(sf::VideoMode(static_cast<int>(DEFAULT_SCREEN_WIDTH) * IMAGE_SCALING, static_cast<int>(DEFAULT_SCREEN_HEIGHT) * IMAGE_SCALING), "BUAS Ray Tracer - davidschep");
	}

	renderer::~renderer()
	{
		delete m_window;
	}

	void renderer::update(float)
	{
		// image order rendering
		for (int y = static_cast<int>(m_application->get_scene()->get_camera()->get_screen_height()) - 1; y >= 0; y--) // render order bottom right to top left
		{
			for (int x = 0; x < static_cast<int>(m_application->get_scene()->get_camera()->get_screen_width()); x++)
			{
				ray r = calculate_point_sample_ray(x, y);
				m_screenimage->setPixel(x, y, calculate_point_sample(r, 0).to_sf_color());
			}
		}

		// apply ray traced rendered image to screen
		sf::Texture screenTex;
		// screenTex.setSrgb(false); // default value is already 'false', when this is set to true no gamma correction is applied.
		screenTex.loadFromImage(*m_screenimage);
		sf::Sprite screenSprite(screenTex);
		screenSprite.setScale(static_cast<float>(IMAGE_SCALING), static_cast<float>(IMAGE_SCALING));
		m_window->draw(screenSprite); // this way all image data is send to the gpu at once
	}

	void renderer::set_resolution(unsigned int width, unsigned int height)
	{
		m_window->setSize(sf::Vector2u(width * IMAGE_SCALING, height * IMAGE_SCALING));
		if (m_screenimage)
		{
			delete m_screenimage;
		}
		m_screenimage = new sf::Image;
		m_screenimage->create(width, height, sf::Color::Magenta);
	}

	void renderer::window_clear() const
	{
		m_window->clear();
	}

	void renderer::window_display() const
	{
		m_window->display();
	}

	ray renderer::calculate_point_sample_ray(int x, int y) const
	{
		camera* cam = m_application->get_scene()->get_camera();

		float xoffset = (static_cast<float>(x) + 0.5f) / cam->get_screen_width() - 0.5f; // number from -0.5f to 0.5f
		float yoffset = (static_cast<float>(y) + 0.5f) / cam->get_screen_width() - (0.5f / cam->get_aspect_ratio()); // number from -0.5f/aspect to 0.5f/aspect
		vec3 raydir = (
			cam->get_cam_dir() +
			cam->get_cam_right() * xoffset +
			cam->get_cam_down() * yoffset).normalize();

		return ray(cam->position, raydir);
		// another way of calculation would be to have a "horizontalvec"*x/width added to "bottomleftpos" 
	}

	const color renderer::calculate_point_sample(ray & r, int recursivecount) const // TODO: ask: should I split this up into more functions (eg all case bodies into functions), or keep it like this. I hear arguments from both sides
	{
		intersection inter = m_application->get_scene()->check_for_intersection(r);

		if (inter.hasintersection)
		{
			sceneobject* obj = inter.object;
			std::shared_ptr<material> mat = obj->get_object_material();
			vec3 intersecpoint = inter.intersectionpoint; // only need there if there are lights in the scene, reason I calculate them here is because I only need to calculate them once
			vec3 normalat = obj->get_normal_at(intersecpoint);

			color col;

			switch (mat->m_mattype)
			{
			case (MTYPE_DEFAULT):
			{
				std::shared_ptr<materialdefault> matdef = std::static_pointer_cast<materialdefault>(mat);

				if (!matdef->m_refractive)
					col += calculate_ambient_shading(matdef->m_diffusecolor);

				std::vector<std::shared_ptr<light>> lights = m_application->get_scene()->get_lights();
				for (unsigned int i = 0; i < lights.size(); i++)
				{
					if (!lies_in_shadow(intersecpoint, obj, normalat, lights[i]))
					{
						vec3 unitlightdir = get_light_dir(lights[i], intersecpoint);

						if (!matdef->m_refractive)
						{
							col += calculate_lamberts_shading(matdef->m_diffusecolor, lights[i], normalat, unitlightdir);
						}

						if (matdef->m_specularintensity != 0.f)
						{
							col += calculate_phong_shading(obj, lights[i], normalat, unitlightdir, matdef->m_specularintensity, matdef->m_specularcolor);
						}
					}
				}

				if (recursivecount < DEFAULT_MAX_CALCULATE_SHADING_RECURSIONS)
				{
					if (matdef->m_refractive)
					{
						float kr = calculate_fresnel(r, normalat, matdef->m_refractiveindex);
						if (kr < 1)
						{
							col += calculate_refraction(recursivecount, r, normalat, intersecpoint, matdef->m_refractiveindex) *(1.f - kr);
						}
						col += calculate_ideal_reflection(recursivecount, r, normalat, intersecpoint) * kr;
					}
					else
					{
						if (matdef->m_reflectionintensity > 0.f)
						{
							col += calculate_ideal_reflection(recursivecount, r, normalat, intersecpoint) * matdef->m_reflectionintensity;
						}
					}
				} // else: ray keeps bouncing, just return ambient + Lambert's shading

				break;
			}
			case(MTYPE_PROCCHECKERBOARD):
			{
				std::shared_ptr<materialproccheckerboard> procmat = std::static_pointer_cast<materialproccheckerboard>(mat);
				float u, v; // TODO: these should be [0,1]
				u = obj->position.m_X - inter.intersectionpoint.m_X; // TODO: fix this, like planes, work in 3d
				v = obj->position.m_Z - inter.intersectionpoint.m_Z;
				sf::Color colatpoint = procmat->get_color_at(u, v);

				col += calculate_ambient_shading(colatpoint);

				std::vector<std::shared_ptr<light>> lights = m_application->get_scene()->get_lights();
				for (unsigned int i = 0; i < lights.size(); i++)
				{
					if (!lies_in_shadow(intersecpoint, obj, normalat, lights[i]))
					{
						col += calculate_lamberts_shading(colatpoint, lights[i], normalat, get_light_dir(lights[i], intersecpoint));
					}
				}
				break;
			}
			default:
				assert(false);
				break;
			}

			return col;
		}
		else
		{
			return SKYCOLOR;
		}
	}

	color renderer::calculate_ambient_shading(const sf::Color& colatpoint) const
	{
		return color(GLOBALAMBIENTCOLOR.m_r * TO_F(colatpoint.r), GLOBALAMBIENTCOLOR.m_g * TO_F(colatpoint.g), GLOBALAMBIENTCOLOR.m_b * TO_F(colatpoint.b)) / 255.f;
	}

	color renderer::calculate_lamberts_shading(const sf::Color& colatpoint, const std::shared_ptr<light> l, const vec3& unitsurfacenormal, const vec3& unitlightdir) const
	{
		float calclightintensityvalue = unitsurfacenormal.dot(unitlightdir);
		float calcdiffuseintensity = calclightintensityvalue > 0.f ? calclightintensityvalue : 0.f;

		return color(TO_F(colatpoint.r) * TO_F(l->get_light_color().m_r), TO_F(colatpoint.g) * TO_F(l->get_light_color().m_g), TO_F(colatpoint.b) * TO_F(l->get_light_color().m_b))
			/ 255.f * l->get_light_intensity() * calcdiffuseintensity;
	}

	color renderer::calculate_phong_shading(const sceneobject* obj, const std::shared_ptr<light> l, const vec3& unitsurfacenormal, const vec3& unitlightdir, const float specintensity, const sf::Color& speccol) const
	{
		vec3 unitintersectionpointtocam = (m_application->get_scene()->get_camera()->position - obj->position).normalize(); // unit ray from intersection point to camera position
		vec3 halfvec = (unitlightdir + unitintersectionpointtocam).normalize(); // halfvec = |b_mag|A + |a_mag|B ----- vectors are already normalized, length=1

		float calcspecintensityvalue = unitsurfacenormal.dot(halfvec);
		float calcspecintensity = calcspecintensityvalue > 0.f ? pow(calcspecintensityvalue, specintensity) : 0.f;

		return color(
			TO_F(speccol.r) * TO_F(l->get_light_color().m_r),
			TO_F(speccol.g) * TO_F(l->get_light_color().m_g),
			TO_F(speccol.b) * TO_F(l->get_light_color().m_b)) / 255.f * calcspecintensity;
	}

	color renderer::calculate_ideal_reflection(int recursivecount, const ray& r, const vec3& normalat, const vec3& intersecpoint) const
	{
		vec3 rstart = intersecpoint + normalat * 0.01f;
		vec3 rdir = mathlibrary::reflect(normalat, r.direction).normalize();
		ray reflectray(rstart, rdir);
		return color(calculate_point_sample(reflectray, recursivecount + 1));
	}

	color renderer::calculate_refraction(int recursivecount, const ray & r, const vec3 & normalat, const vec3& intersecpoint, const float refrectiveindex) const
	{
		vec3 normal = (r.direction.dot(normalat) < 0.f) ? normalat * -1.f : normalat; // if outside: normal * -1, else: normal
		vec3 start = intersecpoint + normal * 0.00001f;
		vec3 end = mathlibrary::refract(normalat, r.direction, refrectiveindex);
		ray refrectiver(start, end.normalize());
		return color(calculate_point_sample(refrectiver, recursivecount + 1));
	}

	float renderer::calculate_fresnel(const ray & r, const vec3 & normalat, const float refrectiveindex) const
	{
		// used scratchapixel for the formula
		// 100% reflective light at a 90 degree angle, center reflects ~6%

		float cost1 = r.direction.dot(normalat); // cos(theta1)

		float n1 = 1, n2 = refrectiveindex;
		if (cost1 > 0) { std::swap(n1, n2); } // swap if outside

		// compute sini using Snell's law, sin(o2)/sin(01) = v2/v1 = n1/n2
		float sint = n1 / n2 * sqrtf(std::max(0.f, 1.f - pow(cost1, 2))); // n1/n2*cos(theta1)
		if (sint >= 1) // going from a medium to another medium with a lower refraction index
		{
			return 1; // total internal reflection
		}
		else
		{
			float cost2 = sqrtf(std::max(0.f, 1.f - pow(sint, 2))); // cos(theta2)
			cost1 = fabsf(cost1);
			float frparallel = pow(((n2 * cost1) - (n1 * cost2)) / ((n2 * cost1) + (n1 * cost2)), 2);
			float frperpendicular = pow(((n1 * cost1) - (n2 * cost2)) / ((n1 * cost1) + (n2 * cost2)), 2);
			return (frparallel + frperpendicular) / 2.f; // Fr = 0.5(Frparallel*Frperpendicular)
		}
	}

	bool renderer::lies_in_shadow(const vec3& intersecpoint, const sceneobject* obj, const vec3& normalat, const std::shared_ptr<light> l) const
	{
		vec3 shadowrdir = (l->position - intersecpoint).normalize();
		ray shadowr(intersecpoint + normalat * SHADOW_BIAS, shadowrdir);
		intersection inter = m_application->get_scene()->check_for_intersection(shadowr);

		return (inter.hasintersection && inter.object != obj); // TODO: not casting shadow of itself, of course sometimes this is wanted, when?
	}

	vec3 renderer::get_light_dir(const std::shared_ptr<light> l, const vec3 & intersecpoint) const
	{
		switch (l->m_ltype)
		{
		case LTYPE_POINT:
			return std::static_pointer_cast<pointlight>(l)->get_light_dir(intersecpoint);
			break;
		case LTYPE_DIRECTIONAL:
			return std::static_pointer_cast<directionallight>(l)->get_light_dir();
			break;
		default:
			assert(false);
			return vec3();
			break;
		}
	}
}
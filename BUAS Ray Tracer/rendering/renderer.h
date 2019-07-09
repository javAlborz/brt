#pragma once
#include <memory>
#include <thread>

class vec3;

namespace sf
{
	class RenderWindow;
	class Color;
	class Image;
}

namespace brt
{
	struct ray;
	class scene;
	class raytracer;
	class sceneobject;
	class light;
	struct color;
	
	class renderer
	{
	public:
		explicit renderer(raytracer* app);
		~renderer();

		void update(float deltat);

		sf::RenderWindow* get_window() const { return m_window; }

		void set_resolution(unsigned int width, unsigned int height);

		const float get_aspect_ratio() const { return static_cast<float>(m_screenwidth) / static_cast<float>(m_screenheight); }
		const unsigned int get_screen_width() const { return m_screenwidth; }
		const unsigned int get_screen_height() const { return m_screenheight; }

		void window_clear() const;
		void window_display() const;

	private:
		void render();

		ray calculate_point_sample_ray(int x, int y) const;

		const color calculate_point_sample(ray& r, int recursivecount) const;

		color calculate_ambient_shading(const color& colatpoint) const;
		color calculate_lamberts_shading(const color& colatpoint, const std::shared_ptr<light> l, const vec3& unitsurfacenormal, const vec3& unitlightdir) const;
		color calculate_phong_shading(const sceneobject* obj, const std::shared_ptr<light> l, const vec3& unitsurfacenormal, const vec3& unitlightdir, const float specintensity, const color& speccol) const;
		color calculate_ideal_reflection(int recursivecount, const ray& r, const vec3& normalat, const vec3& intersecpoint) const;
		color calculate_refraction(int recursivecount, const ray& r, const vec3& normalat, const vec3& intersecpoint, const float refrectiveindex) const;
		float calculate_fresnel(const ray& r, const vec3& normalat, const float refrectiveindex) const;

		bool lies_in_shadow(const vec3& intersecpoint, const sceneobject* obj, const vec3& normalat, const std::shared_ptr<light> l) const;
		vec3 get_light_dir(const std::shared_ptr<light> l, const vec3& intersecpoint) const;

	private:
		raytracer* m_application;

		sf::RenderWindow* m_window;

		sf::Image* m_screenimage;

		std::thread m_renderThread;

		unsigned int m_screenwidth, m_screenheight;
	};
}
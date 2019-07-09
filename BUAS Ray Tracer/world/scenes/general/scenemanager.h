#pragma once

namespace brt
{
	enum class scenes
	{
		MAIN_MENU = 0,
		WHITTED,
		BOXES,
		TEST,
		ACCELERATION
	};

	class scene;
	class raytracer;

	class scenemanager
	{
	public:
		scenemanager(raytracer* application);
		~scenemanager();

		void update();
		void load_scene(scenes nextscene);
		scene* get_scene();

	private:
		void load_scene_internal(scene* s);

	private:
		raytracer* m_application;

		scene* m_scene;

		bool m_loadnewscene = false;
		scenes m_nextscene;
	};
}
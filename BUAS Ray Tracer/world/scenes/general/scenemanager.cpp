#include "scenemanager.h"

#include <../../10.0.10240.0/ucrt/stdio.h>

#include "../../../raytracer.h"

#include "../../../world/scenes/scenemainmenu.h"
#include "../../../world/scenes/scenewhitted.h"
#include "../../../world/scenes/sceneboxes.h"
#include "../../../world/scenes/scenetest.h"
#include "../../../world/scenes/sceneacceleration.h"


namespace brt
{
	scenemanager::scenemanager(raytracer* application) : m_application(application)
	{
	}

	scenemanager::~scenemanager()
	{
		if (m_scene)
		{
			delete(m_scene);
		}
	}

	void scenemanager::update()
	{
		if (m_loadnewscene)
		{
			m_loadnewscene = false;

			switch (m_nextscene)
			{
			case scenes::MAIN_MENU:
				load_scene_internal(new scenemainmenu(m_application));
				break;
			case scenes::WHITTED:
				load_scene_internal(new scenewhitted(m_application));
				break;
			case scenes::BOXES:
				load_scene_internal(new sceneboxes(m_application));
				break;
			case scenes::TEST:
				load_scene_internal(new scenetest(m_application));
				break;
			case scenes::ACCELERATION:
				load_scene_internal(new sceneacceleration(m_application));
				break;
			default:
				printf("scene not recognized.\n");
				break;
			}
		}
	}

	/// waits for frame finish and then loads scene
	void scenemanager::load_scene(scenes nextscene)
	{
		m_loadnewscene = true;
		m_nextscene = nextscene;
	}

	brt::scene* scenemanager::get_scene()
	{
		return m_scene;
	}

	void scenemanager::load_scene_internal(scene* s)
	{
		if (m_scene)
		{
			delete m_scene;
		}
		m_scene = s;
	}
}
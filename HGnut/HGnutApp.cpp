#include <hg.h>
#include <hg/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace hg {

	class HGnut: public Application
	{
	public:
		HGnut()
			: Application("HGnut")
		{
			PushLayer(new EditorLayer());
		}

		~HGnut()
		{
		}
	};

	Application* CreateApplication()
	{
		return new HGnut();
	}

}
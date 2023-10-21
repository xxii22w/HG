#include <hg.h>
#include <hg/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace hg {

	class HGnut: public Application
	{
	public:
		HGnut(ApplicationCommandLineArgs args)
			: Application("HGnut",args)
		{
			PushLayer(new EditorLayer());
		}

		~HGnut()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new HGnut(args);
	}

}
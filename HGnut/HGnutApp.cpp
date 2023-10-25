#include <hg.h>
#include <hg/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace hg {

	class HGnut: public Application
	{
	public:
		HGnut(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "HGnut";
		spec.CommandLineArgs = args;

		return new HGnut(spec);
	}

}
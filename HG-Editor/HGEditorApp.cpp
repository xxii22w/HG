#include <hg.h>
#include <hg/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace hg {

	class HGEditor : public Application
	{
	public:
		HGEditor()
			: Application("Hazel Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HGEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new HGEditor();
	}

}
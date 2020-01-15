#include "vgl.h"
#include "vapp.h"

BEGIN_APP_DECLARATION(OutputDebugInfo)
	virtual void OnKey(int key, int scancode, int action, int mods);
END_APP_DECLARATION()
DEFINE_APP(OutputDebugInfo, "glfw output debug info")

void OutputDebugInfo::OnKey(int key, int scancode, int action, int mods)
{
	char buf[512] = "";
	wsprintf(buf, "key=%d scancode=%d action=%d mods=%d\n", key, scancode, action, mods);
	OutputDebugString(buf);
}
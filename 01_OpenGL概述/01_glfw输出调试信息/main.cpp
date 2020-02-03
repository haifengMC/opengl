#include <sstream>

#include "vgl.h"
#include "vapp.h"
#include "tools.h"

BEGIN_APP_DECLARATION(OutputDebugInfo)
	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouse(int button, int action, int mods);
	virtual void OnCursor(double x, double y);
	virtual void OnDrop(int num, const char** file);
END_APP_DECLARATION()
DEFINE_APP(OutputDebugInfo, "glfw output debug info")

void OutputDebugInfo::OnKey(int key, int scancode, int action, int mods)
{
	std::ostringstream oss;
	oss << "key=" << key << " scancode=" << scancode << " action=" << action << " mods=" << mods << std::endl;
	OutputDebugString(oss.str().c_str());
}

void OutputDebugInfo::OnMouse(int button, int action, int mods)
{
	std::ostringstream oss;
	oss << "button=" << button << " action=" << action << " mods=" << mods << std::endl;
	OutputDebugString(oss.str().c_str());
}

void OutputDebugInfo::OnCursor(double x, double y)
{
	std::ostringstream oss;
	oss << "x=" << x << " y=" << y << std::endl;
	OutputDebugString(oss.str().c_str());
}

void OutputDebugInfo::OnDrop(int num, const char** file)
{
	for (size_t i = 0; i < num; ++i)
	{
		std::string tempStr;
		toANSI(file[i], tempStr);
		std::ostringstream oss;
		
		oss << i + 1 << " : " << tempStr << std::endl;
		OutputDebugString(oss.str().c_str());
	}
}
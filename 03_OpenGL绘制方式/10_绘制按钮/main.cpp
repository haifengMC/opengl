#include "global.h"

//#include "hTool.h"
//#include "hRect.h"
//#include "hObject.h"
//#include "hButton.h"
//
//#include "vgl.h"
//#include "vapp.h"
//#include "hConfig.h"
//
//#include "LoadShaders.h"
//#include "ButtonTest.h"
#include "hTime.h"

//DEFINE_APP(ButtonTest, "button test");

int main()
{
	std::cout << getNow() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << getNow() << std::endl;
	return 0;
}
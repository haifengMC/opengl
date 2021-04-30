#pragma once

class hAppBaseData
{
	GLFWwindow* _pWin = NULL;
	const hTimePoint _begTime;
	hRect _winRect;
	std::string _appName;

public:
	hAppBaseData(const hTimePoint& now) : _begTime(now) {}

	bool createWin();
	GLFWwindow* getWin() { return _pWin; }

	const hTimePoint& getBegTime() const { return _begTime; }
	const hRect& getRect() const { return _winRect; }
	const std::string& getName() const { return _appName; }
};
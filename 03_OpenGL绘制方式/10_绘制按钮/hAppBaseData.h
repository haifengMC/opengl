#pragma once

typedef std::chrono::time_point<std::chrono::steady_clock> hTimePoint;
class hAppBaseData
{
	GLFWwindow* _pWin = NULL;
	const hTimePoint _begTime;
	hRect _winRect;
	std::string _appName;

	uint32_t _prog = 0;
	std::unordered_map<uint32_t, std::string> _shaders;
	std::string _errMsg;
public:
	hAppBaseData(const hTimePoint& now) : _begTime(now) {}

	bool createWin();
	GLFWwindow* getWin() { return _pWin; }
	void resize(int width, int height);
	void setName(const char* name) { _appName = name; }
	void addShader(uint32_t type, const char* shade) { _shaders[type] = shade; }

	const hTimePoint& getBegTime() const { return _begTime; }
	const hRect& getRect() const { return _winRect; }
	hSize getSize() const { return _winRect.size(); }
	const std::string& getName() const { return _appName; }

	bool initOpenGL();

	void putInErr(const char* err) { _errMsg = err; }
	void putOutErr();
private:
	uint32_t loadShaders();
	const char* readShader(const std::string& filename);
};
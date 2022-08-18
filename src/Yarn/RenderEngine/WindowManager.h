/*
#pragma once

#include <hash_map>

#include "Window.h"

class WindowManager
{
public:
	WindowManager();
	unsigned int createWindow();
	void closeWindow(unsigned int id);
private:
	std::hash_map<unsigned int, Window*> window;
	unsigned int windowID = 0;
};
*/
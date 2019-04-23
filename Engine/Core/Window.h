#ifndef WINDOW_H
#define WINDOW_H

#include "Debug.h"

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <iostream>

#define GL3_PROTOTYPES 1

class Window {
public:
	// Make impossible do instantiate this class
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	Window();
	~Window();
	bool Init(std::string name_, int width_, int height_);
	void Shutdown();
	int GetHeight();
	int GetWidth();
	void SetAttributes();
	SDL_Window* GetWindow() const;
private:
	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context;
};
#endif // !WINDOW_H
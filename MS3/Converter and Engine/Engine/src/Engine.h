//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ENGINE_H
#define ENGINE_H

#ifdef WIN32
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#define WIN32_LEAN_AND_MEAN 1

#pragma warning( push )
#pragma warning( disable : 4255 )
#pragma warning( disable : 4820 )
#pragma warning( disable : 4668 )
#pragma warning( disable : 5039 )
#include <windows.h>
#pragma warning( pop )

#else
#include <unistd.h>
#define Sleep(t) sleep(t)
#endif

#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include "GLFW/glfw3.h"

#include "sb7ext.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define SB7_UNUSED_VAR(x) (void)x // Keenan

class Engine
{
public:
	Engine(const char *pWindowName, const int Width, const int Height);
	Engine(const Engine &) = delete;
	Engine &operator = (const Engine &) = delete;
	Engine() = delete;
	virtual ~Engine();

	void Run();

	virtual void Initialize();
	virtual void LoadContent() = 0;
	virtual void Update(float currentTime) = 0;
	virtual void Draw() = 0;
	virtual void UnLoadContent();

	// optional overloading
	virtual void ClearBufferFunc();

	int GetKey(int key);
	int GetMouseButton(int button);
	void GetCursorPos(float& xPos, float& yPos);

private:
	void privPreInitialize();
	void privPreLoadContent();

public:

	void setWindowTitle(const char *title);
	virtual void onResize(int w, int h);
	virtual void onKey(int key, int action);
	virtual void onMouseButton(int button, int action);
	virtual void onMouseMove(int x, int y);
	virtual void onMouseWheel(int pos);
	virtual void onDebugMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message);
	void getMousePosition(int &x, int &y);

public:
	struct APPINFO
	{
		char title[128];
		int windowWidth;
		int windowHeight;
		int majorVersion;
		int minorVersion;
		int samples;
		union
		{
			struct
			{
				unsigned int    fullscreen : 1;
				unsigned int    vsync : 1;
				unsigned int    cursor : 1;
				unsigned int    stereo : 1;
				unsigned int    debug : 1;
				unsigned int    robust : 1;
			};
			unsigned int        all;
		} flags;
	};

protected:
	APPINFO     info;
	static      Engine *app;
	GLFWwindow *window;

	static void glfw_onResize(GLFWwindow *window, int w, int h);
	static void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void glfw_onMouseButton(GLFWwindow *window, int button, int action, int mods);
	static void glfw_onMouseMove(GLFWwindow *window, double x, double y);
	static void glfw_onMouseWheel(GLFWwindow *window, double xoffset, double yoffset);
	void setVsync(bool enable);

private:
	static void APIENTRY debug_callback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message,
		GLvoid *userParam);
};

#endif

// --- End of File ---

#pragma once

#include "External/imgui/imgui.h"
#include "External/imgui/Backend/imgui_impl_glfw.h"
#include "External/imgui/Backend/imgui_impl_opengl3.h"
#include "External/GLFW/glfw3.h"
#include <iostream>

class Window {
public:
    bool Init();
    void BeginFrame();
    void EndFrame();
    void Shutdown();

    GLFWwindow* window = nullptr;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
};


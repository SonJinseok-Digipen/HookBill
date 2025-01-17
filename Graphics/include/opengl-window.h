#pragma once
#include<string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiHelper.h"
namespace HookBill_opengl
{    

	 int create_window(std::string windowname);
	 void update_window();
	 bool ShouldCloseWindow();
	 void shutdown_window();
	 void set_window_user_pointer(void* user_data);

	

	 inline GLFWwindow* window_ptr;




}
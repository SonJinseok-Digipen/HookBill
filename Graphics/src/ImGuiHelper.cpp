/*
 * Rudy Castan
 * CS200
 * Fall 2022
 */

#include "ImGuiHelper.h"
#include"glad/glad.h"
#include<GLFW/glfw3.h>
#include<Imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include<string>

namespace ImGuiHelper
{
    void Initialize(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        {
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }
  
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130"); // or "#version 330" depending on OpenGL version
    }


    void Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void End(GLFWwindow* window)
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_context = glfwGetCurrentContext(); // 현재 OpenGL 컨텍스트 백업
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_context); // 원래 컨텍스트로 복원
        }

        glfwSwapBuffers(window); // 항상 SwapBuffers 호출
    }




    void ShutDown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }



   


}

#pragma once
#include"GameState.h"
#include"Engine.h"
#include"ImGuiHelper.h"
#include"GLVertexArray.h"
#include <GLShader.h>

namespace HookBill
{
	class TestLevel :public GameState
	{
	public:
		TestLevel();
		void Load();
		void Update();
		void Draw();
		void ImGuiDraw();
		void Unload();
		std::string GetName() { return "test level"; }
	private:
		InputKey key;
		GLVertexArray left_eye_model;
		GLShader shader;
	};
}
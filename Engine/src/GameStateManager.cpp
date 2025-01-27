#include"GaemStateManager.h"
#include"Engine.h"
namespace HookBill
{
	ImVec2 ToImGuiCoordinates(float glfwX, float glfwY, float screenHeight)
	{
		// GLFW의 Y 좌표는 화면의 위쪽에서 증가하므로, ImGui에서는 Y 좌표를 반전시켜야 합니다.
		float imguiY = screenHeight - glfwY;
		return ImVec2(glfwX, imguiY);
	}
	GameStateManager::GameStateManager() :currGameState(nullptr),
		nextGameState(nullptr), state(State::START)
	{

	}

	void GameStateManager::AddGameState(GameState& gameState)
	{
		gameStates.push_back(&gameState);
	}

	void GameStateManager::Update()
	{

		switch (state)
		{
		case State::START:
			if (gameStates.empty() == true)
			{
				Engine::GetLogger().LogError("No Game States!!");
				state = State::EXIT;
			}
			else
			{
				nextGameState = gameStates[0];
				state = State::LOAD;
			}
			break;
		case State::LOAD:
			currGameState = nextGameState;

			Engine::GetWindow().InitializeFrameBuffer(1920, 1080);

			Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
			currGameState->Load();
			Engine::GetLogger().LogEvent("Load Complete");
			state = State::UPDATE;
			break;
		case State::UPDATE:
			if (currGameState != nextGameState)
			{
				state = State::UNLOAD;
			}

			else
			{
				currGameState->Update();

				ImGuiHelper::Begin();
				ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_MenuBar |*/ ImGuiWindowFlags_NoDocking;

			    //이거 있어야 전체를 독스페이스로 씀 
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse  /*ImGuiWindowFlags_NoResize*/ | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

				
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				ImGui::Begin("DockSpace Window", nullptr, window_flags);
				ImGui::PopStyleVar(2);

				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
				{
					ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
				}

				ImGui::End();



				glBindFramebuffer(GL_FRAMEBUFFER, HookBill_opengl::fbo);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 장면 지우기

				currGameState->Draw();
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

				ImGui::Begin("Scene View");
				ImVec2 pos = ImGui::GetCursorScreenPos();
				ImGui::GetWindowDrawList()->AddImage(
					HookBill_opengl::texture,
					ImVec2(pos.x, pos.y),
					ImVec2(pos.x +1920, pos.y + 1080),
					ImVec2(0, 1),
					ImVec2(1, 0)
				);

				ImGui::End();





				currGameState->ImGuiDraw();
				ImGuiHelper::End(Engine::GetWindow().Get_OpenGL_Window_ptr());

								//	Engine::GetLogger().LogEvent("Updateing !!! ");

			}

			break;
		case State::UNLOAD:
			Engine::GetLogger().LogEvent("UnLoad " + currGameState->GetName());
			currGameState->Unload();
			if (nextGameState == nullptr)
			{
				state = State::SHUTDOWN;

			}
			else
			{
				state = State::LOAD;

			}
			break;
		case State::SHUTDOWN:
			state = State::EXIT;
			break;
		case State::EXIT:
			break;
		}
	}

	void GameStateManager::SetNextState(int initState)
	{
		nextGameState = gameStates[initState];
	}

	void GameStateManager::Shutdown()
	{
		nextGameState = nullptr;
	}

	void GameStateManager::ReloadState()
	{
		state = State::UNLOAD;
	}


}

#include "../../Fontz.h"
Color cvet = Color(0, (0xFF / 2), 0xFF, 0xFF);
#include <d3d9.h>
#include <dinput.h>
#include <d3dx9tex.h>
bool followbotcheck = 1;


namespace Menu
{
	char lt[100] = "";
	
	bool initialised = false;
	bool opened = false;
	bool InsertDown = false;
	int n_open = 0;
	static char cfgname[32] = "default";

	void morphBtnActiveTab()
	{
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Button] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
	}

	void morphBtnNormalTab()
	{
		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Button] = ImColor(40, 42, 47, 255);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(40, 42, 47, 255);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(40, 42, 47, 255);
		style.Colors[ImGuiCol_Text] = ImColor(140, 140, 140, 255);

	}
	static int tab = 1;
	void drawMenu()
	{
		ImVec2 menu_pos;

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();


		ImVec2 pos = ImGui::GetWindowPos();

		
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.7f);
		style.Colors[ImGuiCol_Border] = ImVec4(0, 0, 0, 0.f);
		int screen_width, screen_height;
		engine()->GetScreenSize(screen_width, screen_height);

		ImGui::SetNextWindowSize(ImVec2(880, 520));
		ImGui::Begin("KV", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		{

			//ImGui::PushFont(gFontz.eagle);
			//style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			//ImGui::MyButton("a", true, ImVec2(880, 95));
			//ImGui::PopFont();

			//style.ItemSpacing = ImVec2(0, 0);
			//ImGui::PushFont(gFontz.NCCIcon);
			//style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			//ImGui::MyButton("A", true, ImVec2(855, 80));
			//ImGui::PopFont();

			ImGui::PushFont(gFontz.feagle);
			
			if (tab == 0) morphBtnActiveTab(); else morphBtnNormalTab();
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			if (ImGui::MyButton("b", true, ImVec2(128, 50))) tab = 0;
			
			ImGui::SameLine();
			if (tab == 1) morphBtnActiveTab(); else morphBtnNormalTab();
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			if (ImGui::MyButton("c", true, ImVec2(128, 50))) tab = 1;
			ImGui::SameLine();

			if (tab == 2) morphBtnActiveTab(); else morphBtnNormalTab();
			style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
			if (ImGui::MyButton("d", true, ImVec2(128, 50))) tab = 2;

			ImGui::PopFont();
			ImGui::PushFont(gFontz.Text);
			
			if (tab == 0)
			{

				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("");
				
				ImGui::BeginChildNew("Ragebot", ImVec2(290, -1), true, ImGuiWindowFlags_ChildZeus);
				{
					ImGui::Spacing();
					ImGui::Spacing();

					ImGui::Checkbox("Enabled", &HackVars::Aimbot::Enabled);
					ImGui::Hotkey("Hotkey", &HackVars::Aimbot::Hotkey);
					ImGui::Checkbox("Enemy Only", &HackVars::Aimbot::EnemyOnly);
					ImGui::PushItemWidth(150.0f);

					ImGui::SliderInt("FOV", &HackVars::Aimbot::FOV, 0, 360);
					ImGui::Checkbox("Silent Aim", &HackVars::Aimbot::Silent);
					ImGui::Checkbox("Autoshoot", &HackVars::Aimbot::Autoshoot);
				}
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChildNew("Other", ImVec2(270, -1), true, ImGuiWindowFlags_ChildZeus);
				{
					ImGui::Checkbox("Draw Target", &HackVars::Visuals::Aimbot::DrawTarget);
					ImGui::Checkbox("Draw FOV", &HackVars::Visuals::Aimbot::FOVCircle);
				}
				ImGui::EndChild();
				
			}
			
			if (tab == 1)
			{
				ImGui::Spacing();
				ImGui::Spacing();


				ImGui::Text("");
				ImGui::BeginChildNew("ESP", ImVec2(285, -1), true, ImGuiWindowFlags_ChildZeus);
				{
					ImGui::Spacing();
					ImGui::Spacing();

					ImGui::Checkbox("Enabled", &HackVars::Visuals::Enabled);
					ImGui::SliderFloat("Draw delay", &HackVars::Visuals::DrawDelay, 0.0, 0.05, "%.3f", 1.0);
					ImGui::Checkbox("Enemy Only", &HackVars::Visuals::ESP::EnemyOnly);

					ImGui::PushItemWidth(150.0f);

					ImGui::Checkbox("Box", &HackVars::Visuals::ESP::PlayerBox);
					ImGui::SameLine();
					ImGui::MyColorEdit4("###boxcolor", HackVars::Visuals::ESP::fPBoxColor, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);

					const char* BoxStyles[]
					{
						"Normal",
						"Corner"
					};

					ImGui::Text("Box Style");
					ImGui::Combo("##boxstyle", &HackVars::Visuals::ESP::PlayerBoxStyle, BoxStyles, ARRAYSIZE(BoxStyles));

					ImGui::Checkbox("Player name", &HackVars::Visuals::ESP::PlayerDrawname);
					ImGui::Checkbox("Health", &HackVars::Visuals::ESP::PlayerDrawHealth);
					//ImGui::Checkbox("Health Bar", &HackVars::Visuals::ESP::PlayerDrawHealthBar);

					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("Chams", &HackVars::Visuals::ESP::PlayerChamsEnabled);
					ImGui::SameLine();
					ImGui::MyColorEdit4("###chamscolor", HackVars::Visuals::ESP::fVPlayerChamsColor, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);

					const char* ChamStyles[]
					{
						"Normal",
						"Flat",
						"Wireframe"
					};

					ImGui::Text("Chams Style");
					ImGui::Combo("##chamsstyle", &HackVars::Visuals::ESP::PlayerChamsStyle, ChamStyles, ARRAYSIZE(ChamStyles));
					ImGui::Checkbox("XQZ", &HackVars::Visuals::ESP::PlayerXQZ);
					ImGui::SameLine();
					ImGui::MyColorEdit4("###chamsxqzcolor", HackVars::Visuals::ESP::fNVPlayerChamsColor, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);

					//ImGui::Checkbox("Entity chams", &HackVars::Visuals::ESP::EntityChams);
					ImGui::Checkbox("Entity box", &HackVars::Visuals::ESP::EntityBox);
					ImGui::SameLine();
					ImGui::MyColorEdit4("###EntityBoxColor", HackVars::Visuals::ESP::EntityBoxColor, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);
					ImGui::Separator();
					ImGui::Separator();
					ImGui::Separator();
					//ImGui::Spacing();
					ImGui::BeginChildNew("entity list", ImVec2(150, 100), true, ImGuiWindowFlags_ChildZeus);
					ImGui::Columns();
					for (int i = 0; i < ENTITY_MAX; i++)
					{
						if (HackVars::Visuals::ESP::wtf[i][0] == '\0')
							continue;
						if (ImGui::Selectable(HackVars::Visuals::ESP::wtf[i]))
							for (int ia = 0; ia < ENTITY_MAX; ia++)
							{
								if (HackVars::Visuals::ESP::meow[ia][0] == '\0')
								{
									for (int ib = 0; ib < ENTITY_NAME_MAX; ib++)
									{
										HackVars::Visuals::ESP::meow[ia][ib] = HackVars::Visuals::ESP::wtf[i][ib];
										HackVars::Visuals::ESP::wtf[i][ib] = '\0';
									}
									break;
								}
							}						//meow[i] = wtf[i];
					}
					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChildNew("entity esp", ImVec2(150, 100), true, ImGuiWindowFlags_ChildZeus);
					ImGui::NextColumn();
					for (int i = 0; i< ENTITY_MAX; i++)
					{
						if (HackVars::Visuals::ESP::meow[i][0] == '\0')
							continue;
						if(ImGui::Selectable(HackVars::Visuals::ESP::meow[i]))
							for (int ia = 0; ia < ENTITY_MAX; ia++)
							{
								if (HackVars::Visuals::ESP::wtf[ia][0] == '\0')
								{
									for (int ib = 0; ib < ENTITY_NAME_MAX; ib++)
									{
										HackVars::Visuals::ESP::wtf[ia][ib] = HackVars::Visuals::ESP::meow[i][ib];
										HackVars::Visuals::ESP::meow[i][ib] = '\0';
									}
									break;
								}
							}
					}
					ImGui::Columns();
					ImGui::EndChild();

				}
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChildNew("Others", ImVec2(285, -1), true, ImGuiWindowFlags_ChildZeus);
				{
					ImGui::Checkbox("Nightmode", &HackVars::Visuals::Nightmode);

					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Hotkey("Thirdperson", &HackVars::Visuals::RenderView::Thirdperson);
					ImGui::SliderInt("Thirdperson Distance", &HackVars::Visuals::RenderView::ThirdPersonDistance, 0, 500);

					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("FOV Changer", &HackVars::Visuals::RenderView::FOVEnabled);
					ImGui::SliderInt("FOV", &HackVars::Visuals::RenderView::FOV, 0, 180);
					ImGui::Checkbox("Viewmodel FOV Changer", &HackVars::Visuals::RenderView::ViewModelFOVEnabled);
					ImGui::SliderInt("Viewmodel FOV", &HackVars::Visuals::RenderView::ViewModelFOV, 0, 180);

					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("Wireframe Hands", &HackVars::Visuals::WireframeHands);
					ImGui::SameLine();
					ImGui::MyColorEdit4("###wireframehandscolor", HackVars::Visuals::ESP::WireframeHandsColor, ImGuiColorEditFlags_Alpha | ImGuiColorEditFlags_NoSliders);

					ImGui::Checkbox("Hitmarker", &HackVars::Visuals::Hitmarker);


					ImGui::Separator();
					ImGui::Spacing();
#ifndef trashout
					ImGui::Checkbox("targetObsInfo", &HackVars::Visuals::TargetObsInfo);
#endif
					ImGui::Separator();

					//bool boolka = false;
					ImGui::Checkbox("target model name", &HackVars::Visuals::ESP::TargetInfo);
					ImGui::Spacing();
					const char* sv[3] = { "client","server","menu" };
					ImGui::Combo("lua interface", &HackVars::Visuals::ESP::LuaIntType, sv, ARRAYSIZE(sv));
					ImGui::Checkbox("lua autoreload", &HackVars::Misc::lua_autoreload); //client 0 server 1 menu 2
					
					//ImGui::Checkbox("respawn",)
					
				}
			
				ImGui::EndChild();
			}

			if (tab == 2)
			{
				ImGui::Spacing();
				ImGui::Spacing();


				ImGui::Text("");
				ImGui::BeginChildNew("Misc", ImVec2(285, -1), true, ImGuiWindowFlags_ChildZeus);
				{
					ImGui::Spacing();
					ImGui::Spacing();

					ImGui::Checkbox("Bunnyhop", &HackVars::Misc::Bunnyhop);

					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("Followbot", &HackVars::Misc::FollowBot::Enabled);
					if (HackVars::Misc::FollowBot::Enabled == false)
						followbotcheck = true;

					if (HackVars::Misc::FollowBot::Enabled)
					{
						if (followbotcheck)
							followbotcheck = false;
						
						ImGui::Hotkey(" > Key", &HackVars::Misc::FollowBot::Key);

						ImGui::SliderFloat(" > Max Distance", &HackVars::Misc::FollowBot::MaxDist, 0.0f, 1000.f, ("%.1f"));
						ImGui::SliderFloat(" > Min Distance", &HackVars::Misc::FollowBot::MinDist, 0.0f, 1000.f, ("%.1f"));
					}
					
					
				}
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChildNew("Accuracy", ImVec2(285, -1), true, ImGuiWindowFlags_ChildZeus);
				{
					ImGui::Checkbox("Nospread", &HackVars::Aimbot::Nospread);

				}
				ImGui::EndChild();
			}


			if (tab == 3)
			{
				//Placeholder
			}
			ImGui::PopFont();

		}
		ImGui::End();
	}


	void OpenMenuThing()
	{
		if (InsertDown)
		{
			n_open++;
			if (n_open == 1)
			{
				opened = !opened;
			}
		}
		else
			n_open = 0;
	}
};
typedef void(__thiscall* PaintTraverseFn)(void*, vgui::VPanel*, bool, bool);
PaintTraverseFn orgPaintTraverse = nullptr;

#include "../../../shit/ILuaObject.hpp"
const char scr[] = "function func() local ply = LocalPlayer() if (!IsValid(ply)) then return false end\
				  local view = ply:GetViewEntity() if (view : IsPlayer()) then return view : GetEyeTrace().Entity\
					else return nil end end if (CLIENT) then local ent = func() if ent then local temp = ent:GetPos()\
					 + ent : OBBCenter() local vec2 = temp : ToScreen() vec2.x = vec2.x + 15 draw.DrawText(ent : GetModel(),\
						 \"DermaDefault\",vec2.x, vec2.y) end end";

const char nametag_and_health[] = "local screen = {} local hgh = 25 local distanceX = 100 local distanceY = 25 local arr = {} local Scry = surface.ScreenHeight() \
for k, ply in pairs(player.GetAll()) do local ent = ply:GetViewEntity() temp = ent : GetPos() + ent : OBBCenter() local vec2 = temp : ToScreen() vec2.x = vec2.x \
local str = \"\" for k, v in pairs(screen) do str = \"\" if v ~= nil then local w = v.y - vec2.y local q = v.x - vec2.x \
if w > -distanceY and w < distanceY and q > -distanceX/2 and q < distanceX then \
local offset = tonumber((vec2.y / Scry) * 10) if arr[offset] == nil then arr[offset] = 1 end vec2.y = v.y + hgh * arr[offset] \
arr[offset] = arr[offset] + 1 end end end \
screen[k] = {} screen[k] = vec2 local obb = ent:GetPos() + ent : OBBCenter() \
local pos = obb : ToScreen() surface.SetDrawColor(team.GetColor(ply:Team())) surface.DrawLine(pos.x, pos.y, vec2.x, vec2.y) \
draw.DrawText(ply : GetName()..\"\\n\"..ply : Health(),\"DebugFixed\", vec2.x, vec2.y, team.GetColor(ply : Team())) end"; //--surface.DrawRect(vec2.x, vec2.y, distanceX, distanceY) 

const char nametag[] = "local screen = {} local hgh = 25 local distanceX = 100 local distanceY = 25 local arr = {} local Scry = surface.ScreenHeight() \
for k, ply in pairs(player.GetAll()) do local ent = ply:GetViewEntity() temp = ent : GetPos() + ent : OBBCenter() local vec2 = temp : ToScreen() vec2.x = vec2.x \
local str = \"\" for k, v in pairs(screen) do str = \"\" if v ~= nil then local w = v.y - vec2.y local q = v.x - vec2.x \
if w > -distanceY and w < distanceY and q > -distanceX/2 and q < distanceX then \
local offset = tonumber((vec2.y / Scry) * 10) if arr[offset] == nil then arr[offset] = 1 end vec2.y = v.y + hgh * arr[offset] \
arr[offset] = arr[offset] + 1 end end end \
screen[k] = {} screen[k] = vec2 local obb = ent:GetPos() + ent : OBBCenter() \
local pos = obb : ToScreen() surface.SetDrawColor(team.GetColor(ply:Team())) surface.DrawLine(pos.x, pos.y, vec2.x, vec2.y) \
draw.DrawText(ply : GetName(),\"DebugFixed\", vec2.x, vec2.y, team.GetColor(ply : Team())) end"; //--surface.DrawRect(vec2.x, vec2.y, distanceX, distanceY) 

bool _init_hack = 1;
FILETIME sft[3];
char* script = 0;
int bla = 0;
bool isOk = false;
#ifndef trashout
void func()
{
	cliententitylist()->GetClientEntity(2261794);

}
#endif


float timer = 0;

void __fastcall hkPaintTraverse(void* ecx, void* edx, vgui::VPanel* vguiPanel, bool forceRepaint, bool allowForce)
{
	orgPaintTraverse(ecx, vguiPanel, forceRepaint, allowForce);

#ifndef trashout
	bla++;
	if (bla > 1000)
	{
		bla = 0;
		CVar()->ConsolePrintf("%x\n\n", func);
		func();
	}
#endif

	static BYTE* IsRecordingMovie = *(BYTE**)(Util::Pattern::FindPattern("engine.dll", "55 8B EC A1 ? ? ? ? 81 EC ? ? ? ? D9 45 18"/*CL_StartMovie*/) + 0x3E);
	if (engine()->IsTakingScreenshot() || *IsRecordingMovie) // steam screenshot & startmovie checks
		return; //

	if (!engine()->IsInGame() || (strcmp(Interfaces::IPanel()->GetName(vguiPanel), "HudGMOD")))
		return;
	GarrysMod::Lua::ILuaBase* lptr = LuaShared()->GetLuaInterface(0); // //(Client)0, (Server)1, (Menu)2
	



	if (HackVars::Misc::lua_autoreload)
	{

		wchar_t wspath[260] = L"snezhkin_autorun\\test.txt";

		if (_init_hack)
		{
			script = (char*)malloc(0xFFFF);
			if (script == NULL)
				goto naxui;
			_init_hack = 0;
			memset(script, 0, 0xFFFF);
		}
		DWORD trashbox;
		////------------------



		if (!_init_hack)
		{
			//Sleep(500);

			HANDLE file = CreateFileW(wspath, GENERIC_READ, 3, 0, 3, 0x80, 0);
			if (file == INVALID_HANDLE_VALUE)
			{
				//error processing
				goto naxui;
			}

			FILETIME ft[3];
			if (!GetFileTime(file, &ft[0], &ft[1], &ft[2]))
			{
				//another error processing
				goto naxui;
			}
			GarrysMod::Lua::ILuaBase* lptr;
			if (ft[2].dwHighDateTime != sft[2].dwHighDateTime || ft[2].dwLowDateTime != sft[2].dwLowDateTime)
			{
				sft[2].dwHighDateTime = ft[2].dwHighDateTime;
				sft[2].dwLowDateTime = ft[2].dwLowDateTime;
				//cout << "\nreloading\n";
				memset(script, 0, 0xFFFF);
				if (!ReadFile(file, script, 0xFFFF, &trashbox, 0))
				{
					//another error processing
					goto naxui;
				}


				switch (HackVars::Visuals::ESP::LuaIntType)
				{
				case 0:
					lptr = LuaShared()->GetLuaInterface(0); // //(Client)0, (Server)1, (Menu)2
					break;

				case 1:
					lptr = LuaShared()->GetLuaInterface(1); // //(Client)0, (Server)1, (Menu)2
					break;

				case 2:
					lptr = LuaShared()->GetLuaInterface(2); // //(Client)0, (Server)1, (Menu)2
					break;

				}

				isOk = lptr->RunString("", "", script, 1, 1);
				goto zaebis;
				//cout << script << endl;
			}
			if (isOk)
			{
				switch (HackVars::Visuals::ESP::LuaIntType)
				{
				case 0:
					lptr = LuaShared()->GetLuaInterface(0); // //(Client)0, (Server)1, (Menu)2
					break;

				case 1:
					lptr = LuaShared()->GetLuaInterface(1); // //(Client)0, (Server)1, (Menu)2
					break;

				case 2:
					lptr = LuaShared()->GetLuaInterface(2); // //(Client)0, (Server)1, (Menu)2
					break;

				}
				isOk = lptr->RunString("", "", script, 1, 1);
			}
		zaebis:
			CloseHandle(file);
		}
		goto kydanibyd;
	naxui:
		CVar()->ConsolePrintf("OIIIIIIIIIIIIIIIIIIIIIII");

	}
kydanibyd:
	BaseEntity* LocalPlayer = (BaseEntity*)cliententitylist()->GetClientEntity(engine()->GetLocalPlayer());
#ifndef trashout
	if (HackVars::Visuals::TargetObsInfo)
	{
		func();
		//HackVars::Visuals::TargetObsInfo = false;
	}
	/*
	if (LocalPlayer)
	{
		engine()->
	}*/

	//BaseEntity* you = (BaseEntity*)renderview()->GetViewEntity();


	/*
	if (you)
	{
		//Vector Pos = you->GetRenderOrigin();

		//auto& frame = *reinterpret_cast<matrix3x4_t*>(reinterpret_cast<uintptr_t>(you) + 0x308);

		//Vector min = Pos + you->CollisionMins();
		//Vector max = Pos + you->CollisionMaxs();

		//Vector points[] = { Vector(min.x, min.y, min.z),
		//			Vector(min.x, max.y, min.z),
		//			Vector(max.x, max.y, min.z),
		//			Vector(max.x, min.y, min.z),
		//			Vector(max.x, max.y, max.z),
		//			Vector(min.x, max.y, max.z),
		//			Vector(min.x, min.y, max.z),
		//			Vector(max.x, min.y, max.z) };

		//Vector vTransformed[8];

		//Vector2D flb;
		//Vector2D brt;
		//Vector2D blb;
		//Vector2D frt;

		//Vector2D frb;
		//Vector2D brb;
		//Vector2D blt;
		//Vector2D flt;

		//int iY = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//if (!H::Util::Math::WorldToScreen(points[0], blb) || !H::Util::Math::WorldToScreen(points[1], brb) || !H::Util::Math::WorldToScreen(points[2], frb) || !H::Util::Math::WorldToScreen(points[3], flb) ||
		//	!H::Util::Math::WorldToScreen(points[4], frt) || !H::Util::Math::WorldToScreen(points[5], brt) || !H::Util::Math::WorldToScreen(points[6], blt) || !H::Util::Math::WorldToScreen(points[7], flt))
			//return;

		//if (!H::Util::Math::WorldToScreen(points[3], flb) || !H::Util::Math::WorldToScreen(points[5], brt)
		//	|| !H::Util::Math::WorldToScreen(points[0], blb) || !H::Util::Math::WorldToScreen(points[4], frt)
		//	|| !H::Util::Math::WorldToScreen(points[2], frb) || !H::Util::Math::WorldToScreen(points[1], brb)
		//	|| !H::Util::Math::WorldToScreen(points[6], blt) || !H::Util::Math::WorldToScreen(points[7], flt))
		//	return;

		//Vector2D arr[] = { blb,brb,frb,flb,frt,brt,blt,flt };
		//float left = flb.x;
		//float top = flb.y;
		//float right = flb.x;
		//float bottom = flb.y;

		//for (int i = 1; i < 8; i++)
		//{
		//	if (left > arr[i].x)
		//		left = arr[i].x;
		//	if (top < arr[i].y)
		//		top = arr[i].y;
		//	if (right < arr[i].x)
		//		right = arr[i].x;
		//	if (bottom > arr[i].y)
		//		bottom = arr[i].y;
		//}

		//float x = left;
		//float y = bottom;
		//float w = right - left;
		//float h = top - bottom;

		//x += ((right - left) / 8); //pseudo fix for those THICC boxes
		//w -= ((right - left) / 8) * 2;

		///////////////////////////////////////////////////////////////////////////////////////

		if (0 == 1)
		{
			if (you->GetLuaName())
			{
				H::Draw::Drawtext(you->GetLuaName(), 1, x + w + 2, y + iY);
				iY += 15;
			}
			if (you->GetLuaScriptName())
			{
				H::Draw::Drawtext(you->GetLuaScriptName(), 1, x + w + 2, y + iY);
				iY += 15;
			}
			if (you->GetHealth())
			{
				H::Draw::Drawtext(std::to_string(you->GetHealth()).c_str(), 1, x + w + 2, y + iY);
				iY += 15;
			}
			if (you->IsAlive())
			{
				H::Draw::Drawtext("ALIVE", 1, x + w + 2, y + iY);
				iY += 15;
			}
			if (you->IsHands())
			{
				H::Draw::Drawtext("HANDS", 1, x + w + 2, y + iY);
				iY += 15;
			}
			if (you->IsVehicle())
			{
				H::Draw::Drawtext("VEHICLE", 1, x + w + 2, y + iY);
				iY += 15;
			}




}
		//TODO: доделотб блинб
	}
	*/
#endif
	if (!LocalPlayer)
		return;

	if (HackVars::Visuals::Hitmarker)
		hitmarker::singleton()->on_paint();

	if (HackVars::Visuals::Aimbot::FOVCircle)
		H::ESP::FovCircle(HackVars::Aimbot::FOV);

	if (HackVars::Visuals::Aimbot::DrawTarget)
		H::ESP::DrawAimbotTarget();



	if (HackVars::Visuals::Nightmode)
		H::ESP::NightMode();

	/*
	* for (int i = 0; i < ENTITY_MAX; i++)
				{
					if (HackVars::Visuals::ESP::wtf[i][0] == '\0')
					{
						memcpy_s(HackVars::Visuals::ESP::wtf[i], 256, player->GetLuaName(), 256);
						break;
					}
				}

	*/

	if (HackVars::Visuals::Enabled && engine()->Time() - timer > HackVars::Visuals::DrawDelay)
	{
		timer = engine()->Time();
		if (HackVars::Visuals::ESP::PlayerDrawname && HackVars::Visuals::ESP::PlayerDrawHealth)
		{
			lptr->RunString("", "", nametag_and_health, 1, 1);
		}
		else if (HackVars::Visuals::ESP::PlayerDrawname)
			lptr->RunString("", "", nametag, 1, 1);

	for (int i = 0; i < cliententitylist()->GetHighestEntityIndex(); i++)
	{

		BaseEntity* ent = (BaseEntity*)cliententitylist()->GetClientEntity(i);
		if (!ent || ent->IsDormant())
			continue;
#ifndef trashout
		if (ent->IsClientCreated())
			H::ESP::DrawSomeExtraInfo(ent);
#endif
		if ((ent->UsesLua() && !ent->hasowner() && (HackVars::Visuals::ESP::LuaESP && HackVars::Visuals::ESP::LuaBox || HackVars::Visuals::ESP::LuaESP && HackVars::Visuals::ESP::LuaDrawHealth || HackVars::Visuals::ESP::LuaESP && HackVars::Visuals::ESP::LuaDrawName)))
			H::ESP::DrawBoundingBox(ent);
	}
	

		for (int i = 0; i <= globals()->maxClients; i++)
		{

			BaseEntity* player = (BaseEntity*)cliententitylist()->GetClientEntity(i);
			/*
			for (int i = 0; i < ENTITY_MAX; i++)
			{
				if (HackVars::Visuals::ESP::wtf[i][0] == '\0')
				{
					memcpy_s(HackVars::Visuals::ESP::wtf[i], 256, player->getname, 256);
					break;
				}
			}
			*/
			//if(*(char*)player->Lua_GetLuaClass() != '\0')
			//CVar()->ConsolePrintf("%s\n", player->Lua_GetLuaClass()); -- разобраться

			if (!player || player->IsDormant())
				continue;

			if (player == LocalPlayer || !player->IsAlive())
				continue;



			if (HackVars::Visuals::ESP::EnemyOnly && player->GetTeam() == LocalPlayer->GetTeam())
				continue;

			if (player->ShouldDraw()) {
				if (HackVars::Visuals::ESP::PlayerBox || HackVars::Visuals::Enabled && HackVars::Visuals::ESP::PlayerDrawHealth || HackVars::Visuals::Enabled && HackVars::Visuals::ESP::PlayerDrawHealth)
					H::ESP::DrawBoundingBox(player);
			}
		}
	}
}

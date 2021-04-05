#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <tlhelp32.h>
#include <process.h>
#include <stdint.h>
#include <string>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

using namespace std;

LPD3DXFONT pFont;
#include "Misc.h"
#include "Xor.h"
#include "Addr.h"
#include "Menu.h"
#include "Class.h"
#include "Esp.h"
#include "version.h"
#include "Alter.h"

DWORD esAddr;
DWORD esRet; //+0x5
DWORD DIP_hook;
DWORD DIP_return;

bool hooked = false;

char *opt_OnOff[]   = {"[OFF]", "[ON]"};
char *opt_OnOff2[]   = {"[AUTO]", "[AUTO]"};
char *opt_HeadShot[]= {"[OFF]","[NORMAL]","[GOLDEN]"};
void ErstelleMenu (LPDIRECT3DDEVICE9 pDevice)
{
	if(GetAsyncKeyState(VK_INSERT)&1) 
		Show = !Show;

	if(Show)
	{
		if(GetAsyncKeyState(VK_UP)&1)
			MenuSelection--;

		if(GetAsyncKeyState(VK_DOWN)&1) 
			MenuSelection++;

		DrawBox(pDevice, 20, 15, 190, 20, 2, TGray, TBlack);
		cWriteText(110, 18, D3DCOLOR_ARGB(255, 255, 255, 153), "Bash Pub Hack V1");
		DrawBox(pDevice, 215, 80, 100, 70, 2, TGray, TBlack);
		cWriteText(265, 90, D3DCOLOR_ARGB(255, 255, 255, 153), "**CREDITS**");
		cWriteText(265, 100, D3DCOLOR_ARGB(255, 255, 255, 153), "ComboDance");
		cWriteText(265, 110, D3DCOLOR_ARGB(255, 255, 255, 153), "[i]FluX");
		cWriteText(265, 120, D3DCOLOR_ARGB(255, 255, 255, 153), "Mae");

		DrawBox(pDevice, 20, 40, 190, Current * 15, 2, TGray, TBlack);
		
		Current = 1;
		Kategorie(pDevice, " ESP");
		/*AddItem(pDevice, " Triggerbot",			Trigger,		opt_OnOff,1);*/
		AddItem(pDevice, " Player Names",		NameESP,		opt_OnOff,1);
		AddItem(pDevice, " Player C4",			C4ESP,			opt_OnOff,1);
		AddItem(pDevice, " Player HPBar",		HPBar,			opt_OnOff,1);
		AddItem(pDevice, " Player Skeleton",	BoneEsp,		opt_OnOff,1);
		AddItem(pDevice, " Player Lines",		LineEsp,		opt_OnOff,1);
		AddItem(pDevice, " Player Boxes",		Box3D,			opt_OnOff,1);
		AddItem(pDevice, " Player Distance",	DistanceESP,	opt_OnOff,1);
		AddItem(pDevice, " Player Rank Names",	RankName,		opt_OnOff,1);
		Kategorie(pDevice, " D3D");
		AddItem(pDevice, " Cross Hair",			CrossHair,		opt_OnOff,1);
		AddItem(pDevice, " WallHack",			tagos,			opt_OnOff,1);
		AddItem(pDevice, " ShowGhosts",			aswang,			opt_OnOff,1);
		AddItem(pDevice, " Player WireFrame" ,  WireFrame,		opt_OnOff,1);
		AddItem(pDevice, " Chams" ,				TextureModels,	opt_OnOff,1);
		AddItem(pDevice, " No Walls" ,			DrawWorld,		opt_OnOff,1);
		AddItem(pDevice, " No Sky" ,			SkyScale,		opt_OnOff,1);
		/*Kategorie(pDevice, " [AIMBOT]");
		AddItem(pDevice, " Aimbot",				AimKey,			opt_OnOff,5);
		AddItem(pDevice, " Aim Position",		AimBone,		opt_OnOff,7);
		AddItem(pDevice, " Visible Check",		VisibleCheck,	opt_OnOff,1);*/
		Kategorie(pDevice, " MEMORY");
		//AddItem(pDevice, " Always Headshot",	aHeadshot,		opt_HeadShot,2);
		AddItem(pDevice, " SuperKill",			SuperKill,		opt_OnOff,1);
		/*AddItem(pDevice, " Fly Hack",		MovingToUpSize,		opt_OnOff,1);*/
		//AddItem(pDevice, " No Reload/Change",	InstantChange,			opt_OnOff,1);
		//AddItem(pDevice, " SpeedHack [SHIFT]",	SpeedHack,		opt_OnOff,6);
		//AddItem(pDevice, " No Boom",		AntiBoom,		opt_OnOff,1);
		AddItem(pDevice, " No Fall",			nofall,			opt_OnOff,1);
		AddItem(pDevice, " No Recoil",			DummyRecoil,	opt_OnOff2,1);
		/*AddItem(pDevice, " Unlimited Bag",		baghack,		opt_OnOff,1);*/
		/*AddItem(pDevice, " 100% WallBang",		WallBang,		opt_OnOff,1);
		AddItem(pDevice, " Spy Mode [F]",		spymode,		opt_OnOff,1);
		AddItem(pDevice, " Anti Knockback",		knockback,		opt_OnOff,1);
		AddItem(pDevice, " Knife 360",			Knife360,		opt_OnOff,1);
		AddItem(pDevice, " Mini Long Knife",	LongKnife,		opt_OnOff,1);
		AddItem(pDevice, " SpeedKnife",			speedknife,		opt_OnOff,1);
		AddItem(pDevice, " Max Weapon Range",	MaxRange,		opt_OnOff,1);
		AddItem(pDevice, " Zoom With All Guns",	ZoomAllWeapons,	opt_OnOff,1);
		AddItem(pDevice, " Rapid/Fast Fire",	fastfire,		opt_OnOff,1); */

		//Kategorie2(pDevice, " ** CREDITS ** ");
		//Kategorie2(pDevice, " ComboDance ");
		//Kategorie3(pDevice, " [i]FluX ");
		//Kategorie3(pDevice, " Mamo007 ");
		//Kategorie4(pDevice, "  Mae");
		
		if(MenuSelection >= Current)
			MenuSelection = 1;

		if(MenuSelection < 1)
			MenuSelection = Current;

		


		
	}
}

//VOID DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
//{
//	#define PI 3.14159265358979f
//	D3DXVECTOR2 Line[128];
//    float Step = PI * 2.0 / numSides;
//    int Count = 0;
//    for (float a=0; a < PI*2.0; a += Step)
//    {
//        float X1 = radius * cos(a) + X;
//        float Y1 = radius * sin(a) + Y;
//        float X2 = radius * cos(a+Step) + X;
//        float Y2 = radius * sin(a+Step) + Y;
//        Line[Count].x = X1;
//        Line[Count].y = Y1;
//        Line[Count+1].x = X2;
//        Line[Count+1].y = Y2;
//        Count += 2;
//    }
//}


				void CrossPic(LPDIRECT3DDEVICE9 pDevice)
				{
						D3DVIEWPORT9 pViewport;
						pDevice->GetViewport(&pViewport);
						DWORD cx = pViewport.Width / 2;
						DWORD cy = pViewport.Height / 2;
						D3DRECT rec2 = {cx-5, cy, cx+6, cy+1};
						D3DRECT rec3 = {cx, cy-5, cx+1, cy+6};

						if(CrossHair)
						{
						/*DrawCircle(cx-1,cy-1,8,8,Red);*/
						pDevice->Clear(1, &rec2, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 0, 0); 
						pDevice->Clear(1, &rec3, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 173, 255, 047), 0, 0); 
						}

				//		 D3DVIEWPORT9 gViewPort;
				//		 pDevice->GetViewport(&gViewPort);
				//		 float ScreenCenterX = ( float )gViewPort.Width / 2;//Horizontal Position
				//		 float ScreenCenterY = ( float )gViewPort.Height / 2;//Vertical Position
				//		 D3DRECT rec2 = {ScreenCenterX-20, ScreenCenterY, ScreenCenterX+ 20, ScreenCenterY+2};
				//		 D3DRECT rec3 = {ScreenCenterX, ScreenCenterY-20, ScreenCenterX+ 2,ScreenCenterY+20};
				//				
				//		 if(CrossHair)
				//			{
				//		   pDevice->Clear(1, &rec2, D3DCLEAR_TARGET,D3DCOLOR_ARGB(255, 255, 255, 255), 0,  0);
				//		   pDevice->Clear(1, &rec3, D3DCLEAR_TARGET,D3DCOLOR_ARGB(255, 255, 255, 255), 0,  0);
				//		 }
				//}

				}





__declspec (naked) void esDetour(LPDIRECT3DDEVICE9 pDevice)
{
	__asm
	{
        MOV ESI,DWORD PTR SS:[EBP+8]
        XOR EBX,EBX
		PUSHAD	
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//draw
	CreateFont(pDevice);
	ErstelleMenu(pDevice);
	CrossPic(pDevice);
	xxxSex(pDevice);
	angelsburger();
	DetourWeaponCheck();
	StartHack();



	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	
	__asm
	{
	POPAD
	JMP esRet
	}
}

void hEndscene()
{
	DWORD hd3d = 0;
	DWORD * VTable;

	while(!hd3d)
	{ //wait
		hd3d = (DWORD)GetModuleHandleA(ed3d9);
	}
	DWORD pDevice = FindPattern2(hd3d, 0xFFFFFF,(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "00????00????00");
	if(pDevice)
	{
		memcpy(&VTable, (VOID*)(pDevice+2),4);
		esAddr = VTable[42] +0x2D;
		esRet = esAddr + 0x5;	
		MakeJMP((PBYTE)esAddr,(DWORD)esDetour, 5);

		
	}
}

unsigned int __stdcall lighter (LPVOID)
{
	while(1)
	{
		if(hooked == false)
		{
		
			hEndscene();

			
			hooked = true;
		}
	}
}

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		EraseHeaders(hDll);
		HideModule(hDll);
		/*MessageBox( 0, "Hook DIP Engine", "Crossfire", 0 );*/
		_beginthreadex(0, 0, lighter, 0, 0, 0);
	}
	return TRUE;
}
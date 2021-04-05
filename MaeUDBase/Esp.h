#pragma warning(disable:4244)
#pragma warning(disable:4101)
#pragma warning(disable:4305)
#include <stdio.h>


#define GetPlayerByIndex(LTClientShell, dwID) (CPlayer*)(LTClientShell + (dwID * dwCPlayerSize) + dwCPlayerStart)

void DrawBorder2 (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB2(pDevice, x,(y + h - px), w, px, BorderColor);
	FillRGB2(pDevice, x, y, px, h, BorderColor);
	FillRGB2(pDevice, x, y, w, px, BorderColor);
	FillRGB2(pDevice, x + w - px, y, px, h, BorderColor);
}

bool Trans3DTo2D (LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 *InOut)
{
	D3DXVECTOR3 vScreen;
	D3DXVECTOR3 PlayerPos(InOut->x, InOut->y, InOut->z);
	D3DVIEWPORT9 viewPort = {0};
	D3DXMATRIX projection, view, world;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetTransform(D3DTS_WORLD, &world);
	pDevice->GetViewport(&viewPort);
	D3DXVec3Project(&vScreen, &PlayerPos, &viewPort, &projection, &view, &world);
	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < viewPort.Width && vScreen.y < viewPort.Height)
	{
		*InOut = vScreen;
		return true;	
	}
	return false;
}

bool IsValidClient (CPlayer* Clients)
{
	if ((Clients != 0) && (Clients->Health >> 0))
		return true;
	return false;
}

bool isEntered()
{
	DWORD CShellBase = (DWORD)GetModuleHandleA(eCShell);
	DWORD pWeaponMgr = *(DWORD*)(CShellBase+dw_pWeaponMgr);
	if(pWeaponMgr > 0)
		return true;
	return false;
}
struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};
void DrawLine (LPDIRECT3DDEVICE9 pDevice, float X, float Y, float X2, float Y2, DWORD dwColor)
{
	if(!pDevice) return;
	D3DTLVERTEX qV[2] = 
	{ 
		{(float)X, (float)Y, 0.0f, 1.0f, dwColor},
		{(float)X2, (float)Y2, 0.0f, 1.0f, dwColor},
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	pDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
}

char GetMyIndex (DWORD pLTCLientShell)
{
	if (pLTCLientShell)
	{
		BYTE clients = *(BYTE*)(pLTCLientShell + dwCPlayerStart);
		if (clients < 16)
			return *(char*)(pLTCLientShell + clients * dwCPlayerSize + MEOffset);
	}
	return -1;
}

bool IsTM (DWORD pLTClientShell, CPlayer* pPlayer)
{
	bool IsAlly = true;
	CPlayer* Me = GetPlayerByIndex(pLTClientShell, GetMyIndex(pLTClientShell));
	if(Me->Team != pPlayer->Team) 
		IsAlly = false;

	return IsAlly;
}

D3DXVECTOR3 GetMidPoint (D3DXVECTOR3 V1, D3DXVECTOR3 V2)
{
	D3DXVECTOR3 Mid;
	Mid.x = (V1.x + V2.x) / 2;
	Mid.y = (V1.y + V2.y) / 2;
	Mid.z = (V1.z + V2.z) / 2;
	return Mid;
}

void GetBonePositionEx (cObject* obj, UINT Bone, Transform* Trans)
{
	DWORD CShellBase = (DWORD)GetModuleHandleA(eCShell);
	if(!CShellBase) return;
	DWORD pLTModel = *(DWORD*)(CShellBase+dw_pLTModel);

	__asm
	{
		MOV ECX,pLTModel
		MOV EDX,DWORD PTR DS:[ECX]
		MOV EDX,DWORD PTR DS:[EDX + 0x3C]
		PUSH 1
		PUSH Trans
		PUSH Bone
		PUSH obj
		CALL EDX
	}
}

void GetNodePosition (cObject* obj, UINT Bone, D3DXVECTOR3 &Out)
{
	Transform Trans;
	GetBonePositionEx(obj, Bone, &Trans);
	Out = Trans.Pos;
	Out.y += 5;
}

void DrawBone (LPDIRECT3DDEVICE9 pDevice, cObject *Obj, UINT iStart, UINT iEnd, D3DCOLOR Color)
{
	D3DXVECTOR3 StartPos, EndPos;
	GetNodePosition(Obj, iStart, StartPos);
	GetNodePosition(Obj, iEnd, EndPos);

	if (Trans3DTo2D(pDevice, &StartPos) && Trans3DTo2D(pDevice, &EndPos))
		DrawLine(pDevice, StartPos.x, StartPos.y, EndPos.x, EndPos.y,Color);
}

D3DXVECTOR3 GetBonePosition (cObject* obj, UINT Bone)
{
	Transform Trans;
	GetBonePositionEx(obj,Bone,&Trans);
	return (Trans.Pos);
}

void DrawSkeleton(LPDIRECT3DDEVICE9 pDevice, CPlayer* pPlayer, D3DCOLOR Color)
{
	DrawBone(pDevice, pPlayer->Object, 6, 0, Color);
	DrawBone(pDevice, pPlayer->Object, 5, 6, Color);
	DrawBone(pDevice, pPlayer->Object, 4, 5, Color);
	DrawBone(pDevice, pPlayer->Object, 3, 4, Color);
	DrawBone(pDevice, pPlayer->Object, 2, 3, Color);
	DrawBone(pDevice, pPlayer->Object, 1, 2, Color);
	DrawBone(pDevice, pPlayer->Object, 21, 1, Color);
	DrawBone(pDevice, pPlayer->Object, 22, 21, Color);
	DrawBone(pDevice, pPlayer->Object, 23, 22, Color);
	DrawBone(pDevice, pPlayer->Object, 24, 23, Color);
	DrawBone(pDevice, pPlayer->Object, 25, 1, Color);
	DrawBone(pDevice, pPlayer->Object, 26, 25, Color);
	DrawBone(pDevice, pPlayer->Object, 27, 26, Color);
	DrawBone(pDevice, pPlayer->Object, 28, 27, Color);
	DrawBone(pDevice, pPlayer->Object, 14, 5, Color);
	DrawBone(pDevice, pPlayer->Object, 15, 14, Color);
	DrawBone(pDevice, pPlayer->Object, 16, 15, Color);
	DrawBone(pDevice, pPlayer->Object, 17, 16, Color);
	DrawBone(pDevice, pPlayer->Object, 18, 17, Color);
	DrawBone(pDevice, pPlayer->Object, 19, 17, Color);
	DrawBone(pDevice, pPlayer->Object, 20, 17, Color);
	DrawBone(pDevice, pPlayer->Object, 7, 5, Color);
	DrawBone(pDevice, pPlayer->Object, 8, 7, Color);
	DrawBone(pDevice, pPlayer->Object, 9, 8, Color);
	DrawBone(pDevice, pPlayer->Object, 10, 9, Color);
	DrawBone(pDevice, pPlayer->Object, 11, 10, Color);
	DrawBone(pDevice, pPlayer->Object, 12, 10, Color);
	DrawBone(pDevice, pPlayer->Object, 13, 10, Color);
}

void DrawBox(LPDIRECT3DDEVICE9 pDevice, CPlayer* pPlayer, D3DCOLOR Color)
					{
					D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
					Pos0 = GetMidPoint(GetBonePosition(pPlayer->Object, 6), GetBonePosition(pPlayer->Object, 3));
					Pos1 = Pos0 + D3DXVECTOR3(-50, 160, -50);
					Pos2 = Pos0 + D3DXVECTOR3(-50, -160, -50);
					Pos3 = Pos0 + D3DXVECTOR3(50, -160, -50);
					Pos4 = Pos0 + D3DXVECTOR3(50, 160, -50);
					Pos5 = Pos0 + D3DXVECTOR3(-50, 160, 50);
					Pos6 = Pos0 + D3DXVECTOR3(-50, -160, 50);
					Pos7 = Pos0 + D3DXVECTOR3(50, -160, 50);
					Pos8 = Pos0 + D3DXVECTOR3(50, 160, 50);

					if (Trans3DTo2D(pDevice, &Pos1) && Trans3DTo2D(pDevice, &Pos2) && Trans3DTo2D(pDevice, &Pos3) && Trans3DTo2D(pDevice, &Pos4) && Trans3DTo2D(pDevice, &Pos5) && Trans3DTo2D(pDevice, &Pos6) && Trans3DTo2D(pDevice, &Pos7) && Trans3DTo2D(pDevice, &Pos8))
					{
						DrawLine(pDevice, Pos1.x, Pos1.y, Pos2.x, Pos2.y,  Color);
						DrawLine(pDevice, Pos2.x, Pos2.y, Pos3.x, Pos3.y,  Color);
						DrawLine(pDevice, Pos3.x, Pos3.y, Pos4.x, Pos4.y,  Color);
						DrawLine(pDevice, Pos4.x, Pos4.y, Pos1.x, Pos1.y,  Color);
						DrawLine(pDevice, Pos5.x, Pos5.y, Pos6.x, Pos6.y,  Color);
						DrawLine(pDevice, Pos6.x, Pos6.y, Pos7.x, Pos7.y,  Color);
						DrawLine(pDevice, Pos7.x, Pos7.y, Pos8.x, Pos8.y,  Color);
						DrawLine(pDevice, Pos8.x, Pos8.y, Pos5.x, Pos5.y,  Color);
						DrawLine(pDevice, Pos1.x, Pos1.y, Pos5.x, Pos5.y,  Color);
						DrawLine(pDevice, Pos2.x, Pos2.y, Pos6.x, Pos6.y,  Color);
						DrawLine(pDevice, Pos3.x, Pos3.y, Pos7.x, Pos7.y,  Color);
						DrawLine(pDevice, Pos4.x, Pos4.y, Pos8.x, Pos8.y,  Color);
					}
				}


float CalculateDist (D3DXVECTOR3 from, D3DXVECTOR3 to)
{
	float _x, _y, _z;
	_x = to.x - from.x;
	_y = to.y - from.y;
	_z = to.z - from.z;
	return sqrt(_x*_x + _y*_y + _z*_z);
}

VOID xxxSex(LPDIRECT3DDEVICE9 pDevice)
{
	DWORD CShellBase = (DWORD)GetModuleHandleA(eCShell);
	if(CShellBase)
	{
				DWORD pLTClientShell = *(DWORD*)(CShellBase+dw_pLTClientShell);
				CPlayer* Me = GetPlayerByIndex(pLTClientShell, GetMyIndex(pLTClientShell));
				D3DVIEWPORT9 viewP;
				pDevice->GetViewport(&viewP);
				DWORD ScreenCenterX = viewP.Width/2;
				DWORD ScreenCenterY = viewP.Height;

				
				char pNAME[10000];
				char szRank[100];
				char txt[0x30];
				char *HasC4 = "->Has C4<-";	

		for(int i = 0; i<16; i++)
		{
			CPlayer* pPlayer = GetPlayerByIndex(pLTClientShell, i);
			if(IsValidClient(pPlayer) && Me != pPlayer)
			{
				D3DXVECTOR3 Body = GetBonePosition(pPlayer->Object, 2);
				DWORD ESP_Color = 0;
				DWORD healthcolor = 0xFF00FF00;

				

				if(pPlayer->Health > 80) 
				healthcolor = 0xFF00FF00; 
				else if(pPlayer->Health > 60) 
				healthcolor = 0xFFFFFF00;
				else if(pPlayer->Health > 40) 
				healthcolor = 0xFFFF4500;
				else 
				healthcolor = 0xFFFF0000;

				int G = pPlayer->Health;

				if(!IsTM(pLTClientShell, pPlayer))
				{
					if(Trans3DTo2D(pDevice,&Body))
					{
						if(BoneEsp)
						{
						DrawSkeleton(pDevice, pPlayer, D3DCOLOR_ARGB(255,255,0,0));
								}

						if(Box3D)
						{
						DrawBox(pDevice, pPlayer, D3DCOLOR_ARGB(255, 000, 000, 255));
								}

						if(LineEsp)
						{
						DrawLine(pDevice,ScreenCenterX,ScreenCenterY,Body.x,Body.y,D3DCOLOR_ARGB(255,255,0,0));
								}

						if(NameESP)
						{
						sprintf_s(pNAME," %s ", (int)pPlayer->Name);
						cWriteText2(Body.x + 20, Body.y -50, D3DCOLOR_ARGB(255,255,0,0), pNAME);
								}
					
						if(C4ESP)
						{	
							if(pPlayer->Has_C4)
							cWriteText2(Body.x+20, Body.y-80, D3DCOLOR_ARGB(255,255,0,0), HasC4);
							}

						if(HPBar)
						{
							DrawBorder2(pDevice, Body.x, Body.y-2, 41, 5, 1, D3DCOLOR_ARGB(255, 255, 255, 255));
							FillRGB2(pDevice, Body.x, Body.y-2, G/2.5, 3, healthcolor);
							}
				
						if(RankName)
						{
							sprintf_s(szRank, " %s", ranks[pPlayer->Rank]);
							cWriteText2(Body.x+20, Body.y -70, D3DCOLOR_ARGB(255, 255, 255, 255), szRank);
							}

						if(DistanceESP)
						{
							sprintf_s(txt, " %d", (DWORD)(CalculateDist(Me->Object->Body, pPlayer->Object->Body)/100));
							cWriteText2(Body.x+20 ,Body.y -60 , D3DCOLOR_ARGB(255, 255, 255, 255), txt);
						}

					}
				}
			}
		}
	} 
}
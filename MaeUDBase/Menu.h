#define Green				D3DCOLOR_ARGB(255, 000, 255, 000)
#define Red					D3DCOLOR_ARGB(255, 255, 000, 000)
#define Blue				D3DCOLOR_ARGB(255, 000, 000, 255)
#define Orange				D3DCOLOR_ARGB(255, 255, 165, 000)
#define Yellow				D3DCOLOR_ARGB(255, 255, 255, 000)
#define Pink				D3DCOLOR_ARGB(255, 255, 192, 203)
#define Cyan				D3DCOLOR_ARGB(255, 000, 255, 255)
#define Purple				D3DCOLOR_ARGB(255, 160, 032, 240)
#define Black				D3DCOLOR_ARGB(255, 000, 000, 000) 
#define White				D3DCOLOR_ARGB(255, 255, 255, 255)
#define Grey				D3DCOLOR_ARGB(255, 112, 112, 112)
#define SteelBlue			D3DCOLOR_ARGB(255, 033, 104, 140)
#define LightSteelBlue		D3DCOLOR_ARGB(255, 201, 255, 255)
#define LightBlue			D3DCOLOR_ARGB(255, 026, 140, 306)
#define Salmon				D3DCOLOR_ARGB(255, 196, 112, 112)
#define Brown				D3DCOLOR_ARGB(255, 168, 099, 020)
#define Teal				D3DCOLOR_ARGB(255, 038, 140, 140)
#define Lime				D3DCOLOR_ARGB(255, 050, 205, 050)
#define ElectricLime		D3DCOLOR_ARGB(255, 204, 255, 000)
#define Gold				D3DCOLOR_ARGB(255, 255, 215, 000)
#define OrangeRed			D3DCOLOR_ARGB(255, 255, 069, 000)
#define GreenYellow			D3DCOLOR_ARGB(255, 173, 255, 047)
#define AquaMarine			D3DCOLOR_ARGB(255, 127, 255, 212)
#define SkyBlue				D3DCOLOR_ARGB(255, 000, 191, 255)
#define SlateBlue			D3DCOLOR_ARGB(255, 132, 112, 255)
#define Crimson				D3DCOLOR_ARGB(255, 220, 020, 060)
#define DarkOliveGreen		D3DCOLOR_ARGB(255, 188, 238, 104)
#define PaleGreen			D3DCOLOR_ARGB(255, 154, 255, 154)
#define DarkGoldenRod		D3DCOLOR_ARGB(255, 255, 185, 015)
#define FireBrick			D3DCOLOR_ARGB(255, 255, 048, 048)
#define DarkBlue			D3DCOLOR_ARGB(255, 000, 000, 204)
#define DarkerBlue			D3DCOLOR_ARGB(255, 000, 000, 153)
#define DarkYellow			D3DCOLOR_ARGB(255, 255, 204, 000)
#define LightYellow			D3DCOLOR_ARGB(255, 255, 255, 153)
#define DarkOutline			D3DCOLOR_ARGB(255, 37,   48,  52)
//#define TBlack				D3DCOLOR_ARGB(180, 000, 000, 000) 
#define TBlack				D3DCOLOR_ARGB(225, 000, 000, 000) 
#define Gray				D3DCOLOR_ARGB(255, 150, 150, 150)
#define TGray				D3DCOLOR_ARGB(225, 20, 20, 20)
#define TGold				D3DCOLOR_ARGB(195, 255, 215, 000)
int NoReload		= 1;
int NoRecoil	    = 1;
int CrossHair		= 0;
int tagos			= 0;
int aswang			= 0;
int AimKey			= 0;
int AimBone			= 0;
int VisibleCheck	= 0;
int NameESP			= 0;
int DistanceESP		= 0;
int C4ESP			= 0;
int RankName		= 0;
int HPBar			= 0;
int BoneEsp			= 0;
int LineEsp			= 0;
int Box3D			= 0;
int Trigger			= 0;
int aHeadshot		= 0;
int onehitkill		= 0;
int norecoil		= 1;
int noeffects		= 0;
int SpeedHack		= 0;
int AntiBoom		= 0;
int nofall			= 0;
int WallBang		= 0;
int spymode			= 0;
int knockback		= 0;
int Knife360		= 0;
int LongKnife		= 0;
int speedknife		= 0;
int MaxRange		= 0;
int ZoomAllWeapons	= 0;
int baghack			= 0;
int fastfire		= 0;
int InstantChange	= 1;
int InstantReload	= 1;
int SuperKill		= 0;
int DummyRecoil		= 1;

/* PTC */
int WireFrame		= 0;
int	DrawWorld		= 0;
int	TextureModels	= 0;
int	SkyScale		= 0;

/*testing*/
int MovingToUpSize = 0;
int recoil2 = 0;




int MenuSelection = 0;
int Current = true;

int PosX = 30;
int PosY = 27;

int Show = true;

POINT cPos;

#define ItemColorOn D3DCOLOR_ARGB(255, 000, 255, 000)
#define ItemColorOff D3DCOLOR_ARGB(255, 255, 255, 255)
#define ItemCurrent D3DCOLOR_ARGB(255, 255, 000, 000)
#define GroupColor D3DCOLOR_ARGB(255, 255, 255, 000)
#define KategorieFarbe D3DCOLOR_ARGB(255, 255, 185, 015)
#define ItemText Gray

int CheckTabs (int x, int y, int w, int h)
{
	GetCursorPos(&cPos);
	ScreenToClient(GetForegroundWindow(),&cPos);
	if(cPos.x > x && cPos.x < x + w && cPos.y > y && cPos.y < y + h)
	{
		if(GetAsyncKeyState(VK_LBUTTON)&1)
		{
			return 1;
		}
		return 2;
	}
	return 0;
}

void FillRGB (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec = {x, y, x + w, y + h};
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawBorder (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB(pDevice, x,(y + h - px), w, px, BorderColor);
	FillRGB(pDevice, x, y, px, h, BorderColor);
	FillRGB(pDevice, x, y, w, px, BorderColor);
	FillRGB(pDevice, x + w - px, y, px, h, BorderColor);
}

void DrawBox (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, DWORD Fill, DWORD Border)
{
	FillRGB(pDevice,x, y, w, h, Fill);
	DrawBorder(pDevice,x, y, w, h, px, Border);
}

void WriteText2 (int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void lWriteText (int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_RIGHT, color);
}

void cWriteText (int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_CENTER, color);
}


void Kategorie (LPDIRECT3DDEVICE9 pDevice, char *text)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190, 10);
		DWORD ColorText;

		ColorText = KategorieFarbe;

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText2(PosX - 5,	PosY  + (Current * 15) - 1, D3DCOLOR_ARGB(255, 255, 255, 153), text);
		lWriteText(PosX + 175,	PosY  + (Current * 15) - 1, D3DCOLOR_ARGB(255, 000, 255, 000), "[-]");
		Current++;
	}
}
void Kategorie2 (LPDIRECT3DDEVICE9 pDevice, char *text)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190,10);
		DWORD ColorText;

		ColorText = KategorieFarbe;

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText2(PosX + 47,	PosY  + (Current * 15) - 1, D3DCOLOR_ARGB(255, 255, 255, 153), text);
		lWriteText(PosX + 175,	PosY  + (Current * 15) - 1, ColorText, "");
		Current++;
	}
}
void Kategorie3(LPDIRECT3DDEVICE9 pDevice, char *text)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190,10);
		DWORD ColorText;

		ColorText = KategorieFarbe;

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText2(PosX + 65,	PosY  + (Current * 15) - 1, D3DCOLOR_ARGB(255, 255, 255, 153), text);
		Current++;
	}
}
void Kategorie4(LPDIRECT3DDEVICE9 pDevice, char *text)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190,10);
		DWORD ColorText;

		ColorText = KategorieFarbe;

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText2(PosX + 68,	PosY  + (Current * 15) - 1, D3DCOLOR_ARGB(255, 255, 255, 153), text);
		Current++;
	}
}


void AddItem (LPDIRECT3DDEVICE9 pDevice, char *text, int &var, char **opt, int MaxValue)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190, 10);
		DWORD ColorText;

		if(var)
		{
			DrawBox(pDevice, PosX, PosY  + (Current * 15), 10, 10, 1, D3DCOLOR_ARGB(255, 000, 255, 000), D3DCOLOR_ARGB(255, 000, 255, 000));
			ColorText = ItemColorOn;
		}
		if(var == 0)
		{
			DrawBox(pDevice, PosX, PosY  + (Current * 15), 10, 10, 1, Gray, Gray);
			ColorText = ItemColorOff;
		}

		if(Check == 1)
		{
			var++;
			if(var > MaxValue)
				var = 0;
		}

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current) 
		{
			if(GetAsyncKeyState(VK_RIGHT)&1)
			{
				var++;
				if(var > MaxValue)
					var = 0;
			}
			else if(GetAsyncKeyState(VK_LEFT)&1)
			{
				var--;
				if(var < 0)
					var = MaxValue;
			}
		}

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText2(PosX + 13,	PosY  + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 175,	PosY  + (Current * 15) - 1, ColorText, opt[var]);
		Current++;
	}
}
void AddItem2 (LPDIRECT3DDEVICE9 pDevice, char *text, int &var, char **opt, int MaxValue)
{
	if(Show) 
	{
		int Check = CheckTabs(PosX, PosY  + (Current * 15), 190, 10);
		DWORD ColorText;

		if(var)
		{
			DrawBox(pDevice, PosX, PosY  + (Current * 15), 10, 10, 1, D3DCOLOR_ARGB(255, 000, 255, 000), D3DCOLOR_ARGB(255, 000, 255, 000));
			ColorText = ItemColorOn;
		}
		if(var == 0)
		{
			DrawBox(pDevice, PosX, PosY  + (Current * 15), 10, 10, 1, D3DCOLOR_ARGB(255, 000, 255, 000), D3DCOLOR_ARGB(255, 000, 255, 000));
			ColorText = ItemColorOn;
		}

		if(Check == 1)
		{
			var++;
			if(var > MaxValue)
				var = 0;
		}

		if(Check == 2)
			ColorText = ItemCurrent;

		if(MenuSelection == Current) 
		{
			if(GetAsyncKeyState(VK_RIGHT)&1)
			{
				var++;
				if(var > MaxValue)
					var = 0;
			}
			else if(GetAsyncKeyState(VK_LEFT)&1)
			{
				var--;
				if(var < 0)
					var = MaxValue;
			}
		}

		if(MenuSelection == Current)
			ColorText = ItemCurrent;

		WriteText2(PosX + 13,	PosY  + (Current * 15) - 1, ColorText, text);
		lWriteText(PosX + 175,	PosY  + (Current * 15) - 1, ColorText, opt[var]);
		Current++;
	}
}


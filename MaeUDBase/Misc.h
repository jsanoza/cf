void EraseHeaders(HINSTANCE hModule)
{
	/* 
	* jus a func to erase headers by Croner.
	* keep in mind you wont be able to load 
	* any resources after you erase headers.
	*/

	PIMAGE_DOS_HEADER pDoH; 
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;
	
	// well just to make clear what we doing
	pDoH = (PIMAGE_DOS_HEADER)(hModule);

	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	ersize = sizeof(IMAGE_DOS_HEADER);
	if ( VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect) )
	{
		for ( i=0; i < ersize; i++ )
				*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if ( pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect) )
	{
		for ( i=0; i < ersize; i++ )
				*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}


void HideModule(HINSTANCE hModule)/*Credits to Thanatos aka Surpintine for his hide module function*/
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]             
		mov eax, [eax+0Ch]               
		mov dwPEB_LDR_DATA, eax	

		InLoadOrderModuleList:
			mov esi, [eax+0Ch]	     
			mov edx, [eax+10h]	     

		LoopInLoadOrderModuleList: 
		    lodsd		         
			mov esi, eax	
			mov ecx, [eax+18h]  
			cmp ecx, hModule	
			jne SkipA		 
		    mov ebx, [eax]	  
		    mov ecx, [eax+4]  
		    mov [ecx], ebx    
		    mov [ebx+4], ecx	  
			jmp InMemoryOrderModuleList 

		SkipA:
			cmp edx, esi     
			jne LoopInLoadOrderModuleList

		InMemoryOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+14h]
			mov edx, [eax+18h]

		LoopInMemoryOrderModuleList: 
			lodsd
			mov esi, eax
			mov ecx, [eax+10h]
			cmp ecx, hModule
			jne SkipB
			mov ebx, [eax] 
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp InInitializationOrderModuleList

		SkipB:
			cmp edx, esi
			jne LoopInMemoryOrderModuleList

		InInitializationOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+1Ch]	  
			mov edx, [eax+20h]	  

		LoopInInitializationOrderModuleList: 
			lodsd
			mov esi, eax		
			mov ecx, [eax+08h]
			cmp ecx, hModule		
			jne SkipC
			mov ebx, [eax] 
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp Finished

		SkipC:
			cmp edx, esi
			jne LoopInInitializationOrderModuleList

		Finished:
			popfd;
			popad;
	}
}
void cWriteText2(int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_CENTER, color);
}

void lWriteText2 (int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_RIGHT, color);
}

void FillRGB2 (LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec = {x, y, x + w, y + h};
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void WriteText (int x, int y, DWORD color, char *text)
{    
    RECT rect;
    SetRect(&rect,x,y,x,y);
    pFont->DrawText(0, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void CreateFont (LPDIRECT3DDEVICE9 pDevice)
{
	bool bFont = false;
	if(pFont)
	{
		pFont->Release();
		pFont = false; 
		bFont = false;
	}

	if(!bFont)
	{
		D3DXCreateFontA(pDevice, 14, 6, FW_MEDIUM, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Calibri", &pFont);
		bFont = true;
	}
}


bool bCompare2 (const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(; *szMask; ++szMask, ++pData, ++bMask)
		if(*szMask=='0' && *pData != *bMask)
			return false;
	return (*szMask) == 0;
}

DWORD FindPattern2 (DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i<dwLen; i++)
		if (bCompare2((BYTE*)(dwAddress + i), bMask, szMask))  
			return (DWORD)(dwAddress + i);
	return false;
}

void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}
BOOL bCompare( const BYTE* pData, const BYTE* bMask, const char* szMask )
{
    for ( ;*szMask; ++szMask, ++pData, ++bMask )
    {
        if ( *szMask == 'x' && *pData != *bMask )
             return 0;
    }
    return (*szMask) == NULL;
}

DWORD FindPattern ( DWORD dwStartAddress,DWORD dwSize, BYTE *bMask, char * szMask, int codeOffset, BOOL extract )
{ 
    for ( DWORD i = 0; i < dwSize; i++ )
    {
        if ( bCompare((BYTE*)(dwStartAddress + i),bMask,szMask) )
        {
            if ( extract )  
            {
                return *(DWORD*)(dwStartAddress+i+codeOffset);

            } else {

                return  (DWORD)(dwStartAddress+i+codeOffset);
            }
        }
    }
    return NULL;
}

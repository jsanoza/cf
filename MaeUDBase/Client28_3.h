typedef struct _WEAPON
{
    unsigned char Data[0x4000];
} WEAPON, *PWEAPON;

PWEAPON pOldWeapons[2000];

void CreateBackup()
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
    DWORD pWeaponMgr = *(DWORD*)(CShell + 0x1A16B2C);
    for(int i = 0; i < 1820; i++)
    {
        DWORD dwWeapon = *(DWORD*)(pWeaponMgr + (4 * i));
        if (dwWeapon)
        {
            pOldWeapons[i] = new WEAPON;
            memcpy(pOldWeapons[i], (void*)(dwWeapon), sizeof(WEAPON));
        }
    }

}

PWEAPON GetWeaponByIndex(int index)
{
    return pOldWeapons[index];
}

bool bCompare5(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(; *szMask; ++szMask, ++pData, ++bMask)
		if(*szMask=='0' && *pData != *bMask)
			return false;
	return (*szMask) == 0;
}

DWORD FindPattern5(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i<dwLen; i++)
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))  
			return (DWORD)(dwAddress + i);
	return false;
}

void MakeE8JMP(BYTE* paddress, DWORD yourfunction, DWORD dwlen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(paddress, dwlen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (yourfunction - (DWORD) paddress) - 5;
    *paddress = 0xE8;
        *((DWORD*) (paddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwlen; x++) *(paddress + x) = 0x90;
    VirtualProtect(paddress, dwlen, dwOldProtect, &dwBkup);
    return;
}

void DetourWeaponCheck()
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
																	   
	DWORD dwBypassWeaponHack = FindPattern5(CShell, 0xFFFFFF, (PBYTE)"\xE8\x00\x00\x00\x00\x8B\xF0\x83\xC4\x04\x85\xF6\x0F\x84\x00\x00\x00\x00\xD9\x86\x00\x00\x00\x00", "x????xxxxxxxxx????xx????");
	DWORD dwOldProtect;
	VirtualProtect((void*)(dwBypassWeaponHack + 0x1), sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*(DWORD*)(dwBypassWeaponHack + 0x1) = (DWORD)GetWeaponByIndex - dwBypassWeaponHack - 5;
	VirtualProtect((void*)(dwBypassWeaponHack + 0x1), sizeof(DWORD), dwOldProtect, NULL);
}

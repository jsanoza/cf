#include "Client28_3.h"

int Ready = 0;
void StartHack()
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
	DWORD pWeaponMgr2 = *(DWORD*)(CShell + 0x1A16B2C);

	if(Ready == false)
	{
		CreateBackup();
		if (*(BYTE*)(CShell+0x5A1835)) 
		{
			MakeE8JMP((BYTE*)(CShell+0x5A1835), (DWORD)GetWeaponByIndex, 5); 
			
			Ready = true;

	if(pWeaponMgr2 != NULL)
		   {
			   for(int i=0; i<1820; i++)
			   {
				   DWORD Weapon2 = *(DWORD*)(pWeaponMgr2 + (4*i));
				   if(Weapon2 != NULL)
					 {
						 if(NoRecoil)
						 {
						   *(float*)(Weapon2 + 0x11E8) = 0;
						   *(float*)(Weapon2 + 0x1350) = 0;
						   *(float*)(Weapon2 + 0x14B8) = 0;		 
						 }
					 }
				}
		    }	
		}
	}
}
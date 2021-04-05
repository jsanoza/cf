struct Transform
{
	D3DXVECTOR3 Pos;
	char Spacer[0x100];
};

struct cObject
{
public:
	char Spacer[4];
	D3DXVECTOR3 Body;
	D3DXVECTOR3 Foot;
	D3DXVECTOR3 Head;
};

struct CPlayer
{ 
	char Spacer00[4];
	cObject* Object;
	char ClientID;
	char Team;     
	char Name[12];
	char Spacer01[2];
	int SHIT;
	int PlayerSlotTeam;
	int unkstruct1; 
	bool Has_C4; 
	int State;
	int Rank;
	int unkstruct2; 
	int unkstruct3;
	short Health;
	short Kills;
	__int32 Deaths;
	__int32 HeadShots;
	__int32 TeamID;
	__int32 Ping;
};

static char* ranks[] = 
{
	"Trainee 1"            ,
	"Trainee 2"            ,
	"Private"              ,
	"PFC"                  ,
	"Corporal"             ,
	"Sergeant 1"           ,
	"Sergeant 2"           ,
	"Sergeant 3"           ,
	"Sergeant 4"           ,
	"Staff Sergeant 1"     ,
	"Staff Sergeant 2"     ,
	"Staff Sergeant 3"     ,
	"Staff Sergeant 4"     ,
	"Staff Sergeant 5"     ,
	"Staff Sergeant 6"     ,
	"SFC 1"                ,
	"SFC 2"                ,
	"SFC 3"                ,
	"SFC 4"                ,
	"SFC 5"                ,
	"SFC 6"                ,
	"Master Sergeant 1"    ,
	"Master Sergeant 2"    ,
	"Master Sergeant 3"    ,
	"Master Sergeant 4"    ,
	"Master Sergeant 5"    ,
	"Master Sergeant 6"    ,
	"2nd Lieutenant 1"     ,
	"2nd Lieutenant 2"     ,
	"2nd Lieutenant 3"     ,
	"2nd Lieutenant 4"     ,
	"2nd Lieutenant 5"     ,
	"2nd Lieutenant 6"     ,
	"2nd Lieutenant 7"     ,
	"2nd Lieutenant 8"     ,
	"1st Lieutenant 1"     ,
	"1st Lieutenant 2"     ,
	"1st Lieutenant 3"     ,
	"1st Lieutenant 4"     ,
	"1st Lieutenant 5"     ,
	"1st Lieutenant 6"     ,
	"1st Lieutenant 7"     ,
	"1st Lieutenant 8"     ,
	"Captain 1"            ,
	"Captain 2"            ,
	"Captain 3"            ,
	"Captain 4"            ,
	"Captain 5"            ,
	"Captain 6"            ,
	"Captain 7"            ,
	"Captain 8"            ,
	"Major 1"              ,
	"Major 2"              ,
	"Major 3"              ,
	"Major 4"              ,
	"Major 5"              ,
	"Major 6"              ,
	"Major 7"              ,
	"Major 8"              ,
	"Lieutenant Colonel 1" ,
	"Lieutenant Colonel 2" ,
	"Lieutenant Colonel 3" ,
	"Lieutenant Colonel 4" ,
	"Lieutenant Colonel 5" ,
	"Lieutenant Colonel 6" ,
	"Lieutenant Colonel 7" ,
	"Lieutenant Colonel 8" ,
	"Colonel 1"            ,
	"Colonel 2"            ,
	"Colonel 3"            ,
	"Colonel 4"            ,
	"Colonel 5"            ,
	"Colonel 6"            ,
	"Colonel 7"            ,
	"Colonel 8"            ,
	"Brigadiar General 1"  ,
	"Brigadiar General 2"  ,
	"Brigadiar General 3"  ,
	"Brigadiar General 4"  ,
	"Brigadiar General 5"  ,
	"Brigadiar General 6"  ,
	"Major General 1"      ,
	"Major General 2"      ,
	"Major General 3"      ,
	"Major General 4"      ,
	"Major General 5"      ,
	"Major General 6"      ,
	"Lieutenant General 1" ,
	"Lieutenant General 2" ,
	"Lieutenant General 3" ,
	"Lieutenant General 4" ,
	"Lieutenant General 5" ,
	"Lieutenant General 6" ,
	"General 1"            ,
	"General 2"            ,
	"General 3"            ,
	"General 4"            ,
	"General 5"            ,
	"General 6"            ,
	"Marshal"
};
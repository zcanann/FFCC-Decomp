#ifndef _FFCC_GAME_H_
#define _FFCC_GAME_H_

class Vec;
class PPPIFPARAM;
class CGObject;
class CGPrgObj;
class CGPartyObj;
class CCombi2Set;
class CMapLightHolder;
class CCharaPcs;
class CBound;
struct _GXColor;

void VECMaximize(const Vec *, const Vec *, Vec *);
void VECMinimize(const Vec *, const Vec *, Vec *);
void SAFE_CAST_CARAVAN_WORK(CGObjWork *);

class CGame
{
public:
	class CNextScript
	{
	public:
		CNextScript &operator=(const CNextScript &);
	};

	class CGameWork
	{
	public:
		CGameWork();
		void Init();
		void InitNewGame();
		void ClearScriptChange();
	};
	
	CGame();
	~CGame();

	void Init();
	void Quit();
	void LoadLogoWaitingData();
	void Exec();
	void Create();
	void Destroy();
	void InitNewGame();
	void clearWork();
	void clearWorkMap();
	void clearWorkScript();
	void CheckScriptChange();
	void ChangeMap(int, int, int, int);
	void ScriptChanging(char *);
	void ScriptChanged(char *, int);
	void MapChanging(int, int);
	void MapChanged(int, int, int);
	void loadCfd();
	void Calc();
	void Calc2();
	void Calc3();
	void Draw();
	void Draw2();
	void Draw3();
	void HitParticleBG(int, int, int, Vec *, PPPIFPARAM *);
	void ParticleFrameCallback(int, int, int, int, int, Vec *);
	void SaveScript(char *);
	void LoadScript(char *);
	void LoadInit();
	void LoadFinished();
	void GetBossArtifact(int, int);
	void GetFoodLevel(int, int);
	void GetTargetCursor(int, Vec &, Vec &);
	void GetParticleSpecialInfo(PPPIFPARAM &, int &, int &);
	void GetPartyObj(int);
	void MakeArtItemName(char *, int, int);
	void MakeArtsItemNames(char *, int);
	void MakeNumItemName(char *, int, int);
	void MakeArtMonName(char *, int, int);
	void MakeArtsMonNames(char *, int);
	void MakeNumMonName(char *, int, int);
	void GetLangString();
	void SetNextScript(CGame::CNextScript *);
	void IsWorldMap();
	void IsPartyExist(int);
	void GetItemName(int);
	void GetItemArt(int);
	void GetItemNames(int);
	void GetItemArts(int);
	void GetItemName(int, int);
	void GetMonName(int);
	void GetMonArt(int);
	void GetMonNames(int);
	void GetMonArts(int);
	void GetMonName(int, int);
};

#endif // _FFCC_GAME_H_

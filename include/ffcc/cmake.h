#ifndef _FFCC_CMAKE_H_
#define _FFCC_CMAKE_H_

class CMenuPcs;

void GetChara(char*, int, char*);
void GetCharaType(char*, int);
void GetCharaCnt(char*);

class CMenuPcs
{
public:
	enum FMT
	{
		TODO_FMT
	};

	enum TEX
	{
		TODO_TEX
	};
	struct CTmp
	{
		int m_textureSetIndex;
		char* m_textureName;
	};

	CMenuPcs();
	~CMenuPcs();

	void CalcSingCMake();
	void DrawSingCMake();
	void DrawDiaryBase(int, float);
	void DrawCmakeWin(float, float, float);
	void DrawCmakeTitle(int, float, float);
	void DrawCrystal(int, int, float);
	void DrawCmakeNameBase(int, float);
	void DrawCmakePageMark(float);
	void DrawCmakeDecision(int, float);
	void DrawCmakeBallCursor(int, int, float);
	void DrawCmakeCharaText(int, float);
	void DrawCmakeCrest(int, int, int, float);
	void DrawCmakeName(int, int, char*, float);
	void AddNameChara(int, int, int, int);
	void DrawCmakeYesNo(int, float);
	unsigned short GetButtonDown(int);
	unsigned short GetButtonRepeat(int);
	void InitFrame0Info();
	void CalcWMFrame0(int);
	void DrawWMFrame0(int, float);
	void CallWorldParam(int, int, int);
	void ChgModel(int, int, int, int);
	void SetAnim(int);
	void PCAnimCtrl();
	void SetProjection(int);
	void SetLight(int);
	void SetAttrFmt(FMT);
	void SetTexture(TEX);
	void DrawInit();
	void DrawRect(unsigned long, float, float, float, float, float, float, float, float, float);
	void DrawCursor(int, int, float);
	void RestoreProjection();
	void loadFont(int, char*, int, int);
	void loadTexture(char**, int, int, CTmp*, int, int, int);
	void freeTexture(int, int, int, int);
	void SetMcWinInfo(int, int);
	void DrawMcWin(short, short);
	void DrawMcWinMess(int, int);
	void GetWinSize(int, short*, short*, int);
	int GetModelNo(int, int, int);
	float GetMaxAnimWait();
	char* GetMenuStr(int);
	char* GetTribeStr(int);
	char* GetJobStr(int);
	char* GetHairStr(int);

	void CmakeOpen();
	void CmakeCtrl();
	void CmakeClose();
	void CmakeDraw();

	void CmakeNameOpen();
	int CmakeNameCtrl();
	void CmakeNameClose();
	void CmakeNameDraw();

	void CmakeSexOpen();
	void CmakeSexCtrl();
	void CmakeSexClose();
	void CmakeSexDraw();

	void CmakeTribeOpen();
	unsigned short CmakeTribeCtrl();
	void CmakeTribeClose();
	void CmakeTribeDraw();

	void CmakeJobOpen();
	unsigned short CmakeJobCtrl();
	void CmakeJobClose();
	void CmakeJobDraw();

	void CmakeResultOpen();
	void CmakeResultCtrl();
	void CmakeResultClose();
	void CmakeResultDraw();

	void CmakeResultOpen1();
	void CmakeResultCtrl1();
	void CmakeResultClose1();
	void CmakeResultDraw1();

	void CmakeVillageOpen();
	unsigned short CmakeVillageCtrl();
	void CmakeVillageClose();
	void CmakeVillageDraw();

	void SetSingMakeChara();

	void createVillageMenu();
	void destroyVillageMenu();
	void calcVillageMenu();
	void drawVillageMenu();

	void CalcSingleCMakeChara();
	void DrawSingleCMakeChara(float);
};

#endif // _FFCC_CMAKE_H_

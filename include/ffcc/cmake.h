#ifndef _FFCC_CMAKE_H_
#define _FFCC_CMAKE_H_

class CMenuPcs;

void GetChara(char *, int, char *);
void GetCharaType(char *, int);
void GetCharaCnt(char *);

class CMenuPcs
{
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
	void DrawCmakeName(int, int, char *, float);
	void AddNameChara(int, int, int, int);
	void DrawCmakeYesNo(int, float);

	void CmakeOpen();
	void CmakeCtrl();
	void CmakeClose();
	void CmakeDraw();

	void CmakeNameOpen();
	void CmakeNameCtrl();
	void CmakeNameClose();
	void CmakeNameDraw();

	void CmakeSexOpen();
	void CmakeSexCtrl();
	void CmakeSexClose();
	void CmakeSexDraw();

	void CmakeTribeOpen();
	void CmakeTribeCtrl();
	void CmakeTribeClose();
	void CmakeTribeDraw();

	void CmakeJobOpen();
	void CmakeJobCtrl();
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
	void CmakeVillageCtrl();
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

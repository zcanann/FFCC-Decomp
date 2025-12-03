#ifndef _FFCC_BONUS_MENU_H_
#define _FFCC_BONUS_MENU_H_

class CMenuPcs
{
	class Sprt2
	{
		void operator=(const Sprt2 &);
	};
	
	CMenuPcs();
	~CMenuPcs();

	void BonusInit();
	void createBonus();
	void destroyBonus();
	void calcBonus();
	void drawBonus();

	void CalcResultOpenAnim();
	void DrawResultOpenAnim();
	void CalcResultCountAnim();
	void DrawResultCountAnim();
	void CalcResultCloseAnim();
	void DrawResultCloseAnim();

	void CalcSelectOpenAnim();
	void DrawSelectOpenAnim();
	void CalcSelectWait();
	void DrawSelectWait();
	void CalcSelectCloseAnim();
	void DrawSelectCloseAnim();

	void DrawBonusCnt(CMenuPcs::Sprt2 *, int);
	void DrawBonusFrame(float, float, float, float, float);
	void DrawArtiBase(CMenuPcs::Sprt2 *, float);
	void DrawBonusChkMark(float);
	void ArtiBaseInfoInit(CMenuPcs::Sprt2 *, CMenuPcs::Sprt2 *);

	void GetAllPadOn();
	void ClrBattleItem();
};

#endif // _FFCC_BONUS_MENU_H_

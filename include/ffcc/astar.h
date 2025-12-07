#ifndef _FFCC_ASTAR_H_
#define _FFCC_ASTAR_H_

struct Vec;
class CGPartyObj;

class CAStar
{
	class CATemp
	{
		CATemp();
		CATemp(const CATemp&);
		void operator=(const CATemp&);
	};

	class CAPos
	{
		void IsUse();
		void CalcLength(CAPos&);
		void IsExist(int);
	};
	
	CAStar();
	~CAStar();

	void reset();
	void addAstar(Vec&, int, int);
	void addAstar(float, float, float, int, int);
	void dumpAStar();
	void check(int, int, CAStar::CATemp&);
	void calcAStar();
	void drawAStar();
	void addRealTime(CGPartyObj*);
	void getEscapePos(Vec&, Vec&, int, int);
	void calcSpecialPolygonGroup(Vec*);
	void calcPolygonGroup(Vec*, int);
};

#endif // _FFCC_ASTAR_H_

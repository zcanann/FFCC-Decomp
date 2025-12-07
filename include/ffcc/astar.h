#ifndef _FFCC_ASTAR_H_
#define _FFCC_ASTAR_H_

#include <dolphin/mtx.h>
#include <dolphin/types.h>

class CGPartyObj;

class CAStar
{
public:
	class CAPos
	{
	public:
		float CalcLength(CAPos&);
		unsigned char GetOthers(int group);
		int IsExist(int group);

		Vec m_position;         // 0x0
		unsigned char m_groupA; // 0xc
		unsigned char m_groupB; // 0xd
		// Unfilled             // 0xe-0xf
	}; // Size 0x10

	class CATemp
	{
	public:
		CATemp();
		CATemp(const CATemp&);

		void operator=(const CATemp&);

		unsigned char m_visited[64]; // 0x0
		unsigned char m_path[64];    // 0x40
		int m_pathLength;            // 0x80
		float m_cost;                // 0x84
	}; // Size 0x88
	
	CAStar();
	~CAStar();

	void reset();
	void addAstar(float x, float y, float z, int groupA, int groupB);
	void check(int current, int goal, CATemp& temp);
	void calcAStar();
	void drawAStar();
	void addRealTime(CGPartyObj*);
	void getEscapePos(Vec&, Vec&, int, int);
	void calcSpecialPolygonGroup(Vec*);
	void calcPolygonGroup(Vec*, int);

	unsigned char m_flags;                  // 0x00
	// Unused                               // 0x1-0x3
	unsigned int m_hitAttributeMask;        // 0x4
	int m_portalCount;                      // 0x8
	CAPos m_portals[64];                    // 0xc
	unsigned char m_routeTable[64][64][2];  // 0x40c
	unsigned int m_lastSeenGroup;           // 0x240c
	// Unused                               // 0x240d-0x240f
	Vec m_lastGroupPos;                     // 0x2410
	unsigned char m_currentGroup;           // 0x241c
	unsigned char m_previousGroup;          // 0x241d
	// Unused                               // 0x241e-0x241f
	CATemp m_bestPath;                      // 0x2420
}; // Size 0x24a8

#endif // _FFCC_ASTAR_H_

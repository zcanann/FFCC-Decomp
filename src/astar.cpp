#include "ffcc/astar.h"

#include "ffcc/charaobj.h"
#include "ffcc/color.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/maphit.h"
#include "ffcc/p_camera.h"
#include "ffcc/pad.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_map.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"

#include "string.h"

CAStar AStar;

inline int CMapPcs::CheckHitCylinderNear(Vec* cylinderBottom, Vec* direction, float radius, unsigned long hitMask)
{
    CMapCylinder cylinder;

    cylinder.m_bottom = *cylinderBottom;
    cylinder.m_axis = *direction;
    cylinder.m_radius = radius;

    return MapMng.CheckHitCylinderNear(&cylinder, direction, hitMask);
}

static inline int getHitPolygonGroup(Vec* pos, unsigned long hitAttributeMask)
{
	if (MapPcs.CheckHitCylinderNear(CVector(pos->x, pos->y + 5.0f, pos->z),
	                                CVector(0.0f, -100.0f, 0.0f),
	                                0.0f, hitAttributeMask) != 0)
	{
		return gMapHitFace->m_groupIndex;
	}

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x80141550
 * PAL Size: 468b
 * EN Address: 0x801636D8
 * EN Size: 228b
 * JP Address: TODO
 * JP Size: TODO
 */
int CAStar::calcPolygonGroup(Vec* pos, int hitAttributeMask)
{
	if ((AStar.m_flags & 1) != 0)
	{
		return getHitPolygonGroup(pos, m_hitAttributeMask);
	}

	if (MapPcs.CheckHitCylinderNear(CVector(pos->x, pos->y + 5.0f, pos->z),
	                                CVector(0.0f, -100.0f, 0.0f),
	                                0.0f, hitAttributeMask) != 0)
	{
		return gMapHitFace->m_groupIndex;
	}

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x80141724
 * PAL Size: 252b
 * EN Address: 0x80163618
 * EN Size: 192b
 * JP Address: TODO
 * JP Size: TODO
 */
int CAStar::calcSpecialPolygonGroup(Vec* pos)
{
	if (MapPcs.CheckHitCylinderNear(CVector(pos->x, pos->y + 5.0f, pos->z),
	                                CVector(0.0f, -100.0f, 0.0f),
	                                0.0f, m_hitAttributeMask) != 0)
	{
		return gMapHitFace->m_groupIndex;
	}

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x80141820
 * PAL Size: 584b
 * EN Address: 0x801633CC
 * EN Size: 588b
 * JP Address: TODO
 * JP Size: TODO
 */
CAStar::CAPos* CAStar::getEscapePos(Vec& from, Vec& base, int startGroup, int forbiddenGroup)
{
	CVector escapeDir = CVector(from) - CVector(base);
	escapeDir.Normalize();

	CAPos* aheadBest = (CAPos*)0;
	CAPos* behindBest = (CAPos*)0;
	float initialBestDist = -1000000.0f;
	double aheadBestDist = initialBestDist;
	double behindBestDist = aheadBestDist;
	int i = 0;

	do
	{
		if (m_portals[i].IsUse() && m_portals[i].IsExist(startGroup))
		{
			{
				int otherGroup = m_portals[i].GetOthers(startGroup);

				if (forbiddenGroup != otherGroup)
				{
					CVector portalVec = CVector(m_portals[i].m_position) - CVector(base);
					portalVec.Normalize();

					float dot = PSVECDotProduct(escapeDir, portalVec);
					portalVec = CVector(m_portals[i].m_position) - CVector(base);
					float dist = PSVECMag(portalVec);

					if (dot >= 0.0f)
					{
						if (aheadBestDist < dist)
						{
							aheadBest = &m_portals[i];
							aheadBestDist = dist;
						}
					}
					else if (behindBestDist < dist)
					{
						behindBestDist = dist;
						behindBest = &m_portals[i];
					}
				}
			}
		}

		++i;
	} while (i < 64);

	if (aheadBest != (CAPos*)0)
	{
		return aheadBest;
	}

	return behindBest;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CAStar::addAstar(Vec& pos, int groupA, int groupB)
{
	if (groupB < groupA)
	{
		int groupSwap = groupA;
		groupA = groupB;
		groupB = groupSwap;
	}

	int index = 0;

	for (; index < 64; ++index)
	{
		CAPos& p = m_portals[index];

		if (p.m_group[0] == groupA && p.m_group[1] == groupB)
		{
			break;
		}
	}

	if (index == 64)
	{
		index = 0;

		for (; index < 64; ++index)
		{
			if (!m_portals[index].IsUse())
			{
				m_portalCount++;
				break;
			}
		}
	}

	m_portals[index].m_position = pos;
	m_portals[index].m_group[0] = groupA;
	m_portals[index].m_group[1] = groupB;
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CAStar::dumpAStar()
{
	System.Printf(const_cast<char*>("//A*\n"));

	for (int i = 0; i < 64; ++i)
	{
		CAPos& p = m_portals[i];

		bool used = false;
		if (m_portals[i].m_group[0] != 0 && m_portals[i].m_group[1] != 0)
		{
			used = true;
		}

		if (used)
		{
			System.Printf(
				const_cast<char*>("addAStar(%.5f, %.5f, %.5f, %d, %d, 0, 0);\n"),
				static_cast<double>(p.m_position.x),
				static_cast<double>(p.m_position.y),
				static_cast<double>(p.m_position.z),
				p.m_group[0],
				p.m_group[1]
			);
		}
	}

}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::addRealTime(CGPartyObj* gPartyObj)
{
	if (static_cast<unsigned short>(m_lastSeenGroup) != gPartyObj->m_aStarGroupId)
	{
		m_lastGroupPos.x = gPartyObj->m_worldPosition.x;
		m_lastGroupPos.y = gPartyObj->m_worldPosition.y;
		m_lastGroupPos.z = gPartyObj->m_worldPosition.z;

		m_currentGroup    = static_cast<unsigned char>(gPartyObj->m_aStarGroupId);
		m_previousGroup   = m_lastSeenGroup;
		m_lastSeenGroup   = static_cast<unsigned char>(gPartyObj->m_aStarGroupId);
	}

	Graphic.Printf(10, 10, const_cast<char*>("A* GROUP=%d"), static_cast<int>(gPartyObj->m_aStarGroupId));

	bool padBusy = false;
	int padLock = Pad.m_debugPadLock;

	if (padLock != 0 || Pad.m_debugPadPort != -1)
	{
		padBusy = true;
	}

	u16 trig1;
	if (padBusy)
	{
		trig1 = 0;
	}
	else
	{
		unsigned int resolvedIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
		trig1 = Pad.GetPadInputs()[resolvedIndex].buttonDown[0];
	}

	if ((trig1 & 0x20) == 0)
	{
		return;
	}

	padBusy = false;
	if (padLock != 0 || Pad.m_debugPadPort != -1)
	{
		padBusy = true;
	}

	u16 trig2;
	if (padBusy)
	{
		trig2 = 0;
	}
	else
	{
		unsigned int resolvedIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
		trig2 = Pad.GetPadInputs()[resolvedIndex].button[0];
	}

	if ((trig2 & 0x40) == 0)
	{
		return;
	}

	addAstar(m_lastGroupPos, m_currentGroup, m_previousGroup);

	dumpAStar();
	calcAStar();
}
/*
 * --INFO--
 * PAL Address: 0x80141EB4
 * PAL Size: 700b
 * EN Address: 0x80162FA8
 * EN Size: 736b
 * JP Address: TODO
 * JP Size: TODO
 */
void CAStar::drawAStar()
{
	if ((DbgMenuPcs.GetDbgFlag() & 0x400) != 0)
	{
		if (static_cast<int>(System.m_frameCounter) % 30 == 0)
		{
			for (int group = 0; group < 64; group++)
			{
				MapMng.SetIdGrpColor(group, 0, CColor(Math.Rand(0xff), Math.Rand(0xff), Math.Rand(0xff), 0xFF).color);
			}
		}

		float (*drawMtx)[4] = CameraPcs.m_cameraMatrix;
		bool hasGroups = false;

		if (m_currentGroup != 0 && m_previousGroup != 0)
		{
			hasGroups = true;
		}

		if (hasGroups)
		{
			Graphic.DrawSphere(drawMtx, &m_lastGroupPos, 10.0f, CColor(0xFF, 0xFF, 0xFF, 0xFF));
		}

		for (int i = 0; i < 64; i++)
		{
			if (m_portals[i].IsUse())
			{
				Graphic.DrawSphere(drawMtx, &m_portals[i].m_position, 10.0f, CColor(0xFF, 0xFF, 0x00, 0xFF));

				for (int side = 0; side < 2; side++)
				{
					int groupId = m_portals[i].m_group[side];

					if (groupId != 0)
					{
						for (int j = 0; j < 64; j++)
						{
							if (i != j)
							{
								if (m_portals[j].IsUse())
								{
									if (m_portals[j].IsExist(groupId))
									{
										GXLoadPosMtxImm(drawMtx, GX_PNMTX0);
										GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 2);
										GXPosition3f32(
											m_portals[i].m_position.x,
											m_portals[i].m_position.y + 5.0f,
											m_portals[i].m_position.z);
										GXPosition3f32(
											m_portals[j].m_position.x,
											m_portals[j].m_position.y + 5.0f,
											m_portals[j].m_position.z);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x80142170
 * PAL Size: 324b
 * EN Address: 0x80162E44
 * EN Size: 356b
 * JP Address: TODO
 * JP Size: TODO
 */
void CAStar::calcAStar()
{
	memset(m_routeTable, 0, sizeof(m_routeTable));

	for (int to = 0; to < 64; ++to)
	{
		for (int from = 0; from < 64; ++from)
		{
			if (from == to)
			{
				continue;
			}

			m_bestPath.m_cost = 10000000.0f;

			CATemp temp;

			memset(&temp, 0, sizeof(temp));

			check(from, (int)(unsigned int)to, temp);

			if (m_bestPath.m_cost < 10000000.0f)
			{
				System.Printf(const_cast<char*>("\x8d\xc5\x92\x5a\x8c\x6f\x98\x48%d->%d=%.5fm "), from, to, m_bestPath.m_cost);

				int current = from;

				for (int i = 0; i < m_bestPath.m_pathLength; ++i)
				{
					int portalIndex = m_bestPath.m_path[i];

					m_routeTable[current][to][1] = portalIndex;

					int next = m_portals[portalIndex].m_group[0];

					if (next == current)
					{
						next = m_portals[portalIndex].m_group[1];
					}

					m_routeTable[current][to][0] = static_cast<unsigned char>(next);

					current = static_cast<unsigned char>(next);

					System.Printf(const_cast<char*>("%d "), current);
				}

				System.Printf(const_cast<char*>("\n"));
			}
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x801422B4
 * PAL Size: 1964b
 * EN Address: 0x80162D2C
 * EN Size: 280b
 * JP Address: TODO
 * JP Size: TODO
 */
void CAStar::check(int current, int goal, CATemp& temp)
{
	temp.m_visited[current] = 1;

	if (current == goal)
	{
		if (temp.m_cost < m_bestPath.m_cost)
		{
			m_bestPath = temp;
		}

		return;
	}

	CAPos* pos = m_portals;
	for (int i = 0; i < 64; i++, pos++)
	{
		if (pos->IsExist(current) != 0)
		{
			int next = pos->GetOthers(current);

			if (temp.m_visited[next] == 0)
			{
				CATemp work(temp);
				work.m_cost += pos->CalcLength(m_portals[next]);
				work.m_path[work.m_pathLength++] = static_cast<unsigned char>(i);
				check(next, goal, work);
			}
		}
	}
}
/*
 * --INFO--
 * PAL Address: 0x80142ce8
 * PAL Size: 668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAStar::addAstar(float x, float y, float z, int groupA, int groupB)
{
	addAstar(CVector(x, y, z), groupA, groupB);
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::reset()
{
	m_portalCount = 0;
	memset(m_portals, 0, sizeof(m_portals));
	memset(m_routeTable, 0, sizeof(m_routeTable));
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::~CAStar()
{
	// TODO
}

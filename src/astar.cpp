#include "ffcc/astar.h"

#include "ffcc/charaobj.h"
#include "ffcc/color.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/maphit.h"
#include "ffcc/pad.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_dbgmenu.h"
extern "C" {
extern char kAStarGroupDebugFormat[];
extern char kAStarPortalDebugFormat[];
extern const float kPolyGroupBaseXZ;
extern const float kPolyGroupBaseY;
extern const float kPolyGroupTopOffsetY;
extern const float kPolyGroupAabbMax;
extern const float kPolyGroupAabbMin;
extern const float kAStarEscapeInitialBestDist;
extern const char kAStarGroupDebugLabel[] = "//A*\n";
extern const float kDrawAStarSphereRadius = 10.0f;
extern const float kInfiniteCost = 10000000.0f;
extern const char kAStarStepDebugFormat[] = "%d ";
extern const char kAStarNewLine[] = "\n";
}
#include "ffcc/system.h"
#include "ffcc/vector.h"

#include "string.h"

static const char kAStarCostDebugFormat[] = "%d->%d=%.5fm ";

struct CMapCylinderRaw
{
	Vec m_bottom;
	Vec m_unknown;
	Vec m_direction;
	float m_radius;
	Vec m_top;
	Vec m_direction2;
};

CAStar AStar;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CAStar()
{
	reset();
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
void CAStar::addAstar(float x, float y, float z, int groupA, int groupB)
{
	CVector pos(x, y, z);

	if (groupB < groupA)
	{
		int tmp = groupA;

		groupA  = groupB;
		groupB  = tmp;
	}

	int index = 0;

	for (; index < 64; ++index)
	{
		CAPos& p = m_portals[index];

		if (p.m_groupA == groupA && p.m_groupB == groupB)
		{
			break;
		}
	}

	if (index == 64)
	{
		index = 0;

		for (; index < 64; ++index)
		{
			bool used = false;

			if (m_portals[index].m_groupA != 0 && m_portals[index].m_groupB != 0)
			{
				used = true;
			}

			if (!used)
			{
				m_portalCount++;
				break;
			}
		}
	}

	CAPos& portal = m_portals[index];

	portal.m_position.x = pos.x;
	portal.m_position.y = pos.y;
	portal.m_position.z = pos.z;
	portal.m_groupA = static_cast<unsigned char>(groupA);
	portal.m_groupB = static_cast<unsigned char>(groupB);
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::check(int startGroup, int goalGroup, CATemp& temp)
{
	temp.m_visited[startGroup] = 1;

	if (startGroup == goalGroup)
	{
		if (temp.m_cost < m_bestPath.m_cost)
		{
			unsigned int* dstVisited = reinterpret_cast<unsigned int*>(m_bestPath.m_visited);
			unsigned int* srcVisited = reinterpret_cast<unsigned int*>(temp.m_visited);
			unsigned int* dstPath = reinterpret_cast<unsigned int*>(m_bestPath.m_path);
			unsigned int* srcPath = reinterpret_cast<unsigned int*>(temp.m_path);

			dstVisited[0] = srcVisited[0];
			dstVisited[1] = srcVisited[1];
			dstVisited[2] = srcVisited[2];
			dstVisited[3] = srcVisited[3];
			dstVisited[4] = srcVisited[4];
			dstVisited[5] = srcVisited[5];
			dstVisited[6] = srcVisited[6];
			dstVisited[7] = srcVisited[7];
			dstVisited[8] = srcVisited[8];
			dstVisited[9] = srcVisited[9];
			dstVisited[10] = srcVisited[10];
			dstVisited[11] = srcVisited[11];
			dstVisited[12] = srcVisited[12];
			dstVisited[13] = srcVisited[13];
			dstVisited[14] = srcVisited[14];
			dstVisited[15] = srcVisited[15];

			dstPath[0] = srcPath[0];
			dstPath[1] = srcPath[1];
			dstPath[2] = srcPath[2];
			dstPath[3] = srcPath[3];
			dstPath[4] = srcPath[4];
			dstPath[5] = srcPath[5];
			dstPath[6] = srcPath[6];
			dstPath[7] = srcPath[7];
			dstPath[8] = srcPath[8];
			dstPath[9] = srcPath[9];
			dstPath[10] = srcPath[10];
			dstPath[11] = srcPath[11];
			dstPath[12] = srcPath[12];
			dstPath[13] = srcPath[13];
			dstPath[14] = srcPath[14];
			dstPath[15] = srcPath[15];
			m_bestPath.m_pathLength = temp.m_pathLength;
			m_bestPath.m_cost = temp.m_cost;
		}

		return;
	}

	int idx0 = 0;
	CAPos* pos0 = m_portals;
	do
	{
		unsigned char other0 = pos0->m_groupA;
		bool connected0 = false;

		if (other0 == startGroup)
		{
			connected0 = true;
		}
		else if (pos0->m_groupB == startGroup)
		{
			connected0 = true;
		}

		if (connected0)
		{
			if (other0 == startGroup)
			{
				other0 = pos0->m_groupB;
			}

			if (temp.m_visited[other0] == 0)
			{
				unsigned int visited1[16];
				unsigned int path1[16];
				int pathLen1 = temp.m_pathLength;
				float cost1 = temp.m_cost;
				unsigned char* visited1Bytes = reinterpret_cast<unsigned char*>(visited1);
				unsigned char* path1Bytes = reinterpret_cast<unsigned char*>(path1);

				visited1[0] = reinterpret_cast<unsigned int*>(temp.m_visited)[0];
				visited1[1] = reinterpret_cast<unsigned int*>(temp.m_visited)[1];
				visited1[2] = reinterpret_cast<unsigned int*>(temp.m_visited)[2];
				visited1[3] = reinterpret_cast<unsigned int*>(temp.m_visited)[3];
				visited1[4] = reinterpret_cast<unsigned int*>(temp.m_visited)[4];
				visited1[5] = reinterpret_cast<unsigned int*>(temp.m_visited)[5];
				visited1[6] = reinterpret_cast<unsigned int*>(temp.m_visited)[6];
				visited1[7] = reinterpret_cast<unsigned int*>(temp.m_visited)[7];
				visited1[8] = reinterpret_cast<unsigned int*>(temp.m_visited)[8];
				visited1[9] = reinterpret_cast<unsigned int*>(temp.m_visited)[9];
				visited1[10] = reinterpret_cast<unsigned int*>(temp.m_visited)[10];
				visited1[11] = reinterpret_cast<unsigned int*>(temp.m_visited)[11];
				visited1[12] = reinterpret_cast<unsigned int*>(temp.m_visited)[12];
				visited1[13] = reinterpret_cast<unsigned int*>(temp.m_visited)[13];
				visited1[14] = reinterpret_cast<unsigned int*>(temp.m_visited)[14];
				visited1[15] = reinterpret_cast<unsigned int*>(temp.m_visited)[15];

				path1[0] = reinterpret_cast<unsigned int*>(temp.m_path)[0];
				path1[1] = reinterpret_cast<unsigned int*>(temp.m_path)[1];
				path1[2] = reinterpret_cast<unsigned int*>(temp.m_path)[2];
				path1[3] = reinterpret_cast<unsigned int*>(temp.m_path)[3];
				path1[4] = reinterpret_cast<unsigned int*>(temp.m_path)[4];
				path1[5] = reinterpret_cast<unsigned int*>(temp.m_path)[5];
				path1[6] = reinterpret_cast<unsigned int*>(temp.m_path)[6];
				path1[7] = reinterpret_cast<unsigned int*>(temp.m_path)[7];
				path1[8] = reinterpret_cast<unsigned int*>(temp.m_path)[8];
				path1[9] = reinterpret_cast<unsigned int*>(temp.m_path)[9];
				path1[10] = reinterpret_cast<unsigned int*>(temp.m_path)[10];
				path1[11] = reinterpret_cast<unsigned int*>(temp.m_path)[11];
				path1[12] = reinterpret_cast<unsigned int*>(temp.m_path)[12];
				path1[13] = reinterpret_cast<unsigned int*>(temp.m_path)[13];
				path1[14] = reinterpret_cast<unsigned int*>(temp.m_path)[14];
				path1[15] = reinterpret_cast<unsigned int*>(temp.m_path)[15];

				cost1 += PSVECDistance(&pos0->m_position, &m_portals[other0].m_position);
				path1Bytes[pathLen1] = static_cast<unsigned char>(idx0);
				++pathLen1;
				visited1Bytes[other0] = 1;

				if (other0 == static_cast<unsigned char>(goalGroup))
				{
					if (cost1 < m_bestPath.m_cost)
					{
						unsigned int* dstVisited = reinterpret_cast<unsigned int*>(m_bestPath.m_visited);
						unsigned int* dstPath = reinterpret_cast<unsigned int*>(m_bestPath.m_path);

						dstVisited[0] = visited1[0];
						dstVisited[1] = visited1[1];
						dstVisited[2] = visited1[2];
						dstVisited[3] = visited1[3];
						dstVisited[4] = visited1[4];
						dstVisited[5] = visited1[5];
						dstVisited[6] = visited1[6];
						dstVisited[7] = visited1[7];
						dstVisited[8] = visited1[8];
						dstVisited[9] = visited1[9];
						dstVisited[10] = visited1[10];
						dstVisited[11] = visited1[11];
						dstVisited[12] = visited1[12];
						dstVisited[13] = visited1[13];
						dstVisited[14] = visited1[14];
						dstVisited[15] = visited1[15];

						dstPath[0] = path1[0];
						dstPath[1] = path1[1];
						dstPath[2] = path1[2];
						dstPath[3] = path1[3];
						dstPath[4] = path1[4];
						dstPath[5] = path1[5];
						dstPath[6] = path1[6];
						dstPath[7] = path1[7];
						dstPath[8] = path1[8];
						dstPath[9] = path1[9];
						dstPath[10] = path1[10];
						dstPath[11] = path1[11];
						dstPath[12] = path1[12];
						dstPath[13] = path1[13];
						dstPath[14] = path1[14];
						dstPath[15] = path1[15];
						m_bestPath.m_pathLength = pathLen1;
						m_bestPath.m_cost = cost1;
					}
				}
				else
				{
					int idx1 = 0;
					CAPos* pos1 = m_portals;

					do
					{
						unsigned char other1 = pos1->m_groupA;
						bool connected1 = false;

						if (other1 == other0)
						{
							connected1 = true;
						}
						else if (pos1->m_groupB == other0)
						{
							connected1 = true;
						}

						if (connected1)
						{
							if (other1 == other0)
							{
								other1 = pos1->m_groupB;
							}

							if (visited1Bytes[other1] == 0)
							{
								CATemp level2;
								unsigned int* level2Visited = reinterpret_cast<unsigned int*>(level2.m_visited);
								unsigned int* level2Path = reinterpret_cast<unsigned int*>(level2.m_path);

								level2Visited[0] = visited1[0];
								level2Visited[1] = visited1[1];
								level2Visited[2] = visited1[2];
								level2Visited[3] = visited1[3];
								level2Visited[4] = visited1[4];
								level2Visited[5] = visited1[5];
								level2Visited[6] = visited1[6];
								level2Visited[7] = visited1[7];
								level2Visited[8] = visited1[8];
								level2Visited[9] = visited1[9];
								level2Visited[10] = visited1[10];
								level2Visited[11] = visited1[11];
								level2Visited[12] = visited1[12];
								level2Visited[13] = visited1[13];
								level2Visited[14] = visited1[14];
								level2Visited[15] = visited1[15];

								level2Path[0] = path1[0];
								level2Path[1] = path1[1];
								level2Path[2] = path1[2];
								level2Path[3] = path1[3];
								level2Path[4] = path1[4];
								level2Path[5] = path1[5];
								level2Path[6] = path1[6];
								level2Path[7] = path1[7];
								level2Path[8] = path1[8];
								level2Path[9] = path1[9];
								level2Path[10] = path1[10];
								level2Path[11] = path1[11];
								level2Path[12] = path1[12];
								level2Path[13] = path1[13];
								level2Path[14] = path1[14];
								level2Path[15] = path1[15];
								level2.m_pathLength = pathLen1;
								level2.m_cost = cost1;
								level2.m_cost += PSVECDistance(&pos1->m_position, &m_portals[other1].m_position);
								level2.m_path[level2.m_pathLength] = static_cast<unsigned char>(idx1);
								++level2.m_pathLength;
								level2.m_visited[other1] = 1;

								if (other1 == static_cast<unsigned char>(goalGroup))
								{
									if (level2.m_cost < m_bestPath.m_cost)
									{
										m_bestPath = level2;
									}
								}
								else
								{
									for (int idx2 = 0; idx2 < 64; ++idx2)
									{
										CAPos* edge = &m_portals[idx2];

										if (edge->IsExist(other1) != 0)
										{
											int nextGroup = edge->GetOthers(other1);

											if (level2.m_visited[nextGroup] == 0)
											{
												CATemp deeper(level2);
												deeper.m_cost += edge->CalcLength(m_portals[nextGroup]);
												deeper.m_path[deeper.m_pathLength] = static_cast<unsigned char>(idx2);
												++deeper.m_pathLength;
												check(nextGroup, goalGroup, deeper);
											}
										}
									}
								}
							}
						}

						++idx1;
						++pos1;
					} while (idx1 < 64);
				}
			}
		}

		++idx0;
		++pos0;
	} while (idx0 < 64);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CATemp::CATemp()
{
	memset(this, 0, sizeof(*this));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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

			m_bestPath.m_cost = kInfiniteCost;

			CATemp temp;

			check(from, to, temp);

			if (m_bestPath.m_cost < kInfiniteCost)
			{
				System.Printf(const_cast<char*>(kAStarCostDebugFormat), from, to, m_bestPath.m_cost);

				int current = from;

				for (int i = 0; i < m_bestPath.m_pathLength; ++i)
				{
					int portalIndex = m_bestPath.m_path[i];

					m_routeTable[current][to][1] = portalIndex;

					int next = m_portals[portalIndex].m_groupA;

					if (next == current)
					{
						next = m_portals[portalIndex].m_groupB;
					}

					m_routeTable[current][to][0] = static_cast<unsigned char>(next);

					current = static_cast<unsigned char>(next);

					System.Printf(const_cast<char*>(kAStarStepDebugFormat), current);
				}

				System.Printf(const_cast<char*>(kAStarNewLine));
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80141eb4
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAStar::drawAStar()
{
	if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x400) != 0)
	{
		int frameGroup = System.m_frameCounter / 0x1e + (System.m_frameCounter >> 31);

		if (System.m_frameCounter == (frameGroup - (frameGroup >> 31)) * 0x1e)
		{
			for (int group = 0; group < 64; ++group)
			{
				unsigned char b = static_cast<unsigned char>(Math.Rand(0xff));
				unsigned char g = static_cast<unsigned char>(Math.Rand(0xff));
				unsigned char r = static_cast<unsigned char>(Math.Rand(0xff));
				CColor color(r, g, b, 0xFF);
				MapMng.SetIdGrpColor(group, 0, color.color);
			}
		}

		bool hasGroups = false;
		if (m_currentGroup != 0 && m_previousGroup != 0)
		{
			hasGroups = true;
		}

		if (hasGroups)
		{
			CColor white(0xFF, 0xFF, 0xFF, 0xFF);
			Graphic.DrawSphere(gFlatPosMtx, &m_lastGroupPos, kDrawAStarSphereRadius, &white.color);
		}

		for (int i = 0; i < 64; ++i)
		{
			CAPos& portal = m_portals[i];

			if (portal.m_groupA == 0 || portal.m_groupB == 0)
			{
				continue;
			}

			CColor yellow(0xFF, 0xFF, 0x00, 0xFF);
			Graphic.DrawSphere(gFlatPosMtx, &portal.m_position, kDrawAStarSphereRadius, &yellow.color);

			unsigned char* groupPtr = &portal.m_groupA;
			for (int side = 0; side < 2; ++side, ++groupPtr)
			{
				unsigned char group = *groupPtr;

				if (group == 0)
				{
					continue;
				}

				for (int j = 0; j < 64; ++j)
				{
					if (i == j)
					{
						continue;
					}

					CAPos& other = m_portals[j];

					if (other.m_groupA == 0 || other.m_groupB == 0)
					{
						continue;
					}

					if (other.m_groupA != group && other.m_groupB != group)
					{
						continue;
					}

					GXLoadPosMtxImm(gFlatPosMtx, GX_PNMTX0);
					GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 2);
					GXPosition3f32(
						portal.m_position.x,
						portal.m_position.y + kPolyGroupTopOffsetY,
						portal.m_position.z);
					GXPosition3f32(
						other.m_position.x,
						other.m_position.y + kPolyGroupTopOffsetY,
						other.m_position.z);
				}
			}
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

	Graphic.Printf(10, 10, kAStarGroupDebugFormat, static_cast<int>(gPartyObj->m_aStarGroupId));

	bool padBusy = false;

	if (Pad._452_4_ != 0 || Pad._448_4_ != -1)
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
		__cntlzw(static_cast<unsigned int>(Pad._448_4_));
		trig1 = Pad._8_2_;
	}

	if ((trig1 & 0x20) == 0)
	{
		return;
	}

	padBusy = false;
	if (Pad._452_4_ != 0 || Pad._448_4_ != -1)
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
		__cntlzw(static_cast<unsigned int>(Pad._448_4_));
		trig2 = Pad._4_2_;
	}

	if ((trig2 & 0x40) == 0)
	{
		return;
	}

	unsigned char prev = m_previousGroup;
	unsigned char curr = m_currentGroup;

	unsigned char groupLow  = curr;
	unsigned char groupHigh = prev;

	if (prev < curr)
	{
		groupHigh = curr;
		groupLow  = prev;
	}

	int portalIndex = 64;

	// Look for an existing portal (groupLow, groupHigh)
	for (int i = 0; i < 64; ++i)
	{
		CAPos& p = m_portals[i];

		if (p.m_groupA == groupLow && p.m_groupB == groupHigh)
		{
			portalIndex = i;
			break;
		}
	}

	// If none, find a free slot
	if (portalIndex == 64)
	{
		for (int i = 0; i < 64; ++i)
		{
			CAPos& p = m_portals[i];

			bool used = false;
			if (p.m_groupA != 0 && p.m_groupB != 0)
			{
				used = true;
			}

			if (!used)
			{
				portalIndex = i;
				m_portalCount++;
				break;
			}
		}
	}

	if (portalIndex >= 64)
	{
		return;
	}

	CAPos& portal = m_portals[portalIndex];

	portal.m_position.x = m_lastGroupPos.x;
	portal.m_position.y = m_lastGroupPos.y;
	portal.m_position.z = m_lastGroupPos.z;

	portal.m_groupA = groupLow;
	portal.m_groupB = groupHigh;

	System.Printf(const_cast<char*>(kAStarGroupDebugLabel));

	for (int i = 0; i < 64; ++i)
	{
		CAPos& p = m_portals[i];

		bool used = false;
		if (p.m_groupA != 0 && p.m_groupB != 0)
		{
			used = true;
		}

		if (used)
		{
			System.Printf(
				kAStarPortalDebugFormat,
				static_cast<double>(p.m_position.x),
				static_cast<double>(p.m_position.y),
				static_cast<double>(p.m_position.z),
				p.m_groupA,
				p.m_groupB
			);
		}
	}

	calcAStar();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CAPos* CAStar::getEscapePos(Vec& from, Vec& base, int startGroup, int forbiddenGroup)
{
	CVector baseVec(base);
	CVector fromVec(from);
	CVector diffBaseToFrom;

	PSVECSubtract(reinterpret_cast<Vec*>(&fromVec),
	              reinterpret_cast<Vec*>(&baseVec),
	              reinterpret_cast<Vec*>(&diffBaseToFrom));

	CVector escapeDir;
	escapeDir.x = diffBaseToFrom.x;
	escapeDir.y = diffBaseToFrom.y;
	escapeDir.z = diffBaseToFrom.z;

	escapeDir.Normalize();

	float behindBestDist = kAStarEscapeInitialBestDist;
	float aheadBestDist  = kAStarEscapeInitialBestDist;

	CAPos* behindBest = (CAPos*)nullptr;
	CAPos* aheadBest  = (CAPos*)nullptr;

	for (int i = 0; i < 64; ++i)
	{
		CAPos& portal = m_portals[i];

		bool exists = false;

		if (portal.m_groupA != 0 && portal.m_groupB != 0)
		{
			exists = true;
		}

		if (!exists)
		{
			continue;
		}

		bool connected = false;

		if (portal.m_groupA == startGroup || portal.m_groupB == startGroup)
		{
			connected = true;
		}

		if (!connected)
		{
			continue;
		}

		unsigned int otherGroup = portal.m_groupA;

		if (otherGroup == startGroup)
		{
			otherGroup = portal.m_groupB;
		}

		if (otherGroup == forbiddenGroup)
		{
			continue;
		}

		CVector baseVec1(base);
		CVector portalPos1(portal.m_position);

		Vec diffBaseToPortalNormSrc;
		CVector dirToPortal;

		PSVECSubtract(reinterpret_cast<Vec*>(&portalPos1),
		              reinterpret_cast<Vec*>(&baseVec1),
		              &diffBaseToPortalNormSrc);

		dirToPortal.x = diffBaseToPortalNormSrc.x;
		dirToPortal.y = diffBaseToPortalNormSrc.y;
		dirToPortal.z = diffBaseToPortalNormSrc.z;

		dirToPortal.Normalize();

		float dot = PSVECDotProduct(reinterpret_cast<Vec*>(&escapeDir),
		                            reinterpret_cast<Vec*>(&dirToPortal));

		CVector baseVec2(base);
		CVector portalPos2(portal.m_position);

		Vec diffBaseToPortalMagSrc;
		CVector diffForMag;

		// diffBaseToPortalMagSrc = portalPos2 - baseVec2;
		PSVECSubtract(reinterpret_cast<Vec*>(&portalPos2),
		              reinterpret_cast<Vec*>(&baseVec2),
		              &diffBaseToPortalMagSrc);

		diffForMag.x = diffBaseToPortalMagSrc.x;
		diffForMag.y = diffBaseToPortalMagSrc.y;
		diffForMag.z = diffBaseToPortalMagSrc.z;

		float dist = PSVECMag(reinterpret_cast<Vec*>(&diffForMag));

		if (dot < 0.0)
		{
			if (behindBestDist < dist)
			{
				behindBest    = &portal;
				behindBestDist = dist;
			}
		}
		else
		{
			if (aheadBestDist < dist)
			{
				aheadBest    = &portal;
				aheadBestDist = dist;
			}
		}
	}

	if (aheadBest != nullptr)
	{
		return aheadBest;
	}

	return behindBest;
}

/*
 * --INFO--
 * PAL Address: 0x80141724
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char CAStar::calcSpecialPolygonGroup(Vec* pos)
{
	unsigned int mask = m_hitAttributeMask;
	CVector base(kPolyGroupBaseXZ, kPolyGroupBaseY, kPolyGroupBaseXZ);
	CVector top(pos->x, pos->y + kPolyGroupTopOffsetY, pos->z);
	CMapCylinderRaw cyl;

	cyl.m_top.z = kPolyGroupAabbMax;
	cyl.m_top.y = kPolyGroupAabbMax;
	cyl.m_top.x = kPolyGroupAabbMax;
	cyl.m_direction2.z = kPolyGroupAabbMin;
	cyl.m_direction2.y = kPolyGroupAabbMin;
	cyl.m_direction2.x = kPolyGroupAabbMin;
	cyl.m_bottom.x = top.x;
	cyl.m_bottom.y = top.y;
	cyl.m_bottom.z = top.z;
	cyl.m_direction.x = base.x;
	cyl.m_direction.y = base.y;
	cyl.m_direction.z = base.z;
	cyl.m_radius = kPolyGroupBaseXZ;

	if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl),
	                                reinterpret_cast<Vec*>(&base), mask) != 0)
	{
		return reinterpret_cast<unsigned char*>(gMapHitFace)[0x47];
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80141550
 * PAL Size: 468b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char CAStar::calcPolygonGroup(Vec* pos, int hitAttributeMask)
{
	if ((AStar.m_flags & 1) != 0)
	{
		CVector base(kPolyGroupBaseXZ, kPolyGroupBaseY, kPolyGroupBaseXZ);
		CVector top(pos->x, pos->y + kPolyGroupTopOffsetY, pos->z);
		CMapCylinderRaw cyl;

		cyl.m_top.z = kPolyGroupAabbMax;
		cyl.m_top.y = kPolyGroupAabbMax;
		cyl.m_top.x = kPolyGroupAabbMax;
		cyl.m_direction2.z = kPolyGroupAabbMin;
		cyl.m_direction2.y = kPolyGroupAabbMin;
		cyl.m_direction2.x = kPolyGroupAabbMin;
		cyl.m_bottom.x = top.x;
		cyl.m_bottom.y = top.y;
		cyl.m_bottom.z = top.z;
		cyl.m_direction.x = base.x;
		cyl.m_direction.y = base.y;
		cyl.m_direction.z = base.z;
		cyl.m_radius = kPolyGroupBaseXZ;

		if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl),
		                                reinterpret_cast<Vec*>(&base), m_hitAttributeMask) != 0)
		{
			return reinterpret_cast<unsigned char*>(gMapHitFace)[0x47];
		}
	}
	else
	{
		CVector base(kPolyGroupBaseXZ, kPolyGroupBaseY, kPolyGroupBaseXZ);
		CVector top(pos->x, pos->y + kPolyGroupTopOffsetY, pos->z);
		CMapCylinderRaw cyl;

		cyl.m_top.z = kPolyGroupAabbMax;
		cyl.m_top.y = kPolyGroupAabbMax;
		cyl.m_top.x = kPolyGroupAabbMax;
		cyl.m_direction2.z = kPolyGroupAabbMin;
		cyl.m_direction2.y = kPolyGroupAabbMin;
		cyl.m_direction2.x = kPolyGroupAabbMin;
		cyl.m_bottom.x = top.x;
		cyl.m_bottom.y = top.y;
		cyl.m_bottom.z = top.z;
		cyl.m_direction.x = base.x;
		cyl.m_direction.y = base.y;
		cyl.m_direction.z = base.z;
		cyl.m_radius = kPolyGroupBaseXZ;

		if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl),
		                                reinterpret_cast<Vec*>(&base), hitAttributeMask) != 0)
		{
			return reinterpret_cast<unsigned char*>(gMapHitFace)[0x47];
		}
	}

	return 0;
}

float CAStar::CAPos::CalcLength(CAStar::CAPos& other)
{
	return PSVECDistance(&this->m_position, &other.m_position);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CATemp::CATemp(const CAStar::CATemp& other)
{
	u32 v0;
	u32 v1;
	u32 v2;

	u32* dstV = reinterpret_cast<u32*>(m_visited);
	const u32* srcV = reinterpret_cast<const u32*>(other.m_visited);

	v2 = srcV[1];
	v0 = srcV[0];
	dstV[0] = v0;
	v1 = srcV[2];
	dstV[1] = v2;
	v2 = srcV[3];
	dstV[2] = v1;
	v1 = srcV[4];
	dstV[3] = v2;
	v2 = srcV[5];
	dstV[4] = v1;
	v1 = srcV[6];
	dstV[5] = v2;
	v2 = srcV[7];
	dstV[6] = v1;
	v1 = srcV[8];
	dstV[7] = v2;
	v2 = srcV[9];
	dstV[8] = v1;
	v1 = srcV[10];
	dstV[9] = v2;
	v2 = srcV[11];
	dstV[10] = v1;
	v1 = srcV[12];
	dstV[11] = v2;
	v2 = srcV[13];
	dstV[12] = v1;
	v1 = srcV[14];
	dstV[13] = v2;
	v2 = srcV[15];
	dstV[14] = v1;

	u32* dstP = reinterpret_cast<u32*>(m_path);
	const u32* srcP = reinterpret_cast<const u32*>(other.m_path);

	v0 = srcP[0];
	dstV[15] = v2;
	v1 = srcP[1];
	dstP[0] = v0;
	v0 = srcP[2];
	dstP[1] = v1;
	v1 = srcP[3];
	dstP[2] = v0;
	v0 = srcP[4];
	dstP[3] = v1;
	v1 = srcP[5];
	dstP[4] = v0;
	v0 = srcP[6];
	dstP[5] = v1;
	v1 = srcP[7];
	dstP[6] = v0;
	v0 = srcP[8];
	dstP[7] = v1;
	v1 = srcP[9];
	dstP[8] = v0;
	v0 = srcP[10];
	dstP[9] = v1;
	v1 = srcP[11];
	dstP[10] = v0;
	v0 = srcP[12];
	dstP[11] = v1;
	v1 = srcP[13];
	dstP[12] = v0;
	v0 = srcP[14];
	dstP[13] = v1;
	v1 = srcP[15];
	dstP[14] = v0;

	int pathLength = other.m_pathLength;
	dstP[15] = v1;
	float cost = other.m_cost;
	m_pathLength = pathLength;
	m_cost = cost;
}

unsigned char CAStar::CAPos::GetOthers(int group)
{
	unsigned char others = m_groupA;

	if (others == group)
	{
		others = m_groupB;
	}

	return (unsigned char)others;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CAStar::CAPos::IsExist(int group)
{
	bool result = false;

	if (m_groupA == group || m_groupB == group)
	{
		result = true;
	}

	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::CATemp::operator= (const CAStar::CATemp& other)
{
	u32 v0;
	u32 v1;
	u32 v2;

	u32* dstV = reinterpret_cast<u32*>(m_visited);
	const u32* srcV = reinterpret_cast<const u32*>(other.m_visited);

	v2 = srcV[1];
	v0 = srcV[0];
	dstV[0] = v0;
	v1 = srcV[2];
	dstV[1] = v2;
	v2 = srcV[3];
	dstV[2] = v1;
	v1 = srcV[4];
	dstV[3] = v2;
	v2 = srcV[5];
	dstV[4] = v1;
	v1 = srcV[6];
	dstV[5] = v2;
	v2 = srcV[7];
	dstV[6] = v1;
	v1 = srcV[8];
	dstV[7] = v2;
	v2 = srcV[9];
	dstV[8] = v1;
	v1 = srcV[10];
	dstV[9] = v2;
	v2 = srcV[11];
	dstV[10] = v1;
	v1 = srcV[12];
	dstV[11] = v2;
	v2 = srcV[13];
	dstV[12] = v1;
	v1 = srcV[14];
	dstV[13] = v2;
	v2 = srcV[15];
	dstV[14] = v1;

	u32* dstP = reinterpret_cast<u32*>(m_path);
	const u32* srcP = reinterpret_cast<const u32*>(other.m_path);

	v0 = srcP[0];
	dstV[15] = v2;
	v1 = srcP[1];
	dstP[0] = v0;
	v0 = srcP[2];
	dstP[1] = v1;
	v1 = srcP[3];
	dstP[2] = v0;
	v0 = srcP[4];
	dstP[3] = v1;
	v1 = srcP[5];
	dstP[4] = v0;
	v0 = srcP[6];
	dstP[5] = v1;
	v1 = srcP[7];
	dstP[6] = v0;
	v0 = srcP[8];
	dstP[7] = v1;
	v1 = srcP[9];
	dstP[8] = v0;
	v0 = srcP[10];
	dstP[9] = v1;
	v1 = srcP[11];
	dstP[10] = v0;
	v0 = srcP[12];
	dstP[11] = v1;
	v1 = srcP[13];
	dstP[12] = v0;
	v0 = srcP[14];
	dstP[13] = v1;
	v1 = srcP[15];
	dstP[14] = v0;

	int pathLength = other.m_pathLength;
	dstP[15] = v1;
	float cost = other.m_cost;
	m_pathLength = pathLength;
	m_cost = cost;
}

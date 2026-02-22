#include "ffcc/astar.h"

#include "ffcc/charaobj.h"
#include "ffcc/color.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/pad.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/system.h"
#include "ffcc/vector.h"

#include "string.h"

static const float kPolyGroupBaseX = 0.0f;       // FLOAT_80332088
static const float kPolyGroupBaseY = -100.0f;    // FLOAT_8033208c
static const float kPolyGroupBaseZ = 0.0f;       // FLOAT_80332088
static const float kPolyGroupTopOffsetY = 5.0f;  // FLOAT_80332090
static const float kPolyGroupAabbMax = 1.0e10f;  // FLOAT_80332094
static const float kPolyGroupAabbMin = -1.0e10f; // FLOAT_80332098
static const float kInfiniteCost = 10000000.0f;  // FLOAT_8033209c
static const float kDrawAStarSphereRadius = 5.0f;

struct CMapCylinderRaw
{
	Vec m_bottom;
	Vec m_direction;
	float m_radius;
	float m_height;
	Vec m_top;
	Vec m_direction2;
	float m_radius2;
	float m_height2;
};

extern Mtx gFlatPosMtx;
extern int DAT_8032ed70;
extern unsigned char lbl_8032EC90[];
extern char lbl_801DD6A8[];
extern char lbl_801DD6B4[];
extern char lbl_803320A0[];
extern CMath Math;
extern "C" int __cntlzw(unsigned int);

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
	int start = startGroup;

	temp.m_visited[start] = 1;

	if (start == goalGroup)
	{
		if (temp.m_cost < m_bestPath.m_cost)
		{
			unsigned int* dstV = reinterpret_cast<unsigned int*>(m_bestPath.m_visited);
			unsigned int* srcV = reinterpret_cast<unsigned int*>(temp.m_visited);
			unsigned int* dstP = reinterpret_cast<unsigned int*>(m_bestPath.m_path);
			unsigned int* srcP = reinterpret_cast<unsigned int*>(temp.m_path);

			dstV[0]  = srcV[0];
			dstV[1]  = srcV[1];
			dstV[2]  = srcV[2];
			dstV[3]  = srcV[3];
			dstV[4]  = srcV[4];
			dstV[5]  = srcV[5];
			dstV[6]  = srcV[6];
			dstV[7]  = srcV[7];
			dstV[8]  = srcV[8];
			dstV[9]  = srcV[9];
			dstV[10] = srcV[10];
			dstV[11] = srcV[11];
			dstV[12] = srcV[12];
			dstV[13] = srcV[13];
			dstV[14] = srcV[14];
			dstV[15] = srcV[15];

			dstP[0]  = srcP[0];
			dstP[1]  = srcP[1];
			dstP[2]  = srcP[2];
			dstP[3]  = srcP[3];
			dstP[4]  = srcP[4];
			dstP[5]  = srcP[5];
			dstP[6]  = srcP[6];
			dstP[7]  = srcP[7];
			dstP[8]  = srcP[8];
			dstP[9]  = srcP[9];
			dstP[10] = srcP[10];
			dstP[11] = srcP[11];
			dstP[12] = srcP[12];
			dstP[13] = srcP[13];
			dstP[14] = srcP[14];
			dstP[15] = srcP[15];

			m_bestPath.m_pathLength = temp.m_pathLength;
			m_bestPath.m_cost	   = temp.m_cost;
		}

		return;
	}

	int idx0 = 0;
	CAPos* pos0 = &m_portals[0];

	while (idx0 < 64)
	{
		unsigned char groupA0 = pos0->m_groupA;
		unsigned char groupB0 = pos0->m_groupB;
		bool		  connected0 = false;

		if (groupA0 == start || groupB0 == start)
		{
			connected0 = true;
		}

		if (connected0)
		{
			unsigned char other0 = groupA0;

			if (groupA0 == start)
			{
				other0 = groupB0;
			}

			if (temp.m_visited[other0] == 0)
			{
				unsigned int v1[16];
				unsigned int p1[16];
				int		  pathLen1;
				float		cost1;

				{
					unsigned int* srcV = reinterpret_cast<unsigned int*>(temp.m_visited);
					v1[0]  = srcV[0];  v1[1]  = srcV[1];
					v1[2]  = srcV[2];  v1[3]  = srcV[3];
					v1[4]  = srcV[4];  v1[5]  = srcV[5];
					v1[6]  = srcV[6];  v1[7]  = srcV[7];
					v1[8]  = srcV[8];  v1[9]  = srcV[9];
					v1[10] = srcV[10]; v1[11] = srcV[11];
					v1[12] = srcV[12]; v1[13] = srcV[13];
					v1[14] = srcV[14]; v1[15] = srcV[15];
				}

				{
					unsigned int* srcP = reinterpret_cast<unsigned int*>(temp.m_path);
					p1[0]  = srcP[0];  p1[1]  = srcP[1];
					p1[2]  = srcP[2];  p1[3]  = srcP[3];
					p1[4]  = srcP[4];  p1[5]  = srcP[5];
					p1[6]  = srcP[6];  p1[7]  = srcP[7];
					p1[8]  = srcP[8];  p1[9]  = srcP[9];
					p1[10] = srcP[10]; p1[11] = srcP[11];
					p1[12] = srcP[12]; p1[13] = srcP[13];
					p1[14] = srcP[14]; p1[15] = srcP[15];
				}

				pathLen1 = temp.m_pathLength;
				cost1	= temp.m_cost;
				cost1   += PSVECDistance(&pos0->m_position,
										 &m_portals[other0].m_position);

				reinterpret_cast<unsigned char*>(p1)[pathLen1] =
					static_cast<unsigned char>(idx0);
				++pathLen1;
				reinterpret_cast<unsigned char*>(v1)[other0] = 1;

				if (other0 == static_cast<unsigned char>(goalGroup))
				{
					if (cost1 < m_bestPath.m_cost)
					{
						unsigned int* dstVBest =
							reinterpret_cast<unsigned int*>(m_bestPath.m_visited);
						unsigned int* dstPBest =
							reinterpret_cast<unsigned int*>(m_bestPath.m_path);

						dstVBest[0]  = v1[0];
						dstVBest[1]  = v1[1];
						dstVBest[2]  = v1[2];
						dstVBest[3]  = v1[3];
						dstVBest[4]  = v1[4];
						dstVBest[5]  = v1[5];
						dstVBest[6]  = v1[6];
						dstVBest[7]  = v1[7];
						dstVBest[8]  = v1[8];
						dstVBest[9]  = v1[9];
						dstVBest[10] = v1[10];
						dstVBest[11] = v1[11];
						dstVBest[12] = v1[12];
						dstVBest[13] = v1[13];
						dstVBest[14] = v1[14];
						dstVBest[15] = v1[15];

						dstPBest[0]  = p1[0];
						dstPBest[1]  = p1[1];
						dstPBest[2]  = p1[2];
						dstPBest[3]  = p1[3];
						dstPBest[4]  = p1[4];
						dstPBest[5]  = p1[5];
						dstPBest[6]  = p1[6];
						dstPBest[7]  = p1[7];
						dstPBest[8]  = p1[8];
						dstPBest[9]  = p1[9];
						dstPBest[10] = p1[10];
						dstPBest[11] = p1[11];
						dstPBest[12] = p1[12];
						dstPBest[13] = p1[13];
						dstPBest[14] = p1[14];
						dstPBest[15] = p1[15];

						m_bestPath.m_pathLength = pathLen1;
						m_bestPath.m_cost	   = cost1;
					}
				}
				else
				{
					unsigned char* visited1 =
						reinterpret_cast<unsigned char*>(v1);
					unsigned char* path1 =
						reinterpret_cast<unsigned char*>(p1);
					unsigned char other0U8 = other0;
					int		   idx1	 = 0;

					CAPos* pos1 = &m_portals[0];

					while (idx1 < 64)
					{
						unsigned char gA1 = pos1->m_groupA;
						unsigned char gB1 = pos1->m_groupB;
						bool		  connected1 = false;

						if (gA1 == other0U8 || gB1 == other0U8)
						{
							connected1 = true;
						}

						if (connected1)
						{
							unsigned char other1 = gA1;

							if (gA1 == other0U8)
							{
								other1 = gB1;
							}

							if (visited1[other1] == 0)
							{
								unsigned int v2[16];
								unsigned int p2[16];

								p2[0]  = p1[0];
								p2[1]  = p1[1];
								p2[2]  = p1[2];
								p2[3]  = p1[3];
								p2[4]  = p1[4];
								p2[5]  = p1[5];
								p2[6]  = p1[6];
								p2[7]  = p1[7];
								p2[8]  = p1[8];
								p2[9]  = p1[9];
								p2[10] = p1[10];
								p2[11] = p1[11];
								p2[12] = p1[12];
								p2[13] = p1[13];
								p2[14] = p1[14];
								p2[15] = p1[15];

								v2[0]  = v1[0];
								v2[1]  = v1[1];
								v2[2]  = v1[2];
								v2[3]  = v1[3];
								v2[4]  = v1[4];
								v2[5]  = v1[5];
								v2[6]  = v1[6];
								v2[7]  = v1[7];
								v2[8]  = v1[8];
								v2[9]  = v1[9];
								v2[10] = v1[10];
								v2[11] = v1[11];
								v2[12] = v1[12];
								v2[13] = v1[13];
								v2[14] = v1[14];
								v2[15] = v1[15];

								int   pathLen2 = pathLen1;
								float cost2	= cost1;

								cost2 += PSVECDistance(
									&pos1->m_position,
									&m_portals[other1].m_position);

								unsigned char* visited2 =
									reinterpret_cast<unsigned char*>(v2);
								unsigned char* path2 =
									reinterpret_cast<unsigned char*>(p2);

								visited2[other1] = 1;
								path2[pathLen2]  =
									static_cast<unsigned char>(idx1);
								++pathLen2;

								CATemp level2;

								for (int w = 0; w < 64; ++w)
								{
									level2.m_visited[w] = visited2[w];
									level2.m_path[w]	= path2[w];
								}

								level2.m_pathLength = pathLen2;
								level2.m_cost	   = cost2;

								if (other1 ==
									static_cast<unsigned char>(goalGroup))
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
										CAPos& edge = m_portals[idx2];

										if (!edge.IsExist(
												static_cast<int>(other1)))
											continue;

										int nextGroup =
											edge.GetOthers(
												static_cast<int>(other1));

										if (level2.m_visited[nextGroup] != 0)
											continue;

										CATemp deeper(level2);
										deeper.m_cost += edge.CalcLength(
											m_portals[nextGroup]);
										deeper.m_path[deeper.m_pathLength] =
											static_cast<unsigned char>(idx2);
										++deeper.m_pathLength;

										check(nextGroup, goalGroup, deeper);
									}
								}
							}
						}

						++idx1;
						++pos1;
					}
				}
			}
		}

		idx0++;
		pos0++;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::calcAStar()
{
	memset(m_routeTable, 0, sizeof(m_routeTable));

	for (int from = 0; from < 64; ++from)
	{
		for (int to = 0; to < 64; ++to)
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
				System.Printf("%d->%d=%.5fm ", from, to, m_bestPath.m_cost);

				int current = from;

				for (int i = 0; i < m_bestPath.m_pathLength; ++i)
				{
					unsigned char portalIndex = m_bestPath.m_path[i];

					m_routeTable[current][0][1] = portalIndex;

					unsigned int next = m_portals[portalIndex].m_groupA;

					if (next == static_cast<unsigned int>(current))
					{
						next = m_portals[portalIndex].m_groupB;
					}

					m_routeTable[current][0][0] = static_cast<unsigned char>(next);

					System.Printf("%d ", static_cast<int>(next));

					current = static_cast<int>(next);
				}

				System.Printf("\n");
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
	if ((DAT_8032ed70 & 0x400) != 0)
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

			for (int side = 0; side < 2; ++side)
			{
				unsigned char group = (side == 0) ? portal.m_groupA : portal.m_groupB;

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

	Graphic.Printf(10, 10, lbl_801DD6A8, static_cast<int>(gPartyObj->m_aStarGroupId));

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

	System.Printf(lbl_803320A0);

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
				lbl_801DD6B4,
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

	float behindBestDist = -1000000.0f;
	float aheadBestDist  = -1000000.0f;

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
	unsigned long mask = m_hitAttributeMask;
	CVector base(kPolyGroupBaseX, kPolyGroupBaseY, kPolyGroupBaseZ);
	CVector top(pos->x, pos->y + kPolyGroupTopOffsetY, pos->z);
	CMapCylinderRaw cyl;

	cyl.m_bottom = *reinterpret_cast<Vec*>(&top);
	cyl.m_direction = *reinterpret_cast<Vec*>(&base);
	cyl.m_radius = kPolyGroupBaseZ;
	cyl.m_height = kPolyGroupAabbMax;
	cyl.m_top.x = kPolyGroupAabbMax;
	cyl.m_top.y = kPolyGroupAabbMax;
	cyl.m_top.z = kPolyGroupAabbMax;
	cyl.m_direction2.x = kPolyGroupAabbMin;
	cyl.m_direction2.y = kPolyGroupAabbMin;
	cyl.m_direction2.z = kPolyGroupAabbMin;

	if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl),
	                                reinterpret_cast<Vec*>(&base), mask) != 0)
	{
		return lbl_8032EC90[0x47];
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
	if ((DAT_8032ed70 & 1) == 0)
	{
		CVector base(kPolyGroupBaseX, kPolyGroupBaseY, kPolyGroupBaseZ);
		CVector top(pos->x, pos->y + kPolyGroupTopOffsetY, pos->z);
		CMapCylinderRaw cyl;

		cyl.m_bottom = *reinterpret_cast<Vec*>(&top);
		cyl.m_direction = *reinterpret_cast<Vec*>(&base);
		cyl.m_radius = kPolyGroupBaseZ;
		cyl.m_height = kPolyGroupAabbMax;
		cyl.m_top.x = kPolyGroupAabbMax;
		cyl.m_top.y = kPolyGroupAabbMax;
		cyl.m_top.z = kPolyGroupAabbMax;
		cyl.m_direction2.x = kPolyGroupAabbMin;
		cyl.m_direction2.y = kPolyGroupAabbMin;
		cyl.m_direction2.z = kPolyGroupAabbMin;

		if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl),
		                                reinterpret_cast<Vec*>(&base), hitAttributeMask) != 0)
		{
			return lbl_8032EC90[0x47];
		}
	}
	else
	{
		CVector base(kPolyGroupBaseX, kPolyGroupBaseY, kPolyGroupBaseZ);
		CVector top(pos->x, pos->y + kPolyGroupTopOffsetY, pos->z);
		CMapCylinderRaw cyl;

		cyl.m_bottom = *reinterpret_cast<Vec*>(&top);
		cyl.m_direction = *reinterpret_cast<Vec*>(&base);
		cyl.m_radius = kPolyGroupBaseZ;
		cyl.m_height = kPolyGroupAabbMax;
		cyl.m_top.x = kPolyGroupAabbMax;
		cyl.m_top.y = kPolyGroupAabbMax;
		cyl.m_top.z = kPolyGroupAabbMax;
		cyl.m_direction2.x = kPolyGroupAabbMin;
		cyl.m_direction2.y = kPolyGroupAabbMin;
		cyl.m_direction2.z = kPolyGroupAabbMin;

		if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl),
		                                reinterpret_cast<Vec*>(&base), m_hitAttributeMask) != 0)
		{
			return lbl_8032EC90[0x47];
		}
	}

	return 0;
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

	u32* dstV = reinterpret_cast<u32*>(m_visited);
	const u32* srcV = reinterpret_cast<const u32*>(other.m_visited);

	v1 = srcV[1];
	dstV[0] = srcV[0];
	v0 = srcV[2];
	dstV[1] = v1;
	v1 = srcV[3];
	dstV[2] = v0;
	v0 = srcV[4];
	dstV[3] = v1;
	v1 = srcV[5];
	dstV[4] = v0;
	v0 = srcV[6];
	dstV[5] = v1;
	v1 = srcV[7];
	dstV[6] = v0;
	v0 = srcV[8];
	dstV[7] = v1;
	v1 = srcV[9];
	dstV[8] = v0;
	v0 = srcV[10];
	dstV[9] = v1;
	v1 = srcV[11];
	dstV[10] = v0;
	v0 = srcV[12];
	dstV[11] = v1;
	v1 = srcV[13];
	dstV[12] = v0;
	v0 = srcV[14];
	dstV[13] = v1;
	v1 = srcV[15];
	dstV[14] = v0;

	u32* dstP = reinterpret_cast<u32*>(m_path);
	const u32* srcP = reinterpret_cast<const u32*>(other.m_path);

	v0 = srcP[0];
	dstV[15] = v1;
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

	u32* dstV = reinterpret_cast<u32*>(m_visited);
	const u32* srcV = reinterpret_cast<const u32*>(other.m_visited);

	v1 = srcV[1];
	dstV[0] = srcV[0];
	v0 = srcV[2];
	dstV[1] = v1;
	v1 = srcV[3];
	dstV[2] = v0;
	v0 = srcV[4];
	dstV[3] = v1;
	v1 = srcV[5];
	dstV[4] = v0;
	v0 = srcV[6];
	dstV[5] = v1;
	v1 = srcV[7];
	dstV[6] = v0;
	v0 = srcV[8];
	dstV[7] = v1;
	v1 = srcV[9];
	dstV[8] = v0;
	v0 = srcV[10];
	dstV[9] = v1;
	v1 = srcV[11];
	dstV[10] = v0;
	v0 = srcV[12];
	dstV[11] = v1;
	v1 = srcV[13];
	dstV[12] = v0;
	v0 = srcV[14];
	dstV[13] = v1;
	v1 = srcV[15];
	dstV[14] = v0;

	u32* dstP = reinterpret_cast<u32*>(m_path);
	const u32* srcP = reinterpret_cast<const u32*>(other.m_path);

	v0 = srcP[0];
	dstV[15] = v1;
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

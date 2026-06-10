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
extern "C" {
extern const char kAStarGroupDebugFormat[] = "A* GROUP=%d";
extern const char kAStarPortalDebugFormat[] = "addAStar(%.5f, %.5f, %.5f, %d, %d, 0, 0);\n";
extern const char kAStarCostDebugFormat[0x18] = "\x8d\xc5\x92\x5a\x8c\x6f\x98\x48%d->%d=%.5fm ";
extern const float kPolyGroupBaseXZ = 0.0f;
extern const float kPolyGroupBaseY = -100.0f;
extern const float kPolyGroupTopOffsetY = 5.0f;
extern const float kPolyGroupAabbMax = 10000000000.0f;
extern const float kPolyGroupAabbMin = -10000000000.0f;
extern const float kAStarEscapeInitialBestDist = -1000000.0f;
extern const char kAStarGroupDebugLabel[] = "//A*\n";
extern const float kDrawAStarSphereRadius;
extern const float kInfiniteCost;
extern const char kAStarStepDebugFormat[4];
extern const char kAStarNewLine[4];
}
#include "ffcc/system.h"
#include "ffcc/vector.h"

#include "string.h"

struct CMapCylinderRaw
{
	Vec m_bottom;
	Vec m_top;
	Vec m_axis;
	float m_radius;
	Vec m_boundsMax;
	Vec m_boundsMin;
};

struct CABlock
{
	unsigned int m_words[16];
};

static inline float LoadFloat(const float& value)
{
	return value;
}

CAStar AStar;

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
		unsigned int mask = m_hitAttributeMask;
		const CVector& baseVec =
		    CVector(LoadFloat(kPolyGroupBaseXZ), LoadFloat(kPolyGroupBaseY), LoadFloat(kPolyGroupBaseXZ));
		const CVector& topVec = CVector(pos->x, kPolyGroupTopOffsetY + pos->y, pos->z);
		Vec* base = reinterpret_cast<Vec*>(const_cast<CVector*>(&baseVec));
		Vec* top = reinterpret_cast<Vec*>(const_cast<CVector*>(&topVec));
		CMapCylinderRaw cyl;
		float aabbMin = LoadFloat(kPolyGroupAabbMin);
		float aabbMax = LoadFloat(kPolyGroupAabbMax);

		cyl.m_boundsMax.z = aabbMax;
		cyl.m_boundsMax.y = aabbMax;
		cyl.m_boundsMax.x = aabbMax;
		cyl.m_boundsMin.z = aabbMin;
		cyl.m_boundsMin.y = aabbMin;
		cyl.m_boundsMin.x = aabbMin;
		cyl.m_bottom = *top;
		cyl.m_axis = *base;
		cyl.m_radius = LoadFloat(kPolyGroupBaseXZ);

		if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl), base, mask) != 0)
		{
			return gMapHitFace->m_groupIndex;
		}

		return 0;
	}
	else
	{
		const CVector& baseVec =
		    CVector(LoadFloat(kPolyGroupBaseXZ), LoadFloat(kPolyGroupBaseY), LoadFloat(kPolyGroupBaseXZ));
		const CVector& topVec = CVector(pos->x, kPolyGroupTopOffsetY + pos->y, pos->z);
		Vec* base = reinterpret_cast<Vec*>(const_cast<CVector*>(&baseVec));
		Vec* top = reinterpret_cast<Vec*>(const_cast<CVector*>(&topVec));
		CMapCylinderRaw cyl;
		float aabbMin = LoadFloat(kPolyGroupAabbMin);
		float aabbMax = LoadFloat(kPolyGroupAabbMax);

		cyl.m_boundsMax.z = aabbMax;
		cyl.m_boundsMax.y = aabbMax;
		cyl.m_boundsMax.x = aabbMax;
		cyl.m_boundsMin.z = aabbMin;
		cyl.m_boundsMin.y = aabbMin;
		cyl.m_boundsMin.x = aabbMin;
		cyl.m_bottom = *top;
		cyl.m_axis = *base;
		cyl.m_radius = LoadFloat(kPolyGroupBaseXZ);

		if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl), base, hitAttributeMask) != 0)
		{
			return gMapHitFace->m_groupIndex;
		}

		return 0;
	}
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
	const CVector& baseVec =
	    CVector(LoadFloat(kPolyGroupBaseXZ), LoadFloat(kPolyGroupBaseY), LoadFloat(kPolyGroupBaseXZ));
	const CVector& topVec = CVector(pos->x, kPolyGroupTopOffsetY + pos->y, pos->z);
	Vec* base = reinterpret_cast<Vec*>(const_cast<CVector*>(&baseVec));
	Vec* top = reinterpret_cast<Vec*>(const_cast<CVector*>(&topVec));
	CMapCylinderRaw cyl;
	float aabbMin = LoadFloat(kPolyGroupAabbMin);
	float aabbMax = LoadFloat(kPolyGroupAabbMax);

	cyl.m_boundsMax.z = aabbMax;
	cyl.m_boundsMax.y = aabbMax;
	cyl.m_boundsMax.x = aabbMax;
	cyl.m_boundsMin.z = aabbMin;
	cyl.m_boundsMin.y = aabbMin;
	cyl.m_boundsMin.x = aabbMin;
	cyl.m_bottom = *top;
	cyl.m_axis = *base;
	cyl.m_radius = LoadFloat(kPolyGroupBaseXZ);

	if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cyl), base, mask) != 0)
	{
		return gMapHitFace->m_groupIndex;
	}

	return 0;
}
/*
 * --INFO--
 * PAL Address: 0x80141820
 * PAL Size: 584b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CAStar::CAPos* CAStar::getEscapePos(Vec& from, Vec& base, int startGroup, int forbiddenGroup)
{
	Vec escapeDir;
	CVector baseVec(base);
	Vec* fromVec = reinterpret_cast<Vec*>(&CVector(from));
	CVector escapeDirSource;

	PSVECSubtract(fromVec, reinterpret_cast<Vec*>(&baseVec), reinterpret_cast<Vec*>(&escapeDirSource));

	escapeDir.x = escapeDirSource.x;
	escapeDir.y = escapeDirSource.y;
	escapeDir.z = escapeDirSource.z;
	reinterpret_cast<CVector*>(&escapeDir)->Normalize();

	CAPos* aheadBest = (CAPos*)0;
	CAPos* behindBest = (CAPos*)0;
	double aheadBestDist = LoadFloat(kAStarEscapeInitialBestDist);
	double behindBestDist = aheadBestDist;
	int i = 0;

	do
	{
		unsigned char otherGroup = m_portals[i].m_groupA;
		bool exists = false;

		if (otherGroup != 0 && m_portals[i].m_groupB != 0)
		{
			exists = true;
		}

		if (exists)
		{
			bool connected = false;

			if (otherGroup == startGroup || m_portals[i].m_groupB == startGroup)
			{
				connected = true;
			}

			if (connected)
			{
				if (otherGroup == startGroup)
				{
					otherGroup = m_portals[i].m_groupB;
				}

				if (forbiddenGroup != otherGroup)
				{
					CVector portalDirBase(base);
					Vec* portalDirPos = reinterpret_cast<Vec*>(&CVector(m_portals[i].m_position));
					CVector dirToPortalSource;
					Vec portalVec;

					PSVECSubtract(portalDirPos, reinterpret_cast<Vec*>(&portalDirBase),
					              reinterpret_cast<Vec*>(&dirToPortalSource));

					portalVec.x = dirToPortalSource.x;
					portalVec.y = dirToPortalSource.y;
					portalVec.z = dirToPortalSource.z;
					reinterpret_cast<CVector*>(&portalVec)->Normalize();

					float dot = PSVECDotProduct(reinterpret_cast<Vec*>(&escapeDir),
					                            reinterpret_cast<Vec*>(&portalVec));

					CVector distBase(base);
					Vec* distPortal = reinterpret_cast<Vec*>(&CVector(m_portals[i].m_position));
					CVector distVecSource;

					PSVECSubtract(distPortal, reinterpret_cast<Vec*>(&distBase),
					              reinterpret_cast<Vec*>(&distVecSource));

					portalVec.x = distVecSource.x;
					portalVec.y = distVecSource.y;
					portalVec.z = distVecSource.z;

					float dist = PSVECMag(reinterpret_cast<Vec*>(&portalVec));

					if (dot >= LoadFloat(kPolyGroupBaseXZ))
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

	Graphic.Printf(10, 10, const_cast<char*>(kAStarGroupDebugFormat), static_cast<int>(gPartyObj->m_aStarGroupId));

	int padLock = Pad.m_debugPadLock;
	bool padBusy = false;

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
		int padIndex = 0;
		padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
		trig1 = Pad.GetPadInputs()[padIndex].buttonDown[0];
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
		int padIndex = 0;
		padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
		trig2 = Pad.GetPadInputs()[padIndex].button[0];
	}

	if ((trig2 & 0x40) == 0)
	{
		return;
	}

	int groupLow = m_currentGroup;
	int groupHigh = m_previousGroup;

	if (groupHigh < groupLow)
	{
		int groupSwap = groupLow;
		groupLow = groupHigh;
		groupHigh = groupSwap;
	}

	int portalIndex = 0;

	// Look for an existing portal (groupLow, groupHigh)
	for (; portalIndex < 64; ++portalIndex)
	{
		CAPos& p = m_portals[portalIndex];

		if (p.m_groupA == groupLow && p.m_groupB == groupHigh)
		{
			break;
		}
	}

	// If none, find a free slot
	if (portalIndex == 64)
	{
		portalIndex = 0;

		for (; portalIndex < 64; ++portalIndex)
		{
			CAPos& p = m_portals[portalIndex];

			bool used = false;
			if (p.m_groupA != 0 && p.m_groupB != 0)
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

	CAPos& portal = m_portals[portalIndex];

	portal.m_position.x = m_lastGroupPos.x;
	portal.m_position.y = m_lastGroupPos.y;
	portal.m_position.z = m_lastGroupPos.z;

	m_portals[portalIndex].m_groupA = groupLow;
	m_portals[portalIndex].m_groupB = groupHigh;

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
				const_cast<char*>(kAStarPortalDebugFormat),
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
		if (static_cast<int>(System.m_frameCounter) % 30 == 0)
		{
			int group = 0;

			do
			{
				unsigned char b = static_cast<unsigned char>(Math.Rand(0xff));
				unsigned char g = static_cast<unsigned char>(Math.Rand(0xff));
				unsigned char r = static_cast<unsigned char>(Math.Rand(0xff));
				MapMng.SetIdGrpColor(group, 0, CColor(r, g, b, 0xFF).color);
				++group;
			} while (group < 64);
		}

		bool hasGroups = false;
		float (*drawMtx)[4] = CameraPcs.m_cameraMatrix;

		if (m_currentGroup != 0 && m_previousGroup != 0)
		{
			hasGroups = true;
		}

		if (hasGroups)
		{
			CColor white(0xFF, 0xFF, 0xFF, 0xFF);
			Graphic.DrawSphere(drawMtx, &m_lastGroupPos, LoadFloat(kDrawAStarSphereRadius), &white.color);
		}

		int i = 0;

		do
		{
			bool exists = false;

			if (m_portals[i].m_groupA != 0 && m_portals[i].m_groupB != 0)
			{
				exists = true;
			}

			if (exists)
			{
				CColor yellow(0xFF, 0xFF, 0x00, 0xFF);
				Graphic.DrawSphere(drawMtx, &m_portals[i].m_position, LoadFloat(kDrawAStarSphereRadius), &yellow.color);

				int side = 0;
				unsigned char* group = &m_portals[i].m_groupA;

				do
				{
					int groupId = *group;

					if (groupId != 0)
					{
						int j = 0;

						do
						{
							if (i != j)
							{
								bool otherExists = false;

								if (m_portals[j].m_groupA != 0 && m_portals[j].m_groupB != 0)
								{
									otherExists = true;
								}

								if (otherExists)
								{
									bool matches = false;

									if (m_portals[j].m_groupA == groupId || m_portals[j].m_groupB == groupId)
									{
										matches = true;
									}

									if (matches)
									{
										GXLoadPosMtxImm(drawMtx, GX_PNMTX0);
										GXBegin((GXPrimitive)0xA8, GX_VTXFMT0, 2);
										GXPosition3f32(
											m_portals[i].m_position.x,
											m_portals[i].m_position.y + kPolyGroupTopOffsetY,
											m_portals[i].m_position.z);
										GXPosition3f32(
											m_portals[j].m_position.x,
											m_portals[j].m_position.y + kPolyGroupTopOffsetY,
											m_portals[j].m_position.z);
									}
								}
							}

							++j;
						} while (j < 64);
					}

					++side;
					++group;
				} while (side < 2);
			}

			++i;
		} while (i < 64);
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

	for (unsigned int to = 0; to < 64; ++to)
	{
		for (int from = 0; from < 64; ++from)
		{
			if (from == to)
			{
				continue;
			}

			m_bestPath.m_cost = LoadFloat(kInfiniteCost);

			CATemp temp;

			memset(&temp, 0, sizeof(temp));

			check(from, to, temp);

			if (m_bestPath.m_cost < LoadFloat(kInfiniteCost))
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
			*reinterpret_cast<CABlock*>(m_bestPath.m_visited) = *reinterpret_cast<CABlock*>(temp.m_visited);
			*reinterpret_cast<CABlock*>(m_bestPath.m_path) = *reinterpret_cast<CABlock*>(temp.m_path);
			m_bestPath.m_pathLength = temp.m_pathLength;
			m_bestPath.m_cost = temp.m_cost;
		}

		return;
	}

	CAPos* pos0 = m_portals;
	int idx0 = 0;
	do
	{
		int other0 = pos0->m_groupA;
		bool connected0 = (other0 == startGroup || pos0->m_groupB == startGroup);

		if (connected0)
		{
			if (other0 == startGroup)
			{
				other0 = pos0->m_groupB;
			}

			int other0Index = static_cast<unsigned char>(other0);

			if (temp.m_visited[other0Index] == 0)
			{
				CATemp level1;
				*reinterpret_cast<CABlock*>(level1.m_visited) = *reinterpret_cast<CABlock*>(temp.m_visited);
				*reinterpret_cast<CABlock*>(level1.m_path) = *reinterpret_cast<CABlock*>(temp.m_path);
				level1.m_pathLength = temp.m_pathLength;
				level1.m_cost = temp.m_cost;
				float distance1 = PSVECDistance(&pos0->m_position, &m_portals[other0Index].m_position);
				int pathSlot1 = level1.m_pathLength;
				level1.m_pathLength = pathSlot1 + 1;
				level1.m_cost += distance1;
				level1.m_path[pathSlot1] = static_cast<unsigned char>(idx0);
				level1.m_visited[other0Index] = 1;

				if (other0Index == goalGroup)
				{
					if (level1.m_cost < m_bestPath.m_cost)
					{
						*reinterpret_cast<CABlock*>(m_bestPath.m_visited) = *reinterpret_cast<CABlock*>(level1.m_visited);
						*reinterpret_cast<CABlock*>(m_bestPath.m_path) = *reinterpret_cast<CABlock*>(level1.m_path);
						m_bestPath.m_pathLength = level1.m_pathLength;
						m_bestPath.m_cost = level1.m_cost;
					}
				}
				else
				{
					CAPos* pos1 = m_portals;
					int idx1 = 0;

					do
					{
						int other1 = pos1->m_groupA;
						bool connected1 = (other1 == other0Index || pos1->m_groupB == other0Index);

						if (connected1)
						{
							if (other1 == other0Index)
							{
								other1 = pos1->m_groupB;
							}

							int other1Index = static_cast<unsigned char>(other1);

							if (level1.m_visited[other1Index] == 0)
							{
								CATemp level2;
								*reinterpret_cast<CABlock*>(level2.m_visited) = *reinterpret_cast<CABlock*>(level1.m_visited);
								*reinterpret_cast<CABlock*>(level2.m_path) = *reinterpret_cast<CABlock*>(level1.m_path);
								level2.m_pathLength = level1.m_pathLength;
								level2.m_cost = level1.m_cost;
								float distance2 = PSVECDistance(&pos1->m_position, &m_portals[other1Index].m_position);
								int pathSlot2 = level2.m_pathLength;
								level2.m_pathLength = pathSlot2 + 1;
								level2.m_cost += distance2;
								level2.m_path[pathSlot2] = static_cast<unsigned char>(idx1);
								level2.m_visited[other1Index] = 1;

								if (other1Index == goalGroup)
								{
									if (level2.m_cost < m_bestPath.m_cost)
									{
										m_bestPath = level2;
									}
								}
								else
								{
									CAPos* edge = m_portals;
									int idx2 = 0;

									do
									{
										if (edge->IsExist(other1Index) != 0)
										{
											int nextGroup = edge->GetOthers(other1Index);

											if (level2.m_visited[nextGroup] == 0)
											{
												CATemp deeper(level2);
												deeper.m_cost += edge->CalcLength(m_portals[nextGroup]);
												deeper.m_path[deeper.m_pathLength++] = static_cast<unsigned char>(idx2);
												check(nextGroup, goalGroup, deeper);
											}
										}

										++idx2;
										++edge;
									} while (idx2 < 64);
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
float CAStar::CAPos::CalcLength(CAStar::CAPos& other)
{
	return PSVECDistance(&this->m_position, &other.m_position);
}
/*
 * --INFO--
 * PAL Address: 0x80142a80
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CAStar::CATemp::CATemp(const CAStar::CATemp& other)
{
	u32 v0;
	u32 v1;

	u32* dst = reinterpret_cast<u32*>(this);
	const u32* src = reinterpret_cast<const u32*>(&other);

	v0 = src[0];
	v1 = src[1];
	dst[0] = v0;
	v0 = src[2];
	dst[1] = v1;
	v1 = src[3];
	dst[2] = v0;
	v0 = src[4];
	dst[3] = v1;
	v1 = src[5];
	dst[4] = v0;
	v0 = src[6];
	dst[5] = v1;
	v1 = src[7];
	dst[6] = v0;
	v0 = src[8];
	dst[7] = v1;
	v1 = src[9];
	dst[8] = v0;
	v0 = src[10];
	dst[9] = v1;
	v1 = src[11];
	dst[10] = v0;
	v0 = src[12];
	dst[11] = v1;
	v1 = src[13];
	dst[12] = v0;
	v0 = src[14];
	dst[13] = v1;
	v1 = src[15];
	dst[14] = v0;
	v0 = src[16];
	dst[15] = v1;
	v1 = src[17];
	dst[16] = v0;
	v0 = src[18];
	dst[17] = v1;
	v1 = src[19];
	dst[18] = v0;
	v0 = src[20];
	dst[19] = v1;
	v1 = src[21];
	dst[20] = v0;
	v0 = src[22];
	dst[21] = v1;
	v1 = src[23];
	dst[22] = v0;
	v0 = src[24];
	dst[23] = v1;
	v1 = src[25];
	dst[24] = v0;
	v0 = src[26];
	dst[25] = v1;
	v1 = src[27];
	dst[26] = v0;
	v0 = src[28];
	dst[27] = v1;
	v1 = src[29];
	dst[28] = v0;
	v0 = src[30];
	dst[29] = v1;
	v1 = src[31];
	dst[30] = v0;
	v0 = src[32];
	dst[31] = v1;
	float cost = other.m_cost;
	dst[32] = v0;
	m_cost = cost;
}
unsigned int CAStar::CAPos::GetOthers(int group)
{
	unsigned char others = m_groupA;

	if (others == group)
	{
		others = m_groupB;
	}

	return others;
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
 * PAL Address: 0x80142bd4
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CAStar::CATemp::operator= (const CAStar::CATemp& other)
{
	u32 v0;
	u32 v1;

	u32* dst = reinterpret_cast<u32*>(this);
	const u32* src = reinterpret_cast<const u32*>(&other);

	v0 = src[0];
	v1 = src[1];
	dst[0] = v0;
	v0 = src[2];
	dst[1] = v1;
	v1 = src[3];
	dst[2] = v0;
	v0 = src[4];
	dst[3] = v1;
	v1 = src[5];
	dst[4] = v0;
	v0 = src[6];
	dst[5] = v1;
	v1 = src[7];
	dst[6] = v0;
	v0 = src[8];
	dst[7] = v1;
	v1 = src[9];
	dst[8] = v0;
	v0 = src[10];
	dst[9] = v1;
	v1 = src[11];
	dst[10] = v0;
	v0 = src[12];
	dst[11] = v1;
	v1 = src[13];
	dst[12] = v0;
	v0 = src[14];
	dst[13] = v1;
	v1 = src[15];
	dst[14] = v0;
	v0 = src[16];
	dst[15] = v1;
	v1 = src[17];
	dst[16] = v0;
	v0 = src[18];
	dst[17] = v1;
	v1 = src[19];
	dst[18] = v0;
	v0 = src[20];
	dst[19] = v1;
	v1 = src[21];
	dst[20] = v0;
	v0 = src[22];
	dst[21] = v1;
	v1 = src[23];
	dst[22] = v0;
	v0 = src[24];
	dst[23] = v1;
	v1 = src[25];
	dst[24] = v0;
	v0 = src[26];
	dst[25] = v1;
	v1 = src[27];
	dst[26] = v0;
	v0 = src[28];
	dst[27] = v1;
	v1 = src[29];
	dst[28] = v0;
	v0 = src[30];
	dst[29] = v1;
	v1 = src[31];
	dst[30] = v0;
	v0 = src[32];
	dst[31] = v1;
	float cost = other.m_cost;
	dst[32] = v0;
	m_cost = cost;
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
	int groupLow = groupA;
	int groupHigh = groupB;

	if (groupB < groupA)
	{
		groupLow = groupB;
		groupHigh = groupA;
	}

	int index = 0;

	for (; index < 64; ++index)
	{
		CAPos& p = m_portals[index];

		if (p.m_groupA == groupLow && p.m_groupB == groupHigh)
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
	m_portals[index].m_groupA = static_cast<unsigned char>(groupLow);
	m_portals[index].m_groupB = static_cast<unsigned char>(groupHigh);
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
	int groupLow = groupA;
	int groupHigh = groupB;
	Vec* pos = reinterpret_cast<Vec*>(&CVector(x, y, z));

	if (groupB < groupA)
	{
		groupLow = groupB;
		groupHigh = groupA;
	}

	int index = 0;

	for (; index < 64; ++index)
	{
		CAPos& p = m_portals[index];

		if (p.m_groupA == groupLow && p.m_groupB == groupHigh)
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

	portal.m_position.x = pos->x;
	portal.m_position.y = pos->y;
	portal.m_position.z = pos->z;
	m_portals[index].m_groupA = static_cast<unsigned char>(groupLow);
	m_portals[index].m_groupB = static_cast<unsigned char>(groupHigh);
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

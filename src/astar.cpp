#include "ffcc/astar.h"

#include "ffcc/system.h"
#include "ffcc/vector.h"

#include "string.h"

static const float InfiniteCost = 10000000.0f;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CAStar()
{
	// TODO
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

	for (int portalIndex = 0; portalIndex < 64; ++portalIndex)
	{
		CAPos& portal = m_portals[portalIndex];

		if (!portal.IsExist(current))
		{
			continue;
		}

		const int next = portal.GetOthers(current);

		if (temp.m_visited[next])
		{
			continue;
		}

		CATemp nextTemp(temp);

		nextTemp.m_cost += portal.CalcLength(m_portals[next]);
		nextTemp.m_path[nextTemp.m_pathLength++] = static_cast<unsigned char>(portalIndex);
		nextTemp.m_visited[next] = 1;

		check(next, goal, nextTemp);
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

			m_bestPath.m_cost = InfiniteCost;

			CATemp temp;
			memset(&temp, 0, sizeof(temp));

			check(from, to, temp);

			if (m_bestPath.m_cost < InfiniteCost)
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
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::drawAStar()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::addRealTime(CGPartyObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::getEscapePos(Vec&, Vec&, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::calcSpecialPolygonGroup(Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CAStar::calcPolygonGroup(Vec*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CATemp::CATemp()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CAStar::CAPos::CalcLength(CAStar::CAPos& other)
{
	PSVECDistance(&this->m_position, &other.m_position);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CAStar::CATemp::CATemp(const CAStar::CATemp&)
{
	// TODO
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
void CAStar::CATemp::operator= (const CAStar::CATemp&)
{
	// TODO
}

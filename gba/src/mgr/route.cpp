extern "C" {
#include "global.h"
#include "route.h"

struct Route gRoutes[3];
struct PointList gPointLists[3];

void Route_Init(struct Route *routes)
{
    routes[0].count = gRouteData0.count;
    routes[0].length = gRouteData0.length;
    routes[0].pts = gRouteData0.pts;
    routes[1].count = gRouteData1.count;
    routes[1].length = gRouteData1.length;
    routes[1].pts = gRouteData1.pts;
    routes[2].count = gRouteData2.count;
    routes[2].length = gRouteData2.length;
    routes[2].pts = gRouteData2.pts;
}

struct Route *Route_Get(struct Route *routes, s16 no)
{
    return &gRoutes[no];
}

static inline s16 NextPoint(struct Route *route, s16 i)
{
    if (++i >= route->count)
        return 0;
    return i;
}

static inline s16 PrevPoint(struct Route *route, s16 i)
{
    if (--i < 0)
        return route->count - 1;
    return i;
}

/* Searches for the segment whose gates enclose (x, z) */
s16 Route_FindSegment(struct Route *route, s16 start, s16 x, s16 z)
{
    s16 i = start;
    s16 next = NextPoint(route, i);
    const struct RoutePoint *p;
    const struct RoutePoint *q;
    s16 dx;
    s16 dz;
    s16 qx;
    s16 qz;
    s32 d;
    s32 side;

    do {
        p = &route->pts[i];
        dx = x - p->x;
        dz = z - p->z;
        side = dx * p->nx + dz * p->nz;
        if (side >= 0) {
            q = &route->pts[next];
            qx = x - q->x;
            qz = z - q->z;
            side = qx * q->nx + qz * q->nz;
            if (side <= 0) {
                d = dx * p->dx + dz * p->dz;
                if (d > -0xA0000 && d < 0xA0000)
                    return i;
            }
        }
        i = next;
        next = NextPoint(route, i);
    } while (i != start);
    return 0xFF;
}

s16 Route_Track(struct Route *route, s16 idx, s16 x, s16 z, s16 *pos)
{
    const struct RoutePoint *p;
    const struct RoutePoint *q;
    s16 dx;
    s16 dz;
    s16 i;
    s32 d;

    if (idx == 0xFF) {
        i = Route_FindSegment(route, 0, x, z);
        dx = x - GetRoutePoint(route, i)->x;
        dz = z - GetRoutePoint(route, i)->z;
        *pos = (dx * GetRoutePoint(route, i)->dx + dz * GetRoutePoint(route, i)->dz) >> 6;
        return i;
    }
    p = GetRoutePoint(route, idx);
    dx = x - p->x;
    dz = z - p->z;
    *pos = (dx * p->dx + dz * p->dz) >> 6;
    d = dx * p->nx + dz * p->nz;
    if (d < 0)
        return PrevPoint(route, idx);
    i = NextPoint(route, idx);
    q = GetRoutePoint(route, i);
    dx = x - q->x;
    dz = z - q->z;
    d = dx * q->nx + dz * q->nz;
    if (d > 0)
        return i;
    if (*pos <= -0x2800 || *pos >= 0x2800)
        return Route_FindSegment(route, i, x, z);
    return idx;
}

s16 Route_Advance(struct Route *route, s16 idx, s16 x, s16 z)
{
    const struct RoutePoint *q;
    s16 dx;
    s16 dz;
    s16 i;

    if (idx == 0xFF)
        return Route_FindSegment(route, 0, x, z);
    i = NextPoint(route, idx);
    q = &route->pts[i];
    dx = x - q->x;
    dz = z - q->z;
    if (dx * q->nx + dz * q->nz >= 0)
        return i;
    return idx;
}

s32 Route_Dot(struct Route *route, s16 idx, s16 vx, s16 vz)
{
    const struct RoutePoint *p = &route->pts[idx];
    const struct RoutePoint *q = &route->pts[NextPoint(route, idx)];

    return vx * (q->x - p->x) + vz * (q->z - p->z);
}

void PointList_Init(struct PointList *lists)
{
    lists[POINTS_START].count = gStartPoints.count;
    lists[POINTS_START].pts = gStartPoints.pts;
    lists[POINTS_ITEM_BOX].count = gItemBoxPoints.count;
    lists[POINTS_ITEM_BOX].pts = gItemBoxPoints.pts;
    lists[POINTS_PANEL].count = gPanelPoints.count;
    lists[POINTS_PANEL].pts = gPanelPoints.pts;
}

struct PointList *PointList_Get(struct PointList *lists, s16 no)
{
    return &gPointLists[no];
}
}

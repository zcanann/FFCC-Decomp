#ifndef GUARD_ROUTE_H
#define GUARD_ROUTE_H

#include "global.h"

/* A gate on a racing line: position, gate normal and track direction */
struct RoutePoint {
    s16 x;
    s16 z;
    s8 nx;
    s8 nz;
    s8 dx;
    s8 dz;
    s8 speedType;
    u8 progress;
    u8 unkA[6];
};

struct Route {
    s16 count;
    s16 scale;
    struct RoutePoint *pts;
};

struct RouteData {
    s16 count;
    u8 unk2[0xA];
    s16 scale;
    u8 unkE[2];
    struct RoutePoint pts[0];
};

struct PointList {
    s16 count;
    struct Point *pts;
};

struct PointData {
    s16 count;
    struct Point pts[0];
};

struct RouteSpeed {
    s16 value;
    u16 unk2;
};

enum {
    POINTS_START,
    POINTS_ITEM_BOX,
    POINTS_PANEL,
};

extern struct Route gRoutes[];
extern struct PointList gPointLists[];
extern struct RouteData gRouteData0;
extern struct RouteData gRouteData1;
extern struct RouteData gRouteData2;
extern struct PointData gStartPoints;
extern struct PointData gItemBoxPoints;
extern struct PointData gPanelPoints;
extern const struct RouteSpeed gRouteSpeedTable[];

static inline struct RoutePoint *GetRoutePoint(struct Route *route, s16 no)
{
    return &route->pts[no];
}

void Route_Init(struct Route *routes);
struct Route *Route_Get(struct Route *routes, s16 no);
s16 Route_FindSegment(struct Route *route, s16 start, s16 x, s16 z);
s16 Route_Track(struct Route *route, s16 idx, s16 x, s16 z, s16 *pos);
s16 Route_Advance(struct Route *route, s16 idx, s16 x, s16 z);
s32 Route_Dot(struct Route *route, s16 idx, s16 vx, s16 vz);
void PointList_Init(struct PointList *lists);
struct PointList *PointList_Get(struct PointList *lists, s16 no);

#endif

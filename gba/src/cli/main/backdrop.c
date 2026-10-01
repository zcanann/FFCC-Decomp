#include "global.h"

extern const u16 gBackdrop0Tiles[];
extern const u16 gBackdrop0Map[];
extern const u16 gBackdrop1Tiles[];
extern const u16 gBackdrop1Map[];
extern const u16 gBackdrop2Tiles[];
extern const u16 gBackdrop2Map[];
extern const u16 gBackdrop3Tiles[];
extern const u16 gBackdrop3Map[];

const u16 *gBackdropTiles[] = {
    gBackdrop0Tiles,
    gBackdrop1Tiles,
    gBackdrop2Tiles,
    gBackdrop3Tiles,
};

const u16 *gBackdropMaps[] = {
    gBackdrop0Map,
    gBackdrop1Map,
    gBackdrop2Map,
    gBackdrop3Map,
};

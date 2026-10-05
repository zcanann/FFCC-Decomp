#ifndef FFCC_CARDCONST_H
#define FFCC_CARDCONST_H

namespace CardConst {
#ifdef VERSION_GCCJGC
static char* MC_ICONIMG_FNAME = "dvd/menu/icon.dat";
#else
static char* MC_ICONIMG_FNAME = "icon.dat";
#endif
static char* MC_FNAME = "FFCC";
#ifdef VERSION_GCCJGC
static char* MC_COMMENT = "\xCC\xA7\xB2\xC5\xD9\xCC\xA7\xDD\xC0\xBC\xDE\xB0\xA5\xB8\xD8\xBD\xC0\xD9\xB8\xDB\xC6\xB8\xD9";
#else
static char* MC_COMMENT = "FF Crystal Chronicles";
#endif
static char* MCDAT_MAKER = "GDS";
static char* MCDAT_TITLE = "FFCC";
static char* MCDAT_MACHINE = "GC";
static char* MCDAT_VERSION = "1.00";
}

#endif

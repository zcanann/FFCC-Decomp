#include <dolphin.h>
#include <dolphin/dvd.h>

#include "dolphin/dvd/__dvd.h"

typedef struct FSTEntry {
    /* 0x00 */ unsigned int isDirAndStringOff;
    /* 0x04 */ unsigned int parentOrPosition;
    /* 0x08 */ unsigned int nextEntryOrLength;
} FSTEntry;

static OSBootInfo* BootInfo;
static FSTEntry* FstStart;
char* FstStringStart;
static u32 MaxEntryNum;
u32 sDvdfsCurrentDirEntry;

// prototypes
static BOOL isSame(const char* path, const char* string);
static u32 entryToPath(u32 entry, char* path, u32 maxlen);
static void cbForReadAsync(s32 result, DVDCommandBlock* block);

void __DVDFSInit(void) {
    BootInfo = (void*)OSPhysicalToCached(0);
    FstStart = BootInfo->FSTLocation;
    if (FstStart) {
        MaxEntryNum = FstStart->nextEntryOrLength;
        FstStringStart = (char*)FstStart + (MaxEntryNum* sizeof(FSTEntry));
    }
}

/* For convenience */
#define entryIsDir(i) (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart[i].parentOrPosition)
#define nextDir(i) (FstStart[i].nextEntryOrLength)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

static BOOL isSame(const char* path, const char* string) {
    while (*string != '\0') {
        if (tolower(*path++) != tolower(*string++)) {
            return FALSE;
        }
    }
    
    if (*path == '/' || *path == '\0') {
        return TRUE;
    }
    
    return FALSE;
}

s32 DVDConvertPathToEntrynum(const char* pathPtr) {
    const char* ptr;
    char* stringPtr;
    BOOL isDir;
    u32 length;
    u32 dirLookAt;
    u32 i;
    const char* origPathPtr = pathPtr;
    const char* extentionStart;
    BOOL illegal;
    BOOL extention;
    
    ASSERTMSGLINE(318, pathPtr, "DVDConvertPathToEntrynum(): null pointer is specified  ");
    
    dirLookAt = sDvdfsCurrentDirEntry;
    
    while (1) {
        if (*pathPtr == '\0') {
            return (s32)dirLookAt;
        } else if (*pathPtr == '/') {
            dirLookAt = 0;
            pathPtr++;
            continue;
        } else if (*pathPtr == '.') {
            if (*(pathPtr + 1) == '.') {
                if (*(pathPtr + 2) == '/') {
                    dirLookAt = parentDir(dirLookAt);
                    pathPtr += 3;
                    continue;
                } else if (*(pathPtr + 2) == '\0') {
                    return (s32)parentDir(dirLookAt);
                }
            } else if (*(pathPtr + 1) == '/') {
                pathPtr += 2;
                continue;
            } else if (*(pathPtr + 1) == '\0') {
                return (s32)dirLookAt;
            }
        }
        
        if (__DVDLongFileNameFlag == 0) {
            extention = FALSE;
            illegal = FALSE;
        
            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
                if (*ptr == '.') {
                    if ((ptr - pathPtr > 8) || (extention == TRUE)) {
                        illegal = TRUE;
                        break;
                    }
                    extention = TRUE;
                    extentionStart = ptr + 1;
            
                } else if (*ptr == ' ')
                    illegal = TRUE;
            }
        
            if ((extention == TRUE) && (ptr - extentionStart > 3))
                illegal = TRUE;
        
            if (illegal)
                OSPanic(__FILE__, 379,
                    "DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): "
                    "specified directory or file (%s) doesn't match standard 8.3 format. This is a "
                    "temporary restriction and will be removed soon\n",
                    origPathPtr);
        } else {
            for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++)
                ;
        }
        
        isDir = (*ptr == '\0') ? FALSE : TRUE;
        length = (u32)(ptr - pathPtr);
        
        ptr = pathPtr;
        
        for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1)) {
            if ((entryIsDir(i) == FALSE) && (isDir == TRUE)) {
                continue;
            }
        
            stringPtr = FstStringStart + stringOff(i);
        
            if (isSame(ptr, stringPtr) == TRUE) {
                goto next_hier;
            }
        }
        
        return -1;
    
next_hier:
        if (!isDir) {
            return (s32)i;
        }
        
        dirLookAt = i;
        pathPtr += length + 1;
    }
}

BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) {
    ASSERTMSGLINE(455, fileInfo, "DVDFastOpen(): null pointer is specified to file info address  ");
    ASSERTMSG1LINE(458, (entrynum >= 0) && ((u32) entrynum < (u32) MaxEntryNum), "DVDFastOpen(): specified entry number '%d' is out of range  ", entrynum);
    ASSERTMSG1LINE(461, !entryIsDir(entrynum), "DVDFastOpen(): entry number '%d' is assigned to a directory  ", entrynum);
    
    if (entrynum < 0 || entrynum >= MaxEntryNum || entryIsDir(entrynum)) {
        return FALSE;
    }
    
    fileInfo->startAddr = filePosition(entrynum);
    fileInfo->length = fileLength(entrynum);
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_END;
    
    return TRUE;
}

BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo) {
    s32 entry;
    char currentDir[128];
    
    ASSERTMSGLINE(491, fileName, "DVDOpen(): null pointer is specified to file name  ");
    ASSERTMSGLINE(492, fileInfo, "DVDOpen(): null pointer is specified to file info address  ");
    
    entry = DVDConvertPathToEntrynum(fileName);
    
    if (0 > entry) {
        DVDGetCurrentDir(currentDir, 128);
        OSReport("Warning: DVDOpen(): file '%s' was not found under %s.\n", fileName, currentDir);
        return FALSE;
    }
    
    if (entryIsDir(entry)) {
        ASSERTMSG1LINE(506, !entryIsDir(entry), "DVDOpen(): directory '%s' is specified as a filename  ", fileName);
        return FALSE;
    }
    
    fileInfo->startAddr = filePosition(entry);
    fileInfo->length = fileLength(entry);
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_END;
    
    return TRUE;
}

BOOL DVDClose(DVDFileInfo* fileInfo) {
    ASSERTMSGLINE(530, fileInfo, "DVDClose(): null pointer is specified to file info address  ");
    DVDCancel(&(fileInfo->cb));
    return TRUE;
}

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - entryToPath and DVDGetCurrentDir are still the only code mismatches in
 *   dvdfs.c
 * - the remaining miss looks like stack / register allocation in the recursive
 *   path-copy loops, not missing logic recovery
 *
 * Most useful probe so far:
 * - rewriting both functions toward the direct Ghidra shape did not move the
 *   objdiff score at all
 * - that rules out the obvious "fewer locals / single-exit return" rewrite as
 *   the fix for this unit
 * - a follow-up DVDGetCurrentDir probe that used a shared BOOL result plus a
 *   ghidra-style shared return also left the tail mismatch unchanged
 * - a follow-up entryToPath probe that scoped parentName / dst / remaining
 *   down into the two copy blocks also held completely flat, so shortening the
 *   visible local lifetimes is not enough to change the register shape here
 */

static u32 entryToPath(u32 entry, char* path, u32 maxlen) {
    char* name;
    char* parentName;
    char* dst;
    u32 loc;
    u32 remaining;
    u32 parent;

    if (entry == 0) {
        return 0;
    } else {
        name = FstStringStart + stringOff(entry);
        parent = parentDir(entry);
        if (parent == 0) {
            loc = 0;
        } else {
            parentName = FstStringStart + stringOff(parent);
            loc = entryToPath(parentDir(parent), path, maxlen);
            if (loc != maxlen) {
                path[loc++] = '/';
                remaining = maxlen - loc;
                dst = path + loc;
                while ((remaining != 0) && (*parentName != '\0')) {
                    remaining--;
                    *dst++ = *parentName++;
                }
                loc = loc + ((maxlen - loc) - remaining);
            }
        }

        if (loc != maxlen) {
            path[loc++] = '/';
            remaining = maxlen - loc;
            dst = path + loc;
            while ((remaining != 0) && (*name != '\0')) {
                remaining--;
                *dst++ = *name++;
            }
            loc = loc + ((maxlen - loc) - remaining);
        }
    }

    return loc;
}

BOOL DVDGetCurrentDir(char* path, u32 maxlen) {
    u32 currentDirEntry;
    u32 loc;

    ASSERTMSG1LINE(671, (maxlen > 1), "DVDGetCurrentDir: maxlen should be more than 1 (%d is specified)", maxlen);

    ASSERTMSG1LINE(622, (s32)sDvdfsCurrentDirEntry >= 0 && sDvdfsCurrentDirEntry < MaxEntryNum, "DVDConvertEntrynumToPath: specified entrynum(%d) is out of range  ", sDvdfsCurrentDirEntry);
    ASSERTMSGLINE(629, entryIsDir(sDvdfsCurrentDirEntry), "DVDConvertEntrynumToPath: cannot convert an entry num for a file to path  ");

    currentDirEntry = sDvdfsCurrentDirEntry;
    loc = entryToPath(currentDirEntry, path, maxlen);
    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }

    if (entryIsDir(currentDirEntry)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }
        path[loc++] = '/';
    }

    path[loc] = '\0';
    return TRUE;
}

BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio) {
    ASSERTMSGLINE(736, fileInfo, "DVDReadAsync(): null pointer is specified to file info address  ");
    ASSERTMSGLINE(737, addr, "DVDReadAsync(): null pointer is specified to addr  ");
    ASSERTMSGLINE(741, !OFFSET(addr, 32), "DVDReadAsync(): address must be aligned with 32 byte boundaries  ");
    ASSERTMSGLINE(743, !(length & 0x1F), "DVDReadAsync(): length must be  multiple of 32 byte  ");
    ASSERTMSGLINE(745, !(offset & 3), "DVDReadAsync(): offset must be multiple of 4 byte  ");

    DVD_ASSERTMSGLINE(742, (0 <= offset) && (offset < fileInfo->length), "DVDReadAsync(): specified area is out of the file  ");
    DVD_ASSERTMSGLINE(748, (0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE), "DVDReadAsync(): specified area is out of the file  ");

    fileInfo->callback = callback;
    DVDReadAbsAsyncPrio(&fileInfo->cb, addr, length, (s32)(fileInfo->startAddr + offset), cbForReadAsync, prio);
    return TRUE;
}

#ifndef offsetof
#define offsetof(type, memb) ((u32) & ((type*)0)->memb)
#endif

static void cbForReadAsync(s32 result, DVDCommandBlock* block) {
    DVDFileInfo* fileInfo;

    fileInfo = (DVDFileInfo*)((char*)block - offsetof(DVDFileInfo, cb));
    ASSERTLINE(774, (void*) &fileInfo->cb == (void*) block);
    if (fileInfo->callback) {
        fileInfo->callback(result, fileInfo);
    }
}

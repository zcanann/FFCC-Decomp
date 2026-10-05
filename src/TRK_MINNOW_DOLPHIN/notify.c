#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/notify.h"

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#ifdef VERSION_GCCJGC
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#endif

/*
 * --INFO--
 * PAL Address: 0x801AB994
 * PAL Size: 152b
 * EN Address: 0x801AA878
 * EN Size: 152b
 * JP Address: 0x801A7DB4
 * JP Size: 216b
 */
#ifdef VERSION_GCCJGC
DSError TRKDoNotifyStopped(u8 cmd) {
#else
DSError TRKDoNotifyStopped(MessageCommandID cmd) {
#endif
    int reqIdx;
    int bufIdx;
    TRKBuffer* msg;
    DSError err;
    DSError bufError;

    bufError = TRKGetFreeBuffer(&bufIdx, &msg);
    if ((err = bufError) == FALSE) {
#ifdef VERSION_GCCJGC
        err = TRKAppendBuffer1_ui8(msg, cmd);
#endif
        if (err == DS_NoError) {
            if (cmd == DSMSG_NotifyStopped) {
                TRKTargetAddStopInfo(msg);
            } else {
                TRKTargetAddExceptionInfo(msg);
            }
        }
        bufError = TRKRequestSend(msg, &reqIdx, 2, 3, 1);
        err = bufError;
        if (err == DS_NoError) {
            TRKReleaseBuffer(reqIdx);
        }
        TRKReleaseBuffer(bufIdx);
    }
    return err;
}
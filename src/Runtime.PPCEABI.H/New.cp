#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Runtime/exception.h"
#include "PowerPC_EABI_Support/Runtime/New.h"

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - baseline source already matches the target destructor / what() code shape
 * - final linkage is still blocked by constant / RTTI object-source shape, not control flow
 * - live MWCC output materializes an extra private std::exception RTTI/string blob
 *   alongside the authored _new symbols the target object wants
 *
 * Most useful probe so far:
 * - keep named s_std_exception_new / s_exception plus an out-of-line
 *   exception::~exception() in this file
 * - compile this unit with -RTTI off
 * - that drops the extra private RTTI blob while preserving the target code shape
 * - a fresh follow-up naming the two string literals directly in namespace std
 *   is not keepable: MWCC duplicates `"std::exception"` into a second local
 *   rodata blob and grows `.rodata` from `0x1A` to `0x2B` instead of matching
 *   the target's padded `0x20` layout
 *
 * Why this is not keepable yet:
 * - promoting that probe to Matching still failed final main.dol checksum
 * - promoting New.cp together with Gecko_ExceptionPPC.cp on latest main still
 *   fails only at the final checksum, so this is not just one unresolved
 *   exception-runtime cluster seam between those two units
 * - so there is still at least one remaining object-shape / linkage detail beyond
 *   the obvious duplicate RTTI emission
 */

inline void operator delete(void* arg0) throw() {
    if (arg0 != 0) {
        free(arg0);
    }
}

namespace std {
const char* exception::what() const { return "exception"; }

} // namespace std

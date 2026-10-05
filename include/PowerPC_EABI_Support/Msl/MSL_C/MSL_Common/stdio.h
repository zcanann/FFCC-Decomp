#ifndef MSL_STDIO_H_
#define MSL_STDIO_H_

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/char_io.h" // IWYU pragma: export
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h" // IWYU pragma: export
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/printf.h"  // IWYU pragma: export
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/extras.h"  // IWYU pragma: export

#ifdef VERSION_GCCJGC
#define BUFSIZ 4096
#else
#define BUFSIZ 1024
#endif

#define stdin  (&__files[0])
#define stdout (&__files[1])
#define stderr (&__files[2])

#endif

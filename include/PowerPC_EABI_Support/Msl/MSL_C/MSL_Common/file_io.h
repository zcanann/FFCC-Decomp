#ifndef _MSL_COMMON_FILE_IO_H
#define _MSL_COMMON_FILE_IO_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *fopen(const char *filename, const char *mode);
int fflush(FILE* file);
int fclose(FILE* file);
int __get_file_modes(const char* mode, file_modes* modes);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_FILE_IO_H */

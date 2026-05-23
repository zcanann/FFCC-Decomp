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
int __position_file(__file_handle file, fpos_t* position, int mode, __idle_proc idle_proc);
int __read_file(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
int __write_file(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
int __close_file(__file_handle file);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_FILE_IO_H */

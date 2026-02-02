#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include <string.h>

static unsigned char stdin_buff[0x100];
static unsigned char stdout_buff[0x100];
static unsigned char stderr_buff[0x100];

FILE __files[4] = {
    {0,
     {0, 1, 1, 2, 0},
     {0, 0, 0, 0},
     0,
     0,
     0,
     {0, 0},
     {0, 0},
     0,
     stdin_buff,
     sizeof(stdin_buff),
     stdin_buff,
     0,
     0,
     0,
     0,
     NULL,
     &__read_console,
     &__write_console,
     &__close_console,
     0,
     &__files[1]},
    {1,
     {0, 2, 1, 2, 0},
     {0, 0, 0, 0},
     0,
     0,
     0,
     {0, 0},
     {0, 0},
     0,
     stdout_buff,
     sizeof(stdout_buff),
     stdout_buff,
     0,
     0,
     0,
     0,
     NULL,
     &__read_console,
     &__write_console,
     &__close_console,
     0,
     &__files[2]},
    {2,
     {0, 2, 0, 2, 0},
     {0, 0, 0, 0},
     0,
     0,
     0,
     {0, 0},
     {0, 0},
     0,
     stderr_buff,
     sizeof(stderr_buff),
     stderr_buff,
     0,
     0,
     0,
     0,
     NULL,
     &__read_console,
     &__write_console,
     &__close_console,
     0,
     &__files[3]},
};

void __close_all() {
    FILE* file = &__files[0];
    FILE* last_file;

    __begin_critical_region(2);

    while (file != NULL) {
        if (file->file_mode.file_kind != __closed_file) {
            fclose(file);
        }

        last_file = file;
        file = file->next_file_struct;

        if (last_file->is_dynamically_allocated) {
            free(last_file);
        } else {
            last_file->file_mode.file_kind = __strinFile;
            if (file != NULL && file->is_dynamically_allocated) {
                last_file->next_file_struct = NULL;
            }
        }
    }

    __end_critical_region(2);
}

unsigned int __flush_all() {
  unsigned int retval = 0;
  FILE* __stream;

    __stream = &__files[0];
    while (__stream) {
        if ((__stream->file_mode.file_kind) && (fflush(__stream))) {
            retval = -1;
        }
        __stream = __stream->next_file_struct;
    };

    return retval;
}

FILE* __find_unopened_file(void) {
    FILE* file = &__files[0];
    FILE* prev = NULL;
    
    while (file != NULL) {
        if (file->file_mode.file_kind == __closed_file) {
            return file;
        }
        prev = file;
        file = file->next_file_struct;
    }
    
    // Allocate new file structure
    file = (FILE*)malloc(sizeof(FILE));
    if (file == NULL) {
        return NULL;
    }
    
    memset(file, 0, sizeof(FILE));
    file->is_dynamically_allocated = 1;
    
    if (prev != NULL) {
        prev->next_file_struct = file;
    }
    
    return file;
}

void __init_file(FILE* file, file_modes mode, unsigned char* buffer, int buffer_size) {
    file->handle = 0;
    file->file_mode = mode;
    
    // Clear file state flags
    file->file_state.io_state = __neutral;
    file->file_state.free_buffer = 0;
    file->file_state.eof = 0;
    file->file_state.error = 0;
    
    file->buffer_length = 0;
    
    if (buffer_size == 0) {
        setvbuf(file, NULL, _IONBF, 0);
    } else {
        setvbuf(file, (char*)buffer, _IOFBF, buffer_size);
    }
    
    file->buffer_ptr = file->buffer;
    file->buffer_position = 0;
    
    // Set I/O function pointers for disk files
    if (file->file_mode.file_kind == __disk_file) {
        file->position_fn = NULL;
        file->read_fn = NULL;
        file->write_fn = NULL;
        file->close_fn = NULL;
    }
    
    file->idle_fn = NULL;
}

int __flush_line_buffered_output_files(void) {
    FILE* file = &__files[0];
    int result = 0;
    
    while (file != NULL) {
        if (file->file_mode.file_kind != __closed_file && 
            file->file_mode.io_mode != __read &&
            file->file_mode.buffer_mode == _IOLBF) {
            if (fflush(file) != 0) {
                result = -1;
            }
        }
        file = file->next_file_struct;
    }
    
    return result;
}

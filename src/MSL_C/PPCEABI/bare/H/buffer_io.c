#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"

void* malloc(size_t size);

int __load_buffer(FILE* file, size_t* bytes_loaded, int mode)
{
	int ioresult;
	unsigned char* buffer_start;
	
	file->buffer_ptr = file->buffer;
	file->buffer_length = file->buffer_size;
	file->buffer_length -= file->position & file->buffer_alignment;
	file->buffer_position = file->position;
	
	if (mode == 1) {
		file->buffer_length = file->buffer_size;
	}
	
	ioresult = (*file->read_fn)(file->handle, file->buffer, &file->buffer_length, file->idle_fn);
	
	if (ioresult == 2) {
		file->buffer_length = 0;
	}
	
	if (bytes_loaded != NULL) {
		*bytes_loaded = file->buffer_length;
	}
	
	if (ioresult == 0) {
		int i;
		file->position += file->buffer_length;
		if (!file->file_mode.binary_io) {
			buffer_start = file->buffer;
			for (i = file->buffer_length; i != 0; i--) {
				char c = *buffer_start;
				buffer_start++;
				if (c == '\n') {
					file->position++;
				}
			}
		}
		ioresult = 0;
	}
	
	return ioresult;
}

int setvbuf(FILE* file, char* buffer, int mode, size_t size)
{
	if (mode == _IONBF) {
		fflush(file);
	}
	
	if (!file->file_state.free_buffer && file->file_mode.io_mode != 0) {
		if (mode == _IONBF || mode == _IOLBF || mode == _IOFBF) {
			if (file->buffer != NULL && file->file_state.free_buffer) {
				free(file->buffer);
			}
			
			file->file_mode.buffer_mode = mode;
			file->file_state.free_buffer = 0;
			file->buffer = (unsigned char*)file->ungetc_buffer;
			file->buffer_ptr = (unsigned char*)file->ungetc_buffer;
			file->buffer_size = 1;
			file->buffer_length = 0;
			file->buffer_position = 0;
			
			if (mode == _IONBF || size == 0) {
				*file->buffer_ptr = 0;
				return 0;
			} else {
				if (buffer == NULL) {
					buffer = (char*)malloc(size);
					if (buffer == NULL) {
						return -1;
					}
					file->file_state.free_buffer = 1;
				}
				file->buffer = (unsigned char*)buffer;
				file->buffer_ptr = (unsigned char*)buffer;
				file->buffer_size = size;
				file->buffer_position = 0;
				return 0;
			}
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

void __prep_buffer(FILE* file)
{
	file->buffer_ptr    = file->buffer;
	file->buffer_length = file->buffer_size;
	file->buffer_length -= file->position & file->buffer_alignment;
	file->buffer_position = file->position;
}

void __convert_from_newlines(unsigned char* p, size_t* n) { }

int __flush_buffer(FILE* file, size_t* bytes_flushed)
{
	size_t buffer_len;
	int ioresult;

	buffer_len = file->buffer_ptr - file->buffer;

	if (buffer_len) {
		file->buffer_length = buffer_len;

		if (!file->file_mode.binary_io)
			__convert_from_newlines(file->buffer, &file->buffer_length);

		ioresult = (*file->write_fn)(file->handle, file->buffer,
		                             &file->buffer_length, file->idle_fn);

		if (bytes_flushed)
			*bytes_flushed = file->buffer_length;

		if (ioresult)
			return ioresult;

		file->position += file->buffer_length;
	}

	__prep_buffer(file);

	return __no_io_error;
}

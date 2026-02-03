#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"

void __prep_buffer(FILE* file)
{
	file->buffer_ptr    = file->buffer;
	file->buffer_length = file->buffer_size;
	file->buffer_length -= file->position & file->buffer_alignment;
	file->buffer_position = file->position;
}

void __convert_from_newlines(unsigned char* p, size_t* n) { }

int __load_buffer(FILE* file, size_t* bytes_loaded, int load_once)
{
	int ioresult;
	unsigned char* pcVar;
	int i;
	
	file->buffer_ptr = file->buffer;
	file->buffer_length = file->buffer_size;
	file->buffer_length -= file->position & file->buffer_alignment;
	file->buffer_position = file->position;
	
	if (load_once == 1) {
		file->buffer_length = file->buffer_size;
	}
	
	ioresult = (*file->read_fn)(file->handle, file->buffer, 
	                           &file->buffer_length, file->idle_fn);
	
	if (ioresult == __io_EOF) {
		file->buffer_length = 0;
	}
	
	if (bytes_loaded != 0) {
		*bytes_loaded = file->buffer_length;
	}
	
	if (ioresult == __no_io_error) {
		file->position += file->buffer_length;
		
		if (!file->file_mode.binary_io) {
			pcVar = file->buffer;
			for (i = file->buffer_length; i != 0; i--) {
				if (*pcVar == '\n') {
					file->position++;
				}
				pcVar++;
			}
		}
		ioresult = __no_io_error;
	}
	
	return ioresult;
}

int setvbuf(FILE* file, char* buffer, int mode, size_t size)
{
	unsigned short file_state;
	
	file_state = file->file_state.io_state;
	
	if (mode == _IONBF) {
		fflush(file);
	}
	
	if ((file->file_state.free_buffer == 0) && ((file_state >> 6 & 7) != 0)) {
		if ((mode == _IONBF) || (mode == _IOLBF) || (mode == _IOFBF)) {
			if ((file->buffer != 0) && (file->file_state.free_buffer != 0)) {
				free(file->buffer);
			}
			
			__begin_critical_region(2);
			
			file->file_mode.buffer_mode = mode;
			file->file_state.free_buffer = 0;
			file->buffer = (unsigned char*)&file->char_buffer;
			file->buffer_ptr = (unsigned char*)&file->char_buffer; 
			file->buffer_size = 1;
			file->buffer_length = 0;
			file->buffer_position = 0;
			
			if ((mode == _IONBF) || (size == 0)) {
				*file->buffer_ptr = 0;
				__end_critical_region(2);
				return 0;
			} else {
				if (buffer == 0) {
					buffer = (char*)malloc(size);
					if (buffer == 0) {
						__end_critical_region(2);
						return -1;
					}
					file->file_state.free_buffer = 1;
				}
				
				file->buffer = (unsigned char*)buffer;
				file->buffer_ptr = file->buffer;
				file->buffer_size = size;
				file->buffer_position = 0;
				__end_critical_region(2);
				return 0;
			}
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

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

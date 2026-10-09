#include "string.h"
#include "stddef.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/errno.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h"

#define K1 0x80808080
#define K2 0xFEFEFEFF


size_t strlen(const char* str)
{
	size_t len       = -1;
	unsigned char* p = (unsigned char*)str - 1;

	do {
		len++;
	} while (*++p);

	return len;
}

char* strcpy(char* dst, const char* src)
{
	register unsigned char *destb, *fromb;
	register unsigned long w, t, align;

	fromb = (unsigned char*)src;
	destb = (unsigned char*)dst;

	if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
		goto bytecopy;
	}

	if (align) {
		if ((*destb = *fromb) == 0) {
			return dst;
		}

		for (align = 3 - align; align; align--) {
			if ((*(++destb) = *(++fromb)) == 0) {
				return dst;
			}
		}
		++destb;
		++fromb;
	}

	w = *((int*)(fromb));

	t = w + K2;

	t &= K1;
	if (t) {
		goto bytecopy;
	}
	--((int*)(destb));

	do {
		*(++((int*)(destb))) = w;
		w                    = *(++((int*)(fromb)));

		t = w + K2;
		t &= K1;
		if (t) {
			goto adjust;
		}
	} while (1);

adjust:
	++((int*)(destb));

bytecopy:
	if ((*destb = *fromb) == 0) {
		return dst;
	}

	do {
		if ((*(++destb) = *(++fromb)) == 0) {
			return dst;
		}
	} while (1);

	return dst;
}

char* strncpy(char* dst, const char* src, size_t n)
{
	const unsigned char* p = (const unsigned char*)src - 1;
	unsigned char* q       = (unsigned char*)dst - 1;

	n++;
	while (--n) {
		if (!(*++q = *++p)) {
			while (--n) {
				*++q = 0;
			}
			break;
		}
	}

	return dst;
}

char* strcat(char* dst, const char* src)
{
	const unsigned char* srcPtr = (const unsigned char*)src - 1;
	unsigned char* dstPtr       = (unsigned char*)dst - 1;

	while (*++dstPtr) {
	}

	--dstPtr;
	while ((*++dstPtr = *++srcPtr) != 0) {
	}

	return dst;
}

int strcmp(const char* str1, const char* str2)
{
	register unsigned char* left  = (unsigned char*)str1;
	register unsigned char* right = (unsigned char*)str2;
	unsigned long align, l1, r1, x;

	l1 = *left;
	r1 = *right;
	if (l1 - r1) {
		return l1 - r1;
	}

	if ((align = ((int)left & 3)) != ((int)right & 3)) {
		goto bytecopy;
	}

	if (align) {
		if (l1 == 0) {
			return 0;
		}
		for (align = 3 - align; align; align--) {
			l1 = *(++left);
			r1 = *(++right);
			if (l1 - r1) {
				return l1 - r1;
			}
			if (l1 == 0) {
				return 0;
			}
		}
		left++;
		right++;
	}

	l1 = *(int*)left;
	r1 = *(int*)right;
	x  = l1 + K2;
	if (x & K1) {
		goto adjust;
	}

	while (l1 == r1) {
		l1 = *(++((int*)(left)));
		r1 = *(++((int*)(right)));
		x  = l1 + K2;
		if (x & K1) {
			goto adjust;
		}
	}

	if (l1 > r1) {
		return 1;
	}
	return -1;

adjust:
	l1 = *left;
	r1 = *right;
	if (l1 - r1) {
		return l1 - r1;
	}

bytecopy:
	if (l1 == 0) {
		return 0;
	}

	do {
		l1 = *(++left);
		r1 = *(++right);
		if (l1 - r1) {
			return l1 - r1;
		}
		if (l1 == 0) {
			return 0;
		}
	} while (1);
}

int strncmp(const char* str1, const char* str2, size_t n)
{
    const unsigned char* p1 = (unsigned char*)str1 - 1;
    const unsigned char* p2 = (unsigned char*)str2 - 1;
    unsigned long c1, c2;

    n++;

    while (--n)
        if ((c1 = *++p1) != (c2 = *++p2))
            return (c1 - c2);
        else if (!c1)
            break;
    return 0;
}

char* strchr(const char* str, int c)
{
	const unsigned char* p = (unsigned char*)str - 1;
	unsigned long chr      = (c & 0xFF);

	unsigned long ch;
	while (ch = *++p) {
		if (ch == chr) {
			return (char*)p;
		}
	}

	return chr ? NULL : (char*)p;
}

char* strrchr(const char* str, int c)
{
	const unsigned char* p = (unsigned char*)str - 1;
	const unsigned char* q = NULL;
	unsigned long chr      = (c & 0xFF);

	unsigned long ch;
	while (ch = *++p) {
		if (ch == chr) {
			q = p;
		}
	}

	if (q != NULL) {
		return (char*)q;
	}

	return chr ? NULL : (char*)p;
}

/*
 * --INFO--
 * PAL Address: 0x801b8c58
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* strtok(char* str, const char* delim)
{
	static char* n = "";
	static char* s = "";
	unsigned char delimiter_table[32] = { 0 };
	int ch;
	unsigned char* p;
	char* tokenStart;

	if (str != NULL) {
		s = str;
	}

	p = (unsigned char*)delim - 1;
	while ((ch = *++p) != '\0') {
		delimiter_table[(ch & 0xFF) >> 3] |= 1 << (ch & 7);
	}

	p = (unsigned char*)s - 1;
	while ((ch = *++p) != '\0') {
		if ((delimiter_table[(ch & 0xFF) >> 3] & (1 << (ch & 7))) == 0) {
			break;
		}
	}

	if (ch == '\0') {
		s = n;
		return NULL;
	}

	tokenStart = (char*)p;
	while ((ch = *++p) != '\0') {
		if ((delimiter_table[(ch & 0xFF) >> 3] & (1 << (ch & 7))) != 0) {
			break;
		}
	}

	if (ch == '\0') {
		s = n;
	} else {
		s = (char*)(p + 1);
		*p = '\0';
	}

	return tokenStart;
}

char* strstr(const char* str, const char* pat)
{
	const unsigned char* s1 = (const unsigned char*)str - 1;
	const unsigned char* p1 = (const unsigned char*)pat - 1;
	unsigned long firstc, c1, c2;

	if ((pat == 0) || (!(firstc = *++p1))) {
		return (char*)str;
	}

	while (c1 = *++s1) {
		if (c1 == firstc) {
			const unsigned char* s2 = s1 - 1;
			const unsigned char* p2 = p1 - 1;

			while ((c1 = *++s2) == (c2 = *++p2) && c1)
				;

			if (!c2)
				return (char*)s1;
		}
	}

	return NULL;
}

char* __strerror(int errnum, char* str);

char* strerror(int errnum)
{
	static char error_string[256];

	return __strerror(errnum, error_string);
}

char* __strerror(int errnum, char* str)
{
	switch (errnum) {
	case E2BIG:
		strcpy(str, "Argument list too long");
		break;
	case EACCES:
		strcpy(str, "Permission denied");
		break;
	case EAGAIN:
		strcpy(str, "Resource temporarily unavailable");
		break;
	case EBADF:
		strcpy(str, "Bad file descriptor");
		break;
	case EBUSY:
		strcpy(str, "Device busy");
		break;
	case ECHILD:
		strcpy(str, "No child processes");
		break;
	case EDEADLK:
		strcpy(str, "Resource deadlock avoided");
		break;
	case EDOM:
		strcpy(str, "Numerical argument out of domain");
		break;
	case EEXIST:
		strcpy(str, "File exists");
		break;
	case EFAULT:
		strcpy(str, "Bad address");
		break;
	case EFBIG:
		strcpy(str, "File too large");
		break;
	case EFPOS:
		strcpy(str, "File Position Error");
		break;
	case EILSEQ:
		strcpy(str, "Wide character encoding error");
		break;
	case EINTR:
		strcpy(str, "Interrupted system call");
		break;
	case EINVAL:
		strcpy(str, "Invalid argument");
		break;
	case EIO:
		strcpy(str, "Input/output error");
		break;
	case EISDIR:
		strcpy(str, "Is a directory");
		break;
	case EMFILE:
		strcpy(str, "Too many open files");
		break;
	case EMLINK:
		strcpy(str, "Too many links");
		break;
	case ENAMETOOLONG:
		strcpy(str, "File name too long");
		break;
	case ENFILE:
		strcpy(str, "Too many open files in system");
		break;
	case ENODEV:
		strcpy(str, "Operation not supported by device");
		break;
	case ENOENT:
		strcpy(str, "No such file or directory");
		break;
	case ENOERR:
		strcpy(str, "No error detected");
		break;
	case ENOEXEC:
		strcpy(str, "Exec format error");
		break;
	case ENOLCK:
		strcpy(str, "No locks available");
		break;
	case ENOMEM:
		strcpy(str, "Cannot allocate memory");
		break;
	case ENOSPC:
		strcpy(str, "No space left on device");
		break;
	case ENOSYS:
		strcpy(str, "Function not implemented");
		break;
	case ENOTDIR:
		strcpy(str, "Not a directory");
		break;
	case ENOTEMPTY:
		strcpy(str, "Directory not empty");
		break;
	case ENOTTY:
		strcpy(str, "Inappropriate ioctl for device");
		break;
	case ENXIO:
		strcpy(str, "Device not configured");
		break;
	case EPERM:
		strcpy(str, "Operation not permitted");
		break;
	case EPIPE:
		strcpy(str, "Broken pipe");
		break;
	case ERANGE:
		strcpy(str, "Result too large");
		break;
	case EROFS:
		strcpy(str, "Read-only file system");
		break;
	case ESIGPARM:
		strcpy(str, "Signal error");
		break;
	case ESPIPE:
		strcpy(str, "Illegal seek");
		break;
	case ESRCH:
		strcpy(str, "No such process");
		break;
	case EUNKNOWN:
		strcpy(str, "Unknown error");
		break;
	case EXDEV:
		strcpy(str, "Cross-device link");
		break;
	default:
		sprintf(str, "Unknown Error (%d)", errnum);
		break;
	}

	return str;
}

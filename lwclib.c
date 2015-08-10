#include <stdio.h>
#include "lwclib.h"

#define BUFFER_SIZE		4096
#define BASE_OFFSET		70
#define PLATFORM_OFFSET	25
#define LIBC_FINDSTR	"libc-"
#define PROC_DIR		"/proc/self/maps"

// finds the first libc*.so mapped into the current process's memory space
int find_libc(void* out, size_t count)
{
	char buf[BUFFER_SIZE + 1] = {0};
	char* needle = NULL;
	unsigned int fd;
	size_t slen = 0;
	ssize_t len = 0;

	if(0 >= (fd = lw_open(PROC_DIR, O_RDONLY, 0))) {
		return -1;
	}

	if(0 >= (len = lw_read(fd, buf, BUFFER_SIZE))) {
		return -2;
	}

	if(NULL == (needle = lw_strstr(buf, LIBC_FINDSTR))) {
		return -3;
	}
	slen = lw_strlen(buf);

	lw_strncpy(out, (char*)(needle - (BASE_OFFSET + PLATFORM_OFFSET)), slen);

	return 0;
}
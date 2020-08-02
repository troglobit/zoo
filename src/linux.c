/* Basically code stolen from bsd.c and adjusted for Linux. */

#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "zooio.h"

/* Function isadir() returns 1 if the supplied handle is a directory,
 * else it returns 0. */

int isadir (ZOOFILE f)
{
	struct stat buffer;             /* buffer to hold file information */

	if (fstat (fileno (f), &buffer) == -1)
		return 0;               /* inaccessible -- assume not dir */

	if (buffer.st_mode & S_IFDIR)
		return 1;

	return 0;
}


/* Standard UNIX-compatible time routines */
#include "nixtime.i"

/* Standard UNIX-specific file attribute routines */
#include "nixmode.i"

/* Function gettz() returns the offset from GMT in seconds */
long gettz()
{
#define SEC_IN_DAY      (24L * 60L * 60L)
#define INV_VALUE       (SEC_IN_DAY + 1L)

	static long retval = INV_VALUE;    /* cache, init to impossible value */
	struct timeval tp;
	struct timezone tzp;

	if (retval != INV_VALUE)           /* if have cached value, return it */
		return retval;

	gettimeofday (&tp, &tzp);
	retval = tzp.tz_minuteswest * 60 - tzp.tz_dsttime * 3600L;

	return retval;
}

/* Function fixfname() converts the supplied filename to a syntax
 * legal for the host system.  It is used during extraction.
 * Undocumented */

char *fixfname(char *fname)
{
	return fname; /* default is no-op */
}

/* Function zootrunc() truncates the file passed to it.
 * Undocumented. */

int zootrunc(FILE *f)
{
	long seekpos;
	int fd = fileno(f);

	seekpos = lseek(fd, 0L, SEEK_CUR);
	if (seekpos >= 0)
		return ftruncate(fd, seekpos);

	return 0;
}

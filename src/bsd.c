/* machine.c for 4.3BSD.
 *
 * WARNING: This file assumes that ZOOFILE is a standard buffered file.
 * It will have to be modified if ZOOFILE is changed to be an unbuffered
 * file descriptor or to any other kind of file.
 *
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi  1987/07/23
 */

#include <unistd.h>

#ifdef UNBUF_IO
/*
Function tell() returns the current seek position for a file 
descriptor.  4.3BSD on VAX-11/785 has an undocumented tell() function
but it may not exist on all implementations, so we code one here
to be on the safe side.  It is needed for unbuffered I/O only.
*/
long tell (fd)
int fd;
{ return (lseek (fd, 0L, SEEK_CUR)); }
#endif

/****************
Function fixfname() converts the supplied filename to a syntax
legal for the host system.  It is used during extraction.
*/

char *fixfname(fname)
char *fname;
{
   return fname; /* default is no-op */
}

/****************
Date and time functions are standard UNIX-style functions.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include "zooio.h"

/*
** Function isadir() returns 1 if the supplied handle is a directory,
** else it returns 0.
*/
int isadir (f)
ZOOFILE f;
{
	struct stat buf;	/* buffer to hold file information */

	if (fstat (fileno (f), &buf) == -1)
		return 0;	/* inaccessible -- assume not dir */

	if (buf.st_mode & S_IFDIR)
		return 1;

	return 0;
}

/* Function gettz() returns the offset from GMT in seconds */
long gettz()
{
#define SEC_IN_DAY	(24L * 60L * 60L)
#define INV_VALUE	(SEC_IN_DAY + 1L)
	static long retval = INV_VALUE;	     /* cache, init to impossible value */
	struct timeval tp;
	struct timezone tzp;

	if (retval != INV_VALUE)		/* if have cached value, return it */
		return retval;

	gettimeofday (&tp, &tzp);		/* specific to 4.3BSD */
	/* return (tzp.tz_minuteswest * 60); */ /* old incorrect code */
	/* Timezone fix thanks to Bill Davidsen <wedu@ge-crd.ARPA> */
	retval = tzp.tz_minuteswest * 60 - tzp.tz_dsttime * 3600L;

	return retval;
}

/* Standard UNIX-compatible time routines */
#include "nixtime.i"

/* Standard UNIX-specific file attribute routines */
#include "nixmode.i"

#ifndef SEEK_CUR
# define  SEEK_CUR    1
#endif

/* Truncate a file. */
int zootrunc(f)
FILE *f;
{
	off_t seekpos;
	int fd = fileno(f);

	seekpos = lseek(fd, 0L, SEEK_CUR);
	if (seekpos >= 0)
		return ftruncate(fd, seekpos);

	return 0;
}

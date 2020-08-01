/* Declarations for portable I/O
 *
 * The contents of this file are hereby placed in the public domain.
 *
 *				-- Rahul Dhesi 1988/01/24
 */

#ifndef ZOOIO_H_
#define ZOOIO_H_

#include "zoo.h"
#ifndef	OK_STDIO
#include <stdio.h>
#define	OK_STDIO
#endif

/*
In theory, all I/O using buffered files could be replaced with unbuffered
I/O simply by changing the following definitions.  This has not been tried
out yet, and there may be some remaining holes in the scheme.  On systems
with limited memory, it might prove necessary to use unbuffered I/O
only.
*/
typedef FILE *		ZOOFILE;
#define NOFILE		((ZOOFILE) 0)
#define NULLFILE	((ZOOFILE) -1)		/* or any unique value */
#define STDOUT		stdout

#ifdef FILTER
#define STDIN		stdin
#endif

#ifdef IO_MACROS
#define zooread(file, buffer, count)		fread (buffer, 1, count, file)
#define zoowrite(file, buffer, count) \
	(file == NULLFILE ? count : fwrite (buffer, 1, count, file))
#define zooseek(file, offset, whence)		fseek (file, offset, whence)
#define zootell(file)				ftell (file)
#else
int zooread (ZOOFILE, char *, int);
int zoowrite (ZOOFILE, char *, int);
long zooseek (ZOOFILE, long, int);
long zootell (ZOOFILE);
#endif /* IO_MACROS */

ZOOFILE zooopen (char *, char *);
ZOOFILE zoocreate (char *);
ZOOFILE zoofdcreate (int);
int zooclose (ZOOFILE);
int zootrunc (ZOOFILE);

char *choosefname (struct direntry *);
char *fullpath (struct direntry *);
int frd_zooh (struct zoo_header *, ZOOFILE);
int frd_dir (struct direntry *, ZOOFILE);
int fwr_dir (struct direntry *, ZOOFILE);
int fwr_zooh (struct zoo_header *, ZOOFILE);
int readdir (struct direntry *, ZOOFILE, int);
void rwheader (struct zoo_header *, ZOOFILE, int);
void newdir (struct direntry *);
void writedir (struct direntry *, ZOOFILE);

#endif	/* ZOOIO_H_ */

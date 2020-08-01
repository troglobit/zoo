/* Definitions for most external functions used by Zoo
 *
 * If ANSI_PROTO is defined, ANSI-style function prototypes are used,
 * else normal K&R function declarations are used.
 *
 * Note: Always precede this file with an include of stdio.h because it
 *       uses the predefined type FILE.
 *
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi 1986/11/14
 */

#ifndef ZOO_VARIOUS_H_
#define ZOO_VARIOUS_H_
#include "config.h"

#if defined(HAVE_STRING_H) && defined(HAVE_STDLIB_H)
# include <string.h>
# include <stdlib.h>
#else
FILE *fdopen (int, char *);
FILE *fopen (char *, char *);
char *fgets (char *, int, FILE *);
char *gets (char *);
VOIDPTR malloc (unsigned int);
VOIDPTR realloc (char *, unsigned int);
char *strcat (char *, char *);
char *strchr (char *, int);
char *strcpy (char *, char *);
char *strncat (char *, char *, unsigned int);
char *strncpy (char *, char *, unsigned int);
char *strrchr (char *, int);
int fclose (FILE *);
int fflush (FILE *);
int fgetc (FILE *);
int fgetchar ();
int fprintf (FILE *, char *, ...);
int fputchar (int);
int fputs (char *, FILE *);

#ifndef NO_STDIO_FN
# ifdef ALWAYS_INT
int fputc (int, FILE *);
int fread (VOIDPTR, int, int, FILE *);
int fwrite (VOIDPTR, int, int, FILE *);
# else
int fputc (char, FILE *);
int fread (VOIDPTR, unsigned, unsigned, FILE *);
int fwrite (VOIDPTR, unsigned, unsigned, FILE *);
# endif /* ALWAYS_INT */
#endif /* NO_STDIO_FN */

int fseek (FILE *, long, int);
int printf (char *, ...);
int rename (char *, char *);
int setmode (int, int);
int strcmp (char *, char *);
int strncmp (char *, char *, unsigned int);
int unlink (char *);
long ftell (FILE *);
unsigned int strlen (char *);

#endif
#endif /* ZOO_VARIOUS_H_ */

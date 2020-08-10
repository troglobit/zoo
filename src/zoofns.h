/* Defines function declarations for all Zoo functions
 *
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi 1986/11/14
 */

#ifndef ZOOFNS_H_
#define ZOOFNS_H_

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#else
char *memset (char *, int, unsigned);
#endif /* ANSI_HDRS */

long calc_ofs (char *);
char *addext (char *, char *);
char *combine (char[], char *, char *);
VOIDPTR emalloc (unsigned int);
VOIDPTR ealloc (unsigned int);
VOIDPTR erealloc (VOIDPTR, unsigned int);
char *findlast (char *, char *);
char *fixfname (char *);
char *getstdin (void);
char *lastptr (char *);
char *nameptr (char *);
char *newcat (char *, char *);
char *nextfile (int, char *, int);
int cfactor (long, long);
int chname (char *, char *);
int cmpnum (unsigned int, unsigned int, unsigned int, unsigned int);
T_SIGNAL ctrl_c (int);
int exists (char *);
int getfile (ZOOFILE, ZOOFILE, long, int);
int getutime (char *, unsigned *, unsigned *);
int gettime (ZOOFILE, unsigned *, unsigned *);
T_SIGNAL handle_break (int);

#ifdef USE_ASCII
int isupper (int);
int isdigit (int);
#endif /* USE_ASCII */

int kill_files (char *[], int);

void lzc_free(void);
#ifdef UNBUF_IO
int lzc (int, int);
int lzd (int, int);
#else
int lzc (ZOOFILE, ZOOFILE);
int lzd (ZOOFILE, ZOOFILE);
#endif

int lzh_encode (FILE *infile, FILE *outfile);
int lzh_decode (FILE *infile, FILE *outfile);

int match_half (char *, char *);
int samefile (char *, char *);
int settime (ZOOFILE, unsigned, unsigned);
int setutime (char *, unsigned, unsigned);
int str_icmp (char *, char *);

#ifdef USE_ASCII
int tolower (int);
int toascii (int);
#endif /* USE_ASCII */

void zooexit (int);
long inlist (char *, unsigned int *, unsigned int *, unsigned *, unsigned *, unsigned *, long *, int);
unsigned long space (int, int *);
void addbfcrc (char *, int);
void addfname (char *, long, unsigned int, unsigned int, unsigned, unsigned);
void fname_free(void);
void add_version (char *, struct direntry *);
void zoo_basename (char *, char []);
void break_off (void);
void close_file (ZOOFILE);
int  comment (char *, char *);
void extension (char *, char []);
void exit (int);
void fixslash (char *);
void makelist (int, char *[], char *[], int, char *, char *, char *, int *);
void memerr (unsigned int);
void prterror (int, char *, ...);
void rootname (char *, char *);
void skip_files (ZOOFILE, unsigned int *, unsigned int *, int *, char [], long *);
void writenull (ZOOFILE, int);
int  zooadd (char *, int, char **, char *);
int  zoodel (char *, char *, int);
int  zoofilt (char *);
int  zooext (char *, char *);
int  zoolist (char **, char *, int);
int  zoopack (char *, char *);

char *str_dup (char *);
char *str_lwr (char *);

#endif	/* ZOOFNS_H_ */

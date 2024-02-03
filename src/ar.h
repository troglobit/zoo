/* Adapted from "ar" archiver written by Haruhiko Okumura. */

#include <stdio.h>
#include <sys/types.h>

#ifdef ANSI_HDRS
# include <limits.h>
#endif

#ifndef NEED_MEMMOVE
# include <string.h>
#endif

/* uchar should be 8 bits or more */
/* typedef unsigned char  uchar;   -- already in zoo.h */

#ifndef _SYS_TYPES_H
typedef unsigned int   uint;    /* 16 bits or more */
typedef unsigned short ushort;  /* 16 bits or more */
typedef unsigned long  ulong;   /* 32 bits or more */
#endif

/* T_UINT16 must be #defined in options.h to be 
a 16-bit unsigned integer type */

#ifndef T_UINT16
# include "T_UINT16 not defined"
#endif

typedef T_UINT16		  t_uint16;	/* exactly 16 bits */

#ifndef SEEK_SET
# define SEEK_SET 0
#endif
#ifndef SEEK_CUR
# define SEEK_CUR 1
#endif
#ifndef SEEK_END
# define SEEK_END 2
#endif
#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
# define EXIT_FAILURE 1
#endif

/* ar.c */

extern int unpackable;
extern ulong origsize, compsize;

/* all the prototypes follow here for all files */

/* standard library functions */
#ifndef ANSI_HDRS
 extern void exit();
 extern long ftell();
 extern int fseek();
 extern int strlen();
 extern char *strchr();
 extern char *strpbrk();
 extern int strcmp();
 extern char *strcpy();
 extern int memcmp();
 extern VOIDPTR malloc();
 extern VOIDPTR memcpy();
#endif /* ANSI_HDRS */

/* AR.C */
int get_line (char *s , int n );
void exitfunc (int code);
void dlog (char *fmt, ...);
void d1log (char *fmt, ...);
void outcf (FILE *stream, char *buf, int n);
void c1log (char *buf, int n);

/* DECODE.C */
void decode_start (void );
int decode (uint count , uchar buffer []);

/* ENCODE.C */
void encode (FILE *, FILE *);

/* HUF.C */
void output (uint c , uint p );
void huf_encode_start (void );
void huf_encode_end (void );
uint decode_c (void );
uint decode_p (void );
void huf_decode_start (void );

/* IO.C */
void make_crctable (void );
void fillbuf (int n );
uint getbits (int n );
void putbits (int n , uint x );
int fread_crc (uchar *p , int n , FILE *f );
void fwrite_crc (uchar *p , int n , FILE *f );
void init_getbits (void );
void init_putbits (void );

/* MAKETBL.C */
void make_table
	(int nchar, uchar bitlen[], int tablebits, ushort table[]);

/* MAKETREE.C */
int make_tree
	(int nparm, ushort freqparm [], uchar lenparm [], ushort codeparm []);

/* delete */

#ifdef NEED_MEMMOVE
# define MOVE_LEFT move_left
  void move_left();
#else
# define MOVE_LEFT memmove
#endif

#if 0
/* global crc variable stuff for use by various routines */
extern t_uint16 crc;
#define INIT_CRC  0  /* CCITT: 0xFFFF */
#endif

/* for lzh modules and also for ar.c to use in defining buffer size */
#define DICBIT    13    /* 12(-lh4-) or 13(-lh5-) */
#define DICSIZ ((unsigned) 1 << DICBIT)

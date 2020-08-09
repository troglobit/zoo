/* Filter mode -- compress or decompress standard input and write to stdout
 *
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi 2004/06/19
 */

#include "options.h"

#ifdef FILTER

#include "zooio.h"
#include "errors.h"
#include "zoofns.h"

/* action */
#define COMPRESS		0
#define UNCOMPRESS	1

#define FTAG	((unsigned int) 0x5a32)	/* magic number */

extern unsigned int crccode;

int rdint (unsigned int *);	/* read an unsigned int */
int wrint (unsigned int);	/* write an unsigned int */

/* global variable used to pass two bytes (CRC value) back from lzd to here */
unsigned int filt_lzd_word;

int zoofilt(option)
char *option;
{
	int choice;			/* what to do -- [de]compress */
	unsigned int filetag;		/* tag stored in input */
	int stat1, stat2, stat3;	/* status codes */
	int use_lzh = 0;		/* use lzh instead */

	while (*++option) {
		switch (*option) {
			case 'c':	choice = COMPRESS;    break;
			case 'u':	choice = UNCOMPRESS;  break;
			case 'h':	use_lzh = 1; break;
			default:
         	prterror ('f', inv_option, *option);	/* fatal error -- abort */
		}
	}

	crccode = 0;	/* needed whether compressing or uncompressing */

	switch (choice) {
		case COMPRESS:
			stat1 = wrint (FTAG);
			stat2 = (use_lzh ? lzh_encode : lzc) (STDIN, STDOUT);
			stat3 = wrint (crccode);
			if (stat1 == 0 && stat2 == 0 && stat3 == 0)
				return 0;

			fprintf (stderr, "Zoo: FATAL: Compression error.\n");
			return 1;
		case UNCOMPRESS:
			stat1 = rdint (&filetag);
			if (stat1 != 0 || filetag != FTAG)
				zooexit (1);
			stat2 = (use_lzh ? lzh_decode : lzd) (STDIN, STDOUT);
			if (stat2 == 0 && filt_lzd_word == crccode)
				return 0;

			fprintf (stderr, "Zoo: FATAL: Uncompression error.\n");
			return 1;
	}

	return 0;
}

#endif /* FILTER */

/*
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi 2004/06/19
 */

#include "options.h"
#include "portable.h"
#include "errors.h"
#include "zoo.h"
#include "zooio.h"
#include "various.h"

#include "zoofns.h"
#include "assert.h"
#include "debug.h"

char *nameptr(char *);
void modpath(char *);
int isadir(ZOOFILE);
int isfdir(char *);

/*******************
 * makelist() gets all pathnames corresponding to a set of filespecs and
 * adds them to a list.  Not more than "flistsize" pathnames are added.
 * Into `longest' it returns the length of the longest name added, or
 * zero if none added.
 *
 * Files ignore1, ignore2, and ignore3 are not added to the list.  A
 * file that is a device/directory is also not added to the list.
 *
 * However, if ignore1 is NULL, both these tests are skipped and all
 * files will be added to the list.
 */
void makelist(argc, argv, flist, flistsize, ignore1, ignore2, ignore3, longest)
int argc;				 /* number of filespec supplied */
char *argv[];				 /* array of pointers to supplied filespecs */
char *flist[];				 /* array of pointers to filenames we will add */
int flistsize;				 /* home many names we can use */
char *ignore1, *ignore2, *ignore3;	 /* files to exclude from list */
int *longest;				 /* length of longest name in list */
{
	char *this_path;		 /* current pathname */
	int fptr;			 /* pointer to within flist */
	int i, j;			 /* loop counters */
#ifdef WILDCARD
	char *pat_name;			 /* filename part of pattern */
#endif
	int gap;			 /* for Shell sort */

	this_path = NULL;
	flistsize--;			 /* allow for one terminating NULL entry */
	fptr = *longest = 0;

	assert(argc > 0);

#define WCLEN	4			 /* length needed for wildcard, and a little extra */

	while (argc > 0) {
#ifdef WILDCARD
		int argok = 0;		 /* arg not matched yet */
#endif
		char *this_arg;

		this_arg = emalloc(strlen(*argv) + WCLEN);
		strcpy(this_arg, *argv);
		
		/*
		 * Initialize fileset 0.  Select all files -- we will
		 * later filter out the ones wanted
		 */
#ifdef FOLD
		str_lwr(this_arg);
#endif

#ifdef WILDCARD
		pat_name = str_dup(nameptr(this_arg));	/* pattern without path */
#ifdef VER_CH	/* trailing version field */
		{
			static char version_field[] = " *";
			char *p;

			p = strrchr(pat_name, VER_CH);
			if (p == NULL) {
				*version_field = VER_CH;
				pat_name = newcat(pat_name, version_field);
			}
		}
#endif
		/*
		 * replace filename by wildcard; however, if argument
		 * ends in slash, then simply append wildcard so we get
		 * all files in that directory
		 */
#ifdef FORCESLASH
		fixslash(this_arg);	 /* convert backslashes to slashes */
#endif

		if (*lastptr(this_arg) == *(char *)PATH_CH) {
			strcat(this_arg, WILDCARD);
			pat_name = "*";	 /* and select all files */
		} else
#ifdef SPEC_WILD
			spec_wild(this_arg);
#else
			strcpy(nameptr(this_arg), WILDCARD);
#endif
#endif /* WILDCARD */

		nextfile(0, this_arg, 0);
		while (fptr < flistsize && (this_path = nextfile(1, (char *)NULL, 0)) != NULL) {
			char *this_name = nameptr(this_path);

			modpath(this_path);	/* do any needed changes to path */

#ifdef IGNORECASE
#define	COMPARE	str_icmp
#else
#define	COMPARE	strcmp
#endif
			if (ignore1 != NULL) {
				if (samefile(this_name, ignore1) ||	/* exclude ignored files */
				    samefile(this_name, ignore2) || samefile(this_name, ignore3))
					continue;
#ifdef CHEKUDIR
				if (isuadir(this_path))
					continue;
#else
#ifdef CHEKDIR
				if (isfdir(this_path))
					continue;
#endif
#endif
			}

			/* 
			 * If WILDCARD is defined (e.g. AmigaDOS, MS-DOS, VAX/VMS), then nextfile()
			 * returns all filenames and we must now select the ones we need by pattern
			 * matching.  If WILDCARD is not defined (e.g. **IX), filenames have
			 * already been selected by the shell and need not be tested again.
			 */
#ifdef WILDCARD
			if (match_half(this_name, pat_name) || match_half(pat_name, "?-?") &&
			    *this_name >= *pat_name && *this_name <= pat_name[2])
#endif
			{
#ifdef WILDCARD
				argok = 1;	/* remember arg matched */
#endif
				flist[fptr++] = str_dup(this_path);
				if (*longest < strlen(this_path))
					*longest = strlen(this_path);
			}

		}			 /* end while */
#ifdef WILDCARD
		if (argok == 0) {	 /* no match for argument */
			prterror('e', "Could not open %s\n", *argv);
		}
#endif
		free(this_arg);
		argc--;
		argv++;
	}

	/* fptr is now 1 + index of last item in array */
	if (this_path != NULL && fptr >= flistsize)
		prterror('w', too_many_files, flistsize);
#ifndef  DONT_SORT
	/* Shell sort -- K&R p. 58 */
	for (gap = fptr / 2; gap > 0; gap /= 2)
		for (i = gap; i < fptr; i++)
			for (j = i - gap; j >= 0 && strcmp(flist[j], flist[j + gap]) > 0; j -= gap) {
				char *t = flist[j];

				flist[j] = flist[j + gap];
				flist[j + gap] = t;
			}
#endif

	fptr--;				 /* fptr is now index of last item in array */

	/* Remove duplicates */
	for (i = 0; i < fptr; i++) {
		while (i < fptr && COMPARE(flist[i], flist[i + 1]) == 0) {
			for (j = i; j < fptr; j++)
				flist[j] = flist[j + 1];
			fptr--;
		}
	}

	flist[++fptr] = NULL;		 /* NULL entry terminates list */
}

/*******
 * modpath() makes any changes needed before pathname is stored;
 * currently these could involve folding it to lower case and converting
 * backslashes to forward slashes
 */
void modpath(path)
char *path;
{
#ifdef FOLD
	str_lwr(path);
#endif

#ifdef FORCESLASH
	fixslash(path);			 /* convert backslashes to slashes */
#endif
}

#ifdef CHEKDIR
/* Function isfdir returns 1 if pathname is a directory else 0 */
int isfdir(this_path)
char *this_path;
{
	ZOOFILE f;
	int dir;

	f = zooopen(this_path, Z_READ);
	if (f == NOFILE)
		return 0;
	else {
		dir = isadir(f);
		zooclose(f);
	}
	return dir;
}
#endif

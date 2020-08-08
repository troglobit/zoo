/* Main entry point for zoo
 *
 * The contents of this file are hereby released to the public domain.
 *
 *                              -- Rahul Dhesi 2004/06/19
 */

#if 0
#define TRACEI(item)	printf("line %d: %s= %d\n", __LINE__, #item, item)
#define TRACES(item)	printf("line %d: %s= [%s]\n", __LINE__, #item, item)
#endif

#include "config.h"
#include <unistd.h>
#include "options.h"
#include "zooio.h"
#include "various.h"

#include "zoo.h"
#include "zoofns.h"

#include "errors.h"
#include "zoomem.h"

static void ms_help();
static void wait_return();

#ifdef TRACE_IO
int verbose = 0;
#endif

char *out_buf_adr;			 /* points to memory allocated for output buffer(s) */
char *in_buf_adr;			 /* points to memory allocated for input buffer */

/* static declarations */
int quiet = 0;				 /* whether to be quiet */
int next_arg = FIRST_ARG;		 /* filenames start at this position */
int arg_count;				 /* count of arguments supplied to program */
char **arg_vector;			 /* vector of arguments supplied to program */

void spec_init(void);
int instr(char *, char *);
void putstr (char *);

static int help(void)
{
	printf("Usage:\n" "  zoo COMMAND[OPTION] archive [file(s)]\n" "  zoo -cmd archive [file(s)]\n" "\n");

	printf("Commands:                      | Options:\n");
	printf("  a     add files              |   a     show archive name(s) in listing\n");
	printf("  c     update comments        |   A     apply g or c to archive\n");
	printf("  D     delete stored files    |   c     add/list comments\n");
	printf("  e,x   extract files          |   d     extract/list deleted files too\n");
	printf("  g     adj. gen. limit/count  |   dd    extract/list only deleted files\n");
	printf("  l,L,v,V list filenames       |   E     erase backup after packing\n");
	printf("  P     pack archive           |   f     fast add (no compression) or list\n");
	printf("  T     fix archive datestamp  |   M     move when adding (erase original)\n");
	printf("  u     add only newer files   |   n     add only files not already in archive\n");
	printf("  U     undelete stored files  |   N     send extracted data to Nowhere\n");
#ifdef FILTER
	printf("  f     act as filter          |   c/u   compress/uncompress as filter\n");
#endif
	printf(" ------------------------------'   O     don't ask \"Overwrite?\"\n");
	printf("  q     be quiet                   p     pipe extracted data to standard output\n");
	printf("  :     strip any pathnames        /,//  extract/create full pathnames (default)\n");
	printf("  .     pack to current dir        I     add filenames read from stdin\n");
	printf("  C     show file CRC value        +/-   enable/disable generations\n");
	printf("  S     overwrite newer files      g     list generation limits\n");
	printf("  P     pack after adding          @n    start extract/list at position n\n");

#ifdef FATTR
	printf("  m     list file modes            OO    overwrite read-only files\n");
#endif
	printf("  C     change archive cmnt        h     use high-compression method\n");

	printf("\nNovice commands:\n");
	printf(" -add      add files              -extract  extract files\n");
	printf(" -freshen  add if older exists    -delete   delete matching files from archive\n");
	printf(" -update   add or freshen file    -move     move into archive from filesystem\n");
	printf(" -print    print files to stdout  -list     Show info about files in archive\n");
	printf(" -test     check archive          -comment  Add or modify archive comment\n");
	printf(" -help     this help text         -version  show program version\n");
	printf("\n");
	printf("Examples:\n");
	printf("  zoo a  save /bin/*   # Create save.zoo from all files in /bin\n");
	printf("  zoo x  save          # Extract save.zoo with full paths in current directory\n");
	printf("  zoo x: save          # Extract files in save.zoo to current directory\n");
	printf("  zoo l  save          # List contents of save.zoo\n");
	printf("-------------------------------------------------------------------------------\n");
	printf("See also 'zoo H', or the manual page zoo(1) for more information.\n");

	return 0;
}

/* usage list including Novice commands */
static int usage(int rc)
{
	printf("zoo: invalid or missing command, please use: 'acDeglLPTuUvx' or '-cmd' syntax\n"
	       "Try 'zoo -h', 'zoo H', or the manual page zoo(1) for more information.\n");

	return rc;
}

static int version(void)
{
	printf("%s\n", PACKAGE_STRING);
	return 0;
}

int main(argc, argv)
int argc;
char **argv;
{
	char *zooname;			 /* synonym for argv[2] -- to make life easier */

#ifndef OOZ
	static char incorrect_args[] = "Incorrect number of arguments.\n";
	int filecount;			 /* how many filespecs supplied */
	char *option;
	/* ADD=0 EXT=5 MOV=14 TES=20 PRI=26 DEL=33 LIS=41 UPD=47 FRE=55 COMMENT=64 HELP=73 VER=79 */
	static char nov_cmds[] =
	    "-add -extract -move -test -print -delete -list -update -freshen -comment -help -version\n";

#ifdef NOENUM
#define NONE      -1
#define ADD        0
#define EXTRACT    5
#define MOVE      14
#define TEST      20
#define PRINT     26
#define DELETE    33
#define LIST      41
#define UPDATE    47
#define FRESHEN   55
#define COMMENT   64
#define HELP      73
#define VERS      79
	int cmd = NONE;
#else
	enum choice {
		NONE = -1, ADD = 0, EXTRACT = 5, MOVE = 14, TEST = 20, PRINT = 26,
		DELETE = 33, LIST = 41, UPDATE = 47, FRESHEN = 55, COMMENT = 64,
		HELP = 73, VERS = 79
	};
	enum choice cmd = NONE;		 /* assume no Novice command */
#endif /* NOENUM */
#else
	static char usage1[] = "Ooz 2.11 (2004/06/19) public domain Zoo unarchiver utility by Rahul Dhesi\n";
	static char usage2[] = "Usage:  ooz archive[.zoo]  (\"ooz -h\" for help)\n";
#endif /* !OOZ */

#ifdef SPECINIT
	spec_init();			 /* system-specific startup code */
#endif

/*
 * make sure T_UINT16 is an unsigned 16-bit type, exactly.  This code is
 * included only if T_UINT16 was defined by default at the end of
 * options.h.
 */
#ifdef CHECK_TUINT
	{
		T_UINT16 i;
		int status = 0;

		i = ((unsigned)1) << 15;
		if (i < 0)
			status = 1;
		if (i != ((unsigned)1) << 15)
			status = 1;
		i *= 2;
		if (i != 0)
			status = 1;
		if (status != 0)
			prterror('w', "Configuration problem: T_UINT16 is not 16 bits\n");
	}
#endif

	arg_count = argc;
	arg_vector = argv;
	zooname = argv[FIRST_ARG - 1];	 /* points to name or archive */

#ifdef OOZ
	if (argc < 2) {
		putstr(usage1);
		putstr(usage2);
		zooexit(1);
	}
#else
	if (argc < 2)
		return usage(0);

	filecount = argc - 3;
	option = str_dup(argv[1]);

#ifdef TRACE_IO
	if (*option == ':') {		 /* for debugging output */
		verbose++;
		option++;		 /* hide the : from other functions */
	}
#endif

#ifdef WAIT_PROMPT
	if (*option == 'w') {
		option++;		 /* hide w from other functions */
		wait_return();
	}
#endif					 /* WAIT_PROMPT */

	if (*option == 'H')
		ms_help(option);
	if (*option == 'h' || *option == 'H')
		return help();
	if (strchr("-acDegflLPTuUvVx", *option) == NULL)
		return usage(1);

	if (*option == '-') {
#ifdef NOENUM
		cmd = instr(nov_cmds, str_lwr(option));
#else
		cmd = (enum choice)instr(nov_cmds, str_lwr(option));
#endif
		if (strlen(option) < 2 || cmd == NONE)
			return usage(1);
		if (cmd == HELP)
			return help();
		if (cmd == VERS)
			return version();
		if (((cmd == ADD  || cmd == MOVE || cmd == FRESHEN || cmd == UPDATE || cmd == DELETE)  && argc < 4) ||
		    ((cmd == LIST || cmd == TEST || cmd == EXTRACT || cmd == PRINT  || cmd == COMMENT) && argc < 3)) {
			fprintf(stderr, "%s", incorrect_args);
			return usage(1);
		}
	} else {
		char *wheresI;		 /* will be null if I option not supplied */
		char *wheresA;		 /* will be null if I option not supplied */

		wheresI = strchr(option, 'I');
		wheresA = strchr(option, 'A');

		if ((strchr("au", *option) && ((wheresI && argc != 3) || (!wheresI && argc < 4)))
		    || (strchr("DU", *option) && argc < 4)
		    || (strchr("cexlvVL", *option) && argc < 3)
		    || (strchr("TP", *option) && argc != 3)
		    || (*option == 'f' && argc != 2)
		    || (*option == 'g' && ((!wheresA && argc < 4) || (wheresA && argc != 3)))) {
			if (*option == 'v')
				return version();

			fprintf(stderr, "%s", incorrect_args);
			return usage(0);
		}
	}
#endif /* end of not OOZ */

#ifndef OOZ
	/*
	 * if not doing a list and no extension in archive name, add
	 * default extension 
	 */
	if (*option != 'f' && cmd != LIST && strchr("lvVL", *option) == NULL &&
	    strchr(nameptr(zooname), EXT_CH) == NULL)
		zooname = newcat(zooname, EXT_DFLT);
#endif

	/*
	 * Here we allocate a large block of memory for the duration of the program.
	 * lzc() and lzd() will use half of it each.  Routine getfile() will use all
	 * of it.  Routine decode() will use the first 8192 bytes of it.  Routine
	 * encode() will use all of it.
	 */

	/*                          fudge/2           fudge/2
	**             [______________||________________|]
	**               output buffer    input buffer
	*/
	out_buf_adr = ealloc(MEM_BLOCK_SIZE);
	in_buf_adr = out_buf_adr + OUT_BUF_SIZE + (FUDGE / 2);

#ifdef OOZ
	zooext(zooname, "\0");		 /* just extract -- no fancy stuff   */
#else
	if (cmd != NONE) {
		switch (cmd) {

		case ADD:
			zooadd(zooname, filecount, &argv[3], "aP:");
			break;
		case FRESHEN:
			zooadd(zooname, filecount, &argv[3], "auP:");
			break;
		case UPDATE:
			zooadd(zooname, filecount, &argv[3], "aunP:");
			break;
		case MOVE:
			zooadd(zooname, filecount, &argv[3], "aMP:");
			break;

		case EXTRACT:
			zooext(zooname, "x");
			break;
		case TEST:
			zooext(zooname, "xNd");
			break;
		case PRINT:
			zooext(zooname, "xp");
			break;

		case DELETE:
			zoodel(zooname, "DP", 1);
			break;
		case LIST:
			zoolist(&argv[2], "VC", argc - 2);
			break;
		case COMMENT:
			comment(zooname, "c");
			break;
		default:
			return usage(0);
		}
	} else {
		switch (*option) {
		case 'a':
		case 'u':
		case 'T':
			zooadd(zooname, filecount, &argv[3], option);
			break;
#ifdef FILTER
		case 'f':
			zoofilt(option);
			break;
#endif
		case 'D':
			zoodel(zooname, option, 1);
			break;
		case 'U':
			zoodel(zooname, option, 0);
			break;
		case 'g':
			zoodel(zooname, option, 2);
			break;
		case 'v':
		case 'V':
		case 'l':
			zoolist(&argv[2], option, 1);
			break;
		case 'L':
			zoolist(&argv[2], option, argc - 2);
			break;
		case 'e':
		case 'x':
			zooext(zooname, option);
			break;
		case 'P':
			zoopack(zooname, option);
			break;
		case 'c':
			comment(zooname, option);
			break;
		default:
			return usage(1);
		}
	}

#endif /* OOZ */
	return 0;			 /* keep lint & compilers happy */
}

/* multi-screen help facility thanks to Bill Davidsen */

/* help screens */
static char *scrn1[] = {
	"Usage:",
	"  zoo COMMAND[OPTIONS] archive files(s)",
	"",
	"Commands:",
	" a  add files",
	"    u - update, replace only if file is newer than saved version",
	"    n - new, add if file is not in archive",
	"    f - fast, don't compress at all",
	"    h - high performance compressor, slower than default",
	"    M - move files to archive, delete after saving",
	"    c - add a comment to each file added",
	"    C - add a comment to the archive as a whole",
	"    : - strip directory names, save filenames only",
	"    q - quiet (qq suppresses warnings, qqq suppresses nonfatal errors too)",
	"    P - pack after adding, remove overwritten or deleted files",
	"        (leaves a .bak file, use PP to overwrite it)",
	"    I - read filenames from standard input",
	"    + - enable generations",
	NULL
};

static char *scrn2[] = {
	"",
	" e  extract files",
	" x  extract files",
	"    : - extract to current directory (ignore pathnames)",
	"    . - make absolute pathnames relative to current directory",
	"        (name /etc/hosts becomes ./etc/hosts)",
	"    / - extract to subdirs, // create subdirs as needed - default",
	"        (the sequence :/ may be used to use but not create subdirs)",
	"    q - quiet",
	"    d - extract deleted files, too. dd extract *only* deleted files",
	"    N - extract to nowhere. Used to test the archive with xN or xNq",
	"    p - extract for pipe to standard output. Use q to avoid header",
	"",
#ifdef FATTR
	"    O - overwrite without asking, OO overwrites readonly files",
#else
	"    O - overwrite without asking",
#endif
	"    S - overwrite superseded (newer) files",
	NULL
};

static char *scrn3[] = {
	"",
	" l  list archive info",
	" L  list info for multiple archives",
	" v  list verbose file info and archive comment",
	" V  list verbose file info, archive and file comments",
	"    v - verbose (same as v command, used with L for multiple files",
	"    V - verbose with file comments",
	"    C - show CRC",
	"    a - show archive name in file listing (useful with L)",
#ifdef FATTR
	"    m - mode, show file modes in octal",
#endif
	"    d - show deleted files",
	"    q - quiet, shows only file info, no comments or headers",
	"    f - fast, lists only filename, no pathname, multiple columns",
	"    1 - one column output (for the f option)",
	"",
	" c  comment changes, change or add comments to listed files",
	"    (changes all file comments if no files given)",
	"    A - only change archive comment",
	NULL
};

static char *scrn4[] = {
	"",
	" P  pack archive, remove deleted or overwritten files",
	"    E - erase the .bak file when done",
	"",
	" D  delete files by name",
	"    P - pack after deletion, use PP if .bak file exists",
	"    q - quiet",
	"",
	" T  timestamp adjust, make archive age of newest file",
	"",
	" g  generation commands",
	"    l - set generation limit on files",
	"    A - apply limit to archive rather than a file (with gl)",
	"",
	" f  filter, copy stdin to stdout with [de]compression",
	"    c - compress",
	"    u - uncompress",
	"    h - use the high compression method",
	NULL
};

static char *scrn5[] = {
	"",
	"Examples:",
	"  zoo a arch file1 files             # just add a few files",
	"  zoo a test part1/*.c part2/*.c     # add C source files in subdirectories",
	"  zoo ah test *.doc                  # add all .doc files with high compression",
	"  zoo x test                         # extract all files",
	"  zoo x: test                        # extract files to current directory",
	"  zoo xp test users.lst | sort       # extract a single file and sort before listing",
	"  zoo v arch                         # list the contents and archive comments",
	"  zoo L xxx.zoo /doc/*.zoo ../*.zoo  # list all files in all archives",
	NULL
};

static char **screens[] = {
	scrn1,				 /* intro and add */
	scrn2,				 /* extract */
	scrn3,				 /* list commands */
	scrn4,				 /* other commands */
	scrn5,				 /* add and extract examples */
	NULL
};

/* multi-screen help routine */
static void ms_help(options)
char *options;
{
#ifndef SZ_SCREEN			 /* screen size can be overridden in options.h */
#define SZ_SCREEN 24
#endif
	int scrnlen = SZ_SCREEN;
	char ***curscreen, **curline;
	int linecount;

	/* if "Hnn" output in nn line format */
	if (++options)
		sscanf(options, "%d", &scrnlen);
	if (scrnlen < 2)
		scrnlen = SZ_SCREEN;

	/* loop thru screens */
	for (curscreen = screens; *curscreen != NULL; ++curscreen) {
 /*		printf("\n\n\n\n"); */
		linecount = scrnlen;
		curline = *curscreen;
		while (*curline != NULL) {
			printf("%s\n", *(curline++));
			--linecount;
		}

	/* slew page */
/*		while (--linecount != 0) putchar('\n'); */
		wait_return();		 /* print msg & wait for RETURN */
	}

	exit(0);
}

/********
 * wait_return prints a message, then waits until user hits RETURN key,
 * then returns.  Special cases: (a) if not interactive (as tested with
 * isatty() if available), it returns immediately; (b) while waiting for
 * RETURN, if EOF occurs, it causes zooexit(0)
 */
static void wait_return()
{
#ifdef HAVE_ISATTY
	if (!isatty(fileno(stdout)) || !isatty(fileno(stdin)))
		return;
#endif
#ifdef PAUSE_HELP
	(void)printf("Hit RETURN (or ENTER) key to continue...");
	for (;;) {
		int key;

		key = getchar();
		if (key == EOF)
			zooexit(0);
		if (key == '\n' || key == '\r')
			return;
	}
#endif
}

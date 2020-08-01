# Make Zoo
#
# This makefile expects two macro names, `CFLAGS' and `EXTRA', to hold
# all the switches to be supplied to the C compiler.  It also expects a
# macro `LDFLAGS' to hold the switch for the loader when invoked.  The
# macro "MODEL" holds switches needed for both compile and link, such as
# "memory model" for Intel and Z8000 processors. OPTIM is the optimize
# option and may be set on the make command line to -O2 or whatever your
# compiler thinks is nice.
#
# The contents of this makefile are hereby released to the public domain.
#                             -- Rahul Dhesi 1991/07/05


MAKE      ?= make	      # needed for some systems e.g. older BSD

CC        ?= cc
CFLAGS    ?=
MODEL     ?=
EXTRA     ?= -DBIG_MEM -DNDEBUG

DESTDIR   ?= /usr/local/bin

#List of all object files created for Zoo
ZOOOBJS = addbfcrc.o addfname.o basename.o comment.o crcdefs.o \
		getfile.o lzc.o lzd.o machine.o makelist.o misc.o misc2.o \
		nextfile.o needed.o options.o parse.o portable.o prterror.o \
		version.o zoo.o zooadd.o zooadd2.o zoodel.o zooext.o zoofilt.o \
		zoolist.o zoopack.o io.o lzh.o maketbl.o maketree.o huf.o \
		encode.o decode.o

FIZOBJS = fiz.o addbfcrc.o portable.o crcdefs.o

.c.o :
	$(CC) $(CFLAGS) $(MODEL) $(EXTRA) $*.c

all : 
	@echo 'There is no default.  Please specify an appropriate target from'
	@echo 'the makefile, or type "make help" for more information'

help :
	@echo "Possible targets are as follows.  Please examine the makefile"
	@echo "for more information."
	@echo ' '
	@echo "generic:      generic **IX environment, minimal functionlity"
	@echo "bsd:          4.3BSD or reasonable equivalent"
	@echo "bsdansi:      4.3BSD with ANSI C"
	@echo "ultrix:       ULTRIX 4.1"
	@echo "convex:       Convex C200 series"
	@echo "sysv:         System V Release 2 or 3; or SCO Xenix"
	@echo "linux:        Linux"
	@echo "scodos:       Cross-compiler under SCO Xenix/UNIX for MS-DOS"
	@echo "xenix286:     Older Xenix/286 (not tested)"
	@echo "xenix68k:     Xenix/68000 (not tested)"
	@echo ' '
	@echo "install:      Move zoo to $(DESTDIR)/tzoo (alpha test)"
	@echo "inst_beta:    Move zoo to $(DESTDIR)/bzoo (beta test)"
	@echo "inst_prod:    Move zoo to $(DESTDIR)/zoo  (production)"

# install alpha zoo as "tzoo"
install:
	mv zoo $(DESTDIR)/tzoo

# install beta zoo as "bzoo"
inst_beta:
	mv zoo $(DESTDIR)/bzoo

# install production zoo as "zoo"
inst_prod:
	mv zoo $(DESTDIR)/zoo

# executable targets
TARGETS = zoo fiz

#######################################################################
# SYSTEM-SPECIFIC TARGETS
#######################################################################

# A generic system -- may have less than full functionality.
# Compile with -g, since debugging will probably be needed.
generic:
	$(MAKE) CFLAGS="-c -g -DGENERIC" $(TARGETS)

# Reasonably generic BSD 4.3
bsd:
	$(MAKE) CFLAGS="-c $(OPTIM) -DBSD4_3" $(TARGETS)

# Linux
linux:
	$(MAKE) CC="gcc" CFLAGS="-c $(OPTIM) -DLINUX -DANSI_HDRS" LDFLAGS="$(LDFLAGS)" $(TARGETS)

# ULTRIX 4.1
ultrix:
	$(MAKE) CFLAGS="-c $(OPTIM) -DULTRIX" $(TARGETS)

# BSD with ANSI C - works on MIPS and Ultrix/RISC compilers
bsdansi:
	$(MAKE) CFLAGS="-c $(OPTIM) -DBSD4_3 -DANSI_HDRS" $(TARGETS)

# Convex C200 series
convex:
	$(MAKE) CFLAGS="-c $(OPTIM) -DBSD4_3 -DANSI_HDRS" $(TARGETS)

# SysV.2, V.3, SCO Xenix
sysv:
	$(MAKE) CFLAGS="-c $(OPTIM) -DSYS_V" $(TARGETS)

# DOS version cross compiled from SCO Xenix/UNIX
scodos:
	$(MAKE) CFLAGS="-c $(OPTIM) -DTURBOC -DANSI_HDRS -DBIG_MEM" \
		EXTRA="-dos -Ml" LDFLAGS="-o zoo.exe" $(TARGETS)

# Tested for zoo 2.01 on: Xenix 3.4 on Greg Laskin's Intel 310/286;
# SCO Xenix 2.2 on Robert Cliff's AT.
# `-Ml' for large memory model, `-M2' to generate code for 80286 cpu,
# `-F xxxx' for xxxx (hex) bytes of stack space.
xenix286:
	@echo "Warning: xenix286 is not fully functional"
	$(MAKE) CFLAGS="-c $(OPTIM) -DSYS_V" \
		MODEL="-Ml -M2 -Md" \
		LDFLAGS="-s -n -Md -Mt500 -F 5000" $(TARGETS)

# Radio Shack Model 16 with Xenix/68000 3.01.01. "-DM_VOID" tells not 
# to try to do a typedef of `void'. "-Dvoid=int" because compiler doesn't 
# know about `void'.  `-s -n' strips and makes it shareable.  Used to work
# with zoo 2.01; not tested with 2.1.
xenix68k:
	$(MAKE) CFLAGS="-c $(OPTIM) -DSYS_V -DM_VOID -Dvoid=int" \
		LDFLAGS="-s -n" $(TARGETS)

#######################################################################
# CLEANUP TARGETS
#######################################################################

# standard clean -- remove all transient files
clean :
	rm -f core a.out $(ZOOOBJS) $(FIZOBJS)

# object clean only -- just remove object files
objclean:
	rm -f *.o

#######################################################################
# BINARY TARGETS
#######################################################################

zoo: $(ZOOOBJS)
	$(CC) -o zoo $(MODEL) $(LDFLAGS) $(ZOOOBJS)

fiz: $(FIZOBJS)
	$(CC) -o fiz $(MODEL) $(LDFLAGS) $(FIZOBJS)

#######################################################################
# DEPENDENCIES
#######################################################################
# DO NOT DELETE THIS LINE -- it marks the beginning of this dependency list

addbfcrc.o: options.h
addfname.o: options.h various.h zoo.h zoofns.h zooio.h
addfname.o: zoomem.h
basename.o: assert.h debug.h options.h parse.h various.h
basename.o: zoo.h zoofns.h zooio.h
bsd.o: nixmode.i nixtime.i
comment.o: errors.i options.h portable.h various.h
comment.o: zoo.h zoofns.h zooio.h
crcdefs.o: options.h
decode.o: ar.h lzh.h options.h zoo.h
encode.o: ar.h errors.i lzh.h
encode.o: options.h zoo.h
fiz.o: options.h portable.h various.h zoo.h zoofns.h
fiz.o: zooio.h
generic.o: nixmode.i nixtime.i
getfile.o: options.h various.h zoo.h zoofns.h zooio.h
getfile.o: zoomem.h
huf.o: ar.h errors.i lzh.h options.h zoo.h
io.o: ar.h errors.i lzh.h options.h portable.h zoo.h
io.o: zooio.h
lzc.o: assert.h debug.h lzconst.h options.h various.h
lzc.o: zoo.h zoofns.h zooio.h zoomem.h
lzd.o: assert.h debug.h lzconst.h options.h various.h
lzd.o: zoo.h zoofns.h zooio.h zoomem.h
lzh.o: ar.h errors.i options.h zoo.h
machine.o: options.h various.h zoo.h zoofns.h zooio.h
makelist.o: assert.h debug.h errors.i options.h
makelist.o: portable.h various.h zoo.h zoofns.h zooio.h
maketbl.o: ar.h lzh.h options.h zoo.h
maketree.o: ar.h lzh.h options.h zoo.h
misc.o: errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h
misc2.o: errors.i options.h portable.h various.h zoo.h
misc2.o: zoofns.h zooio.h zoomem.h
msdos.o: errors.i options.h zoo.h zoofns.h zooio.h
needed.o: debug.h options.h portable.h various.h zoo.h
needed.o: zoofns.h zooio.h
nextfile.o: options.h various.h zoo.h
options.o: errors.i options.h various.h zoo.h zoofns.h
options.o: zooio.h
parse.o: assert.h options.h parse.h various.h zoo.h
parse.o: zoofns.h zooio.h
portable.o: assert.h debug.h machine.h options.h
portable.o: portable.h various.h zoo.h zoofns.h zooio.h

# I deleted varags.h dependancy from prterror.o since that is a
# dependancy covered by a #ifdef, and in Debian's case #undef'ed

prterror.o: options.h various.h
prterror.o: zoofns.h zooio.h
sysv.o: nixmode.i nixtime.i
turboc.o: errors.i options.h various.h zoo.h zoofns.h
zoo.o: zooio.h zoomem.h
zooadd.o: debug.h errors.i options.h parse.h portable.h
zooadd.o: various.h zoo.h zoofns.h zooio.h zoomem.h
zooadd2.o: assert.h debug.h errors.i options.h parse.h
zooadd2.o: various.h zoo.h zoofns.h zooio.h
zoodel.o: errors.i options.h portable.h various.h zoo.h zoofns.h zooio.h
zooext.o: errors.i machine.h options.h parse.h portable.h various.h zoo.h
zooext.o: zoofns.h zooio.h
zoofilt.o: options.h
zoolist.o: errors.i options.h portable.h various.h zoo.h
zoolist.o: zoofns.h zooio.h zoomem.h
zoopack.o: errors.i options.h portable.h various.h
zoopack.o: zoo.h zoofns.h zooio.h

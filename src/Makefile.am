AM_CPPFLAGS   = @MACHINE@ -DBIG_MEM -DNDEBUG
bin_PROGRAMS  = fiz zoo unzoo
if ENABLE_OOZ
bin_PROGRAMS += ooz
endif

fiz_SOURCES   = fiz.c addbfcrc.c portable.c crcdefs.c

zoo_CPPFLAGS  = -DZOO $(AM_CPPFLAGS)
zoo_SOURCES   = addbfcrc.c addfname.c ar.h assert.h basename.c comment.c\
		crcdefs.c debug.h getfile.c lzc.c lzconst.h lzd.c lzh.c	\
		lzh.h machine.c machine.h makelist.c misc.c misc2.c	\
		nextfile.c needed.c options.c options.h parse.c parse.h	\
		portable.c portable.h prterror.c zoo.c zoo.h zooadd.c	\
		zooadd2.c zoodel.c zooext.c zoofilt.c zoolist.c		\
		zoopack.c zoofns.h io.c zooio.h zoomem.h maketbl.c	\
		maketree.c huf.c encode.c decode.c various.h errors.h	\
		nixmode.i nixtime.i

ooz_CPPFLAGS  = -DOOZ $(AM_CPPFLAGS)
ooz_SOURCES   = addbfcrc.c addfname.c ar.h assert.h basename.c comment.c\
		crcdefs.c debug.h getfile.c lzc.c lzconst.h lzd.c lzh.c	\
		lzh.h machine.c machine.h makelist.c misc.c misc2.c	\
		nextfile.c needed.c options.c options.h parse.c parse.h	\
		portable.c portable.h prterror.c zoo.c zoo.h 	\
		zooext.c zoofilt.c zoolist.c		\
		zoopack.c zoofns.h io.c zooio.h zoomem.h maketbl.c	\
		maketree.c huf.c encode.c decode.c various.h errors.h	\
		nixmode.i nixtime.i

unzoo_CPPFLAGS = @SYS@
unzoo_SOURCES = unzoo.c

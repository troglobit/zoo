bin_PROGRAMS = zoo fiz

zoo_SOURCES = addbfcrc.c addfname.c ar.h assert.h basename.c comment.c	\
		crcdefs.c debug.h getfile.c lzc.c lzconst.h lzd.c lzh.c	\
		lzh.h machine.c machine.h makelist.c misc.c misc2.c	\
		nextfile.c needed.c options.c options.h parse.c parse.h	\
		portable.c portable.h prterror.c version.c zoo.c zoo.h	\
		zooadd.c zooadd2.c zoodel.c zooext.c zoofilt.c		\
		zoolist.c zoopack.c zoofns.h io.c zooio.h zoomem.h	\
		maketbl.c maketree.c huf.c encode.c decode.c various.h	\
		errors.i nixmode.i nixtime.i
zoo_CFLAGS = -DLINUX -DANSI_HDRS -DBIG_MEM -DNDEBUG

fiz_SOURCES = fiz.c addbfcrc.c portable.c crcdefs.c
fiz_CFLAGS = -DLINUX -DANSI_HDRS -DBIG_MEM -DNDEBUG

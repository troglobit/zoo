#!/bin/sh
# Linux coding style
#
# With the -T <type> we can inform indent about non-ANSI/ISO types
# that we've added, so indent doesn't insert spaces in odd places. 
# 

indent --linux-style -bad -c42 -cd42 -cp42 -d8 --line-length120 \
       -T size_t -T sigset_t -T timeval_t -T pid_t -T pthread_t \
       -T time_t -T uint32_t -T uint16_t -T uint8_t -T socklen_t \
       -T node   -T uchar    -T uint     -T ushort  -T ulong \
       -T T_UINT16  -T t_uint16 -T BYTE -T ZOOFILE \
$*

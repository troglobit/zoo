/* Buffer CRC
 *
 * addbfcrc() accepts a buffer address and a count and adds the CRC for
 * all bytes in the buffer to the global variable crccode using CRC-16.
 *
 * CRC computation algorithm originally from an article by David
 * Schwaderer in the April 1985 issue of PC Tech Journal.
 *
 * Loop optimization done by J. Brian Waters.
 *
 * I claim no copyright over the contents of this file.
 *
 *                              -- Rahul Dhesi 1986/08/27
 */
#include "options.h"

extern unsigned int crccode;
extern unsigned crctab[];

void addbfcrc(buffer,count)
register char *buffer;
register int count;

{
   register unsigned int localcrc;
   localcrc = crccode;

   for (; count--; )
      localcrc = (localcrc>>8) ^ crctab[(localcrc ^ (*buffer++)) & 0x00ff];
   crccode = localcrc;
}

Manipulate .zoo Archives
========================

zoo is a file archiving utility for maintaining collections of files.
It uses [Lempel-Ziv-Welch][LZW] compression to provide space savings in
the range of 20 to 80 percent depending on the type of data.

Unlike other archiving tools, zoo can store and selectively extract
multiple generations of the same file.  If files are added to an archive
with the same pathname yet more recent date, the older version(s) will
be retained (with a semicolon and version number, similar to file
versioning in VMS) as the new file is added.  This allows files that are
frequently modified to be backed up in such a way as to allow access to
previous versions (up to the version limit chosen) from one archive.

This project exists as a service to all computer archaeologists and acts
as a focal point for patches and maintenance for the long haul.


Origin & References
-------------------

zoo was created by Rahul Dhesi, and originally posted to the USENET
newsgroup comp.sources.misc.  This version is based on v2.10 from
[Ibiblio][], with all [Debian patches][patches] applied.

[LZW]:     https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
[Ibiblio]: http://www.ibiblio.org/pub/packages/ccic/software/unix/utils/
[patches]: https://sources.debian.org/patches/zoo/2.10-28/

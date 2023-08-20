Archiver for .zoo files
=======================
[![License Badge][]][License] [![GitHub Status][]][GitHub]

zoo is a ([public domain][pd]) file archiving tool for maintaining
collections of files.  It uses [Lempel-Ziv-Welch][LZW] compression to
provide space savings in the range of 20% to 80%, depending on the
files.

Unlike other archiving tools, zoo can store and selectively extract
multiple generations of the same file.  If files are added to an archive
with the same pathname yet more recent date, the older version(s) will
be retained (with a semicolon and version number, similar to file
versioning in VMS) as the new file is added.  This allows files that are
frequently modified to be backed up in such a way as to allow access to
previous versions (up to the version limit chosen) from one archive.

> This project exists as a service to all computer archaeologists and
> acts as a focal point for patches and maintenance for the long haul.


Examples
--------

    zoo a  save /bin/*   # Create save.zoo from all files in /bin
    zoo x  save          # Extract save.zoo with full paths in current directory
    zoo x: save          # Extract files in save.zoo to current directory
    zoo l  save          # List contents of save.zoo


Origin & References
-------------------

zoo was created by Rahul Dhesi, and originally posted to the USENET
newsgroup comp.sources.misc.  This version is based on v2.10 from
[Ibiblio][], with all [Debian patches][patches] applied.

zoo was placed in the [public domain][pd] in 2004.

[pd]:            doc/public-domain.eml
[LZW]:           https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
[Ibiblio]:       http://www.ibiblio.org/pub/packages/ccic/software/unix/utils/
[patches]:       https://sources.debian.org/patches/zoo/2.10-28/
[License]:       https://unlicense.org/
[License Badge]: https://img.shields.io/badge/License-Unlicense-blue.svg
[GitHub]:        https://github.com/troglobit/zoo/actions/workflows/build.yml/
[GitHub Status]: https://github.com/troglobit/zoo/actions/workflows/build.yml/badge.svg

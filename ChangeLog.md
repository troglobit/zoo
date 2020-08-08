Change Log
==========

All notable changes to the project are documented in this file.


v2.1 - Date Unknown
-------------------

### Changes

- On some systems, extraction of files using the older (default)
  compression method is greatly speeded up.
- Extended multiscreen help is available.
- The default archive-wide generation limit, when generations are
  enabled, is 3.

### Fixes

- Memory allocation is improved, so that the MS-DOS version will not
  prematurely abort when updating a large archive.
- The VAX/VMS version preserves file timestamps during extraction.


v2.01 - Date Unknown
--------------------

### Changes

- A change was made that will make zoo preserve the mode (file
  protection) of a zoo archive when it is packed.  This is effective
  only if zoo is compiled to preserve and restore file attributes.
  Currently this is so only for **IX systems.

- Blanks around equal signs in commands given to "make" were removed
  from the mk* scripts for better compatibility with more **IX
  implementations including Sun's.

- Compression is now greatly improved if the "h" option is used.

- The default behavior is to preserve full pathnames during extraction. 

### Fixes

- A bug was fixed that had caused the first generation of a file to
  sometimes unexpectedly show up in archive listings.

- A bug was fixed that had caused the MS-DOS version to silently skip
  files that could not be extracted because of insufficient disk space.

- A bug was fixed that had sometimes made it impossible to selectively
  extract a file by specifying its name, even though all files could be
  extracted from the archive by not specifying any filenames.  This
  occurred when a file had been archived on a longer-filename system
  (e.g. AmigaDOS) and extraction was attempted on a shorter-filename
  system (e.g. MS-DOS).

- A bug was fixed that had caused an update of an archive to
  not always add all newer files.


v2.0 - Date Unknown
-------------------

### Changes

- A comment may now be attached to the archive itself.

- New option `OO` allows forced overwriting of read-only files.

- zoo no longer extracts a file if a newer copy already exists on disk;
  the `S` option overrides this.

- File attributes are preserved for **IX systems.

- Multiple generations of the same file are supported.

- zoo now act as a compression or decompression filter on a stream of
  data and will use a CRC value to check the integrity of a data stream
  that is uncompressed.

### Fixes

- A bug was fixed that caused removal of a directory link if files were
  moved to an archive by the superuser on a **IX system.

- The data recovery modifier `@` was greatly enhanced.  Self-extracting
  archives created for MS-DOS systems can now be extracted by zoo on any
  system with help from fiz(1).


v1.71 - Date unknown
--------------------

### Changes

- New modifiers to the list commands permit optional suppression of
  header and trailer information, inclusion of directory names in
  columnized listings, and fast one-column listings.

- Timezones are handled.

- zoo can now use of the shared library on the **IX PC.

- VAX/VMS is now supported reasonably well.

### Fixes

- A bug was fixed that had made it impossible to individually update
  comments for a file whose name did not correspond to MS-DOS format.

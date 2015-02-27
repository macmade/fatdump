XEOS / tools / fatdump
======================

[![Build Status](https://img.shields.io/travis/macmade/XEOS-tools-fatdump.svg?branch=master&style=flat)](https://travis-ci.org/macmade/XEOS-tools-fatdump)
[![Issues](http://img.shields.io/github/issues/macmade/XEOS-tools-fatdump.svg?style=flat)](https://github.com/macmade/XEOS-tools-fatdump/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)
![License](https://img.shields.io/badge/license-xeos-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)

About
-----

**fatdump utility for building the XEOS Operating System.**

This subproject is part of the [XEOS Operating System](https://github.com/macmade/XEOS/) project.

Usage
-----

    fatdump [OPTIONS] IMAGE
    
    Options
    
        --mbr      Prints MBR infos
        --mbr-raw  Prints raw MBR data
        --fat      Prints FAT infos
        --fat-raw  Prints raw FAT data
        --dir      Prints root directory infos
        --dir-raw  Prints raw root directory data
        --hidden   Displays hidden file and folders
        --deleted  Displays deleted file and folders
        --data     Displays raw data for files
        --extract  Extract files in the current directory
        -h         Prints this help message
    
    Example:
    
        fatdump --hidden --deleted fat-disk.img

Extracting files
----------------

All files can be extracted in the current working directory using the `--extract` option.

Note that hidden files can be extracted with the `--hidden` option, as well as deleted files with the `--deleted` option.  
This can be useful for data-recovery or forensics.

Example output
--------------

By default, `fatdump` will only display the FAT volume's hierarchy:

    $ fatdump disk.img
    -----------------------------------
    Files in volume: TEST       
    -----------------------------------
    [+] SUBDIR
     |  [+] .
     |  [+] ..
     |   |- A.TXT <7 bytes>
     |   |- B.TXT <12 bytes>
     |  [+] SUBSUB
     |   |  [+] .
     |   |  [+] ..
     |   |   |- A.TXT <7 bytes>
     |   |- C.TXT <12 bytes>
     |- A.TXT <7 bytes>
    [+] SUBDIR2
     |  [+] .
     |  [+] ..
     |   |- A.TXT <7 bytes>
    -----------------------------------

File's data can be displayed with the `--data` option.  
Note that hidden files can be displayed as well with the `--hidden` option, as well as deleted files with the `--deleted` option.  

    $ fatdump --data disk.img
    ----------------------------------------------------------------------------------------------------------------------
    Data for file: /LOREM.TXT - 543 bytes
    ----------------------------------------------------------------------------------------------------------------------
    4C 6F 72 65 6D 20 69 70 73 75 6D 20 64 6F 6C 6F 72 20 73 69 74 20 61 6D 65 74 2C 20 63 | Lorem.ipsum.dolor.sit.amet,.c
    6F 6E 73 65 63 74 65 74 75 65 72 20 61 64 69 70 69 73 63 69 6E 67 20 65 6C 69 74 2C 20 | onsectetuer.adipiscing.elit,.
    73 65 64 20 64 69 61 6D 20 6E 6F 6E 75 6D 6D 79 20 6E 69 62 68 20 65 75 69 73 6D 6F 64 | sed.diam.nonummy.nibh.euismod
    20 74 69 6E 63 69 64 75 6E 74 20 75 74 20 6C 61 6F 72 65 65 74 20 64 6F 6C 6F 72 65 20 | .tincidunt.ut.laoreet.dolore.
    6D 61 67 6E 61 20 61 6C 69 71 75 61 6D 20 65 72 61 74 20 76 6F 6C 75 74 70 61 74 2E 20 | magna.aliquam.erat.volutpat..
    55 74 20 77 69 73 69 20 65 6E 69 6D 20 61 64 20 6D 69 6E 69 6D 20 76 65 6E 69 61 6D 2C | Ut.wisi.enim.ad.minim.veniam,
    ----------------------------------------------------------------------------------------------------------------------

The MBR infos can be displayed with the `--mbr` option:
    
    $ fatdump --mbr disk.img
    -----------------------------------------
    MBR:
    -----------------------------------------
    - OEM ID:                  BSD  4.4
    - Bytes per sector:        512
    - Sectors per cluster:     2
    - Reserved sectors:        1
    - Number of FATs:          2
    - Max root dir entries:    512
    - Total sectors:           28799
    - Media descriptor:        0xF8
    - Sectors per FAT:         56
    - Sectors per track:       32
    - Heads per cylinder:      16
    - Hidden sectors:          1
    - LBA sectors:             0
    - Drive number:            0x80
    - Extended boot signature: 0x29
    - Volume serial number:    0x3D480BFD
    - Volume label:            TEST       
    - File system:             FAT16   
    - Bootable:                yes
    -----------------------------------------
    
Raw data for the MBR can be displayed with the `--mbr-raw` option:

    $ fatdump --mbr-raw disk.img
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    MBR raw data:
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    EB 3C 90 42 53 44 20 20 34 2E 34 00 02 02 01 00 02 00 02 7F 70 F8 38 00 20 00 10 00 01 00 00 00 00 00 00 00 80 00 | .<.BSD..4.4.........p.8...............
    29 FD 0B 48 3D 54 45 53 54 20 20 20 20 20 20 20 46 41 54 31 36 20 20 20 FA 31 C0 8E D0 BC 00 7C FB 8E D8 E8 00 00 | )..H=TEST.......FAT16....1.....|......
    5E 83 C6 19 BB 07 00 FC AC 84 C0 74 06 B4 0E CD 10 EB F5 30 E4 CD 16 CD 19 0D 0A 4E 6F 6E 2D 73 79 73 74 65 6D 20 | ^..........t.......0.......Non-system.
    64 69 73 6B 0D 0A 50 72 65 73 73 20 61 6E 79 20 6B 65 79 20 74 6F 20 72 65 62 6F 6F 74 0D 0A 00 00 00 00 00 00 00 | disk..Press.any.key.to.reboot.........
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 | ......................................
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 AA                                                             | ................U.
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    
The File Allocation Table can be displayed with the `--fat` option (`--fat-raw` for the raw FAT data):
    
    $ fatdump --fat disk.img
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    FAT:
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
           0: Last   |        1: Last   |        2: Last   |        3: 0x0004 |        4: 0x0005 |        5: 0x0006 |        6: Last   |        7: Free  
           8: Free   |        9: Last   |       10: Free   |       11: Free   |       12: Free   |       13: Free   |       14: Free   |       15: Last  
          16: 0x0011 |       17: 0x0012 |       18: 0x0013 |       19: Last   |       20: Last   |       21: 0x0016 |       22: 0x0017 |       23: 0x0018
          24: Last   |       25: Last   |       26: Free   |       27: 0x001C |       28: 0x001D |       29: 0x001E |       30: Last   |       31: Last  
          32: Free   |       33: Free   |       34: Free   |       35: Free   |       36: Free   |       37: Free   |       38: 0x0027 |       39: 0x0028
          40: 0x0029 |       41: Last   |       42: Last   |       43: 0x002C |       44: 0x002D |       45: 0x002E |       46: Last   |       47: 0x0030
          48: 0x0031 |       49: 0x0032 |       50: Last   |       51: Last   |       52: Last   |       53: Last   |       54: Last   |       55: 0x0038
          56: 0x0039 |       57: 0x003A |       58: Last   |       59: Last   |       60: 0x003D |       61: 0x003E |       62: 0x003F |       63: Last   
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    
The volume's root directory can be displayed with the `--dir` option (`--dir-raw` for the raw directory data):

    $ fatdump --dir disk.img
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    Root directory:
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    1   : TEST                                         | 2   : LFN                                          | 3   : ~1      TRA                                 
        - Size:                    0                   | .................................................. |     - Size:                    4096               
        - Cluster:                 0                   | .................................................. |     - Cluster:                 3                  
        - Creation time:           -                   | .................................................. |     - Creation time:           2015/02/26 04:31:18
        - Last access time:        -                   | .................................................. |     - Last access time:        2015/02/26 00:00:00
        - Last modification time:  2015/02/26 04:40:22 | .................................................. |     - Last modification time:  2015/02/26 04:31:18
        - Read-only:               no                  | .................................................. |     - Read-only:               no                 
        - Hidden:                  no                  | .................................................. |     - Hidden:                  yes                
        - System:                  no                  | .................................................. |     - System:                  no                 
        - Volume ID:               yes                 | .................................................. |     - Volume ID:               no                 
        - Directory:               no                  | .................................................. |     - Directory:               no                 
        - Archive:                 yes                 | .................................................. |     - Archive:                 yes                
        - LFN:                     no                  | .................................................. |     - LFN:                     no                 
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    4   : SUBDIR                                       | 5   : LFN                                          | 6   : TRASHE~1                                    
        - Size:                    0                   | .................................................. |     - Size:                    0                  
        - Cluster:                 9                   | .................................................. |     - Cluster:                 2                  
        - Creation time:           2015/02/26 04:31:30 | .................................................. |     - Creation time:           2015/02/26 04:31:18
        - Last access time:        2015/02/26 00:00:00 | .................................................. |     - Last access time:        2015/02/26 00:00:00
        - Last modification time:  2015/02/26 04:31:30 | .................................................. |     - Last modification time:  2015/02/26 04:31:18
        - Read-only:               no                  | .................................................. |     - Read-only:               no                 
        - Hidden:                  no                  | .................................................. |     - Hidden:                  yes                
        - System:                  no                  | .................................................. |     - System:                  no                 
        - Volume ID:               no                  | .................................................. |     - Volume ID:               no                 
        - Directory:               yes                 | .................................................. |     - Directory:               yes                
        - Archive:                 no                  | .................................................. |     - Archive:                 no                 
        - LFN:                     no                  | .................................................. |     - LFN:                     no                 
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
    12  : A       TXT                                  | 506 : Free                                         | 507 : Free                                        
        - Size:                    7                   | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Cluster:                 31                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Creation time:           2015/02/16 03:34:32 | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Last access time:        2015/02/26 00:00:00 | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Last modification time:  2015/02/26 04:31:54 | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Read-only:               no                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Hidden:                  no                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - System:                  no                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Volume ID:               no                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Directory:               no                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - Archive:                 yes                 | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        - LFN:                     no                  | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    ------------------------------------------------------------------------------------------------------------------------------------------------------------

License
-------

XEOS is released under the terms of the XEOS Software License.

Repository Infos
----------------

    Owner:			Jean-David Gadina - XS-Labs
    Web:			www.xs-labs.com
    Blog:			www.noxeos.com
    Twitter:		@macmade
    GitHub:			github.com/macmade
    LinkedIn:		ch.linkedin.com/in/macmade/
    StackOverflow:	stackoverflow.com/users/182676/macmade

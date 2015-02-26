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
        -h         Prints this help message
    
    Example:
    
        fatdump fat-disk.img

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

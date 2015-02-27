/*******************************************************************************
 * Copyright (c) 2015, Jean-David Gadina - www.xs-labs.com
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  -   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *  -   Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *  -   Neither the name of 'Jean-David Gadina' nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*!
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2015, Jean-David Gadina - www.xs-labs.com
 */

#ifndef FATDUMP_DIR_ENTRY_H
#define FATDUMP_DIR_ENTRY_H

#ifdef __cplusplus
extern "C" {
#endif

typedef const struct __DirEntry * DirEntryRef;
typedef       struct __DirEntry * MutableDirEntryRef;

#include "C99.h"
#include "Disk.h"

enum
{
    DirEntryAttributeUnknown   = 0x00,
    DirEntryAttributeReadOnly  = 0x01,
    DirEntryAttributeHidden    = 0x02,
    DirEntryAttributeSystem    = 0x04,
    DirEntryAttributeVolumeID  = 0x08,
    DirEntryAttributeDirectory = 0x10,
    DirEntryAttributeArchive   = 0x20,
    DirEntryAttributeLFN       = 0x0F
};

MutableDirEntryRef  DirEntryCreate( FILE * fp, DirRef dir );
MutableDirEntryRef  DirEntryCreateWithData( uint8_t * data, DirRef dir, bool freeWhenDone );
void                DirEntryDelete( MutableDirEntryRef o );

const void        * DirEntryGetData( DirEntryRef o );
DirRef              DirEntryGetDir( DirEntryRef o );
size_t              DirEntryGetDataSize( DirEntryRef o );
void              * DirEntryCreateFileData( DirEntryRef o, size_t * size );

bool                DirEntryIsFree( DirEntryRef o );
bool                DirEntryIsReadOnly( DirEntryRef o );
bool                DirEntryIsHidden( DirEntryRef o );
bool                DirEntryIsSystem( DirEntryRef o );
bool                DirEntryIsVolumeID( DirEntryRef o );
bool                DirEntryIsDirectory( DirEntryRef o );
bool                DirEntryIsArchive( DirEntryRef o );
bool                DirEntryIsLFN( DirEntryRef o );
bool                DirEntryIsDeleted( DirEntryRef o );

const char        * DirEntryGetFullPath( DirEntryRef o );
const char        * DirEntryGetFilename( DirEntryRef o );
const char        * DirEntryGetName( DirEntryRef o );
int                 DirEntryGetAttributes( DirEntryRef o );
time_t              DirEntryGetCreationTime( DirEntryRef o );
time_t              DirEntryGetLastAccessTime( DirEntryRef o );
time_t              DirEntryGetLastModificationTime( DirEntryRef o );
uint16_t            DirEntryGetCluster( DirEntryRef o );
size_t              DirEntryGetSize( DirEntryRef o );

#ifdef __cplusplus
}
#endif

#endif /* FATDUMP_DIR_ENTRY_H */

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

#include "Disk.h"
#include "__private/Disk.h"

void * DiskCreateFileDataForEntry( DiskRef o, DirEntryRef entry, size_t * size )
{
    uint8_t * data;
    uint8_t * tempData;
    uint16_t  cluster;
    size_t    entrySize;
    size_t    s;
    size_t    r;
    size_t    bytesPerCluster;
    long      offset;
    
    if( size != NULL )
    {
        *( size ) = 0;
    }
    
    if( o == NULL )
    {
        return NULL;
    }
    
    if( o->fp == NULL || o->dataRegion <= 0 )
    {
        return NULL;
    }
    
    if
    (
            DirEntryIsFree( entry )
        || DirEntryIsLFN( entry )
        || DirEntryIsVolumeID( entry )
    )
    {
        return NULL;
    }
    
    cluster   = DirEntryGetCluster( entry );
    
    if( DirEntryIsDirectory( entry ) )
    {
        entrySize = MBRGetMaxRootDirEntries( o->mbr ) * 32;
    }
    else
    {
        entrySize = DirEntryGetSize( entry );
    }
    
    if
    (
           FATGetClusterTypeForEntry( o->fat, cluster ) != FATClusterTypeUsed
        && FATGetClusterTypeForEntry( o->fat, cluster ) != FATClusterTypeLast
    )
    {
        return NULL;
    }
    
    if( entrySize == 0 || cluster < 2 )
    {
        return NULL;
    }
    
    data = calloc( 1, entrySize );
    
    if( data == NULL )
    {
        return NULL;
    }
    
    tempData        = data;
    s               = entrySize;
    bytesPerCluster = MBRGetSectorsPerCluster( o->mbr ) * MBRGetBytesPerSector( o->mbr );
    
    while( 1 )
    {
        offset = o->dataRegion + ( ( cluster - 2 ) * ( long )bytesPerCluster );
        
        fseek( o->fp, offset, SEEK_SET );
        
        if( s > bytesPerCluster )
        {
            r = fread( tempData, 1, bytesPerCluster, o->fp );
            
            if( r != bytesPerCluster )
            {
                return NULL;
            }
        }
        else
        {
            r = fread( tempData, 1, s, o->fp );
            
            if( r != s )
            {
                return NULL;
            }
        }
        
        tempData += r;
        s        -= r;
        
        if( FATGetClusterTypeForEntry( o->fat, cluster ) == FATClusterTypeLast )
        {
            break;
        }
        else
        {
            cluster = FATGetClusterForEntry( o->fat, cluster );
        }
    }
    
    if( size != NULL )
    {
        *( size ) = entrySize;
    }
    
    return data;
}

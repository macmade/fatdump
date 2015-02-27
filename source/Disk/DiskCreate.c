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

MutableDiskRef DiskCreate( const char * path )
{
    FILE          * fp;
    struct __Disk * o;
    MutableMBRRef   mbr;
    MutableFATRef   fat;
    MutableDirRef   dir;
    size_t          i;
    
    if( path == NULL )
    {
        return NULL;
    }
    
    fp   = fopen( path, "rb" );
    o    = calloc( sizeof( struct __Disk ), 1 );
    
    if( fp == NULL )
    {
        free( o );
        fprintf( stderr, "Error: cannot open file for reading (%s).\n", path );
        
        return NULL;
    }
    
    if( o == NULL )
    {
        fclose( fp );
        fprintf( stderr, "Error: out of memory.\n" );
        
        return NULL;
    }
    
    mbr = MBRCreate( fp );
    
    if( mbr == NULL )
    {
        free( o );
        fclose( fp );
        
        return NULL;
    }
    
    o->mbr = mbr;
    
    if( strncmp( MBRGetFileSystem( mbr ), "FAT12", 5 ) == 0 )
    {
        o->format = DiskFormatFAT12;
    }
    else if( strncmp( MBRGetFileSystem( mbr ), "FAT16", 5 ) == 0 )
    {
        o->format = DiskFormatFAT16;
    }
    else
    {
        o->format = DiskFormatUnknown;
    }
    
    if( MBRGetReservedSectors( mbr ) > 1 )
    {
        fseek
        (
            fp,
            ( long )( MBRGetBytesPerSector( mbr ) * MBRGetReservedSectors( mbr ) ),
            SEEK_CUR
        );
    }
    
    fat = FATCreate( fp, o );
    
    if( fat == NULL )
    {
        MBRDelete( mbr );
        free( o );
        fclose( fp );
        
        return NULL;
    }
    
    o->fat = fat;
    
    for( i = 1; i < MBRGetNumberOfFATs( mbr ); i++ )
    {
        fseek( fp, ( long )FATGetDataSize( fat ), SEEK_CUR );
    }
    
    dir = DirCreate( fp, o );
    
    if( dir == NULL )
    {
        MBRDelete( mbr );
        FATDelete( fat );
        
        free( o );
        fclose( fp );
        
        return NULL;
    }
    
    o->dir        = dir;
    o->dataRegion = ftell( fp );
    
    fseek( fp, 0, SEEK_SET );
    
    o->fp  = fp;
    
    return o;
}

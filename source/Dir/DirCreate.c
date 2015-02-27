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

#include "Dir.h"
#include "__private/Dir.h"

MutableDirRef DirCreate( FILE * fp, DiskRef disk )
{
    struct __Dir * o;
    uint8_t      * data;
    DirEntryRef  * entries;
    DirEntryRef    entry;
    size_t         s;
    size_t         c;
    size_t         i;
    MBRRef         mbr;
    
    mbr = DiskGetMBR( disk );
    
    if( fp == NULL || disk == NULL || mbr == NULL )
    {
        return NULL;
    }
    
    c = MBRGetMaxRootDirEntries( mbr );
    s = c * 32;
    
    if( s % MBRGetBytesPerSector( mbr ) != 0 )
    {
        fprintf( stderr, "Error: invalid root directory size (%lu)\n", s );
        
        return NULL;
    }
    
    o       = calloc( sizeof( struct __Dir ), 1 );
    data    = malloc( s );
    entries = calloc( sizeof( DirEntryRef ), c );
    
    if( o == NULL || data == NULL || entries == NULL )
    {
        free( o );
        free( data );
        free( entries );
        fprintf( stderr, "Error: out of memory.\n" );
        
        return NULL;
    }
    
    o->dataSize     = s;
    o->entryCount   = c;
    o->data         = data;
    o->entries      = entries;
    o->disk         = disk;
    
    s = fread( o->data, 1, o->dataSize, fp );
    
    if( s != o->dataSize )
    {
        free( o );
        free( data );
        free( entries );
        fprintf( stderr, "Error: invalid read of root directory - Read %lu bytes, expected %lu\n", s, o->dataSize );
        
        return NULL;
    }
    
    fseek( fp, -( ( long )s ), SEEK_CUR );
    
    for( i = 0; i < c; i++ )
    {
        entry = DirEntryCreate( fp, o );
        
        if( entry == NULL )
        {
            free( o );
            free( data );
            free( entries );
            
            return NULL;
        }
        
        o->entries[ i ] = entry;
    }
    
    return o;
}

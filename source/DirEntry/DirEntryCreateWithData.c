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

#include "DirEntry.h"
#include "__private/DirEntry.h"

MutableDirEntryRef DirEntryCreateWithData( uint8_t * data, DirRef dir, bool freeWhenDone )
{
    struct __DirEntry * o;
    char              * name;
    char              * filename;
    size_t              s;
    
    if( data == NULL || dir == NULL )
    {
        return NULL;
    }
    
    s        = 32;
    o        = calloc( sizeof( struct __DirEntry ), 1 );
    name     = calloc( 1, 12 );
    filename = calloc( 1, 13 );
    
    if( o == NULL || name == NULL || filename == NULL )
    {
        if( freeWhenDone )
        {
            free( data );
        }
        
        free( o );
        free( name );
        free( filename );
        fprintf( stderr, "Error: out of memory.\n" );
        
        return NULL;
    }
    
    o->freeData     = freeWhenDone;
    o->dataSize     = s;
    o->data         = data;
    o->name         = name;
    o->filename     = filename;
    o->dir          = dir;
    o->attributes   = ( int )( data[ 11 ] );
    
    if( o->attributes == DirEntryAttributeLFN )
    {
        return o;
    }
    
    memcpy( o->name, data, 11 );
    __DirEntryFilename( o->name, o->filename );
    o->fullPath = __DirEntryCreateFullPath( o->filename, dir );
    
    o->size = ( ( size_t )data[ 28 ] <<  0 )
            | ( ( size_t )data[ 29 ] <<  8 )
            | ( ( size_t )data[ 31 ] << 16 )
            | ( ( size_t )data[ 30 ] << 24 );
    
    o->creationTime         = __DirEntryTimeFromUInt16( data + 16, data + 14 );
    o->lastAccessTime       = __DirEntryTimeFromUInt16( data + 18, NULL );
    o->lastModificationTime = __DirEntryTimeFromUInt16( data + 24, data + 22 );
    
    o->cluster = ( uint16_t )( ( ( uint16_t )data[ 26 ] ) | ( ( uint16_t )data[ 27 ] << 8 ) );
    
    return o;
}

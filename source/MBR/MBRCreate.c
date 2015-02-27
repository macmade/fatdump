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

#include "MBR.h"
#include "__private/MBR.h"

MutableMBRRef MBRCreate( FILE * fp )
{
    struct __MBR     * o;
    struct __MBRData * data;
    size_t             s;
    
    if( fp == NULL )
    {
        return NULL;
    }
    
    o    = calloc( 1, sizeof( struct __MBR ) );
    data = calloc( 1, sizeof( struct __MBRData ) );
    
    if( o == NULL || data == NULL )
    {
        free( o );
        free( data );
        
        fprintf( stderr, "Error: out of memory." );
        
        return NULL;
    }
    
    s = fread( data, 1, sizeof( struct __MBRData ), fp );
    
    if( s != sizeof( struct __MBRData ) )
    {
        free( o );
        free( data );
        fprintf( stderr, "Error: invalid read of MBR - Read %lu bytes, expected %lu\n", s, sizeof( struct __MBRData ) );
        
        return NULL;
    }
    
    o->data = data;
    
    __MBRCreateStrings( o );
    
    return o;
}

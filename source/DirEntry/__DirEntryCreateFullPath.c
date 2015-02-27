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

char * __DirEntryCreateFullPath( const char * filename, DirRef dir )
{
    size_t       l1;
    size_t       l2;
    size_t       s;
    size_t       i;
    DirEntryRef  e;
    DirRef       d;
    const char * n;
    char       * p;
    
    if( filename == NULL || dir == NULL )
    {
        return NULL;
    }
    
    d = dir;
    s = strlen( filename ) + 2;
    
    while( ( e = DirGetParentEntry( dir ) ) )
    {
        s  += strlen( DirEntryGetFilename( e ) ) + 1;
        dir = DirEntryGetDir( e );
    }
    
    p = calloc( 1, s );
    
    if( p == NULL )
    {
        return NULL;
    }
    
    while( ( e = DirGetParentEntry( d ) ) )
    {
        n  = DirEntryGetFilename( e );
        l1 = strlen( n );
        l2 = strlen( p );
        
        for( i = l2 + 1; i > 0; i-- )
        {
            p[ l1 + i ] = p[ i - 1 ];
        }
        
        for( i = 0; i < l1; i++ )
        {
            p[ i + 1 ] = n[ i ];
        }
        
        p[ 0 ] = '/';
        
        d = DirEntryGetDir( e );
    }
    
    strcat( p, "/" );
    strcat( p, filename );
    
    return p;
}

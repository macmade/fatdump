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

#include "FAT.h"
#include "__private/FAT.h"

uint16_t FATGetClusterForEntry( FATRef o, size_t entry )
{
    uint16_t a;
    uint16_t b;
    uint16_t c;
    size_t   i;
    
    if( o == NULL )
    {
        return 0;
    }
    
    if( entry >= FATGetEntryCount( o ) )
    {
        return 0;
    }
    
    c = 0;
    
    if( DiskGetFormat( o->disk ) == DiskFormatFAT12 )
    {
        i = ( entry * 12 ) / 8;
        a = o->data[ i ];
        b = o->data[ i + 1 ];
        c = ( uint16_t )( b << 8 ) | a;
        
        if( entry % 2 )
        {
            c = c >> 4;
        }
        else
        {
            c = c & 0xFFF;
        }
    }
    else if( DiskGetFormat( o->disk ) == DiskFormatFAT16 )
    {
        i = ( entry * 16 ) / 8;
        a = o->data[ i ];
        b = o->data[ i + 1 ];
        c = ( uint16_t )( b << 8 ) | a;
    }
    
    return c;
}

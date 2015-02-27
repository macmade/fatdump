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

#include "Arguments.h"
#include "__private/Arguments.h"

MutableArgumentsRef ArgumentsCreate( int argc, const char ** argv )
{
    int                  i;
    struct __Arguments * o;
    
    o = calloc( sizeof( struct __Arguments ), 1 );
    
    if( o == NULL )
    {
        fprintf( stderr, "Error: out of memory.\n" );
        
        return NULL;
    }
    
    for( i = 1; i < argc; i++ )
    {
        if( strcmp( argv[ i ], "-h" ) == 0 )
        {
            o->showHelp = true;
        }
        else if( strcmp( argv[ i ], "--mbr" ) == 0 )
        {
            o->showMBR = true;
        }
        else if( strcmp( argv[ i ], "--mbr-raw" ) == 0 )
        {
            o->showRawMBR = true;
        }
        else if( strcmp( argv[ i ], "--fat" ) == 0 )
        {
            o->showFAT = true;
        }
        else if( strcmp( argv[ i ], "--fat-raw" ) == 0 )
        {
            o->showRawFAT = true;
        }
        else if( strcmp( argv[ i ], "--dir" ) == 0 )
        {
            o->showDir = true;
        }
        else if( strcmp( argv[ i ], "--dir-raw" ) == 0 )
        {
            o->showRawDir = true;
        }
        else if( strcmp( argv[ i ], "--hidden" ) == 0 )
        {
            o->showHidden = true;
        }
        else if( strcmp( argv[ i ], "--deleted" ) == 0 )
        {
            o->showDeleted = true;
        }
        else if( strcmp( argv[ i ], "--data" ) == 0 )
        {
            o->showData = true;
        }
        else if( strcmp( argv[ i ], "--extract" ) == 0 )
        {
            o->extract = true;
        }
        else
        {
            if( o->diskPath == NULL )
            {
                o->diskPath= argv[ i ];
            }
        }
    }
    
    __ArgumentsCurrent = o;
    
    return o;
}

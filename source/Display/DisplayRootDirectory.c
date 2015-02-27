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

#include "Display.h"
#include "Print.h"

void DisplayRootDirectory( DiskRef disk )
{
    DirRef      dir;
    DirEntryRef entry;
    size_t      entries;
    size_t      i;
    size_t      j;
    size_t      k;
    size_t      cols;
    size_t      n;
    int         attributes;
    time_t      t;
    char        s[ 20 ];
    struct tm * tm;
    
    if( disk == NULL )
    {
        return;
    }
    
    dir     = DiskGetRootDirectory( disk );
    entries = DirGetEntryCount( dir );
    cols    = PrintGetAvailableColumns();
    n       = ( cols > 50 ) ? ( cols + 3 ) / 53 : 0;
    
    PrintHeader( "Root directory:" );
    
    for( i = 0; i < entries; i++ )
    {
        for( j = 0; j < 13; j++ )
        {
            for( k = 0; k < n; k++ )
            {
                if( i + k >= entries )
                {
                    break;
                }
                
                entry       = DirGetEntry( dir, i + k );
                attributes  = DirEntryGetAttributes( entry );
                
                if( j == 0 )
                {
                    if( DirEntryIsLFN( entry ) )
                    {
                        printf( "%-4lu: %-44s", i + k + 1, "LFN" );
                    }
                    else if( DirEntryIsFree( entry ) )
                    {
                        printf( "%-4lu: %-44s", i + k + 1, "Free" );
                    }
                    else
                    {
                        printf( "%-4lu: %-44s", i + k + 1, DirEntryGetName( entry ) );
                    }
                }
                else if( DirEntryIsLFN( entry ) )
                {
                    printf( ".................................................." );
                }
                else if( DirEntryIsFree( entry ) )
                {
                    printf( "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" );
                }
                else if( j == 1 )
                {
                    printf( "    - Size:                    %-19lu", DirEntryGetSize( entry ) );
                }
                else if( j == 2 )
                {
                    printf( "    - Cluster:                 %-19lu", ( unsigned long )DirEntryGetCluster( entry ) );
                }
                else if( j == 3 )
                {
                    t  = DirEntryGetCreationTime( entry );
                    tm = localtime( &t );
                    
                    strftime( s, sizeof( s ), "%Y/%m/%d %H:%M:%S", tm );
                    printf( "    - Creation time:           %-19s", ( t == 0 ) ? "-" : s );
                }
                else if( j == 4 )
                {
                    t  = DirEntryGetLastAccessTime( entry );
                    tm = localtime( &t );
                    
                    strftime( s, sizeof( s ), "%Y/%m/%d %H:%M:%S", tm );
                    printf( "    - Last access time:        %-19s", ( t == 0 ) ? "-" : s );
                }
                else if( j == 5 )
                {
                    t  = DirEntryGetLastModificationTime( entry );
                    tm = localtime( &t );
                    
                    strftime( s, sizeof( s ), "%Y/%m/%d %H:%M:%S", tm );
                    printf( "    - Last modification time:  %-19s", ( t == 0 ) ? "-" : s );
                }
                else if( j == 6 )
                {
                    printf( "    - Read-only:               %-19s", DirEntryIsReadOnly( entry ) ? "yes" : "no" );
                }
                else if( j == 7 )
                {
                    printf( "    - Hidden:                  %-19s", DirEntryIsHidden( entry ) ? "yes" : "no" );
                }
                else if( j == 8 )
                {
                    printf( "    - System:                  %-19s", DirEntryIsSystem( entry ) ? "yes" : "no" );
                }
                else if( j == 9 )
                {
                    printf( "    - Volume ID:               %-19s", DirEntryIsVolumeID( entry ) ? "yes" : "no" );
                }
                else if( j == 10 )
                {
                    printf( "    - Directory:               %-19s", DirEntryIsDirectory( entry ) ? "yes" : "no" );
                }
                else if( j == 11 )
                {
                    printf( "    - Archive:                 %-19s", DirEntryIsArchive( entry ) ? "yes" : "no" );
                }
                else if( j == 12 )
                {
                    printf( "    - LFN:                     %-19s", DirEntryIsLFN( entry ) ? "yes" : "no" );
                }
                
                if( n > 1 && ( k + 1 ) % n )
                {
                    printf( " | " );
                    
                    if( i + k == entries - 1 )
                    {
                        printf( "\n" );
                    }
                }
                else if( k == n - 1 && j == 12 )
                {
                    printf( "\n" );
                    PrintLine();
                }
                else
                {
                    printf( "\n" );
                }
            }
        }
        
        i += n - 1;
    }
}

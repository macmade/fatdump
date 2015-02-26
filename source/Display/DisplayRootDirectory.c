/*******************************************************************************
 * XEOS - X86 Experimental Operating System
 * 
 * Copyright (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 * All rights reserved.
 * 
 * XEOS Software License - Version 1.0 - December 21, 2012
 * 
 * Permission is hereby granted, free of charge, to any person or organisation
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to deal in the Software, with or without
 * modification, without restriction, including without limitation the rights
 * to use, execute, display, copy, reproduce, transmit, publish, distribute,
 * modify, merge, prepare derivative works of the Software, and to permit
 * third-parties to whom the Software is furnished to do so, all subject to the
 * following conditions:
 * 
 *      1.  Redistributions of source code, in whole or in part, must retain the
 *          above copyright notice and this entire statement, including the
 *          above license grant, this restriction and the following disclaimer.
 * 
 *      2.  Redistributions in binary form must reproduce the above copyright
 *          notice and this entire statement, including the above license grant,
 *          this restriction and the following disclaimer in the documentation
 *          and/or other materials provided with the distribution, unless the
 *          Software is distributed by the copyright owner as a library.
 *          A "library" means a collection of software functions and/or data
 *          prepared so as to be conveniently linked with application programs
 *          (which use some of those functions and data) to form executables.
 * 
 *      3.  The Software, or any substancial portion of the Software shall not
 *          be combined, included, derived, or linked (statically or
 *          dynamically) with software or libraries licensed under the terms
 *          of any GNU software license, including, but not limited to, the GNU
 *          General Public License (GNU/GPL) or the GNU Lesser General Public
 *          License (GNU/LGPL).
 * 
 *      4.  All advertising materials mentioning features or use of this
 *          software must display an acknowledgement stating that the product
 *          includes software developed by the copyright owner.
 * 
 *      5.  Neither the name of the copyright owner nor the names of its
 *          contributors may be used to endorse or promote products derived from
 *          this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE AND NON-INFRINGEMENT ARE DISCLAIMED.
 * 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER, CONTRIBUTORS OR ANYONE DISTRIBUTING
 * THE SOFTWARE BE LIABLE FOR ANY CLAIM, DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN ACTION OF CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
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

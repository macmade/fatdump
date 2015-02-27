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
#include "IO.h"

void DisplayFilesDataOfDirectory( DirRef dir, bool showHidden, bool showDeleted )
{
    MutableDirRef subDir;
    DirEntryRef   entry;
    size_t        entries;
    size_t        i;
    size_t        s;
    void        * data;
    
    if( dir == NULL )
    {
        return;
    }
    
    entries = DirGetEntryCount( dir );
    
    for( i = 0; i < entries; i++ )
    {
        entry = DirGetEntry( dir, i );
        
        if
        (
               DirEntryIsLFN( entry )
            || DirEntryIsFree( entry )
            || DirEntryIsVolumeID( entry )
            || ( DirEntryIsHidden( entry )  && showHidden  == false )
            || ( DirEntryIsDeleted( entry ) && showDeleted == false )
        )
        {
            continue;
        }
        
        if( DirEntryIsDirectory( entry ) )
        {
            subDir = DirCreateFromDirEntry( DirGetDisk( dir ), entry );
            
            if( subDir == NULL )
            {
                continue;
            }
            else if
            (
                   strcmp( DirEntryGetFilename( entry ), "."  ) == 0
                || strcmp( DirEntryGetFilename( entry ), ".." ) == 0
            )
            {
                continue;
            }
            else
            {
                DisplayFilesDataOfDirectory( subDir, showHidden, showDeleted );
            }
            
            DirDelete( subDir );
        }
        else
        {
            data = DirEntryCreateFileData( entry, &s );
            
            if( data != NULL )
            {
                {
                    const char * unit;
                    double       size;
                    
                    if( s < 1024 )
                    {
                        PrintHeader( "Data for file: %s - %lu bytes", DirEntryGetFullPath( entry ), ( unsigned long )s );
                    }
                    else
                    {
                        size = IOHumanFileSize( s, &unit );
                        
                        PrintHeader( "Data for file: %s - %.02f %s", DirEntryGetFullPath( entry ), size, unit );
                    }
                    
                    PrintData( data, s );
                }
            }
            
            free( data );
        }
    }
}

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

#include "Disk.h"
#include "__private/Disk.h"

void * DiskCreateFileDataForEntry( DiskRef o, DirEntryRef entry, size_t * size )
{
    uint8_t * data;
    uint8_t * tempData;
    uint16_t  cluster;
    size_t    entrySize;
    size_t    s;
    size_t    r;
    size_t    bytesPerCluster;
    long      offset;
    
    if( size != NULL )
    {
        *( size ) = 0;
    }
    
    if( o == NULL )
    {
        return NULL;
    }
    
    if( o->fp == NULL || o->dataRegion <= 0 )
    {
        return NULL;
    }
    
    if
    (
            DirEntryIsFree( entry )
        || DirEntryIsLFN( entry )
        || DirEntryIsVolumeID( entry )
    )
    {
        return NULL;
    }
    
    cluster   = DirEntryGetCluster( entry );
    entrySize = DirEntryGetSize( entry );
    
    if
    (
           FATGetClusterTypeForEntry( o->fat, cluster ) != FATClusterTypeUsed
        && FATGetClusterTypeForEntry( o->fat, cluster ) != FATClusterTypeLast
    )
    {
        return NULL;
    }
    
    if( entrySize == 0 || cluster < 2 )
    {
        return NULL;
    }
    
    data = calloc( 1, entrySize );
    
    if( data == NULL )
    {
        return NULL;
    }
    
    tempData        = data;
    s               = entrySize;
    bytesPerCluster = MBRGetSectorsPerCluster( o->mbr ) * MBRGetBytesPerSector( o->mbr );
    
    while( 1 )
    {
        offset = o->dataRegion + ( ( cluster - 2 ) * ( long )bytesPerCluster );
        
        fseek( o->fp, offset, SEEK_SET );
        
        if( s > bytesPerCluster )
        {
            r = fread( tempData, 1, bytesPerCluster, o->fp );
            
            if( r != bytesPerCluster )
            {
                return NULL;
            }
        }
        else
        {
            r = fread( tempData, 1, s, o->fp );
            
            if( r != s )
            {
                return NULL;
            }
        }
        
        tempData += r;
        s        -= r;
        
        if( FATGetClusterTypeForEntry( o->fat, cluster ) == FATClusterTypeLast )
        {
            break;
        }
        else
        {
            cluster = FATGetClusterForEntry( o->fat, cluster );
        }
    }
    
    if( size != NULL )
    {
        *( size ) = entrySize;
    }
    
    return data;
}

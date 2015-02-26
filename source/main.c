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

#include "Arguments.h"
#include "Help.h"
#include "Print.h"
#include "Disk.h"
#include "MBR.h"
#include "FAT.h"
#include "Dir.h"

int main( int argc, char * argv[] )
{
    MutableArgumentsRef args;
    MutableDiskRef      disk;
    int                 ret;
    
    args = ArgumentsCreate( argc, ( const char ** )argv );
    disk = NULL;
    
    if( ArgumentsGetShowHelp( args ) )
    {
        HelpDisplay();
        
        goto success;
    }
    
    if( ArgumentsValidate( args ) == false )
    {
        goto failure;
    }
    
    disk = DiskCreate( ArgumentsGetDiskPath( args ) );
    
    if( disk == NULL )
    {
        goto failure;
    }
    
    if( ArgumentsGetShowMBR( args ) )
    {
        {
            MBRRef mbr;
            
            mbr = DiskGetMBR( disk );
            
            PrintHeader( "MBR:" );
            printf
            (
                "- OEM ID:                  %s\n"
                "- Bytes per sector:        %lu\n"
                "- Sectors per cluster:     %lu\n"
                "- Reserved sectors:        %lu\n"
                "- Number of FATs:          %lu\n"
                "- Max root dir entries:    %lu\n"
                "- Total sectors:           %lu\n"
                "- Media descriptor:        0x%X\n"
                "- Sectors per FAT:         %lu\n"
                "- Sectors per track:       %lu\n"
                "- Heads per cylinder:      %lu\n"
                "- Hidden sectors:          %lu\n"
                "- LBA sectors:             %lu\n"
                "- Drive number:            0x%X\n"
                "- Extended boot signature: 0x%X\n"
                "- Volume serial number:    0x%X\n"
                "- Volume label:            %s\n"
                "- File system:             %s\n"
                "- Bootable:                %s\n",
                MBRGetOEMID( mbr ),
                ( unsigned long )MBRGetBytesPerSector( mbr ),
                ( unsigned long )MBRGetSectorsPerCluster( mbr ),
                ( unsigned long )MBRGetReservedSectors( mbr ),
                ( unsigned long )MBRGetNumberOfFATs( mbr ),
                ( unsigned long )MBRGetMaxRootDirEntries( mbr ),
                ( unsigned long )MBRGetTotalSectors( mbr ),
                MBRGetMediaDescriptor( mbr ),
                ( unsigned long )MBRGetSectorsPerFAT( mbr ),
                ( unsigned long )MBRGetSectorsPerTrack( mbr ),
                ( unsigned long )MBRGetHeadsPerCylinder( mbr ),
                ( unsigned long )MBRGetHiddenSectors( mbr ),
                ( unsigned long )MBRGetLBASectors( mbr ),
                MBRGetDriveNumber( mbr ),
                MBRGetExtendedBootSignature( mbr ),
                MBRGetVolumeSerialNumber( mbr ),
                MBRGetVolumeLabel( mbr ),
                MBRGetFileSystem( mbr ),
                ( MBRIsBootable( mbr ) ) ? "yes" : "no"
            );
        }
    }
    
    if( ArgumentsGetShowRawMBR( args ) )
    {
        {
            MBRRef mbr;
            
            mbr = DiskGetMBR( disk );
            
            PrintHeader( "MBR raw data:" );
            PrintData( MBRGetData( mbr ), MBRGetDataSize( mbr ) );
        }
    }
    
    if( ArgumentsGetShowFAT( args ) )
    {
        {
            FATRef          fat;
            size_t          i;
            size_t          entries;
            size_t          cols;
            size_t          n;
            FATClusterType  type;
            const char    * s;
            
            fat     = DiskGetFAT( disk );
            entries = FATGetEntryCount( fat );
            cols    = PrintGetAvailableColumns();
            n       = ( cols > 20 ) ? ( cols + 3 ) / 19 : 0;
            
            PrintHeader( "FAT:" );
            
            for( i = 0; i < entries; i++ )
            {
                type = FATGetClusterTypeForEntry( fat, i );
                
                switch( type )
                {
                    case FATClusterTypeFree:        s = "Free  "; break;
                    case FATClusterTypeUsed:        s = "Used  "; break;
                    case FATClusterTypeReserved:    s = "N/A   "; break;
                    case FATClusterTypeBad:         s = "Bad   "; break;
                    case FATClusterTypeLast:        s = "Last  "; break;
                }
                
                if( type == FATClusterTypeUsed )
                {
                    printf
                    (
                        "%8lu: 0x%04lX",
                        ( unsigned long )i,
                        ( unsigned long )FATGetClusterForEntry( fat, i )
                    );
                }
                else
                {
                    printf
                    (
                        "%8lu: %s",
                        ( unsigned long )i,
                        s
                    );
                }
                
                if( n > 1 && ( i + 1 ) % n )
                {
                    printf( " | " );
                    
                    if( i == entries - 1 )
                    {
                        printf( "\n" );
                    }
                }
                else
                {
                    printf( "\n" );
                }
            }
        }
    }
    
    if( ArgumentsGetShowRawFAT( args ) )
    {
        {
            FATRef fat;
            
            fat = DiskGetFAT( disk );
            
            PrintHeader( "FAT raw data:" );
            PrintData( FATGetData( fat ), FATGetDataSize( fat ) );
        }
    }
    
    if( ArgumentsGetShowDir( args ) )
    {
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
                            printf( "    - Read-only:               %-19s", ( attributes & DirEntryAttributeReadOnly ) ? "yes" : "no" );
                        }
                        else if( j == 7 )
                        {
                            printf( "    - Hidden:                  %-19s", ( attributes & DirEntryAttributeHidden ) ? "yes" : "no" );
                        }
                        else if( j == 8 )
                        {
                            printf( "    - System:                  %-19s", ( attributes & DirEntryAttributeSystem ) ? "yes" : "no" );
                        }
                        else if( j == 9 )
                        {
                            printf( "    - Volume ID:               %-19s", ( attributes & DirEntryAttributeVolumeID ) ? "yes" : "no" );
                        }
                        else if( j == 10 )
                        {
                            printf( "    - Directory:               %-19s", ( attributes & DirEntryAttributeDirectory ) ? "yes" : "no" );
                        }
                        else if( j == 11 )
                        {
                            printf( "    - Archive:                 %-19s", ( attributes & DirEntryAttributeArchive ) ? "yes" : "no" );
                        }
                        else if( j == 12 )
                        {
                            printf( "    - LFN:                     %-19s", ( DirEntryIsLFN( entry ) ) ? "yes" : "no" );
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
    }
    
    if( ArgumentsGetShowRawDir( args ) )
    {
        {
            DirRef dir;
            
            dir = DiskGetRootDirectory( disk );
            
            PrintHeader( "Root directory raw data:" );
            PrintData( DirGetData( dir ), DirGetDataSize( dir ) );
        }
    }
    
    PrintLine();
    
    success:
    
        ret = EXIT_SUCCESS;
        
        goto cleanup;
        
    failure:
        
        ret = EXIT_FAILURE;
        
    cleanup:
    
    DiskDelete( disk );
    ArgumentsDelete( args );
    
    return ret;
}

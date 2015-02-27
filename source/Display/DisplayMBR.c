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

void DisplayMBR( DiskRef disk )
{
    MBRRef mbr;
    
    if( disk == NULL )
    {
        return;
    }
    
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

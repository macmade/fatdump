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

#ifndef FATDUMP___PRIVATE_MBR_H
#define FATDUMP___PRIVATE_MBR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "C99.h"
#include "../MBR.h"

#pragma pack( 1 )
struct __MBRData
{
    /* BIOS parameter block */
    uint8_t     jmp[ 3 ];
    uint8_t     oemID[ 8 ];
    uint16_t    bytesPerSector;
    uint8_t     sectorsPerCluster;
    uint16_t    reservedSectors;
    uint8_t     numberOfFATs;
    uint16_t    maxRootDirEntries;
    uint16_t    totalSectors;
    uint8_t     mediaDescriptor;
    uint16_t    sectorsPerFAT;
    uint16_t    sectorsPerTrack;
    uint16_t    headsPerCylinder;
    uint32_t    hiddenSectors;
    uint32_t    lbaSectors;
    
    /* Extended BIOS parameter block */
    uint8_t     driveNumber;
    uint8_t     reserved;
    uint8_t     extendedBootSignature;
    uint32_t    volumeSerialNumber;
    uint8_t     volumeLabel[ 11 ];
    uint8_t     fileSystem[ 8 ];
    uint8_t     bootCode[ 448 ] ;
    uint16_t    bootSignature;
};
#pragma options align=reset

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

struct __MBR
{
    struct __MBRData * data;
    char             * oemID;
    char             * volumeLabel;
    char             * fileSystem;
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

void __MBRCreateStrings( MutableMBRRef o );

#ifdef __cplusplus
}
#endif

#endif /* FATDUMP___PRIVATE_MBR_H */

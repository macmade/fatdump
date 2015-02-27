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

#ifndef FATDUMP_FAT_H
#define FATDUMP_FAT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef const struct __FAT * FATRef;
typedef       struct __FAT * MutableFATRef;

#include "C99.h"
#include "Disk.h"

typedef enum
{
    FATClusterTypeFree      = 0x00,
    FATClusterTypeUsed      = 0x01,
    FATClusterTypeLast      = 0x02,
    FATClusterTypeBad       = 0x03,
    FATClusterTypeReserved  = 0x04
}
FATClusterType;

MutableFATRef   FATCreate( FILE * fp, DiskRef disk );
void            FATDelete( MutableFATRef o );

const void    * FATGetData( FATRef o );
size_t          FATGetDataSize( FATRef o );

size_t          FATGetEntryCount( FATRef o );
uint16_t        FATGetClusterForEntry( FATRef o, size_t entry );
FATClusterType  FATGetClusterTypeForEntry( FATRef o, size_t entry );

#ifdef __cplusplus
}
#endif

#endif /* FATDUMP_FAT_H */

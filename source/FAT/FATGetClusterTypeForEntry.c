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

FATClusterType FATGetClusterTypeForEntry( FATRef o, size_t entry )
{
    uint16_t cluster;
    
    if( o == NULL )
    {
        return FATClusterTypeReserved;
    }
    
    if( entry >= FATGetEntryCount( o ) )
    {
        return FATClusterTypeReserved;
    }
    
    cluster = FATGetClusterForEntry( o, entry );
    
    if( DiskGetFormat( o->disk ) == DiskFormatFAT12 )
    {
        if( cluster == 0x000 )
        {
            return FATClusterTypeFree;
        }
        else if( cluster == 0x001 )
        {
            return FATClusterTypeReserved;
        }
        else if( cluster >= 0xFF0 && cluster <= 0xFF6 )
        {
            return FATClusterTypeReserved;
        }
        else if( cluster == 0xFF7 )
        {
            return FATClusterTypeBad;
        }
        else if( cluster >= 0xFF8 && cluster <= 0xFFF )
        {
            return FATClusterTypeLast;
        }
        
        return FATClusterTypeUsed;
    }
    else if( DiskGetFormat( o->disk ) == DiskFormatFAT16 )
    {
        if( cluster == 0x000 )
        {
            return FATClusterTypeFree;
        }
        else if( cluster == 0x001 )
        {
            return FATClusterTypeReserved;
        }
        else if( cluster >= 0xFFF0 && cluster <= 0xFFF6 )
        {
            return FATClusterTypeReserved;
        }
        else if( cluster == 0xFFF7 )
        {
            return FATClusterTypeBad;
        }
        else if( cluster >= 0xFFF8 )
        {
            return FATClusterTypeLast;
        }
        
        return FATClusterTypeUsed;
    }
    
    return FATClusterTypeReserved;
}

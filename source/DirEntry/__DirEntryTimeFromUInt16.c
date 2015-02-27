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

#include "DirEntry.h"
#include "__private/DirEntry.h"

time_t __DirEntryTimeFromUInt16( uint8_t * dateData, uint8_t * timeData )
{
    uint16_t  date;
    uint16_t  time;
    int       y;
    int       m;
    int       d;
    int       h;
    int       i;
    int       s;
    struct tm t;
    
    if( dateData == NULL )
    {
        return 0;
    }
    
    date = ( uint16_t )( ( ( uint16_t )dateData[ 1 ] << 8 ) | ( ( uint16_t )dateData[ 0 ] ) );
    time = 0;
    
    if( timeData != NULL )
    {
        time = ( uint16_t )( ( ( uint16_t )timeData[ 1 ] << 8 ) | ( ( uint16_t )timeData[ 0 ] ) );
    }
    
    if( date == 0 && time == 0 )
    {
        return 0;
    }
    
    y = date >> 9;
    m = ( date >> 5 ) & 0x0F;
    d = date & 0x1F;
    h = time >> 11;
    i = ( time >> 5 ) & 0x3F;
    s = time & 0x1F;
    
    memset( &t, 0, sizeof( struct tm ) );
    
    t.tm_year = y + 80;
    t.tm_mon  = m - 1;
    t.tm_mday = d;
    t.tm_hour = h;
    t.tm_min  = i;
    t.tm_sec  = s * 2;
    
    return mktime( &t );
}

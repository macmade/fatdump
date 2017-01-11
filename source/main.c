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

#include "Arguments.h"
#include "Help.h"
#include "Print.h"
#include "Disk.h"
#include "MBR.h"
#include "FAT.h"
#include "Dir.h"
#include "Display.h"
#include "Extract.h"

int main( int argc, const char * argv[] )
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
        DisplayMBR( disk );
    }
    
    if( ArgumentsGetShowRawMBR( args ) )
    {
        DisplayMBRRaw( disk );
    }
    
    if( ArgumentsGetShowFAT( args ) )
    {
        DisplayFAT( disk );
    }
    
    if( ArgumentsGetShowRawFAT( args ) )
    {
        DisplayFATRaw( disk );
    }
    
    if( ArgumentsGetShowDir( args ) )
    {
        DisplayRootDirectory( disk );
    }
    
    if( ArgumentsGetShowRawDir( args ) )
    {
        DisplayRootDirectoryRaw( disk );
    }
    
    DisplayFiles( disk, ArgumentsGetShowHidden( args ), ArgumentsGetShowDeleted( args ) );
    
    if( ArgumentsGetShowData( args ) )
    {
        DisplayFilesData( disk, ArgumentsGetShowHidden( args ), ArgumentsGetShowDeleted( args ) );
    }
    
    PrintLine();
    
    if( ArgumentsGetExtract( args ) )
    {
        ExtractFilesFromDisk( disk, ArgumentsGetShowHidden( args ), ArgumentsGetShowDeleted( args ) );
    }
    
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

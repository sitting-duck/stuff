// ADOBE SYSTEMS INCORPORATED
// Copyright  1993 - 2002 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this 
// file in accordance with the terms of the Adobe license agreement
// accompanying it.  If you have received this file from a source
// other than Adobe, then your use, modification, or distribution
// of it requires the prior written permission of Adobe.
//-------------------------------------------------------------------
//-------------------------------------------------------------------------------
//
//	File:
//		OutboundUIMac.cpp
//
//	Copyright 1990-1992, Thomas Knoll.
//
//	Description:
//		This file contains the user interface source
//		for the Export module Outbound, a module that
//		creates a file and stores raw pixel data in it.
//
//	Use:
//		This module shows how to export raw data to a file.
//		It uses a simple "FileUtilities" library that comes
//		with the SDK.  You use it via File>>Export>>Outbound.
//
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//	Includes
//-------------------------------------------------------------------------------

#include "PIDefines.h"
#include "Outbound.h"
#include "PIUFile.h"

//-------------------------------------------------------------------------------
//	Definitions -- Dialog items
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//
//	DoAbout
//
//	Displays the About box.
//
//	Inputs:
//		AboutRecordPtr about	Is actually a pointer to some platform
//								specific data for Windows only.
//		AboutID					#define with ID of String resource to use for text
//
//	Outputs:
//		Displays About box (Dialog).  Press Escape, Enter, or Return to
//		dismiss, or click the mouse.
//
//-------------------------------------------------------------------------------

/*****************************************************************************/

void DoAbout (AboutRecordPtr /*about*/)
{
	ShowAbout (AboutID);
}

/*****************************************************************************/

Boolean DoUI (GPtr globals)
{
    
    if (gQueryForParameters)
    {

        NSLog(@"Outbound DoUI start");

        NSSavePanel *panel = [NSSavePanel savePanel];
    
        [panel setNameFieldStringValue:@"Outbound.exp"];
    
        BOOL result = [panel runModal];
    
        if (result == NSFileHandlingPanelOKButton)
        {
            NSString * panelDirectory = [panel directory];
            NSLog(@"Outbound DoUI directory = %@", panelDirectory);
    
            gFileName = [panel filename];
            NSLog(@"Outbound DoUI filename = %@", gFileName);
    
            NSFileHandle *output = [NSFileHandle fileHandleForWritingAtPath:gFileName];

            if (output == nil)
            {
                BOOL madeIt = [[NSFileManager defaultManager] createFileAtPath:gFileName contents:nil attributes:nil];
                if (madeIt)
                    output = [NSFileHandle fileHandleForWritingAtPath:gFileName];
            }
            else
            {
                [output truncateFileAtOffset:0];
            }
    
            gFRefNum = output;
    
            if (output != nil)
                return TRUE;
        }
    }
    else
    {
    
        char fullPath[1024];
        fullPath[0] = 0;
        FSRef fsRef;
        Boolean changed = false;
        OSErr resolveErr = FSResolveAlias(NULL, gAliasHandle, &fsRef, &changed);
        if (resolveErr == noErr || resolveErr == fnfErr)
        {
            HFSUniStr255		targetName;
            HFSUniStr255		volumeName;
            CFStringRef			pathString;
            FSAliasInfoBitmap	whichInfo;
            FSAliasInfo			aliasInfo;
        
            resolveErr = FSCopyAliasInfo(gAliasHandle, &targetName, &volumeName, &pathString, &whichInfo, &aliasInfo);
            if (resolveErr == noErr)
            {
                if (CFStringGetCString(pathString, fullPath, 1024,kCFStringEncodingUTF8))
                {
                    gFileName = [[NSString alloc] initWithUTF8String:(const char *)fullPath];
                    NSFileHandle *output = [NSFileHandle fileHandleForWritingAtPath:gFileName];
                    
                    if (output == nil)
                    {
                        BOOL madeIt = [[NSFileManager defaultManager] createFileAtPath:gFileName contents:nil attributes:nil];
                        if (madeIt)
                            output = [NSFileHandle fileHandleForWritingAtPath:gFileName];
                    }
                    else
                    {
                        [output truncateFileAtOffset:0];
                    }
                    
                    gFRefNum = output;
                    
                    if (pathString != NULL)
                        CFRelease(pathString);
                
                    if (output != nil)
                        return TRUE;
                }
            }

        }
   
    }

    return FALSE;

}

/*****************************************************************************/

Boolean CreateExportFile (GPtr globals)
{
    return PIOpenFile(gFRefNum);
}

/*****************************************************************************/

Boolean CloseExportFile (GPtr globals)
{
	return PICloseFileAndMakeAlias(gFRefNum,
					               gFileName,
					               &gStuff->dirty,
					               &gAliasHandle);
}
//-------------------------------------------------------------------------------
// end OutboundUIMac.cpp
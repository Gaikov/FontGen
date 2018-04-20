// Copyright (c) 2005-2007, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Core.cpp
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#include "Core.h"
#include "sys.h"
#include "log.h"
#include "Package.h"
#include "Config.h"
#include "Name.h"

//---------------------------------------------------------
// nsCore::Init: 
//---------------------------------------------------------
bool nsCore::Init()
{
	Log_Init();
	LogPrintf( PRN_ALL, "*** Core Init ***\n" );

	timeBeginPeriod( 1 );
	LogPrintf( PRN_ALL, "OS Installed: %s\n", Sys_OSName() );
	LogPrintf( PRN_ALL, "CPU Speed: %.2f\n", Sys_CPUSpeed() );

	if ( !g_pack.Init() ) return false;
	if ( !nsConfig::Init() ) return false;

	LogPrintf( PRN_ALL, "\n" );
	return true;
}

//---------------------------------------------------------
// nsCore::Release: 
//---------------------------------------------------------
void nsCore::Release()
{
	LogPrintf( PRN_ALL, "*** Core Shutdown ***\n" );
	
	nsConfig::Release();
	g_pack.Release();

	nsNamePool::Free();

	LogPrintf( PRN_ALL, "\n" );
	Log_Release();
}

#ifndef _LOG_H_
#define _LOG_H_

#include "headers.h"

#define PRN_DEV		0
#define PRN_ALL		1

#ifdef _DEBUG
#define MAX_MSG	65535
#else
#define MAX_MSG	1024
#endif

struct ILogListener
{
	virtual void Print( const char *str ) = 0;
};

void __cdecl	LogPrintf( int prnLevel, const char *fmt, ... );
void			LogAddListener( ILogListener *forwarder );

void			Log_Init();
void			Log_Release();

#endif
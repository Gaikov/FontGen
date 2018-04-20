#include "headers.h"
#include "log.h"
#include "AppInfo.h"
#include "nsLib/StrTools.h"
#include "Config.h"

extern nsVar	*developer;
FILE			*g_log;

void Log_Init()
{
	if ( !(g_log = fopen( StrPrintf( "%s.log", App_GetInfo()->GetAppName() ), "w" )) )
		return;

	time_t	t = time( 0 );
	fprintf( g_log, "open log: %s", ctime( &t ) );
}

void Log_Release()
{
		if ( g_log )
		{
			time_t	t = time( 0 );
			fprintf( g_log, "close log: %s", ctime( &t ) );
			fclose( g_log );
			g_log = 0;
		}
}

//---------------------------------------------------------
// LogAddListener: 
//---------------------------------------------------------
#define LOG_MAX_FORWADERS	16
static ILogListener		*g_lf[LOG_MAX_FORWADERS];
static int				g_lfCount = 0;

void LogAddListener( ILogListener *forwarder )
{
	if ( g_lfCount < LOG_MAX_FORWADERS )
	{
		g_lf[g_lfCount] = forwarder;
		g_lfCount ++;
	}
}

//---------------------------------------------------------
// LogPrintListener: 
//---------------------------------------------------------
static void LogPrintListener( const char *msg )
{
	for ( int i = 0; i < g_lfCount; i++ )
		g_lf[i]->Print( msg );
}

//---------------------------------------------------------
// log_printf: 
//---------------------------------------------------------
void __cdecl LogPrintf( int prnLevel, const char *fmt, ... )
{
	if ( !strlen( fmt ) ) return;
	
	va_list	list;
	char	msg[MAX_MSG];

	if ( g_log )
	{
		va_start( list, fmt );
		vsprintf( msg, fmt, list );
		va_end( list );

		if ( prnLevel == PRN_DEV && developer && developer->Value() )
		{
			fprintf( g_log, "%s", msg );
			LogPrintListener( msg );
		}
		else if ( prnLevel == PRN_ALL )
		{
			fprintf( g_log, "%s", msg );
			LogPrintListener( msg );
		}
		
		fflush( g_log );
	}
}

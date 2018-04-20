#include "Config.h"
#include "Package.h"
#include "AppInfo.h"
#include "log.h"
#include "Args.h"
#include "sys.h"
#include "FileWriter.h"

nsConfig	*g_cfg = 0;

ICfgWriter	*nsConfig::m_writers[CFG_MAX_WRITERS];
int			nsConfig::m_writersCount = 0;

nsVar		*testvar = 0;
nsVar		*gc_savevars = 0;
nsVar		*developer = 0;

//---------------------------------------------------------
// writeconfig_f: 
//---------------------------------------------------------
static void writeconfig_f( int argc, const char *argv[] )
{
	if ( argc < 2 )
	{
		LogPrintf( PRN_ALL, "usage: writeconfig [filename]\n" );
		return;
	}

	g_cfg->SaveConfig( argv[1], true );
}

//---------------------------------------------------------
// quit_f:
//---------------------------------------------------------
static void quit_f( int argc, const char *argv[] )
{
	Sys_Exit();
}

//---------------------------------------------------------
// testcmd_f:
//---------------------------------------------------------
static void testcmd_f( int argc, const char *argv[] )
{
	LogPrintf( PRN_ALL, "===== test command =====\n" );
	for ( int i = 0; i < argc; i++ )
		LogPrintf( PRN_ALL, "arg: %s\n", argv[i] );
}

//---------------------------------------------------------
// fpu_state_f: 
//---------------------------------------------------------
static void fpu_state_f( int argc, const char *argv[] )
{
	Sys_FPUState();
}

//-----------------------------------------------------
//  nsConfig::nsConfig:  
//-----------------------------------------------------
nsConfig::nsConfig() :
	m_cfgFile( 0 ),
	m_defFile( 0 ),
	m_varList( 0 ),
	m_cfgText( 0 )
{
	IDataReader	*in = App_GetInfo()->GetCfgReader();
	if ( !in )
	{
		m_cfgFile = g_pack.LoadFile( StrPrintf( "%s.cfg", App_GetInfo()->GetAppName() ) );
		if ( m_cfgFile )
			m_cfgText = (char*)m_cfgFile->GetData();
	}
	else
	{
		in->Seek( 0, SEEK_END );
		long size = in->Tell();
		if ( size )
		{
			in->Seek( 0, SEEK_SET );
			m_cfgText = new char[size + 1];
			if ( !in->Read( m_cfgText, size ) )
			{
				delete m_cfgText;
				m_cfgText = 0;
			}
			else
				m_cfgText[size] = 0;
		}
		delete in;
	}

	m_defFile = g_pack.LoadFile( App_GetInfo()->GetDefCfgPath() );

	RegCmd( "testcmd", testcmd_f );
	RegCmd( "quit", quit_f );
	RegCmd( "writeconfig", writeconfig_f );
	RegCmd( "fpu_state", fpu_state_f );
	
	testvar = RegVar( "testvar", "0", GVF_SAVABLE );
	developer = RegVar( "developer", "0", GVF_SAVABLE );
	gc_savevars = RegVar( "gc_savevars", "0", GVF_SAVABLE );	
}

//---------------------------------------------------------
// nsConfig::~nsConfig: 
//---------------------------------------------------------
nsConfig::~nsConfig()
{
	nsVar	*delVar = m_varList;
	while ( m_varList )
	{
		delVar = m_varList;
		m_varList = m_varList->m_next;
		delete delVar;
	}

	cmdDesc_t	*cmd;
	m_cmdHash.FetchBegin();
	while ( cmd = m_cmdHash.FetchNext() )
	{
		my_free( cmd->name );
		delete cmd;
	}
	m_cmdHash.FetchEnd();
	m_cmdHash.DeleteAllKeys();

	if ( m_cfgFile )
		g_pack.ReleaseFile( m_cfgFile );
	else
		delete m_cfgText;
	
	g_pack.ReleaseFile( m_defFile );
}

//-----------------------------------------------------
//  nsConfig::Init:  
//-----------------------------------------------------
bool nsConfig::Init()
{
	if ( !g_cfg )
		g_cfg = new nsConfig;

	return true;
}

//-----------------------------------------------------
//  nsConfig::Release:  
//-----------------------------------------------------
void nsConfig::Release()
{
	if ( g_cfg )
	{
		delete g_cfg;
		g_cfg = 0;
	}
}

//---------------------------------------------------------
// nsConfig::AddWriter: 
//---------------------------------------------------------
void nsConfig::AddWriter( ICfgWriter *writer )
{
	if ( !writer 
		|| m_writersCount >= CFG_MAX_WRITERS ) return;

	m_writers[ m_writersCount ] = writer;
	m_writersCount ++;
}

//-----------------------------------------------------
//  nsConfig::SaveConfig:  
//-----------------------------------------------------
void nsConfig::SaveConfig( const char* fileName, bool forceFile )
{
	IDataWriter	*out = App_GetInfo()->GetCfgWriter();
	if ( forceFile || !out )
	{
		if ( !fileName )
			fileName = StrPrintf( "%s.cfg", App_GetInfo()->GetAppName() );
		LogPrintf( PRN_ALL, "...writing config '%s'\n", fileName );
		
		if ( out ) delete out;
		out = new nsFileWriter( fileName, "w" );
	}

	for ( int i = 0; i < m_writersCount; i++ )
		m_writers[i]->OnSaveConfig( out );

	for ( nsVar	*var = m_varList; var; var = var->m_next )
	{
		if ( (var->m_flags & GVF_SAVABLE || gc_savevars->Value())
			&& !(var->m_flags & GVF_INTERNAL) )
			out->Printf( "%s \"%s\"\n", var->m_name, var->String() );
	}

	delete out;
}

//---------------------------------------------------------
// nsConfig::CompleteLine:
//---------------------------------------------------------
const char* nsConfig::CompleteLine( const char* line )
{
	char	*outLine;
	int		len = strlen( line );
	assert( len < nsString::MAX_SIZE );

	//ищем переменную по имени
	nsVar	*var = (nsVar*)FindVar( line );
	if ( var ) return var->m_name;

	//ищем команду по имени
	cmdDesc_t	*cmd = m_cmdHash.GetData( line );
	if ( cmd ) return cmd->name;

	int	refCount = 0;
	//если ничего на нашли, выводим переменные в консоль по фильтру
	for ( var = m_varList; var; var = var->m_next )
	{
		if ( strncmp( var->m_name, line, len ) == 0 )
		{
			refCount ++;
			outLine = var->m_name;
			LogPrintf( PRN_ALL, " %s\n", outLine );
		}
	}
	
	//выводим команды по фильтру в консоль
	m_cmdHash.FetchBegin();
	while ( cmd = m_cmdHash.FetchNext() )
	{
		if ( strncmp( cmd->name, line, len ) == 0 )
		{
			refCount ++;
			outLine = cmd->name;
			LogPrintf( PRN_ALL, " %s\n", outLine );
		}
	}
	m_cmdHash.FetchEnd();

	return refCount == 1 ? outLine : 0;
}

//---------------------------------------------------------
// nsConfig::GetDefaultConfig:
//---------------------------------------------------------
const char* nsConfig::GetDefaultConfig()
{
	if ( m_defFile )
		return (char*)m_defFile->GetData();
	return 0;
}

//---------------------------------------------------------
// nsConfig::GetCurrentConfig:
//---------------------------------------------------------
const char*	nsConfig::GetCurrentConfig()
{
	if ( m_cfgFile )
		return (char*)m_cfgFile->GetData();
	return m_cfgText;
}

//-----------------------------------------------------
// nsConfig::GetConfigValue:
//-----------------------------------------------------
const char* nsConfig::GetConfigValue( const char* varName, const char* cfgFileText )
{
	if ( !cfgFileText || !varName || !strlen( varName ) ) return 0;

	static nsString	tmpLine;
	const char		*line;

	const char	*begin = strstr( cfgFileText, varName );
	if ( !begin ) return 0;

	const char	*end = strchr( begin, '\n' );
	if ( !end )
		line = begin;
	else
	{
		int len = end - begin;
		tmpLine.CopyFrom( begin, len );
		line = tmpLine.AsChar();
	}

	nsArgs	args( line );
	if ( args.ArgCount() < 2
		|| !StrEqual( args.Arg( 0 ), varName ) ) return 0;

	tmpLine = args.Arg( 1 );
	return tmpLine;
}

//-----------------------------------------------------
//  nsConfig::RegisterVariable:  
//-----------------------------------------------------
nsVar* nsConfig::RegVar( const char* varName, const char* defValue, uint flags )
{
	if ( !varName || !defValue || !strlen( varName ) ) return 0;
	nsVar	*var = (nsVar*)FindVar( varName );
	if ( var ) return var;

	var = new nsVar( varName, defValue, flags );
	var->m_next = m_varList;
	m_varList = var;
	
	if ( (flags & GVF_INTERNAL) ) return var;
	
	const char* str;
	str = GetConfigValue( varName, GetDefaultConfig() );
	if ( str )
	{
		if ( var->m_defValue )
			my_free( var->m_defValue );
		var->m_defValue = my_strdup( str );
		var->SetDefault();
	}
	
	str = GetConfigValue( varName, GetCurrentConfig() );
	if ( str ) var->SetString( str );

	
	return var;
}

//-----------------------------------------------------
//  nsConfig::FindVariable:  
//-----------------------------------------------------
nsVar* nsConfig::FindVar( const char* varName )
{
	for ( nsVar *var = m_varList; var; var = var->m_next )
	{
		if ( StrEqual( var->m_name, varName ) )
			return var;
	}
	return 0;
}

//-----------------------------------------------------
//  nsConfig::RegisterCommand:  
//-----------------------------------------------------
void nsConfig::RegCmd( const char* name, func_t cmd )
{
	if ( !name || !cmd || !strlen( name ) ) return;

	cmdDesc_t	*desc = m_cmdHash.GetData( name );
	if ( !desc )
	{
		desc = new cmdDesc_t;
		desc->name = my_strdup( name );
		desc->func = cmd;
		m_cmdHash.SetData( name, desc );
	}
}

//-----------------------------------------------------
//  nsConfig::ExecLine:  
//-----------------------------------------------------
bool nsConfig::ExecLine( const char* cmdLine )
{
	nsArgs		args( cmdLine );
	if ( !args.ArgCount() ) return false;
	
	nsVar*	var;
	cmdDesc_t*	cmd;

	if ( var = FindVar( args.Arg( 0 ) ) )
	{
		if ( args.ArgCount() < 2 )
		{
			LogPrintf( PRN_ALL, "%s = %s (default: %s)\n", var->m_name, var->String(), var->m_defValue );
		}
		else if ( (var->m_flags & GVF_INTERNAL) || (var->m_flags & GVF_READONLY) )
			LogPrintf( PRN_ALL, "WARNING: read only variable!\n" );
		else
			var->SetString( args.Arg( 1 ) );
		return true;
	}
	else if ( cmd = m_cmdHash.GetData( args.Arg( 0 )) )
	{
		cmd->func( args.ArgCount(), args.GetArgs() );
		return true;
	}

	LogPrintf( PRN_ALL, "WARNING: '%s' - invalid variable or command name!\n", cmdLine );
	return false;
}

//---------------------------------------------------------
// nsConfig::ExecFile:
//---------------------------------------------------------
bool nsConfig::ExecFile( const char* fileName )
{
	nsFile	*file = g_pack.LoadFile( fileName );
	if ( !file ) return false;

	int		len;
	char	*line = StrToken( (char*)file->GetData(), "\r\n", len );
	if ( !line ) return false;

	nsString	*lines = 0;
	int			lineCount = 0;

	do 
	{
		char	prevCh = line[len];
		line[len] = 0;
		AddToArray( &lines, lineCount, nsString( line ) );
		line[len] = prevCh;
	}
	while ( line = StrToken( 0, "\r\n", len ) );

	for ( int i = 0; i < lineCount; i++ )
		ExecLine( lines[i] );

	my_free( lines );
	return true;
}


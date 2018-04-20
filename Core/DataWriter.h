// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file DataWriter.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_DataWriter_H_
#define	_DataWriter_H_

#include "nsLib/comm_types.h"
#include "SmartPtr.h"

/*=======================================================================*\
	Интерфесы предназначены для реализации загрузчиков/хранителей даных
	игры, все ресурсы (файлы) должны загружаться через g_pack (nsPackage).
	А это нужно исключительно для сохранения загрузки пользовательских данных
	(конфиг, рекорды, сейвы, профайлы и т.д.)
\*=======================================================================*/

//---------------------------------------------------------
// IDataWriter: 
//---------------------------------------------------------
struct IDataWriter
{
	typedef nsSmartPtr<IDataWriter>	sp_t;
	
	virtual ~IDataWriter() {}
	virtual bool __cdecl	Printf( const char *fmt, ... ) = 0;
	virtual bool			Write( const void *data, uint size ) = 0;
	virtual bool			IsValid() = 0;
	
	// origin - стандартные константы:
	// SEEK_CUR - Current position of file pointer
	// SEEK_END - End of file
	// SEEK_SET - Beginning of file
	virtual bool			Seek( long offset, int origin ) = 0;
	
	virtual long			Tell() = 0;
};

//---------------------------------------------------------
// IDataReader: 
//---------------------------------------------------------
struct IDataReader
{
	typedef nsSmartPtr<IDataReader>	sp_t;

	virtual ~IDataReader() {}
	virtual bool			Read( void *data, uint size ) = 0;
	
	// origin - стандартные константы:
	// SEEK_CUR - Current position of file pointer
	// SEEK_END - End of file
	// SEEK_SET - Beginning of file
	virtual bool			Seek( long offset, int origin ) = 0;

	virtual long			Tell() = 0;
	
	virtual bool			IsValid() = 0;
};

#endif //_DataWriter_H_
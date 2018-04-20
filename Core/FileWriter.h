// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FileWriter.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FileWriter_H_
#define	_FileWriter_H_

#include "DataWriter.h"
#include "headers.h"

class nsFileWriter : public IDataWriter
{
public:
	nsFileWriter( const char *fileName, const char *mode );
	virtual ~nsFileWriter();

	virtual bool __cdecl	Printf( const char *fmt, ... );
	virtual bool			Write( const void *data, uint size );
	virtual bool			IsValid() { return m_fp != 0; }
	virtual bool			Seek( long offset, int origin );
	virtual long			Tell();

private:
	FILE					*m_fp;
};

#endif //_FileWriter_H_

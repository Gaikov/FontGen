// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file FileReader.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_FileReader_H_
#define	_FileReader_H_

#include "DataWriter.h"
#include "headers.h"

class nsFileReader : public IDataReader
{
public:
	nsFileReader( const char *fileName, const char *mode );
	virtual ~nsFileReader();

	virtual bool	Read( void *data, uint size );
	virtual bool	Seek( long offset, int origin );
	virtual long	Tell();
	virtual bool	IsValid();

private:
	FILE			*m_fp;
};

#endif //_FileReader_H_
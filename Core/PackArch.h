// Copyright (c) 2003-2007, Roman Gaikov. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file PackArch.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_PackArch_H_
#define	_PackArch_H_

#define	PACK_VERSION	0x0101

/*
	Cangelist:

version 1.01:
	- Добавлено шифрование .txt файлов

*/

#pragma pack( push, 1 )

typedef struct
{
	char	id[4];				//PACK
	unsigned short	version;	//0x0100
	unsigned int	dir_size;
}
packHeader_t;

typedef struct
{
	char			filename[128];
	unsigned int	offset;
	unsigned int	size;
}
packFileDesc_t;

#pragma pack( pop )

#endif //_PackArch_H_
#ifndef _OS_H_
#define _OS_H_

#include "headers.h"

void __cdecl	Sys_FatalError( const char *fmt, ... );
void __cdecl	Sys_Message( const char *fmt, ... );
void			Sys_Exit();
bool			Sys_IsExit();	//сигнализирует выход, нужно использовать для основного цикла приложения
double			Sys_CPUSpeed();
const char*		Sys_OSName();

void			Sys_SetMaxPriority();
void			Sys_SetNormalPriority();

bool			Sys_MakePath( const char* dirPath );

void			Sys_FPUState();

//---------------------------------------------------------
// nsCriticalSection: 
//---------------------------------------------------------
class nsCriticalSection
{
public:
	nsCriticalSection();
	virtual ~nsCriticalSection();

	void	Enter();
	void	Leave();

private:
	CRITICAL_SECTION	m_cs;
};

#endif
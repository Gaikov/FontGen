// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Polynom.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Polynom_H_
#define	_Polynom_H_

#include "headers.h"

class nsPolynom
{
public:
	void	CalcPoly( float pos1, float vel1, float pos2, float vel2, float time );
	float	CalcPos( float time );

private:
	float	a, b, c, d;
};

//---------------------------------------------------------
// nsPolynom::CalcPoly:
//---------------------------------------------------------
inline void	nsPolynom::CalcPoly( float pos1, float vel1, float pos2, float vel2, float time )
{
	d = pos1;
	c = vel1;
	a = 2.0f * ( ( vel2 + vel1 ) * time / 2.0f + pos1 - pos2 ) / powf( time, 3.0f );
	b = ( -vel2 - 2.0f * vel1 - 3.0f * ( pos1 - pos2 ) / time ) / time;
}

//---------------------------------------------------------
// nsPolynom::CalcPos:
//---------------------------------------------------------
inline float nsPolynom::CalcPos( float time )
{
	return a * powf( time, 3.0f ) + b * powf( time, 2.0f ) + c * time + d;
}


#endif	//_Polynom_H_
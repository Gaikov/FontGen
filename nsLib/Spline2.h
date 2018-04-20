// Copyright (c) 2003-2008, Gaikov Roman. All rights reserved.
//--------------------------------------------------------------------------------------------------
// file Spline2.h
// author Roman Gaikov
//--------------------------------------------------------------------------------------------------
#ifndef	_Spline2_H_
#define	_Spline2_H_

#include "Polynom.h"
#include "Vec2.h"

class nsSpline2
{
public:
	void		SetSegment( const nsVec2 &pos1, const nsVec2 &vel1, const nsVec2 &pos2, const nsVec2 &vel2, float time );
	void		CalcPos( float time, nsVec2 &pos );
	
private:
	nsPolynom	m_x;
	nsPolynom	m_y;
};

//---------------------------------------------------------
// nsSpline2::SetSegment:
//---------------------------------------------------------
inline void nsSpline2::SetSegment( const nsVec2 &pos1, const nsVec2 &vel1, const nsVec2 &pos2, const nsVec2 &vel2, float time )
{
	m_x.CalcPoly( pos1.x, vel1.x, pos2.x, vel2.x, time );
	m_y.CalcPoly( pos1.y, vel1.y, pos2.y, vel2.y, time );
}

//---------------------------------------------------------
// nsSpline2::CalcPos:
//---------------------------------------------------------
inline void nsSpline2::CalcPos( float time, nsVec2 &pos )
{
	pos.x = m_x.CalcPos( time );
	pos.y = m_y.CalcPos( time );
}


#endif	//_Spline2_H_
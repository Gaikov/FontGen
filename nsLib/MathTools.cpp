#include "MathTools.h"

float nsMath::PointOnLine( const nsVec2 &in, nsVec2 &out, const nsVec2 &p1, const nsVec2 &p2 )
{
	out = p2 - p1;
    float 	lineLen = out.Length();
    out /= lineLen;

    float	dist = out.Dot( in - p1 );
    out = p1 + out * dist;

    if ( dist < 0 )
    	return -dist;
    else if ( dist > lineLen )
    	return dist - lineLen;

    float	toP2 = lineLen - dist;
    return -(toP2 < dist ? toP2 : dist);
}

bool nsMath::PointInTriangle( const nsVec2 &pt, const nsVec2 &v1, const nsVec2 &v2, const nsVec2 &v3 )
{
	nsVec2	dir1 = v1 - pt;
    nsVec2	dir2 = v2 - pt;
    nsVec2	dir3 = v3 - pt;
    dir1.Norm();
    dir2.Norm();
    dir3.Norm();

    float	accAngle = (float)acos( Clamp11( dir1.Dot( dir2 ) ) );
    accAngle += (float)acos( Clamp11( dir2.Dot( dir3 ) ) );
    accAngle += (float)acos( Clamp11( dir3.Dot( dir1 ) ) );
    return accAngle >= M_PI * 2.0 * 0.99f;
}

bool nsMath::IsValidTriangle( int i1, int i2, int i3 )
{
	return i1 != i2 && i1 != i3 && i2 != i3;
}

#pragma once
#include "CubieRenderer.h"
class Cube
{
public:
	
	Cube() { m_voidCube = true; };
	Cube(int x, int y, int z);
	int X() const { return m_x; };
	int Y() const { return m_y; };
	int Z() const { return m_z; };
	bool isVoidCube() const { return m_voidCube; };
	

private:
	int m_x, m_y, m_z;
	bool m_voidCube;
	CubieRenderer temp;
	
};


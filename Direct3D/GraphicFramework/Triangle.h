#pragma once
#include "AMesh.h"
class Triangle :
	public AMesh
{
protected:
	void initVertexData();
	void initIndexData();
};


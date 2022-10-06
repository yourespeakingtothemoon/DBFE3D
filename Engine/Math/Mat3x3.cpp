#include "Mat3x3.h"

namespace dbf
{
	//100
	//010
	//001
	const Mat3x3 Mat3x3::identity{ {1,0,0},{0,1,0},{0,0,1} };
	//000
	//000
	//000
	const Mat3x3 Mat3x3::zero{ {0,0,0},{0,0,0},{0,0,0} };

}
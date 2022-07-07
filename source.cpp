#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>

#define MinDelta 0.00000000000001
//using namespace std;


int edgeTable[256] = {
	0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
	0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
	0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
	0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
	0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
	0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
	0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
	0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
	0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
	0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
	0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
	0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
	0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
	0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
	0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
	0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
	0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
	0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
	0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
	0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
	0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
	0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
	0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
	0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
	0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
	0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
	0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
	0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
	0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
	0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
	0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
	0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0 };

int triTable[256][16] =
{ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
{ 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1 },
{ 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1 },
{ 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
{ 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1 },
{ 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1 },
{ 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1 },
{ 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
{ 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1 },
{ 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1 },
{ 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
{ 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1 },
{ 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1 },
{ 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1 },
{ 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1 },
{ 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1 },
{ 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1 },
{ 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
{ 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1 },
{ 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
{ 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1 },
{ 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1 },
{ 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1 },
{ 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
{ 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1 },
{ 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1 },
{ 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
{ 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1 },
{ 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1 },
{ 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1 },
{ 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
{ 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1 },
{ 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1 },
{ 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
{ 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1 },
{ 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1 },
{ 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1 },
{ 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1 },
{ 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1 },
{ 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
{ 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1 },
{ 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
{ 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1 },
{ 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1 },
{ 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1 },
{ 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1 },
{ 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1 },
{ 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1 },
{ 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1 },
{ 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1 },
{ 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1 },
{ 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1 },
{ 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1 },
{ 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1 },
{ 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1 },
{ 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1 },
{ 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1 },
{ 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 },
{ 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 },
{ 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1 },
{ 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 },
{ 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 },
{ 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 },
{ 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 },
{ 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 },
{ 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 },
{ 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 },
{ 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 },
{ 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 },
{ 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 },
{ 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 },
{ 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 },
{ 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 },
{ 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 },
{ 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 },
{ 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 },
{ 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 },
{ 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 },
{ 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 },
{ 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 },
{ 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 },
{ 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 },
{ 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 },
{ 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 },
{ 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 },
{ 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 },
{ 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 },
{ 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 },
{ 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 },
{ 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 },
{ 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 },
{ 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 },
{ 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 },
{ 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 },
{ 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 },
{ 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 },
{ 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 },
{ 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 },
{ 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 },
{ 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 },
{ 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 },
{ 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 },
{ 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 },
{ 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 },
{ 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 },
{ 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 },
{ 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 },
{ 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 },
{ 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } };

//Resource From Paul Broke http://paulbourke.net/geometry/polygonise/

typedef struct point {
	double x;
	double y;
	double z;
}Point;

typedef struct re_check {
	int number[12]; //vertex가 vertex파일에 어느위치에있는지 표시
	Point point;
	int array[12];
}re_check;

void marchingcube(FILE* fpVertex, FILE* fpFace, Point* p, double* density, int* vertexNum, int b, int c, int h, int* faceNum);
Point pointcal(Point p1, Point p2, double val1, double val2);
void vertex_algo(FILE* fpVertex, int i, int* vertexNum, int r, int c, Point* vertlist, int* face_array);
void getEdgeLength(Point p1, Point p2, Point p3);
void convertVertex(Point p1, Point p2, Point p3);
double shortestEdge(double a, double b, double c);
double longestEdge(double a, double b, double c);

double** arr1, ** arr2;
re_check** arr3, ** arr4;
int row, col, height;
int counts = 0;
int cubeVertexCheck[12][8] = { 0 };
//교차점이 복셀의 꼭짓점인지 아닌지 판단하는 배열, 12가 edge 8이 해당 꼭짓점
double cl = 0;			// contour Level 입력 받기 전 선언
//step_size 선언 1~9 2이상의 값을 넣으려면 해당 resolution으로 줄인 sit파일이 필요함.(입력 받기 가능)
int step_size = 1;

//edge에 지나는지 안지나는지 확인하는 여러 정보를 가진 파일
FILE* fpEdgePassCheckFile1;
//edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexInSum
//edgePassNum	:	복셀에서 edge가 mesh와 만나는 개수
//edgePassSum	:	복셀에서 edge가 mesh와 만나는 위치를 0~11까지 하여 2진수로 만든 뒤 10진수로 표현
//b,c,h			:	복셀의 행, 열, 위치 정보 = row, col, height
//vertexInNum	:	복셀에서 mesh에 포함되는 vertex의 개수
//vertexInSum	:	복셀에서 mesh에 포함되는 vertex의 위치를 2진수로 만든 뒤 10진수로 표현
//voxelIndex	:	해당 복셀의 index(번호)

//위 파일에서 edgeList를 더한 파일(미사용)
FILE* fpEdgePassCheckFile2;
//Skinny Triangle 정보
FILE* fpErrorInfoFile;
//Skinny Triangle를 가지는 Face 정보
FILE* fpErrorFaceInfoFile;

point changeA, changeB, changeC;
double vertexXSum = 0;
double vertexYSum = 0;
double vertexZSum = 0;

double minLength = 0.1;					//최소 length 길이 선언(입력 받음)
double minSize = 0.01;					//최소 face 크기 선언(입력 받음)

//사이즈 관련 미사용
//double faceSizeSum = 0;				//face 전체 크기
//double faceAvgSize = 0;				//face 평균 크기

double faceLengthSum = 0;				//전체 face의 전체 edge 길이(한 edge가 여러 face를 겹친다면 중복처리되어 있음)
double faceAvgLength = 0;				//face edge의 평균 길이
int faceTotalNum = 0;					//face 전체 개수

double faceMaxLength = 0;				//face edge의 최대 길이
double faceMinLength = 1000;			//face edge의 최소 길이

//사이즈 관련 미사용
//double faceMaxSize = 0;				//face edge의 최대 크기
//double faceMinSize = 1000;			//face edge의 최소 크기

double length1, length2, length3;		//face edge들의 길이
int isErrorFace = 0;					//해당 face가 Skinny triangle인지 아닌지 확인하는 값
int errorLengthFaceNum = 0;				//최소 length보다 작은 length를 가지는 face의 개수
int valVoxelIndex = 0;					//Face를 가지는 유의미한 복셀의 index
int errorVoxelNum = 0;					//Skinny Triangle을 가지는 복셀의 개수
int isErrorVoxel = 0;					//Skinny Triangle을 가지는 복셀 확인

//사이즈 관련 미사용
//int errorSizeFaceNum = 0;				//최소 Size보다 작은 Size를 가지는 face의 개수
//int errorBothFaceNum = 0;				//최소 length 보다 짧고 최소 Size보다 작은 face의 개수

int main(void)
{
	//EMD 숫자 입력, 숫자를 입력하면 해당 숫자에 맞는 파일이 생성된다.
	//char S[40] = "1003";				//디버그용
	char S[40] = "";					//emd 숫자
	char S1[40] = "emd_";				//emd_	
	char stepName[40] = "step_";		//stepName = "step_"
	char stepSize[40] = "";				//stepsize step숫자
	char stepOFF[40] = "";				//step적용 OFF 파일 이름
	char stepSit[40] = "";				//step적용 sit 파일 이름
	char stepVertex[40] = "";			//step적용 vertex 파일 이름
	char stepFace[40] = "";				//step적용 face 파일 이름
	char stepCenter[40] = "";			//step적용 center 파일 이름
	char stepEdgePass1[40] = "";		//step적용 edegPassCheckFile1
	char stepEdgePass2[40] = "";		//step적용 edegPassCheckFile2
	char stepErrorInfo[40] = "";		//step적용 error 내용 파일 이름
	char stepErrorFaceInfo[40] = "";	//step적용 errro Face 파일 이름
	char Center[40] = "Center_";		//Center = "Center_"

	//EMD 숫자 입력받기
	printf("현재 가지고 있는 EMD : 0204 0840 1003 1059 1303 1709 1815 3947 4124 4372 5778 5805 6493 6552 8743 9102 10676\n");
	printf("EMD 숫자 입력\n");
	scanf("%s", S);

	//contour level 입력 받기
	printf("EMD 0204	0.09\nEMD 0840	0.0128\nEMD 1003	82.8\nEMD 1059	0.144\nEMD 1303	74.3\nEMD 1709	0.03\nEMD 1815	3.5\nEMD 3947	0.075\nEMD 4124	0.56\nEMD 4372	0.3\nEMD 5778	7\nEMD 5805	35.0\nEMD 6493	2.7\nEMD 6552	0.03\nEMD 8743	0.045\nEMD 9102	0.0135\nEMD 10676	0.0601\n");
	printf("EMD_%s Contour Level 입력받기\n", S);
	scanf("%lf", &cl);

	printf("제한 되는 길이 입력\n");
	scanf("%lf", &minLength);

	//사이즈 관련 미사용
	//printf("제한 되는 넓이 입력\n");
	//scanf("%lf", &minSize);

	//step size 입력받기
	//printf("step size 입력:");
	//scanf("%d", &step_size);

	//emd_****, nstep_ 만들기
	strcat(S1, S);						//S1 = "emd_****"
	sprintf(stepSize, "%d", step_size); //stepSize = "n"
	strcat(stepSize, stepName);			//stepSize = "nstep_"
	strcat(stepSit, stepSize);			//stepSit = "nstep_"
	strcpy(stepOFF, stepSize);			//stepOFF = "nstep_"
	strcpy(stepVertex, stepSize);		//stepVertex = "nstep_"
	strcpy(stepFace, stepSize);			//stepFace = "nstep_"	
	strcpy(stepCenter, stepSize);		//stepCenter = "nstep_"
	strcpy(stepEdgePass1, stepSize);	//stepEdgePass1 = "nstep_"
	strcpy(stepEdgePass2, stepSize);	//stepEdgePass2 = "nstep_"
	strcpy(stepErrorInfo, stepSize);	//stepErrorInfo = "nstep_"
	strcpy(stepErrorFaceInfo, stepSize);//stepErrorFaceInfo = "nstep_"
	strcpy(stepOFF, stepSize);			//stepOFF = "nstep_"
				
	//밀도값 저장된 파일
	strcat(stepSit, S1);								//stepSit = "nstep_emd_****"
	strcat(stepSit, ".sit");							// stepSit = "nstep_emd_****.sit"
	FILE* fpDensity = fopen(stepSit, "r");				//stepSit = "nstep_emd_****.sit" , step 변화 없는 건 1step으로 해야함
	
	//vertex, face 적기
	strcat(stepVertex, S1);								//stepVertex = "nstep_emd_****"
	strcat(stepVertex, "_vertex.txt");					//stepVertex = "nstep_emd_****_vertex.txt"
	strcat(stepFace, S1);								//stepFace = "nstep_emd_****"
	strcat(stepFace, "_face.txt");						//stepVertex = "nstep_emd_****_face.txt"
	FILE* fpVertex = fopen(stepVertex, "w");			//step적용 vertex정보 파일 : nstep_emd_****_vertex.txt
	FILE* fpFace = fopen(stepFace, "w");				//step적용 face정보 파일 : nstep_emd_****_face.txt

	//EdgePass, ErrorInfo 파일 만들기
	strcat(stepEdgePass1, S1);							//stepEdgePass1 = "nstep_emd_****"
	strcat(stepEdgePass2, S1);							//stepEdgePass2 = "nstep_emd_****"
	strcat(stepErrorInfo, S1);							//stepErrorInfo = "nstep_emd_****"
	strcat(stepErrorFaceInfo, S1);						//stepErrorFaceInfo = "nstep_emd_****"
	strcat(stepEdgePass1, "_EdgePassCheck1.txt");		//stepEdgePass1 = nstep_emd_****_EdgePassCheck1.txt
	strcat(stepEdgePass2, "_EdgePassCheck2.txt");		//stepEdgePass2 = nstep_emd_****_EdgePassCheck2.txt
	strcat(stepErrorInfo, "_ErrorInfo.txt");			//stepErrorInfo = nstep_emd_****_ErrorInfo.txt
	strcat(stepErrorFaceInfo, "_ErrorFaceInfo.txt");	//stepErrorInfo = nstep_emd_****_ErrorFaceInfo.txt
	fpEdgePassCheckFile1 = fopen(stepEdgePass1, "w");	//edge에 지나는지 안지나는지 확인하는 파일
	fpEdgePassCheckFile2 = fopen(stepEdgePass2, "w");	//edge에 지나는지 안지나는지 확인하는 두번째 파일
	fpErrorInfoFile = fopen(stepErrorInfo, "w");		//Error 관련 정보
	fpErrorFaceInfoFile = fopen(stepErrorFaceInfo, "w");//Error Face 세부 정보

	//EdegPassCheckFile1,2 변수이름 넣기 - FindVoxelCase에서 다시 제거하는 번거로움을 위해 생략
	//fprintf(fpEdgePassCheckFile1, "edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexInSum\n");
	//fprintf(fpEdgePassCheckFile2, "edgePassBy2, edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexInSum\n");

	//전체 중간값 파일 만들기
	strcat(Center, S);									//Center 파일 : Center****
	strcat(stepCenter, Center);							//stepCenter 파일 : nstep_Center****
	strcat(stepCenter, ".txt");							//stepCenter 파일 : nstep_Center****.txt

	//기존 OFF파일 만들기
	strcat(stepOFF, S1);								//stepOFF = "nstep_emd_****"
	strcat(stepOFF, ".OFF");							//stepOFF = "nstep_emd_****.OFF"
	FILE* fpOFF = fopen(stepOFF, "w");					//stepOFF 파일 : nstep_emd_****.OFF
	
	//OFF파일에서 Face 옆에 VoxelIndex 및 Skinny Triangle 유무 포함
	char stepOFF2[40] = "V_";							//새로운 step적용 OFF 파일 이름(voxelNum추가)
	strcat(stepOFF2, stepOFF);							//새로운 step적용 OFF 파일 : V_nstep_emd_****.OFF
	FILE* fpOFF2 = fopen(stepOFF2, "w");				//새로운 stepOFF 파일 : V_nstep_emd_****.OFF

	//이름 출력 디버깅
	printf("%s\n", stepOFF);							//stepOFF = "nstep_emd_****.OFF"
	printf("%s\n", stepOFF2);							//stepOFF = "V_nstep_emd_****.OFF"

	//밀도값 파일(sit)이 올바르지 않음
	if (fpDensity == NULL)
	{
		printf("open() error!");
		exit(1);
	}

	double data[7];
	//행, 열, 높이 입력 받기
	for (int i = 0; i < 7; i++)
	{
		fscanf(fpDensity, "%lf", &data[i]);
		if (i == 4)
			row = (int)data[i];
		else if (i == 5)
			col = (int)data[i];
		else if (i == 6)
			height = (int)data[i];
	}

	//double** arr1,**arr2;
	//double 값을 가지는 이차원 배열 2개를 row 크기만큼 동적할당
	arr1 = (double**)malloc(sizeof(double*) * row);
	arr2 = (double**)malloc(sizeof(double*) * row);

	arr3 = (re_check**)malloc(sizeof(re_check*) * row);
	arr4 = (re_check**)malloc(sizeof(re_check*) * row);


	for (int i = 0; i < row; i++)
	{
		arr1[i] = (double*)malloc(sizeof(double) * col);
		arr2[i] = (double*)malloc(sizeof(double) * col);
	}

	for (int i = 0; i < row; i++)
	{
		arr3[i] = (re_check*)malloc(sizeof(re_check) * col);
		arr4[i] = (re_check*)malloc(sizeof(re_check) * col);
	}


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fscanf(fpDensity, "%lf", &arr1[i][j]);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fscanf(fpDensity, "%lf", &arr2[i][j]);
	}
	//2차원 배열 읽기 (전체가 아니라 처음에 앞면, 뒤면 1번 읽기)

	int h = 0; //z좌표
	int vertexNum = 0;
	int faceNum = 0;
	Point p[8];
	double density[8];

	while (h != (height - 1)) //0~ height - 2 까지 총 (height -1) 개 arr2로 2번 읽으니
	{
		if (counts == 1)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
					fscanf(fpDensity, "%lf", &arr2[i][j]);
			}
		} // 처음에 2차원 배열을 읽을때는 2개만 읽지만 다음부터는 하나만 읽는다. 그전에 파일에서 읽은 2차원배열 하나를 재 사용하기 때문이다.

		int flag = 0; // 복셀의 밀도값이 총 8개 있는데(총 8개의 꼭짓점이 있기 때문) contour_level 값이 밀도값 사이에 있으면 flag=1로 변경 후 마칭큐브 적용

					  //마칭 큐브 적용하기전 contour_level이 복셀(정사면체 하나)의 각 vertex의 밀도값 사이에 한번이라도 존재한다면 flag=1로 변경 후 마칭큐브 적용  
		for (int b = 0; b < row - 1; b++)
		{
			for (int c = 0; c < col - 1; c++)
			{
				if ((arr2[b + 1][c] <= cl && arr2[b + 1][c + 1] >= cl) || (arr2[b + 1][c + 1] <= cl && arr2[b + 1][c] >= cl)) //0&1 - edge : 0
				{
					flag = 1;
				}
				else if ((arr1[b + 1][c + 1] <= cl && arr2[b + 1][c + 1] >= cl) || (arr2[b + 1][c + 1] <= cl && arr1[b + 1][c + 1] >= cl))//2&1 - edge : 1
				{
					flag = 1;
				}
				else if ((arr1[b + 1][c] <= cl && arr1[b + 1][c + 1] >= cl) || (arr1[b + 1][c + 1] <= cl && arr1[b + 1][c] >= cl)) //3&2 - edge : 2
				{
					flag = 1;
				}
				else if ((arr1[b + 1][c] <= cl && arr2[b + 1][c] >= cl) || (arr2[b + 1][c] <= cl && arr1[b + 1][c] >= cl))//3&0 - edge : 3
				{
					flag = 1;
				}
				else if ((arr2[b][c] <= cl && arr2[b][c + 1] >= cl) || (arr2[b][c + 1] <= cl && arr2[b][c] >= cl)) //4&5 - edge : 4
				{
					flag = 1;
				}
				else if ((arr1[b][c + 1] <= cl && arr2[b][c + 1] >= cl) || (arr2[b][c + 1] <= cl && arr1[b][c + 1] >= cl)) //6&5 - edge : 5
				{
					flag = 1;
				}
				else if ((arr1[b][c] <= cl && arr1[b][c + 1] >= cl) || (arr1[b][c + 1] <= cl && arr1[b][c] >= cl)) //7&6 - edge : 6
				{
					flag = 1;
				}
				else if ((arr1[b][c] <= cl && arr2[b][c] >= cl) || (arr2[b][c] <= cl) && arr1[b][c] >= cl) //7&4 - edge : 7
				{
					flag = 1;
				}
				else if ((arr2[b][c] <= cl && arr2[b + 1][c] >= cl) || (arr2[b + 1][c] <= cl && arr2[b][c] >= cl)) //4&0 - edge : 8
				{
					flag = 1;
				}
				else if ((arr2[b][c + 1] <= cl && arr2[b + 1][c + 1] >= cl) || (arr2[b + 1][c + 1] <= cl && arr2[b][c + 1] >= cl)) //5&1 - edge : 9
				{
					flag = 1;
				}
				else if ((arr1[b][c + 1] <= cl && arr1[b + 1][c + 1] >= cl) || (arr1[b + 1][c + 1] <= cl && arr1[b][c + 1] >= cl)) //6&2 - edge : 10
				{
					flag = 1;
				}
				else if ((arr1[b][c] <= cl && arr1[b + 1][c] >= cl) || (arr1[b + 1][c] <= cl && arr1[b][c] >= cl)) //7&3 - edge : 11
				{
					flag = 1;
				}

				if (flag == 1) //flag가 1인경우 마칭큐브 적용
				{
					//vertex 위치 좌표를 인덱스로 생각 (예로 0,0,2에있는 vertex는 (0,0,2)가된다. p는 구조체 Point변수)
					//그림에서 밑으로가면 x값 증가(b) 오른쪽으로 가면 y값 증가(c) 뒷면이 h 값 증가로 본다.
					//왜냐하면 b값을 row값을 보고 c를 col값으로 봐서 행렬로 계산한듯
					//arr1
					p[7].x = b;			p[7].y = c;			p[7].z = h;
					p[3].x = (b + 1);	p[3].y = c;			p[3].z = h;
					p[6].x = b;			p[6].y = (c + 1);	p[6].z = h;
					p[2].x = (b + 1);	p[2].y = (c + 1);	p[2].z = h;
					//arr2
					p[4].x = b;			p[4].y = c;			p[4].z = (h + 1);
					p[0].x = (b + 1);	p[0].y = c;			p[0].z = (h + 1);
					p[5].x = b;			p[5].y = (c + 1);	p[5].z = (h + 1);
					p[1].x = (b + 1);	p[1].y = (c + 1);	p[1].z = (h + 1);
					//한 복셀에서 각각의 vertex의 좌표값 저장

					density[0] = arr2[b + 1][c];
					density[1] = arr2[b + 1][c + 1];
					density[2] = arr1[b + 1][c + 1];
					density[3] = arr1[b + 1][c];
					density[4] = arr2[b][c];
					density[5] = arr2[b][c + 1];
					density[6] = arr1[b][c + 1];
					density[7] = arr1[b][c]; //vertex에 해당하는 밀도값 저장		

					marchingcube(fpVertex, fpFace, p, density, &vertexNum, b, c, h, &faceNum); //marching cube 적용 
					//fpVertex,fpFace : 파일 포인터  , p : 복셀의 꼭짓점들(8개) 위치정보 저장 ,density : 복셀의 각 꼭짓점들 밀도값 저장, vertexNum, faceNum : 파일에 저장될 vertex수(vertexNum)와 face수(faceNum) 저장용도 
					if (isErrorVoxel == 1)
						errorVoxelNum++;
					valVoxelIndex++;
				}
				//printf("b = %d c = %d , h = %d\n", b, c, h);
				//flage가 1이아니면 다른 복셀을 다시 검사하러 올라간다
				flag = 0;
			}
		}
		//arr1, arr2는 면단위, arr1이 arr2의 앞 면
		//arr3, aar4는 복셀단위, arr3이 arr4의 앞 복셀
		double** temp; // 두개의 이차원배열을 모두 비교한 뒤 포인터를 바꾸어서 첫번째 이차원배열을 가리키던 포인터는 두번째를 가리키고 두번째포인터는 새롭게 다시 파일에서 읽어온다.
		temp = arr1;
		arr1 = arr2;
		arr2 = temp;
		h++;
		counts = 1;

		re_check** temp2;
		temp2 = arr3;

		arr3 = arr4;
		arr4 = temp2;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				for (int k = 0; k < 12; k++)
					arr4[i][j].array[k] = 0;
	}
	
	//입력 파일들 각 숫자 적고 닫기
	fprintf(fpVertex, "%d", vertexNum);
	fprintf(fpFace, "%d", faceNum);
	fclose(fpVertex);
	fclose(fpFace);
	
	//OFF파일 적기
	fprintf(fpOFF, "OFF\n\n");
	fprintf(fpOFF, "%d %d 0\n", vertexNum, faceNum);

	//fprintf(fpOFF2, "OFF\n\n"); //다른 처리파일에서 OFF 또 생략해줘야하기 때문에 제거
	//face를 가지는 유의미한 복셀의 개수 또한 추가(valVoxelIndex)
	fprintf(fpOFF2, "%d %d 0 %d\n", vertexNum, faceNum, valVoxelIndex);

	//OFF파일을 만들기 위해 다시 파일 읽기
	FILE* fpVertexOpen = fopen(stepVertex, "r");		//vertex정보 파일 읽기
	FILE* fpFaceOpen = fopen(stepFace, "r");			//face정보 파일 읽기

	double Vx = 0, Vy = 0, Vz = 0;
	for (int i = 0; i < vertexNum; i++)
	{
		fscanf(fpVertexOpen, "%lf %lf %lf", &Vx, &Vy, &Vz);
		fprintf(fpOFF, "%lf %lf %lf\n", Vx, Vy, Vz);
		fprintf(fpOFF2, "%lf %lf %lf\n", Vx, Vy, Vz);
	}

	int FN, Fx, Fy, Fz, Fvn, Fief;
	//3 array1  array2  array3  valVoxelIndex  isErrorFace
	for (int i = 0; i < faceNum; i++)
	{
		fscanf(fpFaceOpen, "%d %d %d %d %d %d", &FN, &Fx, &Fy, &Fz, &Fvn, &Fief);
		fprintf(fpOFF, "%d %d %d %d\n", FN, Fx, Fy, Fz);
		fprintf(fpOFF2, "%d %d %d %d %d %d\n", FN, Fx, Fy, Fz, Fvn, Fief);
		
	}

	fclose(fpDensity);
	fclose(fpVertexOpen);
	fclose(fpFaceOpen);
	fclose(fpEdgePassCheckFile1);
	fclose(fpEdgePassCheckFile2);
	fclose(fpOFF);
	fclose(fpOFF2);

	//전체 좌표 무게중심 구하기
	/*
	FILE* fpCenter = fopen(stepCenter, "w");
	fprintf(fpCenter, S1);
	fprintf(fpCenter, "\nvertex 개수는 %d\n", vertexNum);
	fprintf(fpCenter, "x,y,z 좌표 합계는 %lf, %lf, %lf\n", vertexXSum, vertexYSum, vertexZSum);

	vertexXSum /= vertexNum;
	vertexYSum /= vertexNum;
	vertexZSum /= vertexNum;

	fprintf(fpCenter, "x,y,z 무게중심 좌표는 %lf, %lf, %lf", vertexXSum, vertexYSum, vertexZSum);
	fclose(fpCenter);
	*/

	faceAvgLength = faceLengthSum / faceTotalNum * 3;
	//사이즈 관련 미사용
	//faceAvgSize = faceSizeSum / faceTotalNum;
	
	printf("\n복셀 전체의 크기는 %d이다.\n", row* col* height);
	printf("Face를 가지는 유의미한 복셀의 총 개수는 %d\n", valVoxelIndex);
	printf("face의 edge의 총 길이는 %lf이고 평균은 %lf이다.\n", faceLengthSum, faceAvgLength);
	printf("총 face의 개수는 %d개 이다.\n\n", faceTotalNum);
	printf("Edge가 %lf보다 짧은 Skinny triangle의 개수는 %d\n", minLength, errorLengthFaceNum);
	printf("Skinny Triangle/faceNumd은 %lf이다\n", double(errorLengthFaceNum) / faceTotalNum);
	printf("Skinny Triangle을 가지는 복셀의 총 개수는 %d\n", errorVoxelNum);
	printf("Skinny Triangle 복셀 / 유의미한 복셀는 %lf\n\n", (double)errorVoxelNum / valVoxelIndex);
	printf("가장 짧은 edge는 %lf, 가장 긴 edge는 %lf\n", faceMinLength, faceMaxLength);

	//사이즈 관련 미사용
	//printf("face의 총 넓이는 %lf이고 평균은 %lf이다.\n", faceSizeSum, faceAvgSize);
	//printf("Face 넓이가 %lf보다 작기만 해서 문제가 되는 Face의 개수는 %d\n", minSize, errorSizeFaceNum);
	//printf("Face Edge가 %lf보다 짧고 크기가 %lf보다 작은 Face의 개수는 %d\n", minLength, minSize, errorBothFaceNum);
	//printf("총 Skinny Triangledml 개수는 %d이고 Skinny Triangle/faceNumd은 %lf이다\n", errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum, double(errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum) / faceTotalNum);
	//printf("가장 작은 Face의 크기는 %.20lf, 가장 큰 크기는 %lf\n", faceMinSize, faceMaxSize);
	//최소 크기의 Face가 너무 작아서 소수점 자리 수정

	fprintf(fpErrorInfoFile, "복셀 전체의 크기는 %d이다.\n", row* col* height);
	fprintf(fpErrorInfoFile, "Face를 가지는 유의미한 복셀의 총 개수는 %d\n", valVoxelIndex);
	fprintf(fpErrorInfoFile, "face의 edge의 총 길이는 %lf이고 평균은 %lf이다.\n", faceLengthSum, faceAvgLength);
	fprintf(fpErrorInfoFile, "총 face의 개수는 %d개 이다.\n\n", faceTotalNum);
	fprintf(fpErrorInfoFile, "Edge가 %lf보다 짧은 Skinny triangle의 개수는 %d\n", minLength, errorLengthFaceNum);
	fprintf(fpErrorInfoFile, "Skinny Triangle/faceNumd은 %lf이다\n", double(errorLengthFaceNum) / faceTotalNum);
	fprintf(fpErrorInfoFile, "Skinny Triangle을 가지는 복셀의 총 개수는 %d\n", errorVoxelNum);
	fprintf(fpErrorInfoFile, "Skinny Triangle 복셀 / 유의미한 복셀는 %lf\n\n", (double)errorVoxelNum / valVoxelIndex);
	fprintf(fpErrorInfoFile, "가장 짧은 edge는 %lf, 가장 긴 edge는 %lf\n", faceMinLength, faceMaxLength);
	
	//사이즈 관련 미사용
	//fprintf(fpErrorInfoFile, "face의 총 넓이는 %lf이고 평균은 %lf이다.\n", faceSizeSum, faceAvgSize);
	//fprintf(fpErrorInfoFile, "Face 넓이가 %lf보다 작기만 해서 문제가 되는 Face의 개수는 %d\n", minSize, errorSizeFaceNum);
	//fprintf(fpErrorInfoFile, "Face Edge가 %lf보다 짧고 크기가 %lf보다 작은 Face의 개수는 %d\n", minLength, minSize, errorBothFaceNum);
	//fprintf(fpErrorInfoFile, "총 Skinny Triangledml 개수는 %d이고 Skinny Triangle/faceNumd은 %lf이다\n", errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum, double(errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum) / faceTotalNum);
	//fprintf(fpErrorInfoFile, "가장 작은 Face의 크기는 %.20lf, 가장 큰 크기는 %lf\n", faceMinSize, faceMaxSize);
	
	fclose(fpErrorInfoFile);
	fclose(fpErrorFaceInfoFile);
}

//fpVertex,fpFace : 파일 포인터, p : 복셀의 꼭짓점들(8개) 위치정보 저장 ,density : 복셀의 각 꼭짓점들 밀도값 저장, vertexNum, faceNum : 파일에 저장될 vertex수(vertexNum)와 face수(faceNum) 저장용도
void marchingcube(FILE* fpVertex, FILE* fpFace, Point* p, double* density, int* vertexNum, int b, int c, int h, int* faceNum)  //참고자료 : http://paulbourke.net/geometry/polygonise/
{
	int vertexInNum = 0; //포함 index 개수
	int cubeIndex = 0;

	int val[12];							//val값이 -1이면 교차점이 꼭짓점이다 edge 12개의 값
	Point belowPoint[12];					//val값이 -1이 아닌경우(교차점이 꼭짓점이 아닌 경우) 그 edge에서 cl보다 작은 density를 가지는 값
	int face_array[12] = { 0 };				//교차점의 vertex 파일에서의 위치값
	if (density[0] < cl) {
		cubeIndex |= 1;
		vertexInNum++;
	}
	if (density[1] < cl) {
		cubeIndex |= 2;
		vertexInNum++;
	}
	if (density[2] < cl) {
		cubeIndex |= 4;
		vertexInNum++;
	}
	if (density[3] < cl) {
		cubeIndex |= 8;
		vertexInNum++;
	}
	if (density[4] < cl) {
		cubeIndex |= 16;
		vertexInNum++;
	}
	if (density[5] < cl) {
		cubeIndex |= 32;
		vertexInNum++;
	}
	if (density[6] < cl) {
		cubeIndex |= 64;
		vertexInNum++;
	}
	if (density[7] < cl) {
		cubeIndex |= 128;
		vertexInNum++;
	}
	// determine cubeIndex
	// cubeIndex cl보다 작으면 외부! 즉 0이 내부고 1이 내부가 아님

	Point vertlist[12]; //edge가 12개라서 총 12개이며 각각의 edge에서 나올수 있는 vertex를 계산해서 저장(교차점을 계산해서 저장)
	int edgePassCheck[12];//vertex 있나 없나 체크(교차점이 있나 없나 체크)
	for (int i = 0; i < 12; i++)
	{
		edgePassCheck[i] = 0;      // include vertex check(교차점 체크)
		val[i] = 0;		   // i edge에 위치하는 교차점이 꼭짓점인지 아닌 판단하는 값 초기화
	}

	if (edgeTable[cubeIndex] == 0)//복셀이 표면과의 접점이 없음
	{
		//printf("복셀이 표면과 접점이 없는 것이 marchingCube 함수에서 발견\n");
		return;
	}

	if (edgeTable[cubeIndex] & 1) //표면이 edge 0(0,1)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[0] = *face_vertexNum;
		edgePassCheck[0] = 1;	//표면이 edge 0을 가름
		vertlist[0] = pointcal(p[0], p[1], density[0], density[1]);//edge 0과 표면의 교차점 위치
		if ((vertlist[0].x == p[0].x) && (vertlist[0].y == p[0].y) && (vertlist[0].z == p[0].z))
		{
			val[0] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[0][0] = 1;	//vertex가 edge 0의 꼭짓점 0 위치이다.
		}
		else if ((vertlist[0].x == p[1].x) && (vertlist[0].y == p[1].y) && (vertlist[0].z == p[1].z))
		{
			val[0] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[0][1] = 1;	//vertex가 edge 0의 꼭짓점 1 위치이다.
		}
		else
		{
			if (density[0] < density[1])
				belowPoint[0] = p[0];		//point[0]은 edge 0에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 0(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[0] = p[1];		//point[0]은 edge 0에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 1(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 2) //표면이 edge 1(1,2)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[1] = *face_vertexNum;
		edgePassCheck[1] = 1;	//표면이 edge 1을 가름
		vertlist[1] = pointcal(p[1], p[2], density[1], density[2]);//edge 1과 표면의 교차점 위치
		if ((vertlist[1].x == p[1].x) && (vertlist[1].y == p[1].y) && (vertlist[1].z == p[1].z))
		{
			val[1] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[1][1] = 1;	//vertex가 edge 1의 꼭짓점 1 위치이다.
		}

		else if ((vertlist[1].x == p[2].x) && (vertlist[1].y == p[2].y) && (vertlist[1].z == p[2].z))
		{
			val[1] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[1][2] = 1;	//vertex가 edge 1의 꼭짓점 2 위치이다.
		}
		else
		{
			if (density[1] < density[2])
				belowPoint[1] = p[1];		//point[1]은 edge 1에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 1(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[1] = p[2];		//point[1]은 edge 1에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 2(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 4) //표면이 edge 2(2,3)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[2] = *face_vertexNum;
		edgePassCheck[2] = 1;	//표면이 edge 2을 가름
		vertlist[2] = pointcal(p[2], p[3], density[2], density[3]);//edge 2과 표면의 교차점 위치
		if ((vertlist[2].x == p[2].x) && (vertlist[2].y == p[2].y) && (vertlist[2].z == p[2].z))
		{
			val[2] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[2][2] = 1;	//vertex가 edge 2의 꼭짓점 2 위치이다.
		}
		else if ((vertlist[2].x == p[3].x) && (vertlist[2].y == p[3].y) && (vertlist[2].z == p[3].z))
		{
			val[2] = -1;				//가른점이 복셀의 꼭짓점 이다.	
			cubeVertexCheck[2][3] = 1;	//vertex가 edge 2의 꼭짓점 3 위치이다.
		}
		else
		{
			if (density[2] < density[3])
				belowPoint[2] = p[2];		//point[2]은 edge 2에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 2(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[2] = p[3];		//point[2]은 edge 2에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 3(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 8) //표면이 edge 3(3,0)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[3] = *face_vertexNum;
		edgePassCheck[3] = 1;	//표면이 edge 3을 가름
		vertlist[3] = pointcal(p[3], p[0], density[3], density[0]);//edge 3과 표면의 교차점 위치
		if ((vertlist[3].x == p[3].x) && (vertlist[3].y == p[3].y) && (vertlist[3].z == p[3].z))
		{
			val[3] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[3][3] = 1;	//vertex가 edge 3의 꼭짓점 3 위치이다.
		}

		else if ((vertlist[3].x == p[0].x) && (vertlist[3].y == p[0].y) && (vertlist[3].z == p[0].z))
		{
			val[3] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[3][0] = 1;	//vertex가 edge 3의 꼭짓점 0 위치이다.
		}
		else
		{
			if (density[3] < density[0])
				belowPoint[3] = p[3];		//point[3]은 edge 3에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 3(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[3] = p[0];		//point[3]은 edge 3에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 0(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 16) //표면이 edge 4(4,5)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[4] = *face_vertexNum;
		edgePassCheck[4] = 1;	//표면이 edge 4를 가름
		vertlist[4] = pointcal(p[4], p[5], density[4], density[5]);//edge 4과 표면의 교차점 위치
		if ((vertlist[4].x == p[4].x) && (vertlist[4].y == p[4].y) && (vertlist[4].z == p[4].z))
		{
			val[4] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[4][4] = 1;	//vertex가 edge 4의 꼭짓점 4 위치이다.
		}
		else if ((vertlist[4].x == p[5].x) && (vertlist[4].y == p[5].y) && (vertlist[4].z == p[5].z))
		{
			val[4] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[4][5] = 1;	//vertex가 edge 4의 꼭짓점 5 위치이다.
		}
		else
		{
			if (density[4] < density[5])
				belowPoint[4] = p[4];		//point[4]은 edge 4에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 4(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[4] = p[5];		//point[4]은 edge 4에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 4(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 32) //표면이 edge 5(5,6)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[5] = *face_vertexNum;
		edgePassCheck[5] = 1;	//표면이 edge 5를 가름
		vertlist[5] = pointcal(p[5], p[6], density[5], density[6]);//edge 5과 표면의 교차점 위치
		if ((vertlist[5].x == p[5].x) && (vertlist[5].y == p[5].y) && (vertlist[5].z == p[5].z))
		{
			val[5] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[5][5] = 1;	//vertex가 edge 5의 꼭짓점 5 위치이다.
		}
		else if ((vertlist[5].x == p[6].x) && (vertlist[5].y == p[6].y) && (vertlist[5].z == p[6].z))
		{
			val[5] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[5][6] = 1;	//vertex가 edge 5의 꼭짓점 6 위치이다.
		}
		else
		{

			if (density[5] < density[6])
				belowPoint[5] = p[5];		//point[5]은 edge 5에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 5(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[5] = p[6];		//point[5]은 edge 5에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 6(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 64) //표면이 edge 6(6,7)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[6] = *face_vertexNum;
		edgePassCheck[6] = 1;	//표면이 edge 6를 가름
		vertlist[6] = pointcal(p[6], p[7], density[6], density[7]);//edge 6과 표면의 교차점 위치
		if ((vertlist[6].x == p[6].x) && (vertlist[6].y == p[6].y) && (vertlist[6].z == p[6].z))
		{
			val[6] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[6][6] = 1;	//vertex가 edge 6의 꼭짓점 6 위치이다.
		}
		else if ((vertlist[6].x == p[7].x) && (vertlist[6].y == p[7].y) && (vertlist[6].z == p[7].z))
		{
			val[6] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[6][7] = 1;	//vertex가 edge 6의 꼭짓점 7 위치이다.
		}
		else
		{
			if (density[6] < density[7])
				belowPoint[6] = p[6];		//point[6]은 edge 6에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 6(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[6] = p[7];		//point[6]은 edge 6에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 7(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 128) //표면이 edge 7(7,4)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[7] = *face_vertexNum;
		edgePassCheck[7] = 1;	//표면이 edge 7를 가름
		vertlist[7] = pointcal(p[7], p[4], density[7], density[4]);//edge 7과 표면의 교차점 위치
		if ((vertlist[7].x == p[7].x) && (vertlist[7].y == p[7].y) && (vertlist[7].z == p[7].z))
		{
			val[7] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[7][7] = 1;	//vertex가 edge 7의 꼭짓점 7 위치이다.
		}
		else if ((vertlist[7].x == p[4].x) && (vertlist[7].y == p[4].y) && (vertlist[7].z == p[4].z))
		{
			val[7] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[7][4] = 1;	//vertex가 edge 7의 꼭짓점 4 위치이다.
		}
		else
		{
			if (density[7] < density[4])
				belowPoint[7] = p[7];		//point[7]은 edge 7에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 7(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[7] = p[4];		//point[7]은 edge 7에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 4(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 256)  //표면이 edge 8(0,4)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[8] = *face_vertexNum;
		edgePassCheck[8] = 1;	//표면이 edge 8를 가름
		vertlist[8] = pointcal(p[0], p[4], density[0], density[4]);//edge 8과 표면의 교차점 위치
		if ((vertlist[8].x == p[0].x) && (vertlist[8].y == p[0].y) && (vertlist[8].z == p[0].z))
		{
			val[8] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[8][0] = 1;	//vertex가 edge 8의 꼭짓점 0 위치이다.
		}
		else if ((vertlist[8].x == p[4].x) && (vertlist[8].y == p[4].y) && (vertlist[8].z == p[4].z))
		{
			val[8] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[8][4] = 1;	//vertex가 edge 8의 꼭짓점 4 위치이다.
		}
		else
		{
			if (density[0] < density[4])
				belowPoint[8] = p[0];		//point[8]은 edge 8에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 0(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[8] = p[4];		//point[8]은 edge 8에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 4(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 512)  //표면이 edge 9(1,5)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[9] = *face_vertexNum;
		edgePassCheck[9] = 1;	//표면이 edge 9를 가름
		vertlist[9] = pointcal(p[1], p[5], density[1], density[5]);//edge 9과 표면의 교차점 위치
		if ((vertlist[9].x == p[1].x) && (vertlist[9].y == p[1].y) && (vertlist[9].z == p[1].z))
		{
			val[9] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[9][1] = 1;	//vertex가 edge 9의 꼭짓점 1 위치이다.
		}
		else if ((vertlist[9].x == p[5].x) && (vertlist[9].y == p[5].y) && (vertlist[9].z == p[5].z))
		{
			val[9] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[9][5] = 1;	//vertex가 edge 9의 꼭짓점 5 위치이다.
		}
		else
		{
			if (density[1] < density[5])
				belowPoint[9] = p[1];		//point[9]은 edge 9에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 1(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[9] = p[5];		//point[9]은 edge 9에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 5(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 1024)  //표면이 edge 10(2,6)을 가름
	{
		//	(*face_vertexNum)++;
		//	face_array[10] = *face_vertexNum;
		edgePassCheck[10] = 1;	//표면이 edge 10를 가름
		vertlist[10] = pointcal(p[2], p[6], density[2], density[6]);//edge 10과 표면의 교차점 위치
		if ((vertlist[10].x == p[2].x) && (vertlist[10].y == p[2].y) && (vertlist[10].z == p[2].z))
		{
			val[10] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[10][2] = 1;	//vertex가 edge 10의 꼭짓점 2 위치이다.
		}
		else if ((vertlist[10].x == p[6].x) && (vertlist[10].y == p[6].y) && (vertlist[10].z == p[6].z))
		{
			val[10] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[10][6] = 1;	//vertex가 edge 10의 꼭짓점 6 위치이다.
		}
		else
		{
			if (density[2] < density[6])
				belowPoint[10] = p[2];		//point[10]은 edge 10에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 2(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[10] = p[6];		//point[10]은 edge 10에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 6(의 위치값) = 볼륨의 밖에 있음
		}
	}
	if (edgeTable[cubeIndex] & 2048)  //표면이 edge 11(3,7)을 가름
	{
		edgePassCheck[11] = 1;	//표면이 edge 11를 가름
		vertlist[11] = pointcal(p[3], p[7], density[3], density[7]);//edge 11과 표면의 교차점 위치
		if ((vertlist[11].x == p[3].x) && (vertlist[11].y == p[3].y) && (vertlist[11].z == p[3].z))
		{
			val[11] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[11][3] = 1;	//vertex가 edge 11의 꼭짓점 3 위치이다.
		}
		else if ((vertlist[11].x == p[7].x) && (vertlist[11].y == p[7].y) && (vertlist[11].z == p[7].z))
		{
			val[11] = -1;				//가른점이 복셀의 꼭짓점 이다.
			cubeVertexCheck[11][7] = 1;	//vertex가 edge 11의 꼭짓점 7 위치이다.
		}
		else
		{
			if (density[3] < density[7])
				belowPoint[11] = p[3];		//point[11]은 edge 11에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 3(의 위치값) = 볼륨의 밖에 있음
			else
				belowPoint[11] = p[7];		//point[11]은 edge 11에서의 contour_level 보다 작은 밀도값을 가진 꼭짓점의 위치값 = 7(의 위치값) = 볼륨의 밖에 있음
		}
	}
	/*
	//cubeVertexCheck 검사용 - 교차점이 복셀의 꼭짓점인 경우를 출력
	for (int i = 0; i < 12; i++)
	{
	for (int j = 0; j < 8; j++)
	if (cubeVertexCheck[i][j] == 1)
	{
	printf("%2d edge %d vertex 좌표 %f, %f, %f\n", i, j, p[j].x, p[j].y, p[j].z);
	}
	}
	*/

	int edgepassNum = 0;	//모든 접하는 edge 개수의 합
	int edgepassSum = 0;	//EdgeList 2진수를 10진수화
	int edgePassBY2[12] = { 0 }; //EdgeList 2진수

	int vertexInSum = 0;	//포함 index list 10진수 = cubeIndex


	vertexInSum = cubeIndex;

	int k1 = 1;
	for (int i = 0; i < 12; i++)
	{
		edgepassSum += k1 * edgePassCheck[i];
		edgepassNum += edgePassCheck[i];
		edgePassBY2[i] = edgePassCheck[i];
		k1 *= 2;

		//fprintf(fpEdgePassCheckFile2, "%d", edgePassCheck[i]); // 단순출력 방식
	}

	fprintf(fpEdgePassCheckFile1, "%2d %4d %3d %3d %3d %d %3d\n", edgepassNum, edgepassSum, b, c, h, vertexInNum, vertexInSum);
	for (int i = 0; i < 12; i++)
	{
		fprintf(fpEdgePassCheckFile2, "%d", edgePassBY2[i]);
	}
	fprintf(fpEdgePassCheckFile2, " %2d %4d %3d %3d %3d %d %3d\n", edgepassNum, edgepassSum, b, c, h, vertexInNum, vertexInSum);



	//교차점이 중복이 안되게 정리하는 알고리즘 돌림
	for (int i = 0; i < 12; i++)
	{
		if (edgePassCheck[i] == 1)//표면이 edge i 를 가름 = edge i 에서 교차점에 대한 중복 검사 실시
		{
			vertex_algo(fpVertex, i, vertexNum, b, c, vertlist, face_array);
		}
	}
	//cubeVertexCheck 함수 초기화(교차점이 복셀의 꼭짓점(8개)중 하나인지 체크하는 함수 - vertex algo에서 예외처리 하기 위해 사용)
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cubeVertexCheck[i][j] = 0;
		}
	}

	/*
	//cube에서 특정 개수의 face만을 생성하는 경우만을 face array에 출력
	for (int i = 0; i < 16; i += 3)//i 012, 345, 678, 91011, 121314, 15는 항상 -1, 한번에 하나의 삼각형
	{
		//if (triTable[cubeIndex][3] == -1)//이 큐브의 생성되는 face는 1개일 때만 본다.
		//if (triTable[cubeIndex][6] == -1 && triTable[cubeIndex][3] != -1)//이 큐브의 생성되는 face는 2개일 때만 본다.
		//if (triTable[cubeIndex][9] == -1 && triTable[cubeIndex][6] != -1)//이 큐브의 생성되는 face는 3개일 때만 본다.
		if (triTable[cubeIndex][12] == -1 && triTable[cubeIndex][9] != -1)//이 큐브의 생성되는 face는 4개일 때만 본다.
		//if (triTable[cubeIndex][12] != -1)//이 큐브의 생성되는 face는 5개일 때만 본다.
		//if (triTable[cubeIndex][9] == -1)//이 큐브의 생성되는 face는 3개이하일 때만 본다.
		//if (triTable[cubeIndex][9] != -1)//이 큐브의 생성되는 face는 4개 이상일 때만 본다.
		{
			if (triTable[cubeIndex][i] == -1)// 삼각형을 구성하지 않는다 또는 그다음 삼각형 차례인데 없다
				break;

			fprintf(fpFace, "%d %d %d %d\n", 3, face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]]);
			(*faceNum)++;
			//printf("%d %d %d\n",face_array[triTable[cubeIndex][i]],face_array[triTable[cubeIndex][i+1]],face_array[triTable[cubeIndex][i+2]]);
		}
	}
	*/
	

	isErrorVoxel = 0;
	//face에 적기 face에 적히는건 완성된 삼각형 3 a b c / abc는 각각 몇번째 위치의 vertex 인지 가져옴
	for (int i = 0; i < 16; i += 3)//i 012, 345, 678, 91011, 121314, 15는 항상 -1, 한번에 하나의 삼각형
	{
		//if (triTable[cubeIndex][12] != -1)//이 큐브에 생성되는 face가 5개일 때만 본다.

		if (triTable[cubeIndex][i] == -1)// 삼각형을 구성하지 않는다 또는 그다음 삼각형 차례인데 없다
			break;

		//만약 3개중 같은 값이 있으면 출력 후 제외
		if (face_array[triTable[cubeIndex][i]] == face_array[triTable[cubeIndex][i + 1]] || face_array[triTable[cubeIndex][i]] == face_array[triTable[cubeIndex][i + 2]] || face_array[triTable[cubeIndex][i + 1]] == face_array[triTable[cubeIndex][i + 2]])
		{
			printf("3개가 같은 값 발생\n%d %d %d\n", face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]]);
		}
		else
		{
			//double faceSize = 0;
			double s = 0;
			isErrorFace = 0;

			changeA.x = step_size * vertlist[triTable[cubeIndex][i]].x;
			changeA.y = step_size * vertlist[triTable[cubeIndex][i]].y;
			changeA.z = step_size * vertlist[triTable[cubeIndex][i]].z;

			changeB.x = step_size * vertlist[triTable[cubeIndex][i + 1]].x;
			changeB.y = step_size * vertlist[triTable[cubeIndex][i + 1]].y;
			changeB.z = step_size * vertlist[triTable[cubeIndex][i + 1]].z;

			changeC.x = step_size * vertlist[triTable[cubeIndex][i + 2]].x;
			changeC.y = step_size * vertlist[triTable[cubeIndex][i + 2]].y;
			changeC.z = step_size * vertlist[triTable[cubeIndex][i + 2]].z;

			//구한 Face의 edge의 각 길이를 구하는 경우
			getEdgeLength(changeA, changeB, changeC);
			//length1~3은 전역변수로 계산할때마다 0으로 초기화 된 뒤 계산한다.
			s = 0.5 * (length1 + length2 + length3);

			//사이즈 관련 미사용
			/*
			faceSize = sqrt(s * (s - length1) * (s - length2) * (s - length3));
			
			if (faceSize == 0)
				printf("face 크기가 0 길이 = %lf %lf %lf\n", length1, length2, length3);

			if (faceSize < faceMinSize)
				faceMinSize = faceSize;
			if (faceSize > faceMaxSize)
				faceMaxSize = faceSize;

			faceSizeSum += faceSize;
			*/
			//가장 짧은 edge과 가장 긴 edge의 길이 구하기
			if (shortestEdge(length1, length2, length3) < faceMinLength)
				faceMinLength = shortestEdge(length1, length2, length3);
			if (longestEdge(length1, length2, length3) > faceMaxLength)
				faceMaxLength = longestEdge(length1, length2, length3);

			
			//구한 face의 길이가 기준 값보다 작을 경우
			if (length1 < minLength || length2 < minLength || length3 < minLength)
			{
				isErrorFace = 1;
				isErrorVoxel = 1;
				errorLengthFaceNum++;
				
				//if (faceSize >= minSize) //사이즈 관련 미사용
				fprintf(fpErrorFaceInfoFile, "%6d번 Face : 짧은 edge %lf %lf %lf\n", faceTotalNum, length1, length2, length3);
			}
			//사이즈 관련 미사용
			/*
			if (faceSize < minSize)
			{
				if (isErrorFace == 1)
				{
					fprintf(fpErrorFaceInfoFile, "%6d번 Face : 짧은 edge %lf %lf %lf 작은 크기 %lf\n", faceTotalNum, length1, length2, length3, faceSize);
					errorLengthFaceNum--;
					errorBothFaceNum++;
				}
				else
				{
					fprintf(fpErrorFaceInfoFile, "%6d번 Face : 작은 크기 %lf\n", faceTotalNum, faceSize);
					errorSizeFaceNum++;
				}
				isErrorFace = 1;
				isErrorVoxel = 1;
			}
			faceSizeSum += faceSize;
			*/
			//s = 0.5 * (length1 + length2 + length3) 이므로
			faceLengthSum += (s * 2);
			faceTotalNum++;

			//기존
			//fprintf(fpFace, "%d %d %d %d\n", 3, face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]]);

			//voxelvalNumber 추가
			fprintf(fpFace, "3 %d %d %d %d %d\n", face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]], valVoxelIndex , isErrorFace);
			(*faceNum)++;
		}
		//A,B,C 순, A 교차점을 가진 edge에서 vertex 위치값,  B 교차점을 가진 edge에서 vertex 위치값,  C 교차점을 가진 edge에서 vertex 위치값
	}

}

//fpVertex = vertex 파일 출력 포인터, i = 표면이 edge i를 가름 = edge i 에서 교차점이 생김, vertexNum = face_array에 저장되는 vertex파일에서의 위치정보, b,c = row, col 복셀 위치값, vertlist = 교차점들의 위치 정보
//face_array 12칸을 가진 int 배열 
void vertex_algo(FILE* fpVertex, int i, int* vertexNum, int b, int c, Point* vertlist, int* face_array)
{
	if (arr4[b][c].array[i] == 1)										//이미 꼭짓점 할당으로 인해 값이 정해짐
	{
		face_array[i] = arr4[b][c].number[i];
	}
	else
	{
		if (i == 4)														//edge 4를 보기로 하자
		{

			if (b - 1 >= 0)												//맨 위쪽 칸은 아니다
			{
				if (arr4[b - 1][c].array[0] == 1)						//윗칸 복셀의 edge 0에서 교차점을 이미 가짐
				{
					arr4[b][c].array[i] = 1;							//해당 복셀의 edge 4에서 교차점을 가짐을 표시
					arr4[b][c].number[i] = arr4[b - 1][c].number[0];	//해당 복셀의 edge 4의 vertex 위치는 윗칸 복셀의 edge 0의 vertex 위치
					face_array[i] = arr4[b - 1][c].number[0];			//face array에 윗칸 복셀의 edge 0의 vertex 위치 값 넣기
				}
				else if (arr4[b - 1][c].array[0] == 0)					//윗칸 복셀의 edge 0에서 해당사항 없음
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);	//vertex파일에 출력
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;							//해당 복셀의 edge 4에서 교차점을 가짐을 표시
					arr4[b][c].number[i] = *vertexNum;					//해당 복셀의 edge 4의 vertex 위치 값 넣기
					face_array[i] = *vertexNum;							//face array에 해당 복셀의 edge 4의 vertex 위치 값 넣기
					arr4[b - 1][c].array[0] = 1;						//윗칸 복셀의 edge 0에서 교차점을 가짐을 표시
					arr4[b - 1][c].number[0] = *vertexNum;				//윗칸 복셀의 edge 0의 vertex 위치 값 넣기

					if (cubeVertexCheck[4][4] == 1)						//만약에 교차점이 edge 4의 꼭짓점 4라면
					{
						//해당 복셀의 꼭짓점 4와 연결된 edge들에 교차점 표시(4,7,8) + 4 이미 넣음
						arr4[b][c].array[7] = 1;						//해당 복셀의 edge 7에서 교차점을 가짐을 표시
						arr4[b][c].number[7] = *vertexNum;				//해당 복셀의 edge 7의 vertex 위치 값 넣기
						arr4[b][c].array[8] = 1;						//해당 복셀의 edge 8에서 교차점을 가짐을 표시
						arr4[b][c].number[8] = *vertexNum;				//해당 복셀의 edge 8의 vertex 위치 값 넣기
																		//윗칸 복셀의 꼭짓점 0와 연결된 edge들에 교차점 표시(0,3,8) + 0 이미 넣음
						arr4[b - 1][c].array[3] = 1;					//윗칸 복셀의 edge 3에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[3] = *vertexNum;			//윗칸 복셀의 edge 3의 vertex 위치 값 넣기
						arr4[b - 1][c].array[8] = 1;					//윗칸 복셀의 edge 8에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[8] = *vertexNum;			//윗칸 복셀의 edge 8의 vertex 위치 값 넣기
						if (c >= 1)										//맨 왼쪽 칸은 아니다(+ 맨 위쪽 칸도 아니다)
						{
							//왼칸 복셀의 꼭짓점 5와 연결된 edge들에 교차점 표시(4,5,9)
							arr4[b][c - 1].array[4] = 1;				//왼칸 복셀의 edge 4에서 교차점을 가짐을 표시
							arr4[b][c - 1].number[4] = *vertexNum;		//왼칸 복셀의 edge 4의 vertex 위치 값 넣기
							arr4[b][c - 1].array[5] = 1;				//왼칸 복셀의 edge 5에서 교차점을 가짐을 표시
							arr4[b][c - 1].number[5] = *vertexNum;		//왼칸 복셀의 edge 5의 vertex 위치 값 넣기
							arr4[b][c - 1].array[9] = 1;				//왼칸 복셀의 edge 9에서 교차점을 가짐을 표시
							arr4[b][c - 1].number[9] = *vertexNum;		//왼칸 복셀의 edge 9의 vertex 위치 값 넣기
																		//왼위 복셀의 꼭짓점 1과 연결된 edge들에 교차점 표시(0,1,9)
							arr4[b - 1][c - 1].array[0] = 1;			//왼위 복셀의 edge 0에서 교차점을 가짐을 표시
							arr4[b - 1][c - 1].number[0] = *vertexNum;	//왼위 복셀의 edge 0의 vertex 위치 값 넣기
							arr4[b - 1][c - 1].array[1] = 1;			//왼위 복셀의 edge 1에서 교차점을 가짐을 표시
							arr4[b - 1][c - 1].number[1] = *vertexNum;	//왼위 복셀의 edge 1의 vertex 위치 값 넣기
							arr4[b - 1][c - 1].array[9] = 1;			//왼위 복셀의 edge 9에서 교차점을 가짐을 표시
							arr4[b - 1][c - 1].number[9] = *vertexNum;	//왼위 복셀의 edge 9의 vertex 위치 값 넣기
						}
					}
					if (cubeVertexCheck[4][5] == 1)						//만약에 교차점이 edge 4의 꼭짓점 5라면
					{
						//해당 복셀의 꼭짓점 5와 연결된 edge들에 교차점 표시(4,5,9) + 4 이미 넣음
						arr4[b][c].array[5] = 1;						//해당 복셀의 edge 5에서 교차점을 가짐을 표시
						arr4[b][c].number[5] = *vertexNum;				//해당 복셀의 edge 5의 vertex 위치 값 넣기
						arr4[b][c].array[9] = 1;						//해당 복셀의 edge 9에서 교차점을 가짐을 표시
						arr4[b][c].number[9] = *vertexNum;				//해당 복셀의 edge 9의 vertex 위치 값 넣기
																		//윗칸 복셀의 꼭짓점 1과 연결된 edge들에 교차점 표시(0,1,9) + 0 이미 넣음
						arr4[b - 1][c].array[1] = 1;					//윗칸 복셀의 edge 1에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[1] = *vertexNum;			//윗칸 복셀의 edge 1의 vertex 위치 값 넣기
						arr4[b - 1][c].array[9] = 1;					//윗칸 복셀의 edge 9에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[9] = *vertexNum;			//윗칸 복셀의 edge 9의 vertex 위치 값 넣기
					}
					(*vertexNum)++;										//교차점 갯수 1개 증가
				}
			}
		}
		else if (i == 5)												//edge 5를 보기로 하자
		{
			if (b - 1 >= 0)												//맨 위쪽 칸은 아니다
			{
				if (arr4[b - 1][c].array[1] == 1)						//윗칸 복셀의 edge 1에서 이미 교차점을 가짐
				{
					arr4[b][c].array[i] = 1;							//해당 복셀의 edge 5에서 교차점을 가짐을 표시
					arr4[b][c].number[i] = arr4[b - 1][c].number[1];	//해당 복셀의 edge 5의 vertex 위치는 윗칸 복셀의 edge 1의 vertex 위치
					face_array[i] = arr4[b - 1][c].number[1];			//face array에 윗칸 복셀의 edge 1의 vertex 위치 값 넣기
				}
				else if (arr4[b - 1][c].array[1] == 0)					//윗칸 복셀의 edge 1 에서 해당사항 없음
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);	//vertex파일에 출력
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;							//해당 복셀의 edge 5에서 교차점을 가짐을 표시
					arr4[b][c].number[i] = *vertexNum;					//해당 복셀의 edge 5의 vertex 위치 값 넣기
					arr4[b - 1][c].array[1] = 1;						//윗칸 복셀의 edge 1에서 교차점을 가짐을 표시
					arr4[b - 1][c].number[1] = *vertexNum;				//윗칸 복셀의 edge 1의 vertex 위치 값 넣기
					face_array[i] = *vertexNum;							//face array에 해당 복셀의 edge 5의 vertex 위치 값 넣기
					if (cubeVertexCheck[5][5] == 1)						//만약에 교차점이 edge5의 꼭짓점 5라면
					{
						//해당 복셀의 꼭짓점 5와 연결된 edge들에 교차점 표시(4,5,9) + 5 이미 넣음
						arr4[b][c].array[4] = 1;						//해당 복셀의 edge 4에서 교차점을 가짐을 표시
						arr4[b][c].number[4] = *vertexNum;				//해당 복셀의 edge 4의 vertex 위치 값 넣기
						arr4[b][c].array[9] = 1;						//해당 복셀의 edge 9에서 교차점을 가짐을 표시
						arr4[b][c].number[9] = *vertexNum;				//해당 복셀의 edge 9의 vertex 위치 값 넣기
																		//윗칸 복셀의 꼭짓점 1과 연결된 edge들에 교차점 표시(0,1,9) + 1 이미 넣음
						arr4[b - 1][c].array[0] = 1;					//윗칸 복셀의 edge 0에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[0] = *vertexNum;			//윗칸 복셀의 edge 0의 vertex 위치 값 넣기
						arr4[b - 1][c].array[9] = 1;					//윗칸 복셀의 edge 9에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[9] = *vertexNum;			//윗칸 복셀의 edge 9의 vertex 위치 값 넣기
					}
					if (cubeVertexCheck[5][6] == 1)						//만약에 교차점이 edge 5의 꼭짓점 6라면
					{
						//해당 복셀의 꼭짓점 6와 연결된 edge들에 교차점 표시(5,6,10) + 5 이미 넣음
						arr4[b][c].number[6] = *vertexNum;				//해당 복셀의 edge 6에서 교차점을 가짐을 표시
						arr4[b][c].array[6] = 1;						//해당 복셀의 edge 6의 vertex 위치 값 넣기
						arr4[b][c].number[10] = *vertexNum;				//해당 복셀의 edge 10에서 교차점을 가짐을 표시
						arr4[b][c].array[10] = 1;						//해당 복셀의 edge 10의 vertex 위치 값 넣기
																		//윗칸 복셀의 꼭짓점 2와 연결된 edge들에 교차점 표시(1,2,10) + 1 이미 넣음
						arr4[b - 1][c].array[2] = 1;					//윗칸 복셀의 edge 2에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[2] = *vertexNum;			//윗칸 복셀의 edge 2의 vertex 위치 값 넣기
						arr4[b - 1][c].array[10] = 1;					//윗칸 복셀의 edge 10에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[10] = *vertexNum;			//윗칸 복셀의 edge 10의 vertex 위치 값 넣기

						if (counts == 1)									//맨 앞의 칸은 아니다(+ 맨 위쪽 칸도 아니다)
						{												//앞칸 복셀의 꼭짓점 5와 연결된 edge들에 교차점 표시(4,5,9)
							arr3[b][c].array[4] = 1;					//앞칸 복셀의 edge 4에서 교차점을 가짐을 표시
							arr3[b][c].number[4] = *vertexNum;			//앞칸 복셀의 edge 4의 vertex 위치 값 넣기
							arr3[b][c].array[5] = 1;					//앞칸 복셀의 edge 5에서 교차점을 가짐을 표시
							arr3[b][c].number[5] = *vertexNum;			//앞칸 복셀의 edge 5의 vertex 위치 값 넣기
							arr3[b][c].array[9] = 1;					//앞칸 복셀의 edge 9에서 교차점을 가짐을 표시
							arr3[b][c].number[9] = *vertexNum;			//앞칸 복셀의 edge 9의 vertex 위치 값 넣기
																		//앞위 복셀의 꼭짓점 1와 연결된 edge들에 교차점 표시(0,1,9)
							arr3[b - 1][c].array[0] = 1;				//앞위 복셀의 edge 0에서 교차점을 가짐을 표시
							arr3[b - 1][c].number[0] = *vertexNum;		//앞위 복셀의 edge 0의 vertex 위치 값 넣기
							arr3[b - 1][c].array[1] = 1;				//앞위 복셀의 edge 1에서 교차점을 가짐을 표시
							arr3[b - 1][c].number[1] = *vertexNum;		//앞위 복셀의 edge 1의 vertex 위치 값 넣기
							arr3[b - 1][c].array[9] = 1;				//앞위 복셀의 edge 9에서 교차점을 가짐을 표시
							arr3[b - 1][c].number[9] = *vertexNum;		//앞위 복셀의 edge 9의 vertex 위치 값 넣기
						}
					}
					(*vertexNum)++;										//교차점 갯수 1개 증가
				}
			}
		}
		else if (i == 6)												//edge 6를 보기로 하자
		{
			if ((b - 1 >= 0) && (counts == 1))							//맨 위쪽 칸도 맨 앞의 칸도 아니다
			{
				//윗칸 복셀의 edge 2 또는 앞칸 복셀의 edge 4 또는 앞위 복셀의 edge 0에 이미 교차점을 가짐
				if ((arr4[b - 1][c].array[2] == 1) || (arr3[b][c].array[4] == 1) || (arr3[b - 1][c].array[0] == 1))
				{
					if (arr4[b - 1][c].array[2] == 1)					//윗칸 복셀의 edge 2에서 이미 교차점을 가짐
					{
						int k = arr4[b - 1][c].number[2];				//윗칸 복셀의 edge 2의 vertex 위치 값
						arr4[b][c].number[i] = k;						//해당 복셀의 edge 6의 vertex 위치 값에 윗칸 복셀의 edge 2의 vertex 위치 값 넣기
						arr3[b][c].number[4] = k;						//앞칸 복셀의 edge 4의 vertex 위치 값에 윗칸 복셀의 edge 2의 vertex 위치 값 넣기
						arr3[b - 1][c].number[0] = k;					//앞위 복셀의 edge 0의 vertex 위치 값에 윗칸 복셀의 edge 2의 vertex 위치 값 넣기
						face_array[i] = k;								//face array에 윗칸 복셀의 edge 2의 vertex 위치 값 넣기
					}
					else if (arr3[b][c].array[4] == 1)					//앞칸 복셀의 edge 4에서 이미 교차점을 가짐
					{
						int k = arr3[b][c].number[4];					//앞칸 복셀의 edge 4의 vertex 위치 값
						arr4[b][c].number[i] = k;						//해당 복셀의 edge 6의 vertex 위치 값에 앞칸 복셀의 edge 4의 vertex 위치 값 넣기
						arr4[b - 1][c].number[2] = k;					//윗칸 복셀의 edge 2의 vertex 위치 값에 앞칸 복셀의 edge 4의 vertex 위치 값 넣기
						arr3[b - 1][c].number[0] = k;					//앞위 복셀의 edge 0의 vertex 위치 값에 앞칸 복셀의 edge 4의 vertex 위치 값 넣기
						face_array[i] = k;								//face array에 앞칸 복셀의 edge 4의 vertex 위치 값 넣기
					}
					else if (arr3[b - 1][c].array[0] == 1)				//앞위 복셀의 edge 0에서 이미 교차점을 가짐
					{
						int k = arr3[b - 1][c].number[0];				//앞위 복셀의 edge 0의 vertex 위치 값
						arr4[b][c].number[i] = k;						//해당 복셀의 edge 6의 vertex 위치 값에 앞위 복셀의 edge 0의 vertex 위치 값 넣기
						arr3[b][c].number[4] = k;						//앞칸 복셀의 edge 4의 vertex 위치 값에 앞위 복셀의 edge 0의 vertex 위치 값 넣기
						arr4[b - 1][c].number[2] = k;					//윗칸 복셀의 edge 2의 vertex 위치 값에 앞위 복셀의 edge 0의 vertex 위치 값 넣기
						face_array[i] = k;								//face array에 앞위 복셀의 edge 0의 vertex 위치 값 넣기
					}
					arr4[b][c].array[i] = 1;							//해당 복셀의 edge 6에서 교차점을 가짐을 표시
					arr4[b - 1][c].array[2] = 1;						//윗칸 복셀의 edge 2에서 교차점을 가짐을 표시
					arr3[b][c].array[4] = 1;							//앞칸 복셀의 edge 4에서 교차점을 가짐을 표시
					arr3[b - 1][c].array[0] = 1;						//앞위 복셀의 edge 0에서 교차점을 가짐을 표시
				}
				else
				{														//윗칸 복셀의 edge 2 또는 앞칸 복셀의 edge 4 또는 앞위 복셀의 edge 0에서 해당사항 없음
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z); //vertex파일에 출력
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;							//해당 복셀의 edge 6에서 교차점을 가짐을 표시
					arr4[b][c].number[i] = *vertexNum;					//해당 복셀의 edge 6의 vertex 위치 값 넣기
					arr3[b][c].array[4] = 1;							//앞칸 복셀의 edge 4에서 교차점을 가짐을 표시
					arr3[b][c].number[4] = *vertexNum;					//앞칸 복셀의 edge 4의 vertex 위치 값 넣기
					arr3[b - 1][c].array[0] = 1;						//앞위 복셀의 edge 0에서 교차점을 가짐을 표시
					arr3[b - 1][c].number[0] = *vertexNum;				//앞위 복셀의 edge 0의 vertex 위치 값 넣기
					arr4[b - 1][c].array[2] = 1;						//윗칸 복셀의 edge 2의 교차점을 가짐을 표시
					arr4[b - 1][c].number[2] = *vertexNum;				//윗칸 복셀의 edge 2의 vertex 위치 값 넣기
					face_array[i] = *vertexNum;							//face array에 해당 복셀의 edge 6의 vertex 위치 값 넣기
					if (cubeVertexCheck[6][7] == 1)						//만약에 교차점이 edge 6의 꼭짓점 7라면
					{													//해당 복셀의 꼭짓점 7과 연결된 edge들에 교차점 표시(6,7,11) + 6 이미 넣음
						arr4[b][c].array[7] = 1;						//해당 복셀의 edge 7에서 교차점을 가짐을 표시
						arr4[b][c].number[7] = *vertexNum;				//해당 복셀의 edge 7의 vertex 위치 값 넣기
						arr4[b][c].array[11] = 1;						//해당 복셀의 edge 11에서 교차점을 가짐을 표시
						arr4[b][c].number[11] = *vertexNum;				//해당 복셀의 edge 11의 vertex 위치 값 넣기
																		//앞칸 복셀의 꼭짓점 4과 연결된 edge들에 교차점 표시(4,7,8) + 4 이미 넣음
						arr3[b][c].array[7] = 1;						//앞칸 복셀의 edge 7에서 교차점을 가짐을 표시
						arr3[b][c].number[7] = *vertexNum;				//앞칸 복셀의 edge 7의 vertex 위치 값 넣기
						arr3[b][c].array[8] = 1;						//앞칸 복셀의 edge 8에서 교차점을 가짐을 표시
						arr3[b][c].number[8] = *vertexNum;				//앞칸 복셀의 edge 8의 vertex 위치 값 넣기
																		//앞위 복셀의 꼭짓점 0과 연결된 edge들에 교차점 표시(0,3,8) + 0 이미 넣음
						arr3[b - 1][c].array[3] = 1;					//앞위 복셀의 edge 3에서 교차점을 가짐을 표시
						arr3[b - 1][c].number[3] = *vertexNum;			//앞위 복셀의 edge 3의 vertex 위치 값 넣기
						arr3[b - 1][c].array[8] = 1;					//앞위 복셀의 edge 8에서 교차점을 가짐을 표시
						arr3[b - 1][c].number[8] = *vertexNum;			//앞위 복셀의 edge 8의 vertex 위치 값 넣기
																		//윗칸 복셀의 꼭짓점 3과 연결된 edge들에 교차점 표시(2,3,11) + 2 이미 넣음
						arr4[b - 1][c].array[3] = 1;					//윗칸 복셀의 edge 3에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[3] = *vertexNum;			//윗칸 복셀의 edge 3의 vertex 위치 값 넣기
						arr4[b - 1][c].array[11] = 1;					//윗칸 복셀의 edge 11에서 교차점을 가짐을 표시
						arr4[b - 1][c].number[11] = *vertexNum;			//윗칸 복셀의 edge 11의 vertex 위치 값 넣기
						if (c >= 1)										//맨 왼쪽 칸은 아니다.(+ 맨 위쪽 칸도 맨 앞의 칸도 아니다)
						{												//왼칸 복셀의 꼭짓점 6과 연결된 edge들에 교차점 표시(5,6,10)
							arr4[b][c - 1].array[5] = 1;				//왼칸 복셀의 edge 5에서 교차점을 가짐을 표시
							arr4[b][c - 1].number[5] = *vertexNum;		//왼칸 복셀의 edge 5의 vertex 위치 값 넣기
							arr4[b][c - 1].array[6] = 1;
							arr4[b][c - 1].number[6] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;

							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;

							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;

							arr3[b - 1][c - 1].array[0] = 1;
							arr3[b - 1][c - 1].number[0] = *vertexNum;
							arr3[b - 1][c - 1].array[1] = 1;
							arr3[b - 1][c - 1].number[1] = *vertexNum;
							arr3[b - 1][c - 1].array[9] = 1;
							arr3[b - 1][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[6][6] == 1)//만약에 점이 edg6의 vertex 6라면
					{
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr4[b - 1][c].array[10] = 1;
						arr4[b - 1][c].number[10] = *vertexNum;
						arr4[b - 1][c].array[1] = 1;
						arr4[b - 1][c].number[1] = *vertexNum;

						arr3[b][c].array[5] = 1;
						arr3[b][c].number[5] = *vertexNum;
						arr3[b][c].array[9] = 1;
						arr3[b][c].number[9] = *vertexNum;

						arr3[b - 1][c].array[1] = 1;
						arr3[b - 1][c].number[1] = *vertexNum;
						arr3[b - 1][c].array[9] = 1;
						arr3[b - 1][c].number[9] = *vertexNum;
					}

					(*vertexNum)++;
				}
			}
			else if (b - 1 >= 0) //맨위는 아니고 맨앞이다
			{
				if (arr4[b - 1][c].array[2] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b - 1][c].number[2];
					face_array[i] = arr4[b - 1][c].number[2];
				}
				else if (arr4[b - 1][c].array[2] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					arr4[b - 1][c].number[2] = *vertexNum;
					arr4[b - 1][c].array[2] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[6][7] == 1)
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b - 1][c].array[11] = 1;
						arr4[b - 1][c].number[11] = *vertexNum;
						arr4[b - 1][c].array[3] = 1;
						arr4[b - 1][c].number[3] = *vertexNum;

						if (c >= 1)
						{
							arr4[b][c - 1].array[5] = 1;
							arr4[b][c - 1].number[5] = *vertexNum;
							arr4[b][c - 1].array[6] = 1;
							arr4[b][c - 1].number[6] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;

							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;
						}

					}
					if (cubeVertexCheck[6][6] == 1)
					{
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr4[b - 1][c].array[10] = 1;
						arr4[b - 1][c].number[10] = *vertexNum;
						arr4[b - 1][c].array[1] = 1;
						arr4[b - 1][c].number[1] = *vertexNum;
					}

					(*vertexNum)++;
				}
			}
			else if (counts == 1) // 맨앞은 아닌데 맨 위다
			{
				if (arr3[b][c].array[4] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr3[b][c].number[4];
					face_array[i] = arr3[b][c].number[4];
				}
				else if (arr3[b][c].array[4] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					arr3[b][c].number[4] = *vertexNum;
					arr3[b][c].array[4] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[6][7] == 1)
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr3[b][c].number[7] = *vertexNum;
						arr3[b][c].array[7] = 1;
						arr3[b][c].number[8] = *vertexNum;
						arr3[b][c].array[8] = 1;
						if (c >= 1)
						{
							arr4[b][c - 1].array[5] = 1;
							arr4[b][c - 1].number[5] = *vertexNum;
							arr4[b][c - 1].array[6] = 1;
							arr4[b][c - 1].number[6] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;

							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[6][6] == 1)
					{
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr3[b][c].number[5] = *vertexNum;
						arr3[b][c].array[5] = 1;
						arr3[b][c].number[9] = *vertexNum;
						arr3[b][c].array[9] = 1;
					}
					(*vertexNum)++;

				}
			}
		}//완료
		else if (i == 7)
		{
			if ((b - 1) >= 0 && (c - 1) >= 0)//맨위도 아니고 맨 옆도 아니다 맨 앞가능
			{
				if ((arr4[b][c - 1].array[5] == 1) || (arr4[b - 1][c].array[3] == 1) || (arr4[b - 1][c - 1].array[1] == 1))
				{
					if (arr4[b][c - 1].array[5] == 1)
					{
						int k = arr4[b][c - 1].number[5];
						arr4[b][c].number[i] = k;
						arr4[b - 1][c].number[3] = k;
						arr4[b - 1][c - 1].number[1] = k;
						face_array[i] = k;
					}
					else if (arr4[b - 1][c].array[3] == 1)
					{
						int k = arr4[b - 1][c].number[3];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[5] = k;
						arr4[b - 1][c - 1].number[1] = k;
						face_array[i] = k;
					}
					else if (arr4[b - 1][c - 1].array[1] == 1)
					{
						int k = arr4[b - 1][c - 1].number[1];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[5] = k;
						arr4[b - 1][c].number[3] = k;
						face_array[i] = k;
					}
					arr4[b][c - 1].array[5] = 1;
					arr4[b - 1][c].array[3] = 1;
					arr4[b - 1][c - 1].array[1] = 1;
					arr4[b][c].array[i] = 1;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					arr4[b][c - 1].number[5] = *vertexNum;
					arr4[b][c - 1].array[5] = 1;
					arr4[b - 1][c].number[3] = *vertexNum;
					arr4[b - 1][c].array[3] = 1;
					arr4[b - 1][c - 1].number[1] = *vertexNum;
					arr4[b - 1][c - 1].array[1] = 1;
					face_array[i] = *vertexNum;

					if (cubeVertexCheck[7][7] == 1) // edge 7의 vertex 7
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[10] = *vertexNum;
						arr4[b][c - 1].array[10] = 1;

						arr4[b - 1][c].number[11] = *vertexNum;
						arr4[b - 1][c].array[11] = 1;
						arr4[b - 1][c].number[2] = *vertexNum;
						arr4[b - 1][c].array[2] = 1;

						arr4[b - 1][c - 1].number[2] = *vertexNum;
						arr4[b - 1][c - 1].array[2] = 1;
						arr4[b - 1][c - 1].number[10] = *vertexNum;
						arr4[b - 1][c - 1].array[10] = 1;
						if (counts == 1)//맨앞도 아니다
						{
							arr3[b][c].number[4] = *vertexNum;
							arr3[b][c].array[4] = 1;
							arr3[b][c].number[8] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[7] = *vertexNum;
							arr3[b][c].array[7] = 1;

							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;

							arr3[b - 1][c - 1].number[0] = *vertexNum;
							arr3[b - 1][c - 1].array[0] = 1;
							arr3[b - 1][c - 1].number[1] = *vertexNum;
							arr3[b - 1][c - 1].array[1] = 1;
							arr3[b - 1][c - 1].number[9] = *vertexNum;
							arr3[b - 1][c - 1].array[9] = 1;
						}
					}
					if (cubeVertexCheck[7][4] == 1)// edge 7의 vertex 4
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b][c - 1].number[4] = *vertexNum;
						arr4[b][c - 1].array[4] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;

						arr4[b - 1][c].number[8] = *vertexNum;
						arr4[b - 1][c].array[8] = 1;
						arr4[b - 1][c].number[0] = *vertexNum;
						arr4[b - 1][c].array[0] = 1;

						arr4[b - 1][c - 1].number[0] = *vertexNum;
						arr4[b - 1][c - 1].array[0] = 1;
						arr4[b - 1][c - 1].number[9] = *vertexNum;
						arr4[b - 1][c - 1].array[9] = 1;
					}
					(*vertexNum)++;
				}

			}
			else if (b - 1 >= 0) // 맨위는 아니고 맨옆이다 맨앞모름
			{
				if (arr4[b - 1][c].array[3] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b - 1][c].number[3];
					face_array[i] = arr4[b - 1][c].number[3];
				}
				else if (arr4[b - 1][c].array[3] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b - 1][c].array[3] = 1;
					arr4[b - 1][c].number[3] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[7][7] == 1)
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b - 1][c].array[11] = 1;
						arr4[b - 1][c].number[11] = *vertexNum;
						arr4[b - 1][c].array[2] = 1;
						arr4[b - 1][c].number[2] = *vertexNum;
						if (counts == 1)//맨앞도 아니다
						{
							arr3[b][c].number[4] = *vertexNum;
							arr3[b][c].array[4] = 1;
							arr3[b][c].number[8] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[7] = *vertexNum;
							arr3[b][c].array[7] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;
						}
					}
					if (cubeVertexCheck[7][4] == 1)
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b - 1][c].array[8] = 1;
						arr4[b - 1][c].number[8] = *vertexNum;
						arr4[b - 1][c].array[0] = 1;
						arr4[b - 1][c].number[0] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
			else if (c - 1 >= 0) // 맨 옆은 아니고 맨 위다
			{
				if (arr4[b][c - 1].array[5] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b][c - 1].number[5];
					face_array[i] = arr4[b][c - 1].number[5];
				}
				else if (arr4[b][c - 1].array[5] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[5] = 1;
					arr4[b][c - 1].number[5] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[7][7] == 1)
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[10] = 1;
						arr4[b][c - 1].number[10] = *vertexNum;
						if (counts == 1)
						{
							arr3[b][c].number[4] = *vertexNum;
							arr3[b][c].array[4] = 1;
							arr3[b][c].number[8] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[7] = *vertexNum;
							arr3[b][c].array[7] = 1;

							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
						}
					}
					if (cubeVertexCheck[7][4] == 1)
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b][c - 1].array[4] = 1;
						arr4[b][c - 1].number[4] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//완료
		else if (i == 3)
		{
			if (c - 1 >= 0)//맨 왼쪽은 아니다
			{
				if (arr4[b][c - 1].array[1] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b][c - 1].number[1];
					face_array[i] = arr4[b][c - 1].number[1];
				}
				else if (arr4[b][c - 1].array[1] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[1] = 1;
					arr4[b][c - 1].number[1] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[3][3] == 1)//만약 edge 3의 vertex 3 값이면
					{
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;

						arr4[b][c - 1].array[10] = 1;
						arr4[b][c - 1].number[10] = *vertexNum;
						arr4[b][c - 1].array[2] = 1;
						arr4[b][c - 1].number[2] = *vertexNum;
						if (counts == 1)
						{
							arr3[b][c].array[0] = 1;
							arr3[b][c].number[0] = *vertexNum;
							arr3[b][c].array[3] = 1;
							arr3[b][c].number[3] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[8] = *vertexNum;

							arr3[b][c - 1].array[0] = 1;
							arr3[b][c - 1].number[0] = *vertexNum;
							arr3[b][c - 1].array[1] = 1;
							arr3[b][c - 1].number[1] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[3][0] == 1)//만약에 edge 3의 vertex 0 값이면
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;

						arr4[b][c - 1].array[0] = 1;
						arr4[b][c - 1].number[0] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//완료
		else if (i == 8)
		{
			if (c - 1 >= 0)//맨옆은 아님
			{
				if (arr4[b][c - 1].array[9] == 1)
				{
					int k = arr4[b][c - 1].number[9];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr4[b][c - 1].array[9] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[9] = 1;
					arr4[b][c - 1].number[9] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[8][4] == 1)//만약에 edge 8의 vertex 4이면
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b][c - 1].array[4] = 1;
						arr4[b][c - 1].number[4] = *vertexNum;
						arr4[b][c - 1].array[5] = 1;
						arr4[b][c - 1].number[5] = *vertexNum;
						if (b >= 1)
						{
							arr4[b - 1][c].array[0] = 1;
							arr4[b - 1][c].number[0] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[8] = 1;
							arr4[b - 1][c].number[8] = *vertexNum;

							arr4[b - 1][c - 1].array[0] = 1;
							arr4[b - 1][c - 1].number[0] = *vertexNum;
							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[9] = 1;
							arr4[b - 1][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[8][0] == 1)//만약에 edge 8의 vertex 0이면
					{
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;

						arr4[b][c - 1].array[0] = 1;
						arr4[b][c - 1].number[0] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[1] = *vertexNum;
					}

					(*vertexNum)++;
				}

			}
		}//완료
		else if (i == 11)
		{
			if ((c - 1) >= 0 && (counts == 1))//맨 옆이 아님 맨 앞도 아님 맨위는 몰라
			{
				if ((arr4[b][c - 1].array[10] == 1) || (arr3[b][c].array[8] == 1) || (arr3[b][c - 1].array[9] == 1))
				{
					if (arr4[b][c - 1].array[10] == 1)
					{
						int k = arr4[b][c - 1].number[10];
						arr4[b][c].number[i] = k;
						arr3[b][c].number[8] = k;
						arr3[b][c - 1].number[9] = k;
						face_array[i] = k;
					}
					else if (arr3[b][c].array[8] == 1)
					{
						int k = arr3[b][c].number[8];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[10] = k;
						arr3[b][c - 1].number[9] = k;
						face_array[i] = k;
					}
					else if (arr3[b][c - 1].array[9] == 1)
					{
						int k = arr3[b][c - 1].number[9];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[10] = k;
						arr3[b][c].number[8] = k;
						face_array[i] = k;
					}
					arr4[b][c - 1].array[10] = 1;
					arr3[b][c].array[8] = 1;
					arr3[b][c - 1].array[9] = 1;
					arr4[b][c].array[i] = 1;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].number[10] = *vertexNum;
					arr4[b][c - 1].array[10] = 1;
					arr3[b][c].number[8] = *vertexNum;
					arr3[b][c].array[8] = 1;
					arr3[b][c - 1].number[9] = *vertexNum;
					arr3[b][c - 1].array[9] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[11][7] == 1)//만약 edge 11의 vertex 7이면
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;

						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[5] = *vertexNum;
						arr4[b][c - 1].array[5] = 1;

						arr3[b][c].number[7] = *vertexNum;
						arr3[b][c].array[7] = 1;
						arr3[b][c].number[4] = *vertexNum;
						arr3[b][c].array[4] = 1;

						arr3[b][c - 1].number[4] = *vertexNum;
						arr3[b][c - 1].array[4] = 1;
						arr3[b][c - 1].number[5] = *vertexNum;
						arr3[b][c - 1].array[5] = 1;
						if (b >= 1)//맨위도 아니야
						{
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[11] = *vertexNum;
							arr4[b - 1][c].array[11] = 1;

							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;

							arr3[b - 1][c - 1].number[0] = *vertexNum;
							arr3[b - 1][c - 1].array[0] = 1;
							arr3[b - 1][c - 1].number[1] = *vertexNum;
							arr3[b - 1][c - 1].array[1] = 1;
							arr3[b - 1][c - 1].number[9] = *vertexNum;
							arr3[b - 1][c - 1].array[9] = 1;
						}
					}
					if (cubeVertexCheck[11][3] == 1)//만약 edge 11의 vertex 3이면
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;

						arr4[b][c - 1].number[1] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[2] = *vertexNum;
						arr4[b][c - 1].array[2] = 1;

						arr3[b][c].number[0] = *vertexNum;
						arr3[b][c].array[0] = 1;
						arr3[b][c].number[3] = *vertexNum;
						arr3[b][c].array[3] = 1;

						arr3[b][c - 1].number[0] = *vertexNum;
						arr3[b][c - 1].array[0] = 1;
						arr3[b][c - 1].number[1] = *vertexNum;
						arr3[b][c - 1].array[1] = 1;
					}

					(*vertexNum)++;
				}
			}
			else if (c - 1 >= 0)// 맨 옆만 아니고 맨앞이다 맨위는 모름
			{
				if (arr4[b][c - 1].array[10] == 1)
				{
					int k = arr4[b][c - 1].number[10];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr4[b][c - 1].array[10] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[10] = 1;
					arr4[b][c - 1].number[10] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[11][7])
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;

						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[5] = *vertexNum;
						arr4[b][c - 1].array[5] = 1;
						if (b >= 1)
						{
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[11] = *vertexNum;
							arr4[b - 1][c].array[11] = 1;

							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;
						}
					}
					if (cubeVertexCheck[11][3])
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;

						arr4[b][c - 1].number[1] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[2] = *vertexNum;
						arr4[b][c - 1].array[2] = 1;
					}
					(*vertexNum)++;
				}
			}
			if (counts == 1) // 맨앞은 아닌데 맨옆임 맨위 모름
			{
				if (arr3[b][c].array[8] == 1)
				{
					int k = arr3[b][c].number[8];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr3[b][c].array[8] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr3[b][c].array[8] = 1;
					arr3[b][c].number[8] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[11][7] == 1)
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;

						arr3[b][c].array[7] = 1;
						arr3[b][c].number[4] = *vertexNum;
						arr3[b][c].array[7] = 1;
						arr3[b][c].number[4] = *vertexNum;
						if (b >= 1)	//맨위도 아님
						{
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[11] = *vertexNum;
							arr4[b - 1][c].array[11] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;
						}
					}
					if (cubeVertexCheck[11][3] == 1)
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;

						arr3[b][c].array[3] = 1;
						arr3[b][c].number[3] = *vertexNum;
						arr3[b][c].array[0] = 1;
						arr3[b][c].number[0] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//완료
		else if (i == 2)
		{
			if (counts == 1)//맨앞이 아닐때 맨위 맨옆몰라
			{
				if (arr3[b][c].array[0] == 1)
				{
					int k = arr3[b][c].number[0];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr3[b][c].array[0] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr3[b][c].array[0] = 1;
					arr3[b][c].number[0] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[2][3] == 1)//엣지2에서 vertex 3
					{
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr3[b][c].array[8] = 1;
						arr3[b][c].number[8] = *vertexNum;
						arr3[b][c].array[3] = 1;
						arr3[b][c].number[3] = *vertexNum;
						if (c >= 1)
						{
							arr4[b][c - 1].number[1] = *vertexNum;
							arr4[b][c - 1].array[1] = 1;
							arr4[b][c - 1].number[2] = *vertexNum;
							arr4[b][c - 1].array[2] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;

							arr3[b][c - 1].array[0] = 1;
							arr3[b][c - 1].number[0] = *vertexNum;
							arr3[b][c - 1].array[1] = 1;
							arr3[b][c - 1].number[1] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[2][2] == 1)//엣지2에서 vertex 2
					{
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr3[b][c].array[9] = 1;
						arr3[b][c].number[9] = *vertexNum;
						arr3[b][c].array[1] = 1;
						arr3[b][c].number[1] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}

		}//완료
		else if (i == 10)
		{
			if (counts == 1)//맨앞이 아님 맨위 맨옆 모름
			{
				if (arr3[b][c].array[9] == 1)
				{
					int k = arr3[b][c].number[9];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr3[b][c].array[9] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr3[b][c].array[9] = 1;
					arr3[b][c].number[9] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[10][6] == 1)//엣지10 vertex 6
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;

						arr3[b][c].array[4] = 1;
						arr3[b][c].number[4] = *vertexNum;
						arr3[b][c].array[5] = 1;
						arr3[b][c].number[5] = *vertexNum;
						if (b >= 1) // 맨위도 아냐 
						{
							arr4[b - 1][c].number[1] = *vertexNum;
							arr4[b - 1][c].array[1] = 1;
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[10] = *vertexNum;
							arr4[b - 1][c].array[10] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[1] = *vertexNum;
							arr3[b - 1][c].array[1] = 1;
							arr3[b - 1][c].number[9] = *vertexNum;
							arr3[b - 1][c].array[9] = 1;
						}
					}
					if (cubeVertexCheck[10][2] == 1)//엣지10 vertex 2
					{
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;

						arr3[b][c].array[0] = 1;
						arr3[b][c].number[0] = *vertexNum;
						arr3[b][c].array[1] = 1;
						arr3[b][c].number[1] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//완료
		else if (i == 0) // edge 0
		{
			if (c >= 1)
			{
				if ((arr4[b][c - 1].array[0] == 1) && (cubeVertexCheck[0][0] == 1))
				{
					int k = arr4[b][c - 1].number[0];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[0][0] == 1)//엣지0 vertex 0
					{
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						//c>=1
						arr4[b][c - 1].number[0] = *vertexNum;
						arr4[b][c - 1].array[0] = 1;
						arr4[b][c - 1].number[1] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;
					}
					if (cubeVertexCheck[0][1] == 1)//엣지0 vertex 1
					{
						arr4[b][c].number[9] = *vertexNum;
						arr4[b][c].array[9] = 1;
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
					}
					(*vertexNum)++;
				}
			}
			else // c < 1 ==  c=0
			{
				fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
				vertexXSum += step_size * vertlist[i].x;
				vertexYSum += step_size * vertlist[i].y;
				vertexZSum += step_size * vertlist[i].z;
				arr4[b][c].number[i] = *vertexNum;
				arr4[b][c].array[i] = 1;
				face_array[i] = *vertexNum;
				if (cubeVertexCheck[0][0] == 1)//엣지0 vertex 0
				{
					arr4[b][c].number[3] = *vertexNum;
					arr4[b][c].array[3] = 1;
					arr4[b][c].number[8] = *vertexNum;
					arr4[b][c].array[8] = 1;
				}
				if (cubeVertexCheck[0][1] == 1)//엣지0 vertex 1
				{
					arr4[b][c].number[9] = *vertexNum;
					arr4[b][c].array[9] = 1;
					arr4[b][c].number[1] = *vertexNum;
					arr4[b][c].array[1] = 1;
				}
				(*vertexNum)++;
			}
		}
		else if (i == 1)
		{
			if (counts == 1)//맨앞은 아니다
			{
				if ((arr3[b][c].array[1] == 1) && cubeVertexCheck[1][2] == 1)//앞에 이미 지남
				{
					int k = arr3[b][c].number[1];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[1][1] == 1)//엣지1 vertex 1
					{
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;
						arr4[b][c].number[9] = *vertexNum;
						arr4[b][c].array[9] = 1;
					}
					if (cubeVertexCheck[1][2] == 1)//엣지1 vertex 2
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						if (counts == 1)
						{
							arr3[b][c].number[0] = *vertexNum;
							arr3[b][c].array[0] = 1;
							arr3[b][c].number[1] = *vertexNum;
							arr3[b][c].array[1] = 1;
							arr3[b][c].number[9] = *vertexNum;
							arr3[b][c].array[9] = 1;
						}
					}
					(*vertexNum)++;
				}
			}
			else //count ==0 맨앞
			{
				fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
				vertexXSum += step_size * vertlist[i].x;
				vertexYSum += step_size * vertlist[i].y;
				vertexZSum += step_size * vertlist[i].z;
				arr4[b][c].number[i] = *vertexNum;
				arr4[b][c].array[i] = 1;
				face_array[i] = *vertexNum;
				if (cubeVertexCheck[1][1] == 1)//엣지1 vertex 1
				{
					arr4[b][c].number[0] = *vertexNum;
					arr4[b][c].array[0] = 1;
					arr4[b][c].number[9] = *vertexNum;
					arr4[b][c].array[9] = 1;
				}
				if (cubeVertexCheck[1][2] == 1)//엣지1 vertex 2
				{
					arr4[b][c].number[2] = *vertexNum;
					arr4[b][c].array[2] = 1;
					arr4[b][c].number[10] = *vertexNum;
					arr4[b][c].array[10] = 1;
				}
				(*vertexNum)++;
			}
		}
		else if (i == 9)
		{
			if (b >= 1)
			{
				if ((arr4[b - 1][c].array[9] == 1) && (cubeVertexCheck[9][5] == 1))
				{
					int k = arr4[b - 1][c].number[9];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[9][1] == 1)//엣지9 vertex 1
					{
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
					}
					if (cubeVertexCheck[9][5] == 1)//엣지9 vertex 5
					{
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b - 1][c].number[0] = *vertexNum;
						arr4[b - 1][c].array[0] = 1;
						arr4[b - 1][c].number[1] = *vertexNum;
						arr4[b - 1][c].array[1] = 1;
						arr4[b - 1][c].number[9] = *vertexNum;
						arr4[b - 1][c].array[9] = 1;
					}
					(*vertexNum)++;
				}
			}
			else // b = 0
			{
				fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
				vertexXSum += step_size * vertlist[i].x;
				vertexYSum += step_size * vertlist[i].y;
				vertexZSum += step_size * vertlist[i].z;
				arr4[b][c].array[i] = 1;
				arr4[b][c].number[i] = *vertexNum;
				face_array[i] = *vertexNum;
				if (cubeVertexCheck[9][1] == 1)//엣지9 vertex 1
				{
					arr4[b][c].number[0] = *vertexNum;
					arr4[b][c].array[0] = 1;
					arr4[b][c].number[1] = *vertexNum;
					arr4[b][c].array[1] = 1;
				}
				if (cubeVertexCheck[9][5] == 1)//엣지9 vertex 5
				{
					arr4[b][c].number[4] = *vertexNum;
					arr4[b][c].array[4] = 1;
					arr4[b][c].number[5] = *vertexNum;
					arr4[b][c].array[5] = 1;
				}
				(*vertexNum)++;
			}

		}
	}
}


Point pointcal(Point p1, Point p2, double val1, double val2) //edge에서 나오는 vertex의 좌표 값 계산
{
	Point p;
	if (abs(cl - val1) < 0.00001)
	{
		return p1;
	}
	if (abs(cl - val2) < 0.00001)
	{
		return p2;
	}
	if (abs(val1 - val2) < 0.00001)
	{

		return p1;
	}
	double mu = (cl - val1) / (val2 - val1);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return p;
}

void getEdgeLength(Point p1, Point p2, Point p3)
{
	//double length1, length2, length3

	length1 = 0;
	length2 = 0;
	length3 = 0;

	length1 = pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) + pow((p2.z - p1.z), 2);
	length1 = sqrt(length1);

	length2 = pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2) + pow((p3.z - p1.z), 2);
	length2 = sqrt(length2);

	length3 = pow((p2.x - p3.x), 2) + pow((p2.y - p3.y), 2) + pow((p2.z - p3.z), 2);
	length3 = sqrt(length3);

}

void convertVertex(Point p1, Point p2, Point p3)
{

}

double shortestEdge(double a, double b, double c)
{
	if (a <= b)
	{
		if (a <= c)
			return a;
		else
			return c;
	}
	else //a > b
	{
		if (b <= c)
			return b;
		else
			return c;
	}
}
double longestEdge(double a, double b, double c)
{
	if (a >= b)
	{
		if (a >= c)
			return a;
		else
			return c;
	}
	else //a < b
	{
		if (b >= c)
			return b;
		else
			return c;
	}
}
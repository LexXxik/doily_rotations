/**
 * @file constant_doilies.c
 * @author Adrian Bartko
 * @brief predefines constant doilies
 * 
 */

#include "bv.c"

#define N_GROUPS 3 // division of the doily vertices into outer, mide-edge, inner vertices
#define N_GROUPED_VERTICES 5 // N of vertices in each array of the struct doily
#define N_CONSTANT_DOILIES 4 // Doilies alpha, beta, gamma, delta as per problem specification

bv INDEX_DOILY[DOILY_SIZE];
bv OUTER_VERTICES[N_GROUPED_VERTICES] = {XI, XZ, YX, ZZ, XX};
bv MID_EDGE_VERTICES[N_GROUPED_VERTICES] = {IZ, ZY, XY, YY, IX};
bv INNER_VERTICES[N_GROUPED_VERTICES] = {ZI, YZ, IY, ZX, YI};

bv DOILY_LINES[N_LINES][NB_POINTS_PER_LINE];

/*
 every possible ovoid position
*/
bv DEFAULT_OVOID[OVOID_INDEXES_COUNT][OVOID_COUNT] = 
{
  {IX,IZ,XY,ZY,YY},
  {IX,IY,XZ,ZZ,YZ},
  {XI,ZI,YX,YZ,YY},
  {XI,ZX,YI,ZZ,ZY},
  {XX,IZ,IY,ZX,YX},
  {XX,XZ,XY,ZI,YI}
};

//----------------- 4 different types of constant doilies ---------------------------
#define ALPHA 0
#define BETA 1
#define GAMMA 2
#define DELTA 3

bv CONSTANT_DOILIES[N_CONSTANT_DOILIES][DOILY_SIZE];

bv ALPHA_OUTER[N_GROUPED_VERTICES] = {YI, YX, ZZ, XX, YZ};
bv ALPHA_MID[N_GROUPED_VERTICES] = {IX, XY, YY, ZY, IZ};
bv ALPHA_INNER[N_GROUPED_VERTICES] = {XI, ZX, IY, XZ, ZI};

bv BETA_OUTER[N_GROUPED_VERTICES] = {IZ, XZ, YX, XY, YZ};
bv BETA_MID[N_GROUPED_VERTICES] = {XI, ZY, ZZ, ZX, YI};
bv BETA_INNER[N_GROUPED_VERTICES] = {IY, XX, ZI, YY, IX};

bv GAMMA_OUTER[N_GROUPED_VERTICES] = {XI, IY, YY, ZZ, IZ};
bv GAMMA_MID[N_GROUPED_VERTICES] = {XY, YI, XX, ZI, XZ};
bv GAMMA_INNER[N_GROUPED_VERTICES] = {YX, YZ, IX, ZY, ZX};

bv DELTA_OUTER[N_GROUPED_VERTICES] = {XI, IY, ZY, YZ, IZ};
bv DELTA_MID[N_GROUPED_VERTICES] = {XY, ZI, XX, YI, XZ};
bv DELTA_INNER[N_GROUPED_VERTICES] = {ZX, ZZ, IX, YY, YX};
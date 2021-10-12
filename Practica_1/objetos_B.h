//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

const float AXIS_SIZE=5000; // Cte para los ejes

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor); // parámetros de color y tamaño

vector<_vertex3f> vertices; // vector de vértices de tres dimensiones

// vector<_vertex3f> colores; vector de colores para los vértices

};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2 = 1.0, float g2 =1.0, float b2 = 1.0); // alternar dos colores (ajedrez)

vector<_vertex3i> caras; // vector de caras
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};

//*************************************************************************
// clase icosaedro
//*************************************************************************

class _piramideHexagonal: public _triangulos3D
{
public:

	_piramideHexagonal(float l = 2.0, float h = 6.0);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};







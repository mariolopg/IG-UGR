//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
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
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
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
// clase prisma trapezoidal
//*************************************************************************

class _trapecio: public _triangulos3D
{
public:
	_trapecio(float tam = 1);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
	public:
		_rotacion();
		void  parametros(vector<_vertex3f> perfil1, int num1, int tipo); //Tipos --> 0: cilindro / 1: cono / 2: esfera

		vector<_vertex3f> perfil; 
		int num;
};

class _esfera: public _rotacion{
	public:
		_esfera(float radio, int n, int m);
};

class _cono: public _rotacion{
	public:
		_cono(float radio, int altura, int m);
};

class _cilindro: public _rotacion{
	public:
		_cilindro(float radio, int altura, int m);
};


//************************************************************************
// objeto lego
//************************************************************************

// La cabeza se crea por revolución a partir de un perfil
class _cabeza_lego: public _rotacion{
	public:
		_cabeza_lego();
};

// El tronco se crea a partir de un objeto de la clase _prisma
class _tronco_lego: public _rotacion{
	public:
		_tronco_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_trapecio tronco;

};

class _brazo_lego: public _rotacion{
	public:
		_brazo_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cilindro *articulacion;
		_esfera *hombro;
		_cilindro *antebrazo;
};

class _pelvis_lego: public _rotacion{
	public:
		_pelvis_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cubo *cintura;
		_cilindro *ingle;
		_cilindro *articulacion_piernas;
};

class _pierna_lego: public _rotacion{
	public:
		_pierna_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cilindro *cuadriceps;
		_cubo *gemelo;
		_cubo *pie;
};

class _lego: public _rotacion{
	public:
		_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	protected:
		_cabeza_lego cabeza;
		_tronco_lego tronco;
		_brazo_lego brazo_izquierdo;
		_brazo_lego brazo_derecho;
		_pelvis_lego pelvis;
		_pierna_lego pierna_izquierda;
		_pierna_lego pierna_derecha;
};
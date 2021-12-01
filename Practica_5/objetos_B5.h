//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, SOLID_ILLUMINATED_FLAT, SOLID_ILLUMINATED_GOURAUD} _modo;

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
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );

void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 
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

class _ojo_lego: public _rotacion{
	public:
		_ojo_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_esfera *pupila;
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

class _mano_lego: public _rotacion{
	public:
		_mano_lego();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_cilindro *munheca;
		_cubo *palma;
		_cubo *dedos_izq;
		_cubo *dedos_der;
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
	
		//Giro cabeza
		float giro_cabeza;
		float giro_cabeza_min;
		float giro_cabeza_max;

		//Giro brazos
		float giro_brazo_izq;
		float giro_brazo_der;
		float giro_brazo_min;
		float giro_brazo_max;

		//Giro piernas
		float giro_pierna_izq;
		float giro_pierna_der;
		float giro_pierna_min;
		float giro_pierna_max;

		float  color_pick[3];
		int    color_selec[3][3];
		int    activo[3];
		int    piezas;
	
	protected:
		_cabeza_lego cabeza;
		_ojo_lego ojo_izquierdo;
		_ojo_lego ojo_derecho;
		_tronco_lego tronco;
		_brazo_lego brazo_izquierdo;
		_mano_lego mano_izquierda;
		_brazo_lego brazo_derecho;
		_mano_lego mano_derecha;
		_pelvis_lego pelvis;
		_pierna_lego pierna_izquierda;
		_pierna_lego pierna_derecha;


};
//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CILINDRO, CONO, ESFERA, LEGO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_cilindro cilindro(0.5, 1, 30);
_cono cono(0.5, 1, 24);
_esfera esfera(1, 6, 24);
_lego lego;

int flag_izq = 0, flag_der = 0;
float mov = 0.0;
// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

	switch (t_objeto)
	{
		case CUBO:
			cubo.draw(modo, 0.5, 0.1, 1.0, 0.19, 0.87, 1.0, 2);
			break;
		case PIRAMIDE:
			piramide.draw(modo, 0.5, 0.1, 1.0, 0.19, 0.87, 1.0, 2);
			break;
		case OBJETO_PLY:
			ply.draw(modo, 1.0, 0.6, 0.0, 0.0, 1.0, 0.3, 2);
			break;
		case ROTACION:
			rotacion.draw(modo, 0.5, 0.1, 1.0, 0.19, 0.87, 1.0, 2);
			break;
		case CILINDRO:
			cilindro.draw(modo, 0.5, 0.1, 1.0, 0.19, 0.87, 1.0, 2);
			break;
		case CONO:
			cono.draw(modo, 0.5, 0.1, 1.0, 0.19, 0.87, 1.0, 2);
			break;
		case ESFERA:
			esfera.draw(modo, 0.5, 0.1, 1.0, 0.19, 0.87, 1.0, 2);
			break;
        case LEGO:
            lego.draw(modo, 1, 1, 1, 0.9, 0.9, 9, 2);
            break;
	}
}

//**************************************************************************
// LUCES
//***************************************************************************
 void luces (){
	float  luz1[]={1.0, 1.0, 1.0, 1.0},
			pos1[]= {0, 20.0, 40.0, 1.0}; //Cuidado con no ponerla dentro del objeto

	glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1); 
	glLightfv (GL_LIGHT1, GL_SPECULAR, luz1); //Si no le ponemos componente esepcular, no tiene brillo, por lo qeu no cambia segun observador

	glLightfv (GL_LIGHT1, GL_POSITION, pos1);

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
 }


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
luces();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
    case '5':mov = 3; break;
    case '6':mov = 0.5; break;
    case '7':mov = 0; break;
    case '8': 
        lego.giro_brazo_izq = 0;
        lego.giro_brazo_der = 0;
        lego.giro_pierna_izq = 0;
        lego.giro_pierna_der = 0;
    break;
	case 'P':t_objeto=PIRAMIDE;break;
	case 'C':t_objeto=CUBO;break;
	case 'O':t_objeto=OBJETO_PLY;break;
	case 'R':t_objeto=ROTACION;break;
	case 'B':t_objeto=CILINDRO;break;
	case 'N':t_objeto=CONO;break;
	case 'M':t_objeto=ESFERA;break;
    case 'L':t_objeto=LEGO;break;
    case '9': modo = SOLID_ILLUMINATED_FLAT;break;
	case '0': modo = SOLID_ILLUMINATED_GOURAUD; break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

	switch (Tecla1)
	{
		case GLUT_KEY_LEFT:
			Observer_angle_y--;
			break;
		case GLUT_KEY_RIGHT:
			Observer_angle_y++;
			break;
		case GLUT_KEY_UP:
			Observer_angle_x--;
			break;
		case GLUT_KEY_DOWN:
			Observer_angle_x++;
			break;
		case GLUT_KEY_PAGE_UP:
			Observer_distance *= 1.2;
			break;
		case GLUT_KEY_PAGE_DOWN:
			Observer_distance /= 1.2;
			break;
        //Mover cabeza a la izquierda
        case GLUT_KEY_F1:
            lego.giro_cabeza -= 1.0;
            if(lego.giro_cabeza < lego.giro_cabeza_min)
                lego.giro_cabeza = lego.giro_cabeza_min;
            break;
        //Mover cabeza a la derecha
        case GLUT_KEY_F2:
            lego.giro_cabeza += 1.0;
            if(lego.giro_cabeza > lego.giro_cabeza_max)
                lego.giro_cabeza = lego.giro_cabeza_max;
            break;
        //Mover brazo izquierdo hacia atrás
        case GLUT_KEY_F3:
            lego.giro_brazo_izq += 3.0;
            if(lego.giro_brazo_izq > lego.giro_brazo_min)
                lego.giro_brazo_izq = lego.giro_brazo_min;
            break;
        //Mover brazo izquierdo hacia delante
        case GLUT_KEY_F4:
            lego.giro_brazo_izq -= 3.0;
            if(lego.giro_brazo_izq < lego.giro_brazo_max)
                lego.giro_brazo_izq = lego.giro_brazo_max;
            break;
        //Mover brazo derecho hacia atrás 
        case GLUT_KEY_F5:
            lego.giro_brazo_der += 3.0;
            if(lego.giro_brazo_der > lego.giro_brazo_min)
                lego.giro_brazo_der = lego.giro_brazo_min;
            break;
        //Mover brazo derecho hacia delante 
        case GLUT_KEY_F6:
            lego.giro_brazo_der -= 3.0;
            if(lego.giro_brazo_der < lego.giro_brazo_max)
                lego.giro_brazo_der = lego.giro_brazo_max;
            break;
        //Mover pierna izquierda derecha hacia atras
        case GLUT_KEY_F7:
            lego.giro_pierna_izq += 3.0;
            if(lego.giro_pierna_izq > lego.giro_pierna_min)
                lego.giro_pierna_izq = lego.giro_pierna_min;
            break;
        //Mover pierna izquierda hacia delante
        case GLUT_KEY_F8:
            lego.giro_pierna_izq -= 3.0;
            if(lego.giro_pierna_izq < lego.giro_pierna_max)
                lego.giro_pierna_izq = lego.giro_pierna_max;
            break;
        //Mover pierna derecha derecha hacia atras
        case GLUT_KEY_F9:
            lego.giro_pierna_der += 3.0;
            if(lego.giro_pierna_der > lego.giro_pierna_min)
                lego.giro_pierna_der = lego.giro_pierna_min;
            break;
        //Mover pierna derecha derecha hacia delante
        case GLUT_KEY_F10:
            lego.giro_pierna_der -= 3.0;
            if(lego.giro_pierna_der < lego.giro_pierna_max)
                lego.giro_pierna_der = lego.giro_pierna_max;
            break;
	}
	glutPostRedisplay();
}

void movimiento(){

    // Moviemiento automatico brazo izquierdo
    if(flag_izq == 0){
        lego.giro_brazo_izq -= mov;
        lego.giro_pierna_der -= mov;
    }
    else{
        lego.giro_brazo_izq += mov;
        lego.giro_pierna_der += mov;
    }
    
    if(lego.giro_brazo_izq > 45 && mov != 0){
        lego.giro_brazo_izq = 45;
        lego.giro_pierna_der = 45;
        flag_izq = 0;
    }
    if(lego.giro_brazo_izq < -45 && mov != 0){
        lego.giro_brazo_izq = -45;
        lego.giro_pierna_der = -45;
        flag_izq = 1;
    }

    // Moviemiento automatico brazo derecho y pierna izquierda
    if(flag_der == 1){
        lego.giro_brazo_der -= mov;
        lego.giro_pierna_izq -= mov;
    }
    else{
        lego.giro_brazo_der += mov;
        lego.giro_pierna_izq += mov;
    }

    if(lego.giro_brazo_der > 45 && mov != 0){
        lego.giro_brazo_der = 45;
        lego.giro_pierna_izq = 45;
        flag_der = 1;
    }
    if(lego.giro_brazo_der < -45 && mov != 0){
        lego.giro_brazo_der = -45;
        lego.giro_pierna_izq = -45;
        flag_der = 0;
    }
    
    if(mov != 0)
        glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

    // se inicalizan la ventana y los planos de corte
    Size_x = 0.5;
    Size_y = 0.5;
    Front_plane = 1;
    Back_plane = 1000;

    // se incia la posicion del observador, en el eje z
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0;
    Observer_angle_y = 0;

    // se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(102.0/255, 153.0/255, 1, 1);

    // se habilita el z-bufer
    glEnable(GL_DEPTH_TEST);
    change_projection();
    glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{

    // perfil

    vector<_vertex3f> perfil2;
    _vertex3f aux;

    // Perfil original
    // aux.x = 1.2;
    // aux.y = -1.0;
    // aux.z = 0.0;
    // perfil2.push_back(aux);
    // aux.x = 0.6;
    // aux.y = 0.0;
    // aux.z = 0.0;
    // perfil2.push_back(aux);
    // aux.x = 1.2;
    // aux.y = 1.2;
    // aux.z = 0.0;
    // perfil2.push_back(aux);
    // aux.x = 1.8;
    // aux.y = 1.8;
    // aux.z = 0.0;
    // perfil2.push_back(aux);

    //Perfil Mario
    aux.x = 2;
    aux.y = 0;
    aux.z = 0;
    perfil2.push_back(aux);
    aux.x = 3;
    aux.y = 1;
    aux.z = 0;
    perfil2.push_back(aux);
    aux.x = 3;
    aux.y = 1.25;
    aux.z = 0;
    perfil2.push_back(aux);
    aux.x = 2;
    aux.y = 2.5;
    aux.z = 0;
    perfil2.push_back(aux);
    aux.x = 1;
    aux.y = 3;
    aux.z = 0;
    perfil2.push_back(aux);
    aux.x = 2;
    aux.y = 4;
    aux.z = 0;
    perfil2.push_back(aux);

    rotacion.parametros(perfil2, 12, 0);

    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(Window_x, Window_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(Window_width, Window_high);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("PRACTICA - 2");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw);
    // asignación de la funcion llamada "change_window_size" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "normal_key" al evento correspondiente
    glutKeyboardFunc(normal_key);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_key);

    glutIdleFunc(movimiento);

    // funcion de inicialización
    initialize();

    // creación del objeto ply
    ply.parametros(argv[1]);

    //ply1 = new _objeto_ply(argv[1]);

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}

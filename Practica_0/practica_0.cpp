#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GL/freeglut.h>

void Circle(GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
   int i;
   if (modo == GL_LINE)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else if (modo == GL_FILL)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   else
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
   glBegin(GL_POLYGON);
   for (i = 0; i < n; i++)
      glVertex2f(cx + radio * cos(2.0 * M_PI * i / n), cy + radio * sin(2.0 * M_PI * i / n));
   glEnd();
}

void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
 
// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd();

//Pelo
   glColor3ub(168, 135, 50);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.55,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(0.2,0.35,0.0);
      glVertex3f(-0.2,0.35,0.0);
   glEnd();

// Sombrero
   // Ala
   glColor3ub(0, 0, 0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.55,0.0);
      glVertex3f(0.3,0.55,0.0);
      glVertex3f(0.3,0.4,0.0);
      glVertex3f(-0.3,0.4,0.0);
   glEnd();

   // Copa
   glColor3ub(0, 0, 0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2, 1,0.0);
      glVertex3f(0.2, 1,0.0);
      glVertex3f(0.2,0.4,0.0);
      glVertex3f(-0.2,0.4,0.0);
   glEnd();

//Cuerda
   //Lado izquierdo
   glColor3ub(156, 135, 20);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.1,0.0);
      glVertex3f(0.0,0.05,0.0);
      glVertex3f(0.0,0.0,0.0);
      glVertex3f(-0.2,0.05,0.0);
   glEnd();

   //Lado derecho
   glColor3ub(156, 135, 20);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.2,0.1,0.0);
      glVertex3f(0.0,0.05,0.0);
      glVertex3f(0.0,0.0,0.0);
      glVertex3f(0.2,0.05,0.0);
   glEnd();

   //Boca
   glColor3ub(194, 60, 100);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.1, 0.1, 0.0);
      glVertex3f(0.1, 0.1, 0.0);
      glVertex3f(0.1, 0.14, 0.0);
      glVertex3f(-0.1, 0.14, 0.0);
   glEnd();

   // Ojos

   glColor3ub(255, 255, 255);
   Circle(0.05, 0.1, 0.4, 20, GL_FILL);

}


static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0); 
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0); //Color de fondo
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 ); // (0,0) Se situa arriba izquierda
   glutInitWindowSize(500, 500 ); // Dimensiones de la ventana (largo * ancho)
   glutCreateWindow("Practica 0 IG"); //Título de la ventana


   Init();

   glutReshapeFunc(Reshape); //Evento de cambiar tamaño de ventana
   glutDisplayFunc(Display); //Evento de mostrar la ventana cuando pulsas el icono de la barra de tareas
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}


//  robot.cpp
//  3d-robot
//
//  Created by Maria Miller on 4/3/15.
//  Copyright (c) 2015 Maria Miller. All rights reserved.
//

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct rotation {
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

rotation bodyRotate;
rotation armRotate;

// Movement
float rightRun = 0.0f;
float leftRun = 0.0f;
float ypos = 0.0f;
float angle = 50.0f;
float armPos = 2.0f;
bool moved = false;
bool jumped = false;
float passo = 0.0f;
float passoX = 0;
float passoZ = 0; 
float giro = 0.0f;


// Color
int red = 1;
int green = 1;
int blue = 0;

int eyeRed = 1;
int eyeGreen = 1;
int eyeBlue = 1;

GLfloat ambient_light[]  = { 0.1, 0.1, 0.1, 1.0f };
GLfloat diffuse_light[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular_light[] = { 0, 0, 0, 1.0f };
GLfloat light_position[] = { -5.0f, 0.0f, 5.0f, 1.0f};

GLfloat mat_ambient[]    = { 1, 1, 1, 1 };
GLfloat mat_diffuse[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess[] = { 10.0f };

int scale = 10;
const GLfloat tam_x = 50.0f/scale;
const GLfloat tam_y = 50.0f/scale;

const GLint sy = 30/scale;
const GLint my = 25/scale;
const GLint hy = 20/scale;

int hora;
int minuto;
int segundo;

void circulo(GLfloat xc, GLfloat yc, GLfloat raio, bool fill)
{
  const GLfloat c = 3.14169f / 180.0f;
  GLint i;
  
  glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
  
  for (i = 0; i <= 360; i += 2)
  {
    float a = i * c;
    glVertex2f(xc + sin(a) * raio, yc + cos(a) * raio);
  }
  
  glEnd();
}

void move(int n)
{
     // Apos a execucao desse trecho a estrutura "datahora"
     // tera armazenada a data/hora atual do relogio da maquina
     time_t agora = time(0);
     struct tm *datahora = localtime(&agora);
     
     hora = datahora->tm_hour;
     minuto = datahora->tm_min;
     segundo = datahora->tm_sec;
     
     glutPostRedisplay(); // Pede para redesenhar a tela. Vai chamar a funcao desenha()
     glutTimerFunc(1000, move, 0);     // Pede para chamar de novo a funcao move
}

void init() {
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     
}

// Função callback chamada para fazer o desenho
void desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	//glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glRotatef(45, 0, 0, 1.0f);
    glTranslatef(0, 0, -5);

    glPushMatrix();
    // Desenha os circulos	
    glColor3f(0.7f, 0.7f, 0.0f); // amarelo
    circulo(0, 0, tam_x, true);
    
    glColor3f(0.0f, 0.0f, 0.0f); // preto
    circulo(0, 0, tam_x, false);  
    
    // Calcula o angulo do segundo
    float anguloS = segundo * 6;
    
    // Desenha o ponteiro do segundo
    glRotatef(-anguloS, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    glVertex3i(0,0,0);
    glVertex3i(0,sy,0);
    glEnd();
    glPopMatrix();
    //glLoadIdentity(); // Limpa as transformacoes
    //glTranslatef(0, 0, -5);

    // Calcula o angulo do minuto
    float anguloM = minuto * 6;

    glPushMatrix();
    // Desenha o ponteiro do minuto
    glRotatef(-anguloM, 0.0f, 0.0f, 1.0f);

	glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3i(0,0,0);
    glVertex3i(0,my,0);
    glEnd();
    glPopMatrix();
    //glLoadIdentity(); // Limpa as transformacoes
    //glTranslatef(0, 0, -5);

    // Calcula o angulo da hora
	float anguloH = (hora + minuto/60.0) * 30;

    glPushMatrix();
    // Desenha o ponteiro da hora
    glRotatef(-anguloH, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3i(0,0,0);
    glVertex3i(0,hy,0);
    glEnd();
    glPopMatrix();
    
    glPopMatrix();

    //glLoadIdentity(); // Limpa as transformacoes

	//Executa os comandos OpenGL 
	//glFlush();
}

static void createRobot() {
    glPushMatrix();
    glTranslatef(passoX,0,passoZ);
    glRotatef(giro,0,1,0);

    // Create body
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(red, green, blue);
    glScalef(3, 3, 2);
    glutSolidCube(1);
    glPopMatrix();

    // Create head
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glColor3f(red, green, blue);
    glScalef(1.5, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Create right leg
    glPushMatrix();
    glTranslatef(-1, -2.5, 0);
    glRotatef(rightRun, 1.0f, 0, 0);
    glColor3f(red, green, blue);
    glScalef(1, 2.5, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Create left leg
    glPushMatrix();
    glTranslatef(1, -2.5, 0);
    glRotatef(leftRun, 1.0f, 0, 0);
    glColor3f(red, green, blue);
    glScalef(1, 2.5, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Right arm
    glPushMatrix();
    glTranslatef(-armPos, 1, 0);
    //glRotatef(leftRun, 2.0f, 0, 0);
    glRotatef(angle, 0, 0, 1.0f);
    glColor3f(red, green, blue);
    glScalef(0.3, 1.8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    // Left arm
    glPushMatrix();
    glTranslatef(armPos, 1, 0);
    //glRotatef(rightRun, 1.0f, 0, 0);
    glRotatef(-angle, 0, 0, 1.0f);
    glColor3f(red, green, blue);
    glScalef(0.3, 1.8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    // Left eye
    glPushMatrix();
    glTranslatef(0.5, 2, 0.5);
    glColor3f(eyeRed, eyeGreen, eyeBlue);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    // chão
    glPushMatrix();
    glTranslatef(0, -5, 0);
    glColor3f(0.02, 0.02, 0.02);
    glScalef(20, 0.1, 20 );
    glutSolidCube(1);
    glPopMatrix();
    
}

// Move arms and legs
static void run () {
    if (!moved) {
        rightRun = 25;
        leftRun = -25;
        moved = true;
    }
    
    if (rightRun == 25) {
        while (rightRun != -25) {
            rightRun--;
            leftRun++;
        }
    }
    
    else if (rightRun == -25) {
        while (rightRun != 25) {
            rightRun++;
            leftRun--;
        }
    }
    
}

static void jump() {
    
    if (!jumped) {
        rightRun = 0;
        leftRun = 0;
        ypos++;
        rightRun--;
        leftRun++;

        if (ypos == 10)
            jumped = true;
        
    }
    
    if (jumped) {
        ypos--;
        rightRun++;
        leftRun--;
        
        if (ypos == 0)
            jumped = false;
    }
}

// Change color of robot
static void changeColor() {
    
    for (int i = 0; i < 3; i++) {
        specular_light[i] = 0;
    }
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    red = rand() % 2;
    green = rand() % 2;
    blue = rand() % 2;
    
}

// Blink eyes by switching from white to black to white.
static void blink() {
    // Change specular light so color changes are seen.
    for (int i = 0; i < 3; i++) {
        specular_light[i] = 0;
    }
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    
    if (eyeRed == 1) {
        eyeRed = 0;
        eyeGreen = 0;
        eyeBlue = 0;
    } else {
        eyeRed = 1;
        eyeGreen = 1;
        eyeBlue = 1;
    }
}

// Increase diffusive reflection
static void diffuseReflect() {

    float value = 0.1f;
    
    for (int i = 0; i < 4; i++) {
        value = 0.1f;
        if (diffuse_light[i] >= 1)
            diffuse_light[i] = 0;
        
        else
            diffuse_light[i] += value;
    
    }
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
}

static void specularReflect() {
   
    float value = 0.1f;
    
    for (int i = 0; i < 3; i++) {
        value = 0.1f;
        if (specular_light[i] >= 1)
            specular_light[i] = 0;
        
        else
            specular_light[i] += value;
    }
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
}

static void increaseShiny() {
    if (high_shininess[0] >= 100)
        high_shininess[0] = 0.0f;
    else
        high_shininess[0] += 10.0f;
    
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// Wave arms by moving angle from 50 to 20
static void waveArms() {
    
    if (angle == 50)
        angle = 20;
    else
        angle = 50;
    
}

static void reshape(int width, int height) {
    
    glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'b':           // Blink eyes
            blink();
            break;
        case 'c':           // Change color
            changeColor();
            break;
        case 'd':           // Increase diffusive reflection
            diffuseReflect();
            break;
        case 's':           // Increase specular reflection
            //specularReflect();
            break;
        case 'h':           // Increase shiny
            increaseShiny();
            break;
        case 'u':           // Jump
            jump();
            break;
        case 'i':           // Run frente
            passoX+=sin((giro/180)*3.1416);
            passoZ+=cos((giro/180)*3.1416);
            std::cout<<cos((giro/180)*3.1416)<<std::endl;

            run();
            break;
        case 'k':           // Run tras
            passoX-=sin((giro/180)*3.1416);
            passoZ-=cos((giro/180)*3.1416);
            run();
            break;
        case 'j':           // roda direita
            giro+=10;
            break;
        case 'l':           // roda esquerda
            giro-=10;
            break;
        case 't':           // Turn Around
            rightRun = 0;
            leftRun = 0;
            ypos = 0;
            bodyRotate.y+=5;
            moved = false;
            break;
        case 'w':           // Wave arms
            waveArms();
            break;
        case 'q':           // Quit
            exit(0);
            break;
            
    }
    glutPostRedisplay();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 15.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Isometric view
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    
    /*
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(60, aspect, 1, 40);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    */
    // Move back
    //glTranslatef(-6, 0, 0);
    

    
    // Create the robot
    glRotatef(bodyRotate.y, 0, 1.0f, 0);
    createRobot();
    desenha();
    
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("3D Robot");
    glutTimerFunc(1000, move, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Random
    srand (time(NULL));
    
    init();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}

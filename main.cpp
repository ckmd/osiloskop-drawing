//
//  main.cpp
//  Latihan1
//
//  Created by Student on 9/5/18.
//  Copyright (c) 2018 Student. All rights reserved.
//

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    float x,y;
} point2D_t;

typedef struct{
    float r,g,b;
}color_t;

void fillPolygon(point2D_t p[],color_t col,int n){
    glBegin(GL_POLYGON);
    glColor3f(col.r, col.g, col.b);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x, p[i].y);
    }
    glEnd();
}

void drawPolygon(point2D_t p[],int n){
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x, p[i].y);
    }
    glEnd();
}

void drawPolyline(point2D_t p[],int n){
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x, p[i].y);
    }
    glEnd();
}

void drawLine(float x1,float y1,float x2,float y2){
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawCircle(float px,float py,float r,int n){
    float s;
    float ds=360/n;
    point2D_t p[360];
    for(int i=0; i<n; i++){
        s=i*ds/57.3;
        p[i].x=px+r*cos(s);
        p[i].y=py+r*sin(s);
    }
}

void displayText(float x, float y, char *string){
    char * ch;
    glColor3f(1,1,1);
    glRasterPos2f(x,y);

    for(ch = string; *ch; ch++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)*ch);
    }
}
void createButton(int x,int y){
    point2D_t buttons[3] = {{x,y},{x+20,y-10},{x+20,y+10}};
    point2D_t buttons2[3] = {{x+50,y},{x+30,y-10},{x+30,y+10}};
    color_t cbuttons = {1.,1.,1.};
    fillPolygon(buttons,cbuttons,3);
    fillPolygon(buttons2,cbuttons,3);
}

void userdraw(void){
    static float t=0;
    glLineWidth(1);
    glColor3f(0,1,1);

    for (int i=0;i<=18;i++) {
        drawLine(i*20,-200,i*20,200);
    }
    for(float a=-200;a<=200;a+=50){
        drawLine(0, a, 360, a);
    }

    glColor3f(1, 1, 0);
    drawLine(0,0,360,0);
    point2D_t p[360];
    float a = 100;//a untuk menambahkan amplitudo
    int frek = 10;
    for(int i=0;i<360;i++){
        p[i].x = i;
        //p[i].y = sin(10*i/57.3+t)+0.5*sin(8*i/57.3+t)+0.5*sin(5*i/57.3+t);
        //p[i].y = sin(8*i/57.3+2*(sin(4*i/57.3)+t));
        p[i].y = a*sin(frek*i/57.3+t);//i untuk menentukan frequensi
    }
    glLineWidth(2);
    glColor3f(1,1,1);
    drawPolyline(p,360);
    t+=0.009;


    createButton(400,-190);
    createButton(400,-140);
    createButton(400,-90);
    displayText(380.,-190,"F" );
    displayText(380.,-140,"A" );
    displayText(380.,-90,"S" );
}


void display(void) {
    glClear( GL_COLOR_BUFFER_BIT);
    userdraw();
    glutSwapBuffers();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(100.,100.);
    glutInitWindowSize(600.,400.);
    glutCreateWindow ("Osiloskop");
    glClearColor(1., 0., 1., 0.);
    gluOrtho2D(-40, 500., -250., 300.);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

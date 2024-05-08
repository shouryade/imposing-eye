#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <iostream>
#include "vendor/stb_image/stb_image.h"
#include <math.h>

using namespace std;

GLuint textureID;

float angle = 0.0;
float yPos = 0.0;
float ySpeed = 0.05;
float zPos = 0.0;
float zSpeed = 0.05;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glGenTextures(1, &textureID);

    int width, height, channels;
    glBindTexture(GL_TEXTURE_2D, textureID);
    unsigned char *backgroundImage = stbi_load("assets/work.jpg", &width, &height, &channels, STBI_rgb_alpha);
    if (backgroundImage)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundImage);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        cerr << "Failed to load background texture" << endl;
    }
    stbi_image_free(backgroundImage);
}

float y_offset = 0.0;
float z_offset = 0.0;
float y_speed = 0.05;
float z_speed = -0.02;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-20.0f, -20.0f, -20.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, -20.0f, -20.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20.0f, 20.0f, -20.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-20.0f, 20.0f, -20.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat lightPosition[] = {0.0, 0.0, 10.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glTranslatef(0.0, y_offset, z_offset);
    glRotatef(angle, 1.0, 1.0, 1.0);

    GLfloat glassSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat glassShininess[] = {100.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, glassSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, glassShininess);

    glColor4f(0.5, 0.5, 1.0, 0.5);

    glutSolidSphere(0.5, 200, 200);

    y_offset += y_speed;
    if (fabs(y_offset) > 0.5)
    {
        y_speed *= -1;
    }

    z_offset += z_speed;
    if (fabs(z_offset) > 10.0)
    {
        // z_speed *= -1;
        return;
    }

    glutSwapBuffers();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        cerr << "OpenGL error: " << gluErrorString(error) << endl;
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle()
{
    angle += 0.5;

    yPos += ySpeed;
    zPos += zSpeed;

    if (yPos > 2.0 || yPos < -2.0)
    {
        ySpeed = -ySpeed;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bouncing Ball");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
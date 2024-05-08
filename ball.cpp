#include <GL/glut.h>
#include <sndfile.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

#define CHUNK_SIZE 1024 // Adjust the chunk size as needed
#define PI 3.14159265

vector<float> audioData; // Vector to store audio data

GLfloat glassSpecular[] = {1.0, 1.0, 1.0, 1.0}; // Specular color
GLfloat glassShininess[] = {100.0};             // Shininess

// Function to read audio file and extract waveform data
void readAudio(const char *filename)
{
    SNDFILE *file;
    SF_INFO info;
    file = sf_open(filename, SFM_READ, &info);
    if (!file)
    {
        cerr << "Error: Couldn't open audio file" << endl;
        exit(-1);
    }

    float buffer[CHUNK_SIZE];
    while (true)
    {
        int count = sf_read_float(file, buffer, CHUNK_SIZE);
        if (count == 0)
            break;
        audioData.insert(audioData.end(), buffer, buffer + count);
    }

    sf_close(file);
}

/////////////////////// DRAWing part //////////////////////////

void drawSoundWaves(int start, int end)
{
    glLineWidth(5.0);

    float waveSpacing = 2.0f * PI / (end - start);
    float radius = 0.5f;
    glBegin(GL_LINES);
    for (int i = start; i < end; ++i)
    {

        float angle1 = (i - start) * waveSpacing;
        float angle2 = (i + 1 - start) * waveSpacing;

        float x1 = radius * cos(angle1);
        float y1 = radius * sin(angle1);
        float x2 = radius * cos(angle2);
        float y2 = radius * sin(angle2);

        float x11 = radius * 0.5 * cos(angle1);
        float y11 = radius * 0.5 * sin(angle1);
        float x22 = radius * 0.5 * cos(angle2);
        float y22 = radius * 0.5 * sin(angle2);

        float x13 = radius * 0.75 * cos(angle1);
        float y13 = radius * 0.75 * sin(angle1);
        float x23 = radius * 0.75 * cos(angle2);
        float y23 = radius * 0.75 * sin(angle2);

        float waveMagnitude1 = audioData[i] * 0.1f;     // Adjust the scaling factor as needed
        float waveMagnitude2 = audioData[i + 1] * 0.1f; // Adjust the scaling factor as needed

        glColor3f(1, 0.06, 0.9412);
        glVertex2f(x1 + waveMagnitude1 * cos(angle1), y1 + waveMagnitude1 * sin(angle1));
        glVertex2f(x2 + waveMagnitude2 * cos(angle2), y2 + waveMagnitude2 * sin(angle2));

        glColor3f(1, 1, 1);
        glVertex2f(x11 + waveMagnitude1 * cos(angle1), y11 + waveMagnitude1 * sin(angle1));
        glVertex2f(x22 + waveMagnitude2 * cos(angle2), y22 + waveMagnitude2 * sin(angle2));

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(x13 + waveMagnitude1 * cos(angle1), y13 + waveMagnitude1 * sin(angle1));
        glVertex2f(x23 + waveMagnitude2 * cos(angle2), y23 + waveMagnitude2 * sin(angle2));
    }

    glEnd();
}

// OpenGL display callback function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static int currentChunk = 0;

    glDisable(GL_LIGHTING);

    // Draw sound waves with default material properties
    drawSoundWaves(currentChunk, currentChunk + CHUNK_SIZE);

    // Set material properties for the sphere
    glEnable(GL_LIGHTING);
    GLfloat lightPosition[] = {0.0, 0.0, 10.0, 1.0}; // Position of the light source
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glMaterialfv(GL_FRONT, GL_SPECULAR, glassSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, glassShininess);
    glColor4f(0.5, 0.5, 1.0, 0.5); // Light blue color with transparency

    // Draw the sphere
    glutSolidSphere(0.1, 20, 20);

    currentChunk += CHUNK_SIZE;
    if (currentChunk >= audioData.size())
    {
        exit(0);
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    // Update viewport and projection matrix
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f); // Perspective projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, -1.0, 1.0, // eye position
              0.0, 0.0, 0.0,  // look-at position
              0.0, 1.0, 0.0); // up direction
}

void update(int value)
{
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("StarWars tune waves");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    readAudio("audio.wav");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
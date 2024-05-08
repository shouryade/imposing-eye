
#include <GL/glut.h>
#include <iostream>
using namespace std;

// Constants for controls
float cameraZ = 0.0f;
float zoomFactor = 1.0f;                               // Initial zoom factor
GLuint textureID1, textureID2, textureID3, textureID4; // Texture IDs for all images
int imageWidth1, imageHeight1, imageChannels1;         // Image dimensions and channels for the first image
int imageWidth2, imageHeight2, imageChannels2;         // Image dimensions and channels for the second image
int imageWidth3, imageHeight3, imageChannels3;         // Image dimensions and channels for the third image
int imageWidth4, imageHeight4, imageChannels4;         // Image dimensions and channels for the fourth image
GLuint backgroundTextureID;                            // Texture ID for the background image
int imageWidth, imageHeight, imageChannels;            // Image dimensions and channels for the background image

void initPuzzle()
{
    // Texture 1
    glGenTextures(1, &textureID1);
    glBindTexture(GL_TEXTURE_2D, textureID1);
    unsigned char *image1 = stbi_load("assets/view2.png", &imageWidth1, &imageHeight1, &imageChannels1, STBI_rgb_alpha);
    if (image1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth1, imageHeight1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        cerr << "Failed to load texture 1" << endl;
    }
    stbi_image_free(image1);

    glGenTextures(1, &textureID2);
    glBindTexture(GL_TEXTURE_2D, textureID2);
    unsigned char *image2 = stbi_load("assets/view3.png", &imageWidth2, &imageHeight2, &imageChannels2, STBI_rgb_alpha);
    if (image2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth2, imageHeight2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        cerr << "Failed to load texture 2" << endl;
    }
    stbi_image_free(image2);

    glGenTextures(1, &textureID3);
    glBindTexture(GL_TEXTURE_2D, textureID3);
    unsigned char *image3 = stbi_load("assets/view4.png", &imageWidth3, &imageHeight3, &imageChannels3, STBI_rgb_alpha);
    if (image3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth3, imageHeight3, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        cerr << "Failed to load texture 3" << endl;
    }
    stbi_image_free(image3);

    glGenTextures(1, &textureID4);
    glBindTexture(GL_TEXTURE_2D, textureID4);
    unsigned char *image4 = stbi_load("assets/view5.png", &imageWidth4, &imageHeight4, &imageChannels4, STBI_rgb_alpha);
    if (image4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth4, imageHeight4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        cerr << "Failed to load texture 4" << endl;
    }
    stbi_image_free(image4);

    glGenTextures(1, &backgroundTextureID);
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    unsigned char *backgroundImage = stbi_load("assets/work.jpg", &imageWidth, &imageHeight, &imageChannels, STBI_rgb_alpha);
    if (backgroundImage)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundImage);
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

void displayPuzzle()
{
    float zoomedCameraZ = cameraZ * zoomFactor;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, zoomedCameraZ);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom left
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f); // Bottom right
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f); // Top right
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f); // Top left
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix(); // Restore the previous modelview matrix

    // Draw images
    glEnable(GL_TEXTURE_2D);
    for (float z = -0.25f; z >= -1.0f; z -= 0.25f)
    {
        glBindTexture(GL_TEXTURE_2D, textureID1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.5f, 0.5f, z);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textureID2);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, z - 0.25f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, z - 0.25f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, z - 0.25f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.5f, 0.5f, z - 0.25f);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, textureID3);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, z - 0.5f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, z - 0.5f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, z - 0.5f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.5f, 0.5f, z - 0.5f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, textureID4);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, z - 0.75f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, z - 0.75f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f, 0.5f, z - 0.75f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.5f, 0.5f, z - 0.75f);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void reshapePuzzle(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void updatePuzzle(int value)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cameraZ += 0.01f; // Increment camera Z position for zoom in
    zoomFactor += 0.001f;
    glutPostRedisplay();
    glutTimerFunc(50, updatePuzzle, 0);
}

class Scene;
class PuzzleScene : public Scene
{
public:
    void initialize()
    {
        initPuzzle();
        reshapePuzzle(800, 600); // Pass the window dimensions
    }
    PuzzleScene(int id, float startTime, float endTime) : Scene(id, startTime, endTime) {}
    void render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        initialize();
        updatePuzzle(0);
        displayPuzzle();
    }
};
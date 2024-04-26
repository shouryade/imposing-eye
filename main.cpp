#include <string>
#include <iostream>
#include <scenes/Scene.h>
using namespace std;
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"
#include <GL/glut.h>

time_t programStartTime = time(nullptr);

class ImageScene : public Scene
{
public:
    ImageScene(int id, time_t startTime, time_t endTime, const string &imagePath)
        : Scene(id, startTime, endTime), imagePath(imagePath), textureID(0), zoomFactor(1.0f), rotationAngle(0.0f)
    {
        loadImageTexture();
    }

    ~ImageScene()
    {
        glDeleteTextures(1, &textureID);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
        renderTextureQuad();
        updateAnimation();
    }

private:
    string imagePath;
    GLuint textureID;
    float zoomFactor;
    float rotationAngle;

    void loadImageTexture()
    {
        int width, height, channels;
        unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);

        if (data)
        {
            GLenum format;
            switch (channels)
            {
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                cerr << "Unsupported image format: " << channels << " channels" << endl;
                stbi_image_free(data);
                return;
            }

            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            cerr << "Failed to load texture: " << imagePath << endl;
        }
    }

    void renderTextureQuad()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-1.0f * zoomFactor, -1.0f * zoomFactor);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(1.0f * zoomFactor, -1.0f * zoomFactor);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(1.0f * zoomFactor, 1.0f * zoomFactor);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-1.0f * zoomFactor, 1.0f * zoomFactor);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    void updateAnimation()
    {
        rotationAngle += 1.0f;
        zoomFactor += 0.01f;

        if (zoomFactor > 2.0f)
            zoomFactor = 1.0f;
    }
};

static vector<Scene *> scenesRef; // Global variable to store the scenes reference

void renderSceneSequence(const vector<Scene *> &scenes);
static void renderTimerCallback(int);
static void displayCallback();

void renderSceneSequence(const vector<Scene *> &scenes)
{
    time_t currentTime = time(nullptr);
    currentTime -= programStartTime;

    for (const auto &scene : scenes)
    {
        if (scene->getStartTime() <= currentTime && currentTime < scene->getEndTime())
        {

            scene->render();
            break;
        }
    }

    glutSwapBuffers();
    glutTimerFunc(200, renderTimerCallback, 0);
}

static void renderTimerCallback(int)
{
    renderSceneSequence(scenesRef);
}

static void displayCallback()
{
    renderSceneSequence(scenesRef);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animation");

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black

    vector<Scene *> scenes = {
        new ImageScene(2, 0.0, 1.0, "assets/stairs.png"),
        new ImageScene(3, 1.0, 12.0, "assets/stairs.png"),
    };

    scenesRef = scenes;

    glutDisplayFunc(displayCallback);
    displayCallback();

    glutMainLoop();

    // destructor doesn't get called though
    for (auto scene : scenes)
    {
        delete scene;
    }

    return 0;
}
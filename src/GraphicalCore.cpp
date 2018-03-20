//
// Created by edai on 20/03/18.
//

#include <StarEngine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;

void GraphicalCore::Init()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void GraphicalCore::Run(int ac, char **av, Options *options)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(options->width, options->height);
    glutCreateWindow(options->window_name.c_str());
    Init();

    glutIdleFunc(StarEngine::_Update);
    glutKeyboardFunc(GraphicalCore::_KeyboardHandle);
    glutMainLoop();
}

void GraphicalCore::UpdateGl()
{
    glutSwapBuffers();
    glutPostRedisplay();
}

void GraphicalCore::KeyboardHandle(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q' :
        case 27:
            glutLeaveMainLoop();
            break;
        default:
            return;
    }
}


GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;
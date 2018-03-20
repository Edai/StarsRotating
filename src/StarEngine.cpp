//
// Created by edai on 20/03/18.
//

#include <sstream>
#include <random>
#include "StarEngine.hpp"

StarEngine *StarEngine::instance = nullptr;

StarEngine::StarEngine()
{
    starTexture = SOIL_load_OGL_texture(STAR_PATH, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                        SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    glBindTexture(GL_TEXTURE_2D, starTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
    InitStars();
}

StarEngine::~StarEngine()
{
}

void StarEngine::InitStars()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> color_dis(0.2, 1);
    std::uniform_real_distribution<> positionX_dis(0, glutGet(GLUT_WINDOW_WIDTH));
    std::uniform_real_distribution<> positionY_dis(0, glutGet(GLUT_WINDOW_HEIGHT));

    stars = new std::list<Star>();
    for (int i = 0; i < NUMBER_STAR; i++)
    {
        Star &s = *(new Star());
        s.color = glm::vec3(color_dis(gen), color_dis(gen), color_dis(gen));
        s.position = glm::vec2(positionX_dis(gen), positionY_dis(gen));
        stars->push_back(s);
    }
}

void StarEngine::DrawStar(Star &s)
{
    glBegin(GL_QUADS);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(s.color.x, s.color.y, s.color.z);
    glTexCoord2i(0, 1);
    glVertex2f(s.position.x - STAR_SIZE / 2, s.position.y + STAR_SIZE / 2);
    glTexCoord2i(1, 1);
    glVertex2f(s.position.x + STAR_SIZE / 2, s.position.y + STAR_SIZE / 2);
    glTexCoord2i(1, 0);
    glVertex2f(s.position.x + STAR_SIZE / 2, s.position.y - STAR_SIZE / 2);
    glTexCoord2i(0, 0);
    glVertex2f(s.position.x - STAR_SIZE / 2, s.position.y - STAR_SIZE / 2);
    glEnd();
}

void StarEngine::SpiralEffectCalculate()
{

}

void StarEngine::Update()
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    SpiralEffectCalculate();
    for (auto &star : *stars)
        DrawStar(star);
    glPopMatrix();
}
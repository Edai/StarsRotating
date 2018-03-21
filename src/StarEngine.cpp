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
    InitStars();
}

StarEngine::~StarEngine()
{
}

void StarEngine::InitStars()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> color_dis(0.1, 0.9);
    float num_segments = 64;
    float r = 0.8f;

    stars = new std::list<Star>();
    for (int i = 0; i < num_segments; i += 1)
    {
        Star &s = *(new Star());
        s.color = glm::vec3(color_dis(gen), color_dis(gen), color_dis(gen));
        float theta = 6.0f * M_PI * (i / num_segments);
        s.position = glm::vec2((r / num_segments) * i * cosf(theta), (r / num_segments) * i * sinf(theta));
        stars->push_back(s);
    }
    std::cout << stars->size() << std::endl;
}

void StarEngine::DrawStar(Star &s)
{
    float size = STAR_SIZE;

    glColor3f(s.color.x, s.color.y, s.color.z);
    glTexCoord2i(0, 1);
    glVertex2f(s.position.x - size, s.position.y + size);
    glTexCoord2i(1, 1);
    glVertex2f(s.position.x + size, s.position.y + size);
    glTexCoord2i(1, 0);
    glVertex2f(s.position.x + size, s.position.y - size);
    glTexCoord2i(0, 0);
    glVertex2f(s.position.x - size, s.position.y - size);
}

void StarEngine::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(GraphicalCore::Rotation, 0, 0, 1);

    glBegin(GL_QUADS);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    for (auto star = stars->begin(); star != stars->end(); star++)
//    {
//        auto s = star;
//        star++;
//        if (star != stars->end())
//            s->color = star->color;
//        else
//            s->color = stars->begin()->color;
        DrawStar(*star);
    // }
    glEnd();
    glPopMatrix();
}
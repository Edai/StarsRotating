//
// Created by edai on 20/03/18.
//

#include <sstream>
#include <random>
#include "StarEngine.hpp"

StarEngine *StarEngine::instance = nullptr;

StarEngine::StarEngine()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    std::uniform_real_distribution<> color_dis(0.4, 1.0);
    float nb = 1024;
    float r = 1.15f;

    starPos = *(new std::vector<glm::vec2>());
    stars = *(new std::vector<Star>());
    for (int i = 0; i < nb; i += 1)
    {
        float theta = 6.0f * (float) M_PI * i / nb;
        starPos.emplace_back(glm::vec2(r / nb * i * cosf(theta),
                                       r / nb * i * sinf(theta)));
    }
    for (int i = 0; i < nb; i++)
    {
        Star &s = *(new Star());
        s.pos = i * 20.0f;
        s.color = glm::vec3(color_dis(gen), color_dis(gen), color_dis(gen));
        stars.emplace_back(s);
    }
}

void StarEngine::DrawStar(glm::vec2 &s, glm::highp_vec3 color)
{
    float size = STAR_SIZE;

    glColor4f(color.x, color.y, color.z, 1.0f);
    glTexCoord2i(0, 1);
    glVertex2f(s.x - size, s.y + size);
    glTexCoord2i(1, 1);
    glVertex2f(s.x + size, s.y + size);
    glTexCoord2i(1, 0);
    glVertex2f(s.x + size, s.y - size);
    glTexCoord2i(0, 0);
    glVertex2f(s.x - size, s.y - size);
}

void StarEngine::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    for (auto s = stars.end(); s != stars.begin(); s--)
    {
        DrawStar(starPos[s->pos], s->color);
        s->pos >= starPos.size() ? s->pos = 0 : s->pos++;
    }
    glEnd();
    glPopMatrix();
}
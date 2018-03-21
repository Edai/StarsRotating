//
// Created by edai on 20/03/18.
//

#ifndef ASSIGNMENT2_STARENGINE_HPP
#define ASSIGNMENT2_STARENGINE_HPP

#include "GraphicalCore.hpp"
#include <glm/glm.hpp>
#include <list>

#define STAR_PATH "star.bmp"
#define STAR_SIZE 0.05f

struct Star
{
    glm::vec2 position;
    glm::vec3 color;
};

class StarEngine
{
public:
    StarEngine();
    ~StarEngine();

    static void _Update()
    {
        Instance()->Update();
        GraphicalCore::UpdateGl();
    }

private:
    void Update();

    void DrawStar(Star &s);

    void InitStars();

    void SpiralEffectCalculate();

    GLuint starTexture;
    std::list<Star> *stars;

#pragma SINGLETON
private:
    static StarEngine* instance;

public:
    static StarEngine* Instance()
    {
        if (instance == nullptr)
        {
            instance = new StarEngine();
        }
        return instance;
    }

#pragma END SINGLETON

};


#endif //ASSIGNMENT2_STARENGINE_HPP

//
// Created by edai on 20/03/18.
//

#ifndef ASSIGNMENT2_STARENGINE_HPP
#define ASSIGNMENT2_STARENGINE_HPP

#include "GraphicalCore.hpp"
#include <glm/glm.hpp>
#include <vector>

#define STAR_PATH "star.png"
#define STAR_SIZE 0.15f

struct Star
{
    float pos;
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

    int oldTimeSinceStart = 0;

private:
    void Update();

    void DrawStar(glm::vec2 &s, glm::highp_vec3 color);

    void InitStars();

    GLuint starTexture;
    std::vector<Star> stars;
    std::vector<glm::vec2> starPos;

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

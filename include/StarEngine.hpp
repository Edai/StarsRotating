//
// Created by edai on 20/03/18.
//

#ifndef ASSIGNMENT2_STARENGINE_HPP
#define ASSIGNMENT2_STARENGINE_HPP

#include "GraphicalCore.hpp"

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
#pragma
};

#endif //ASSIGNMENT2_STARENGINE_HPP

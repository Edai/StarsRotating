//
// Created by edai on 19/03/18.
//

#ifndef WEEK04_APPLICATION_HPP
#define WEEK04_APPLICATION_HPP

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <unistd.h>
#include <cstdlib>
#include <getopt.h>
#include <string>

#define DEFAULT_WIDTH 1440
#define DEFAULT_HEIGHT 960
#define WINDOW_TITLE "Assignment 2"

struct Options
{
    std::string window_name;
    int         width;
    int         height;

public:
    Options()
    {
        width = DEFAULT_WIDTH;
        height = DEFAULT_HEIGHT;
    }
};

class Application
{
public:
    static bool Parse(Options *, int, char**);
    static void Start(int, char **);
    static void Update();
    static void Init();
    static void KeyboardHandle(unsigned char, int, int);

protected:
    Application();
    ~Application();
//
//    #pragma SINGLETON
//public:
//    static Application& Instance() {
//        static Application myInstance;
//        return myInstance;
//    }
//    Application(Application const&) = delete;             // Copy construct
//    Application(Application&&) = delete;                  // Move construct
//    Application& operator=(Application const&) = delete;  // Copy assign
//    Application& operator=(Application &&) = delete;      // Move assign
//#pragma
};


#endif //WEEK04_APPLICATION_HPP

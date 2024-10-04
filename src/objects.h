#pragma once
#include <raylib.h>

struct Walls{

    float recWidth = 5;
    float recHeight = 100;


    float cpuRecX = GetScreenWidth()/2.0f + 250.0f;
    float playerRecX = GetScreenWidth()/2.0f - 275.0f;
    float RecY = GetScreenHeight()/2.0f - 50.0f;

    float topRec = RecY + recWidth;

    int Score = 0;
    
    
};

struct Ball{

    Vector2 Position = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f }; // Initital/Current ball position
    Vector2 Speed = { -5.0f, -4.0f }; // How many times going to move x, y axis per frame
    int Radius = 20; // ball radius

};

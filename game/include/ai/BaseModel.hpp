#pragma once

#include <iostream>
#include <string>

class BaseModel
{

public:
    virtual void save(int stage, int current) = 0;
    virtual void load(std::string file) = 0;

};
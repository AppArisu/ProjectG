#pragma once
#include <vector>
#include <string>

#define maxs 10

struct Parameter
{
    int Id = 0;
    char Type[10] = {};
    char Name[24] = {};
    int Price = 0;
    char Comment[256] = {};
};

class Item
{
public:
    Item(std::string textName);
    ~Item() {}

    Parameter* itemParam(int Id)
    {
        return &this->items[Id];
    }

private:
    Parameter items[maxs];

    char dummy[100] = {};
};
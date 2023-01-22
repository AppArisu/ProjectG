#include <fstream>
#include "Item.h"

Item::Item(std::string textName)
{
    std::fstream ifs(textName);

    if (!ifs.is_open())
    {
        _ASSERT(ifs);
    }
    else
    {
        ifs.getline(dummy, 100);

        for (int i = 0; i < maxs; i++)
        {
            if (ifs.eof()) break;
            ifs >> items[i].Id >> items[i].Type >> items[i].Name >> items[i].Price >> items[i].Comment;
        }
    }
}
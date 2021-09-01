#ifndef BATTLEFIELD_H_INCLUDED
#define BATTLEFIELD_H_INCLUDED

#include "init.h"

class Battlefield
{
    private:

        //Content
        BITMAP* fieldlines_image;


    public:
        Battlefield() {}
        ~Battlefield() {}
        void LoadContent();
        void UnloadContent();
};

#endif

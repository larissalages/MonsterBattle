#ifndef BATTLELOG_H_INCLUDED
#define BATTLELOG_H_INCLUDED

#include "init.h"

class Battlelog
{
    private:
        std::vector<std::string> messages;
        int max_messages;

    public:
        Battlelog();
        void PushMessage(std::string message);
        void PushMessage(char message[]);
        void Clear();
        void Draw();
};

#endif

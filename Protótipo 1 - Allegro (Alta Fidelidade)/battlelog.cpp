#include "battlelog.h"

Battlelog::Battlelog()
{
    max_messages = 9;
}

void Battlelog::PushMessage(std::string message)
{
    if(messages.size() == max_messages)
        Clear();

    messages.push_back(message);
}

void Battlelog::PushMessage(char message[])
{
    if(messages.size() == max_messages)
        Clear();

    std::string new_message(message);
    messages.push_back(new_message);
}

void Battlelog::Clear()
{
    messages.clear();
}

void Battlelog::Draw()
{
    int x = 440, y = 15;

    for(int i = 0; i < messages.size(); i++)
        textprintf_ex(buffer, font_impact, x, y+17*i, makecol(255,255,255), -1, messages[i].c_str());
}

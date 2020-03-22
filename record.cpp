#include "record.h"

record::record(unsigned long x, std::vector <std::pair<std::string, std::string> > d) : own_id(x), data(d)
{   }

heading record::get_title()
{
    heading buff;
    buff.id = own_id;
    bool check = false;
    for (auto x : data)
    {
        if (x.first == "name")
        {
            buff.name = x.second;
            check = true;
            break;
        }
    }
    if (check == false)
        buff.name = "null";
    return buff;
}

unsigned long record::get_id()
{
    return own_id;
}

std::vector <std::pair <std::string, std::string> > record::get_fields()
{
    return data;
}

std::vector <std::string> record::get_names_of_fields()
{
    std::vector <std::string> buff;
    for (auto x : data)
    {
        buff.push_back(x.first);
    }
    return buff;
}

void record::save(std::ofstream* out, std::vector <std::string> table_title)
{
    *out << own_id << ';';
    for (auto x : table_title)
    {
        bool check = false;
        for (auto y : data)
        {
            if (y.first == x)
            {
                check = true;
                *out << y.second << ';';
                break;
            }
        }
        if (check == false)
            *out << ';';
    }
    *out << std::endl;
    return;
}
#pragma once
#include <vector>
#include <utility>
#include <string>
#include <fstream>

struct heading
{
    unsigned long id;
    std::string name;
};

class record
{
        private:
    unsigned long own_id;
    std::vector <std::pair<std::string, std::string> > data;
    //methods
        public:
    record();
    record(unsigned long, std::vector <std::pair<std::string, std::string> >);
    unsigned long get_id();
    heading get_title();
    std::vector <std::pair <std::string, std::string> > get_fields();
    void save(std::ofstream*, std::vector <std::string>);
    std::vector <std::string> get_names_of_fields();
};
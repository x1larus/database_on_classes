#pragma once
#include "record.h"
#include <vector>
#include <string>
#include <iostream>

class data_base
{
        private:
    unsigned long global_id;
    std::string password;
    std::vector <std::string> required_fields;
    std::vector <record> list;
    //methods
    unsigned long get_unigue_id();
        public:
    data_base();
    bool log_in(std::string);
    std::vector<std::string> return_required_fields();
    void push_new_record(std::vector<std::pair<std::string, std::string> >);
    std::vector <heading> get_list_of_records();
    bool remove_record(unsigned long);
    record* get_record(unsigned long);
    void save_in_file(std::string);
    void load(std::ifstream*);
};
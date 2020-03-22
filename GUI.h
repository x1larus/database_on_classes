#pragma once
#include "data_base.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

const std::string file_extension = ".csv";

void cherta();

class GUI
{
        private:
    data_base base;
    //methods
    void menu();
    void create_new_record();
    void get_list_of_records();
    void remove_record();
    void get_record();
    void save();
    void load();
        public:
    void login();
};
#include "data_base.h"

data_base::data_base()
{
    required_fields = {"name"};
    global_id = 0;
    password = "admin";
}

bool data_base::log_in(std::string pswd)
{
    if (password == pswd)
        return true;
    else
        return false;
}

std::vector<std::string> data_base::return_required_fields()
{
    return required_fields;
}

unsigned long data_base::get_unigue_id()
{
    return global_id++;
}

void data_base::push_new_record(std::vector<std::pair<std::string, std::string> > new_data)
{
    record curr(get_unigue_id(), new_data);
    list.push_back(curr);
}

std::vector <heading> data_base::get_list_of_records()
{
    std::vector <heading> buff;
    for (auto x : list)
    {
        buff.push_back(x.get_title());
    }
    return buff;
}

bool data_base::remove_record(unsigned long id)
{
    for (unsigned long i = 0; i < list.size(); i++)
    {
        if (list[i].get_id() == id)
        {
            list.erase(list.begin() + i);
            return true;
        }
    }
    return false;
}

record* data_base::get_record(unsigned long id)
{
    for (unsigned long i = 0; i < list.size(); i++)
    {
        if (list[i].get_id() == id)
            return &list[i];
    }
    return nullptr;
}

void data_base::save_in_file(std::string filename)
{
    std::vector <std::string> table_title = {"name"};
    for (auto curr_rec : list)
    {
        std::vector <std::string> curr_names = curr_rec.get_names_of_fields();
        for (auto i : curr_names)
        {
            bool check = false;
            for (auto j : table_title)
            {
                if (i == j)
                {
                    check = true;
                    break;
                }
            }
            if (check == false)
                table_title.push_back(i);
        }
    }
    //write in file
    std::ofstream out(filename);
    out << "ID;";
    for (auto x : table_title)
        out << x << ';';
    out << std::endl;
    for (auto x : list)
        x.save(&out, table_title);
}

void data_base::load(std::ifstream* in)
{
    std::vector <std::string> table_title;
    char buff[100000];
    in->getline(buff, 100000);
    std::string title = buff;
    std::string title_buf;
    for (long long unsigned int i = 0; i < title.size(); i++)
    {
        if (title[i] == ';')
        {
            table_title.push_back(title_buf);
            title_buf.erase();
            continue;
        }
        title_buf += title[i];
    }
    //
    unsigned long max = 0;
    while (!in->eof())
    {
        in->getline(buff, 100000);
        std::string line = buff;
        if (line.empty())
        {
            break;
        }
        int pos = 0;
        std::string str_id;
        while (true)
        {
            if (line[pos] == ';')
            {
                pos++;
                break;
            }
            str_id += line[pos++];
        }
        unsigned long id = std::stoul(str_id);
        if (id > max)
            max = id;
        //
        std::string val_buf;
        val_buf.erase();
        int index = 1;
        std::vector <std::pair<std::string, std::string> > data;
        for (long long unsigned int i = pos; i < line.size(); i++)
        {
            if (line[i] == ';')
            {
                if (val_buf.empty())
                {
                    index++;
                    continue;
                }
                std::pair <std::string, std::string> temp_pair;
                temp_pair.first = table_title[index];
                temp_pair.second = val_buf;
                data.push_back(temp_pair);
                index++;
                val_buf.erase();
                continue;
            }
            //
            val_buf += line[i];
        }
        //
        record temp_rec(id, data);
        list.push_back(temp_rec);
    }
    global_id = max + 1;
    return;
}
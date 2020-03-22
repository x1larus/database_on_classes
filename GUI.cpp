#include "GUI.h"

void GUI::menu()
{
    cherta();
    std::cout << "Enter choice : ";
    int choice;
    std::cin >> choice;
    cherta();
    switch(choice)
    {
        case 0:
            return;
        case 1:
            create_new_record();
            break;
        case 2:
            get_list_of_records();
            break;
        case 3:
            get_record();
            break;
        case 4:
            remove_record();
            break;
        case 5:
            save();
            break;
        default:
            std::cout << "Incorrect input\n";
            break;
    }
    menu();
}

void GUI::login()
{
    std::cout << "Password : ";
    std::string passwd;
    std::cin >> passwd;
    if (base.log_in(passwd) == false)
    {
        std::cout << "Login incorrect. Access denied.\n";
        exit(0);
    }
    std::cout << "Login succesfully\n";
    cherta();
    std::cout << "Load database? (yes/no) : ";
    std::string answ;
    std::cin >> answ;
    if (answ == "yes")
        load();
    cherta();
    std::cout << "0 - exit\n1 - create_new\n2 - get_list\n3 - get_record\n4 - remove_record\n5 - save as .csv file\n";
    menu();
}

void GUI::create_new_record()
{
    std::vector<std::string> required_fields = base.return_required_fields();
    std::vector<std::pair<std::string, std::string> > temp_record;
    //filling req_fields
    for (auto x : required_fields)
    {
        std::pair <std::string, std::string> buff;
        buff.first = x;
        std::cout << x << " : ";
        std::cin >> buff.second;
        temp_record.push_back(buff);
    }
    //filling additional fields
    std::cout << "Would you like to add more fields? (yes/no) : ";
    std::string answ;
    std::cin >> answ;
    if (answ == "yes")
    {
        while(true)
        {
            std::pair<std::string, std::string> buff;
            std::cout << "name : ";
            std::cin >> buff.first;
            std::cout << "value : ";
            std::cin >> buff.second;
            temp_record.push_back(buff);
            //
            std::cout << "More? (yes/no) : ";
            std::string more_ans;
            std::cin >> more_ans;
            if (more_ans != "yes")
                break;
        }
    }
    //pushing into base
    base.push_new_record(temp_record);
    std::cout << "Succesfully added\n";
    return;
}

void GUI::get_list_of_records()
{
    std::vector <heading> headings = base.get_list_of_records();
    for (auto x : headings)
    {
        std::cout << "ID : " << x.id << "; name : " << x.name << std::endl;
    }
    return;
}

void GUI::remove_record()
{
    std::cout << "Enter ID of record which will be deleted : ";
    unsigned long id;
    std::cin >> id;
    bool check = base.remove_record(id);
    if (check == true)
        std::cout << "Succesfully removed\n";
    else
        std::cout << "Record with this id doesn't exist. KERNEL PANIC!!!\n";
    return;
}

void GUI::get_record()
{

    std::cout << "Enter ID of record : ";
    unsigned long id;
    std::cin >> id;
    record* curr_rec = base.get_record(id);
    if (curr_rec == nullptr)
    {
        std::cout << "Record with this id doesn't exist. KERNEL PANIC!!!\n";
        return;
    }
    std::vector <std::pair <std::string, std::string> > data = curr_rec->get_fields();
    std::cout << "ID : " << curr_rec->get_id() << '\n';
    for (auto x : data)
    {
        std::cout << x.first << " : " << x.second << "\n";
    }
    return;
}

void GUI::save()
{
    std::cout << "Write name of file without .csv : ";
    std::string filename;
    std::cin >> filename;
    filename = filename + file_extension;
    base.save_in_file(filename);
    return;
}

void GUI::load()
{
    cherta();
    std::cout << "Enter filename without .csv : ";
    std::string filename;
    std::cin >> filename;
    filename = filename + file_extension;
    std::ifstream in(filename);
    if (in.eof())
    {
        std::cout << "Empty file. KERNEL PANIC!!!\n";
        in.close();
        load();
    }
    base.load(&in);
}

void cherta()
{
    std::cout << "-----------------------------------------------\n";
    return;
}
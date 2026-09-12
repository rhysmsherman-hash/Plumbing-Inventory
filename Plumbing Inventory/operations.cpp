#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#include "operations.hpp"

//print
void print(std::map<std::string, std::map<std::string, std::string>> inventory)
{
    std::cout << '\n';
    for(const auto& [m, ps] : inventory) //measurements
    {
        for(const auto& [p, c] : ps)
        {
            std::cout << m << ", " << p << ", " << c << '\n';
        }
    }
}

//add
std::map<std::string, std::map<std::string, std::string>> add(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name)
{
    std::string measurement {};
    std::cout << "\nEnter measurement:\n";
    std::cin >> measurement;
    std::cin.ignore();
    
    std::string piece {};
    std::cout << "Enter piece:\n";
    std::getline(std::cin, piece);// getline to read amount properly
    
    
    std::string amount {};
    std::cout << "Enter amount:\n";
    std::cin >> amount;
    std::cin.ignore();
    
    try {

        std::string count {inventory[measurement][piece]};
        inventory[measurement][piece] = std::to_string(std::stoi(count) + std::stoi(amount));
         
         std::ofstream writer(file_name);
         for(const auto& [m, ps] : inventory) //measurements
         {
             for(const auto& [p, c] : ps)
             {
                 writer << m << ", " << p << ", " << c << ";" << '\n';
             }
         }
        writer.close();
        
    } catch (...) {//catch(...) = catch-all
        std::cerr << "No such entry exists...\n";
        return inventory;
    }
    
    return inventory;
}

//subtract 3
std::map<std::string, std::map<std::string, std::string>> subtract(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name)
{
    std::string measurement {};
    std::cout << "\nEnter measurement:\n";
    std::cin >> measurement;
    std::cin.ignore();
    
    std::string piece {};
    std::cout << "Enter piece:\n";
    std::getline(std::cin, piece);// getline to read amount properly
    
    
    std::string amount {};
    std::cout << "Enter amount:\n";
    std::cin >> amount;
    std::cin.ignore();
    
    try {
    
        std::string count {inventory[measurement][piece]};
        if(std::stoi(count) - std::stoi(amount) < 0)
        {
            inventory[measurement][piece] = "0";
            std::cout << "This piece now has a count of zero!\nPlease remove if necessary...\n";
        }
        else
        {
            inventory[measurement][piece] = std::to_string(std::stoi(count) - std::stoi(amount));
            if(inventory[measurement][piece] == "0")
            {
                std::cout << "This piece now has a count of zero!\nPlease remove if necessary...\n";
            }
        }
        

//        edit file
//        overwrite file with map updated info
         
         std::ofstream writer(file_name);
         for(const auto& [m, ps] : inventory) //measurements
         {
             for(const auto& [p, c] : ps)
             {
                 writer << m << ", " << p << ", " << c << ";" << '\n';
             }
         }
        writer.close();
        
    } catch (...) {
        std::cerr << "No such entry exists...\n";
        return inventory;
    }
    
    return inventory;
}

//append 4
std::map<std::string, std::map<std::string, std::string>> append(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name)
{
    std::ofstream writer(file_name, std::ios::app);
    if(writer.is_open())
    {
        bool appending {true};
        //begin adding data
        while(appending)
        {
            //appends "measurement, piece, count\n" to file
            std::string measurement {};
            std::string piece {};
            std::string count {};
            
            std::cout << "\nEnter measurement: \n";
            std::getline(std::cin, measurement);
            writer <<"\n" << measurement << ", ";
            
            std::cout << "Enter piece: \n";
            std::getline(std::cin, piece);
            writer << piece << ", ";
            
            std::cout << "Enter count: \n";
            std::getline(std::cin, count);
            writer << count;
            
            writer << ';';
            
            //asks to continue data writing
            char cont {};
            while(cont != 'y' && cont != 'n')
            {
                std::cout << "Add another entry? y/n \n";
                std::cin >> cont;
                std::cin.ignore();//flush
            }
            if(cont == 'y')
            {
                appending = true;
            }
            else if(cont == 'n')
            {
                appending = false;
            }
        }
    }
    else
    {
        std::cout << "Failed to open inventory...";
    }
    writer.close();
    
    //re-write inventory to match file
    std::ifstream reader(file_name);
    inventory.clear();
    
    std::vector<std::string> measurements{};
    std::vector<std::string> pieces{};
    std::vector<std::string> counts{};
    
    
    std::string line {};
    while(std::getline(reader, line))
    {
        if(line.empty())
        {
            continue;
        }
        std::string entry{};
        int comma_count {};
        std::string measurement{};
        std::string piece{};
        std::string count {};
        //parse line by commas and populate maps
        for(int i {0}; i < static_cast<int>(line.size()); ++i)
        {
            if (line.at(i) != ',' && line.at(i) != ';')
            {
                entry.push_back(line.at(i));
            }
            else if(line.at(i) == ',')
            {
                comma_count += 1;
                if (comma_count == 1)
                {
                    //first comma
                    measurement = entry;
                    measurements.push_back(measurement);
                    entry = "";
                    
                    if(i+2 < static_cast<int>(line.size()))
                    {
                        ++i;
                    }
                    
                }
                else if (comma_count == 2)
                {
                    //second comma
                    piece = entry;
                    pieces.push_back(piece);
                    entry = "";
                    
                    //only first instance of piece in list will be added
                    if(i+2 < static_cast<int>(line.size()))
                    {
                        ++i;
                    }
                }
            }
            else if(line.at(i) == ';')
            {
                //end of line
                count = entry;
                counts.push_back(count);
                entry = "";
                
                inventory[measurement][piece] = count;
            }
                
        }
    }
    return inventory;
}

//remove 5
std::map<std::string, std::map<std::string, std::string>> remove(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name)
{
    bool removal {true};
    while(removal)
    {
        std::string measurement {};
        std::cout << "\nEnter measurement:\n";
        std::cin >> measurement;
        std::cin.ignore();
        
        std::string piece {};
        std::cout << "Enter piece:\n";
        std::getline(std::cin, piece);// getline to read amount properly
        
        inventory[measurement].erase(piece);
        
        
        //update file from inventory
        std::ofstream writer(file_name);
        for(const auto& [m, ps] : inventory) //measurements
        {
            for(const auto& [p, c] : ps)
            {
                writer << m << ", " << p << ", " << c << ";" << '\n';
            }
        }
       writer.close();
        char cont {};
        while(cont != 'y' && cont != 'n')
        {
            std::cout << "Remove another? y/n\n";
            std::cin >> cont;
            std::cin.ignore();
        }
        if(cont == 'y')
        {
            removal = true;
        }
        else if(cont == 'n')
        {
            removal = false;
        }
    }
    
    
    return inventory;
}

//sort 6
void sort(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name)
{
    std::ofstream writer(file_name);
    for(const auto& [m, ps] : inventory) //measurements
    {
        for(const auto& [p, c] : ps)
        {
            writer << m << ", " << p << ", " << c << ";" << '\n';
        }
    }
   writer.close();
}

//get 7
void get(std::map<std::string, std::map<std::string, std::string>> inventory)
{
    std::string measurement {};
    std::cout << "\nEnter measurement:\n";
    std::cin >> measurement;
    std::cin.ignore();
    
    std::string piece {};
    std::cout << "Enter piece:\n";
    std::getline(std::cin, piece);// getline to read amount properly
    
    try {
        std::cout << "Count: " << inventory[measurement][piece] << '\n';
    } catch (...) {
        std::cerr << "Couldn't retrieve count...\n";
    }
}

//set 8
std::map<std::string, std::map<std::string, std::string>> set(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name)
{
    std::string measurement {};
    std::cout << "\nEnter measurement:\n";
    std::cin >> measurement;
    std::cin.ignore();
    
    std::string piece {};
    std::cout << "Enter piece:\n";
    std::getline(std::cin, piece);// getline to read amount properly
    
    std::string count{};
    std::cout << "Enter count to set:\n";
    std::cin >> count;
    std::cin.ignore();
    
    try {
        inventory[measurement][piece] = count;
    } catch (...) {
        std::cerr << "Couldn't set count...\n";
    }
    
    //update file from inventory
    std::ofstream writer(file_name);
    for(const auto& [m, ps] : inventory) //measurements
    {
        for(const auto& [p, c] : ps)
        {
            writer << m << ", " << p << ", " << c << ";" << '\n';
        }
    }
   writer.close();
    
    return inventory;
}

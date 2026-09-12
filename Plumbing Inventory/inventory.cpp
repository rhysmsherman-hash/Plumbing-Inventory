/*
 requires c++17
 compilation key:
 g++ -Wall inventory.cpp operations.cpp -std=c++17
 ./a.out
 enter file name, will add .txt on its own
 */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <print>
#include "operations.hpp"

int main()
{
//    1. Ask to create map or search for file
    std::cout << "\nFormat: Measurement: #\", Piece: item, Count: #\n";
    int choice {};
    while (choice != 1 && choice != 2)
    {
        std::cout << "\nChoose an operation: \n1.Create Inventory \n2.Access Inventory\n\nEnter option: ";
        std::cin >> choice;
    }
    std::string file_name{}; // file_name for future edits
    
    if (choice == 1)
    {
        //    2. if create map create and store to file
        //prompt for file name and open in append mode
        std::string name {};
        std::cout << "\nEnter inventory name: \n";
        std:: cin >> name;
        std::cin.ignore(); // ignores 1 '\n'
        
        name += ".txt";
        file_name = name; // file_name
        std::ofstream writer(name, std::ios::app);
        
        if(writer.is_open()) // begin append
        {
            bool append {true};
            //asks to add data now
            char add {};//begin conditional not in append
            while(add != 'y' && add != 'n')
            {
                std::cout << "\nAppend now? y/n \n";
                std::cin >> add;
                std::cin.ignore();//flush
            }
            if(add == 'y')
            {
                append = true;
            }
            else if(add == 'n')
            {
                append = false;
            }//end conditional not in append
            //begin adding data
            while(append)
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

                //std::cout << std::endl;
                
                writer << ';';
                
                //asks to continue data writing
                char cont {};
                while(cont != 'y' && cont != 'n')
                {
                    std::cout << "\nAdd another entry? y/n \n";
                    std::cin >> cont;
                    std::cin.ignore();//flush
                }
                if(cont == 'y')
                {
                    append = true;
                }
                else if(cont == 'n')
                {
                    append = false;
                }
            }
            writer.close(); // end append
        }
        else
        {
            std::cerr << "\nError opening the inventory." << std::endl;
        }
        
        
    }
    else if (choice == 2)
    {
//        3. if file search file and read to map
        //prompt for file name and open in read mode
        std::string name {};
        std::cout << "\nEnter inventory name: \n";
        std::cin >> name;
        std::cin.ignore();//flush
        name += ".txt";
        file_name = name;
        
        std::ifstream reader(name);
        if(!reader.is_open())
        {
            std::cerr << "\nError Inventory DNE!" << std::endl;
            return 1;
        }
        
        //read to map
        std::map<std::string, std::map<std::string, std::string>> inventory{}; // contains pieces as value
        
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
        //let user choose operations
        /*
         Print function to print map
         Add function to increase count
         Subtract function to decrease count
         Append to add joint / piece
         Remove function to remove joint / piece
         */
        
        //operation loop
        bool operate {true};
        while (operate)
        {
            //get operation
            std::string choice {"0"};
            while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8")
            {
                std::cout << "\nChoose an operation:\n1.Print Inventory\n2.Add to Inventory\n3.Subtract from Inventory\n4.Append to Inventory\n5.Remove from Inventory\n6.Sort Inventory\n7.Get Count from Inventory\n8.Set Count to Inventory\n\nEnter option: ";
                std::cin >> choice;
                std::cin.ignore();
            }
            if(choice == "1")
            {
                //prints inventory
                print(inventory);
            }
            else if(choice == "2")
            {
                //adds amount from piece in inventory and updates file
                inventory = add(inventory, file_name);
            }
            else if(choice == "3")
            {
                //subtracts amount from piece in inventory and updates file
                inventory = subtract(inventory, file_name);
            }
            else if(choice == "4")
            {
                //appends new line to file and adds to inventory
                inventory = append(inventory, file_name);
                sort(inventory, file_name);
            }
            else if(choice == "5")
            {
                inventory = remove(inventory, file_name);
            }
            else if(choice == "6")
            {
                //sorts file by inventory (update)
                sort(inventory, file_name);
            }
            else if(choice == "7")
            {
                //gets count of item in inventory
                get(inventory);
            }
            else if(choice == "8")
            {
                //sets count of an item directly
                inventory = set(inventory, file_name);
            }
            
            //continue operating?
            char cont{};
            while(cont != 'y' && cont != 'n')
            {
                std::cout << "\nContinue? y/n\n";
                std::cin >> cont;
                std::cin.ignore();
            }
            if(cont == 'y')
            {
                operate = true;
            }
            else if(cont == 'n')
            {
                operate = false;
            }
            
            
        }
        
    }
    
    return 0;
}

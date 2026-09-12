#include <map>

#ifndef OPERATIONS_H
#define OPERATIONS_H

//print 1
void print(std::map<std::string, std::map<std::string, std::string>> inventory);

//add 2
std::map<std::string, std::map<std::string, std::string>> add(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name);

//subtract 3
std::map<std::string, std::map<std::string, std::string>> subtract(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name);

//append 4
std::map<std::string, std::map<std::string, std::string>> append(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name);

//remove 5
std::map<std::string, std::map<std::string, std::string>> remove(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name);

//sort 6
void sort(std::map<std::string, std::map<std::string, std::string>> inventory, std::string file_name);

//get 7
void get(std::map<std::string, std::map<std::string, std::string>> inventory);

#endif


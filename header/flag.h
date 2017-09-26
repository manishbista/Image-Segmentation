
/*****************************************************************************
Create a database of plausible command line arguments
Each record in database if a Flag structure initialized to default values
Command line arguments can change default values
Using a dictionary, indexing the database is made easier
*****************************************************************************/

#ifndef FLAG_H
#define FLAG_H

#include <string>
#include <iostream>
#include <vector>

//template <class Type>
struct Flag
{
    std::string label;
    std::string* target;
    std::string info;

    Flag() : label("") {}
    Flag(std::string _label, std::string* _target, std::string _info): label(_label), target(_target), info(_info) {}
    void Display();

};


class FlagUsage
{
  private:
    std::vector<Flag>* flagList;
    char** argv;
    int argc;
    void initializeFlags();

  public:
    FlagUsage(std::vector<Flag>* _flagList, char** _argv, int _argc): flagList(_flagList), argv(_argv), argc(_argc) 
    {
	FlagUsage::initializeFlags();
    }

};


#endif

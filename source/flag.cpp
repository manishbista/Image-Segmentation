
#include "header/flag.h"
#include <map>

//to display contents of Flag
void Flag::Display()
{
   std::cout<<label<<" "<<*target<<" "<<info<<" "<<std::endl;
}


void FlagUsage::initializeFlags()
{
   //flagMap is a dictionary which maps query:command line argument to 
   //appropriate index in database: flagList
   std::map<std::string, int> flagMap;
   flagMap.clear();
   for(int i = 0; i < flagList->size(); i++)
       flagMap[(*flagList)[i].label] = i;

   //change contents of database: flagList based on command line arguments
	//ignore if --help is inferred or no arguments are made
   if(argc > 1 and (std::string(argv[1]) != "--help" and std::string(argv[1]) != "-h"))
   {
		std::string _key;
        int pos;
		//take command line argument in pairs as flag and value
		for(int i = 1; i < argc; i+=2)
		{
			_key = std::string(argv[i]);
			//if flag exists in dictionary and value is given in command line argument, then change value in database:flagList
			if(flagMap.find(_key) != flagMap.end() and argc > i+1)	
			{
			   pos = flagMap[_key];
			   *((*flagList)[pos].target) = std::string(argv[i+1]);		//then change its value
			}
			//else show error
			else
			{
			   std::cout<<" No command line argument named: "<<argv[i]<<" or its value is not passed "<<std::endl;
			   std::cout<<" see --help for details"<<std::endl;
			}
		}
   }
	//arguments from command line, if present, has been noted
}



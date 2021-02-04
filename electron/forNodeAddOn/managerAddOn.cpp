#include "managerAddOn.h"

ManagerAddOn::ManagerAddOn(Callback* callback)
{

}

ManagerAddOn::~ManagerAddOn() {}

bool ManagerAddOn::init() 
{
	return true;
}

void ManagerAddOn::writeLog(std::string str)
{
	std::ofstream off("log.txt", std::ios::app);
	off << str;
	off.close();
}
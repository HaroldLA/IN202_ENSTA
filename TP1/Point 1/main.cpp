#include"rational.hpp"
 
#include<iostream>
 
int main()
{
	try
	{
		rational valueA = { 1, 0 };
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	rational valueA = { 4, 3 };
	rational valueB = { 3, 4 };
 
	std::cout << "A + B = " << (valueA + valueB) << std::endl;
	std::cout << "A - B = " << (valueA - valueB) << std::endl;
	std::cout << "A * B = " << (valueA * valueB) << std::endl;
	std::cout << "A / B = " << (valueA / valueB) << std::endl;
 
	std::cout << "4 * B = " << (4 * valueB) << std::endl;
        return 0;
}


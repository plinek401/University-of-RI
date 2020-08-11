#include <iostream>
#include <vector>
#include <string>

struct MyStruct
{
	int number;
	std::string str;
};

int main(){
	std::cout << "Hello" << std::endl << std::endl;

	std::vector<MyStruct> myList;


	for (int i = 0; i < 100; i++)
	{
		MyStruct s;
		s.number = rand() % 100;
		s.str = "This is a string ";
		//s.str.append(std::to_string(i));
		myList.push_back(s);
	}

	for (unsigned int i = 0; i < myList.size(); i++)
	{
		MyStruct s;
		s = myList[i];
		std::cout << "Struct at " << i << std::endl;
		std::cout << "number = " << s.number << std::endl;
		std::cout << "str = " << s.str << std::endl<<std::endl;
	}

	return 0;
}

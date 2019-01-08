#include <iostream>
using namespace std;


/*const char* findTheChar(const char* str, char chr)
{
	while(str != 0)
	{
		if(*str == chr)
		{
			return str;
		}
		str++;
	}
	return nullptr;
}*/

const char* findTheChar(const char* str, char chr)
{
	for (int k = 0; *(str + k) != 0; k++)
	{
		if (*(str + k) == chr)
			return str + k;
	}

	return nullptr;
}



int main()
{
	char s[10] = "hello";
	cout << findTheChar(s, 'p');

}

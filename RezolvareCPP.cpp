#include <iostream>
#include <vector>

bool checkSuperiority(const std::vector<int>& vec)
{
	int sum = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		sum += vec[i];
	}

	int average = sum / vec.size();
	int count = 0;

	for (int i = 0; i < vec.size(); i++)
	{

		if (vec[i] > average)
		{
			count++;
		}
	}
	int half = vec.size() / 2;
	if (half >= count)
	{
		return false;
	}
	return true;
}

int main()
{
	std::vector<int> vec;
	int n;
	std::cout << "Enter the vector size: ";
	std::cin >> n;
	std::cout << std::endl;
	vec.resize(n);

	std::cout << "Enter the vector elements: ";
	for (int i = 0; i < n; i++)
	{
		std::cin >> vec[i];
	}
	std::cout << std::endl;

	if (checkSuperiority(vec))
	{
		std::cout << "The vector is superior" << std::endl;
	}
	else
	{
		std::cout << "The vector is inferior" << std::endl;

	}

	return 0;
}

#include <limits>
#include <stdexcept>
#include <iostream>

template <typename T>
std::enable_if_t<std::is_integral<T>::value, void> TestOverFlow(void)
{
	auto max_value = std::numeric_limits<T>::max();
	try
	{		
		++max_value;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Non-standard exception" << std::endl;
	}

	auto min_value = std::numeric_limits<T>::min();
	try
	{		
		--min_value;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Non-standard exception" << std::endl;
	}
}

int main(void)
{
	// All integral data types are wrapped up (rotated) without throwing an overflow exception.
	// Some of these behaviors are standard, but some of them are undefined.
	TestOverFlow<char>();
	TestOverFlow<unsigned char>();
	TestOverFlow<signed char>();
	TestOverFlow<short>();
	TestOverFlow<unsigned short>();
	TestOverFlow<int>();
	TestOverFlow<unsigned int>();
	TestOverFlow<long long>();
	TestOverFlow<unsigned long long>();
}
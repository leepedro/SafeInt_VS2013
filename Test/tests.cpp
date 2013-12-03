#include <safeint.h>

#include <iostream>
#include <stdexcept>

void test1(void)
{
	int int_a(-1);
	unsigned int uint_a;

	std::cout << "-1 as int = " << int_a << std::endl;
	uint_a = int_a;	
	std::cout << "-1 as unsigned int = " << uint_a << std::endl;
	std::cout << std::endl;
}

void TestSafeCast(void)
{
	int int_a(-1);
	unsigned int uint_a(0);

	std::cout << "-1 as int = " << int_a << std::endl;
	if (msl::utilities::SafeCast(int_a, uint_a))
		std::cout << "-1 as unsigned int = " << uint_a << std::endl;
	else
	{
		std::cout << "-1 failed to cast as unsigned int." << std::endl;
		std::cout << "Destination: " << uint_a << std::endl;	// Destination value is UNCHANGED! Good!
	}
	std::cout << std::endl;
}

void TestSafeGreaterThan(void)
{
	int int_a(-1);
	unsigned int uint_a(0), uint_b(std::numeric_limits<unsigned int>::max());

	std::cout << "-1 as int = " << int_a << std::endl;
	if (msl::utilities::SafeGreaterThan(int_a, uint_a))
		std::cout << int_a << ">" << uint_a << std::endl;
	else
		std::cout << int_a << "<=" << uint_a << std::endl;

	std::cout << "Maximum unsigned int = " << uint_b << std::endl;
	if (msl::utilities::SafeGreaterThan(int_a, uint_b))
		std::cout << int_a << ">" << uint_b << std::endl;
	else
		std::cout << int_a << "<=" << uint_b << std::endl;

	std::cout << std::endl;
}

void TestSafeAdd(void)
{
	int int_a(std::numeric_limits<int>::max()), int_b(0), int_c(0);

	std::cout << "Maximum int = " << int_a << std::endl;
	int_b = int_a + 1;	// Overflowed to a negative value.
	std::cout << "Maximum int + 1= " << int_b << std::endl;

	if (msl::utilities::SafeAdd(int_a, 1, int_c))
		std::cout << "Maximum int + 1= " << int_c << std::endl;
	else
	{
		std::cout << "Add failed." << std::endl;
		std::cout << "Destination: " << int_c << std::endl;	// Destination value is UNCHANGED! Good!
	}
	std::cout << std::endl;
}

void TestSafeInt(void)
{
	int int_a(-1), int_b(std::numeric_limits<int>::max());
	unsigned int uint_a(0);

	std::cout << "-1 as int = " << int_a << std::endl;
	std::cout << "Maximum int = " << int_b << std::endl;

	msl::utilities::SafeInt<int> si_int_a(int_a);
	msl::utilities::SafeInt<int> si_int_b(int_b);
	msl::utilities::SafeInt<unsigned int> si_uint_a;

	si_uint_a = si_int_b;	// casting by SafeInt class.
	si_uint_a++;			// operator overloaded by SafeInt class.
	uint_a = si_uint_a;
	std::cout << "Maximum int + 1 as unsigned int = " << uint_a << std::endl;	

	si_uint_a = si_int_a;	// casting by SafeInt class throws a SafeIntException.
	uint_a = si_uint_a;
	std::cout << "-1 as unsigned int = " << uint_a << std::endl;
}

int main(void)
{
	try
	{
		test1();
		TestSafeCast();
		TestSafeGreaterThan();
		TestSafeAdd();
		TestSafeInt();
	}
	catch (const msl::utilities::SafeIntException &ex)
	{
		switch (ex.m_code)
		{
		case msl::utilities::SafeIntNoError:
			std::cout << "No Error ?!?!" << std::endl;
			break;
		case msl::utilities::SafeIntArithmeticOverflow:
			std::cout << "Arithmetic overflow" << std::endl;
			break;
		case msl::utilities::SafeIntDivideByZero:
			std::cout << "Divide by zero" << std::endl;
			break;
		default:
			std::cout << "Unknown error code !!!" << std::endl;
		}
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unexpected exception!" << std::endl;
	}
}
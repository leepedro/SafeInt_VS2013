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
	// Negative integer overflow
	int int_neg(-1);
	unsigned int uint_dst(0);	
	std::cout << "-1 as int = " << int_neg << std::endl;
	if (msl::utilities::SafeCast(int_neg, uint_dst))
		std::cout << "-1 as unsigned int = " << uint_dst << std::endl;
	else
	{
		std::cout << "-1 failed to cast as unsigned int." << std::endl;
		std::cout << "Destination: " << uint_dst << std::endl;	// Destination value is UNCHANGED! Good!
	}

	// Positive integer overflow
	unsigned int uint_max(std::numeric_limits<unsigned int>::max());
	int int_dst(0);
	std::cout << "Maximum unsigned int = " << uint_max << std::endl;
	if (msl::utilities::SafeCast(uint_max, int_dst))
		std::cout << "Maximum unsigned int as int = " << int_dst << std::endl;
	else
	{
		std::cout << "Maximum unsigned int failed to cast as int." << std::endl;
		std::cout << "Destination: " << int_dst << std::endl;	// Destination value is UNCHANGED! Good!
	}

	// Both negative and positive overflow
	long long longlong_max(std::numeric_limits<long long>::max()), longlong_neg(-1);
	uint_dst = 0;
	std::cout << "Maximum long long = " << longlong_max << std::endl;
	std::cout << "-1 as long long = " << longlong_neg << std::endl;
	if (msl::utilities::SafeCast(longlong_max, uint_dst))
		std::cout << "Maximum long long as unsigned int = " << uint_dst << std::endl;
	else
	{
		std::cout << "Maximum long long failed to cast as unsigned int." << std::endl;
		std::cout << "Destination: " << uint_dst << std::endl;	// Destination value is UNCHANGED! Good!
	}
	if (msl::utilities::SafeCast(longlong_neg, uint_dst))
		std::cout << "-1 as unsigned int = " << uint_dst << std::endl;
	else
	{
		std::cout << "-1 failed to cast as unsigned int." << std::endl;
		std::cout << "Destination: " << uint_dst << std::endl;	// Destination value is UNCHANGED! Good!
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
	int int_neg(-1), int_max(std::numeric_limits<int>::max());
	unsigned int uint_dst(0);

	std::cout << "-1 as int = " << int_neg << std::endl;
	std::cout << "Maximum int = " << int_max << std::endl;

	msl::utilities::SafeInt<int> si_int_neg(int_neg);
	msl::utilities::SafeInt<int> si_int_max(int_max);
	msl::utilities::SafeInt<unsigned int> si_uint_dst;

	si_uint_dst = si_int_max;	// casting by SafeInt class.
	si_uint_dst++;				// operator overloaded by SafeInt class.
	uint_dst = si_uint_dst;
	std::cout << "Maximum int + 1 as unsigned int = " << uint_dst << std::endl;

	si_uint_dst = si_int_neg;	// casting by SafeInt class THROWS a SafeIntException.
	uint_dst = si_uint_dst;
	std::cout << "-1 as unsigned int = " << uint_dst << std::endl;
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
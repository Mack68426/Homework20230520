#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <ratio>

#include "metrics_length.h"

int main(int argc, char* argv[])
{
	// metric_length<std::ratio<1, 100>>

	using meters = metrics_length<std::ratio<1, 1>>;
	using centimeters = metrics_length<std::ratio<1, 100>>;
	using kilometers = metrics_length<std::ratio<1000, 1>>;

	meters l1{ 100 };
	centimeters l2{ 10 };
	kilometers l3{ 1 };


	// operator+() and operator-()
	std::cout << l3 + l1 << std::endl; // 1100 meters
	std::cout << l3 - l1 << std::endl; // 900 meters

	return 0;
}
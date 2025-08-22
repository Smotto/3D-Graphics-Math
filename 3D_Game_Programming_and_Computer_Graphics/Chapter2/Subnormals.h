#ifndef GRAPHICSMATH_SUBNORMALS_H_
#define GRAPHICSMATH_SUBNORMALS_H_

#include <cmath>
#include <iomanip>
#include <iostream>

// If all exponents are 0, subnormals/zero range
// If all exponents are 1, infinity/NaN range
// [10^-38, 10^38] for float 32
// range is traded for precision, where the most significant number is preserved with 7 decimal digits including and after it
// float32 = 7 decimal digits, 1.123456 vs 1.123457
// float64 or double = 16 decimal digits, 1.000000000000000 vs 1.000000000000001

/*
	Floating point spreads its precision across a huge range by using an exponent.
	That means you don’t get infinite digits of accuracy; instead you get a fixed number of significant digits (roughly constant, regardless of magnitude).

	float32: about 7.22 decimal digits

	float64: about 15.95 decimal digits

	std::numeric_limits<float>::digits10;   // 6
	std::numeric_limits<float>::max_digits10; // 9 (for round-trip)
	std::numeric_limits<double>::digits10;   // 15
	std::numeric_limits<double>::max_digits10; // 17 (for round-trip)
*/

inline void TestSubnormals() {
	float min_normal = std::numeric_limits<float>::min();
	float largest_sub = std::nextafter(min_normal, 0.0f);

	std::cout << largest_sub << std::endl;

	std::cout << std::scientific
			  << std::setprecision(std::numeric_limits<float>::max_digits10)
			  << "min_normal      = " << min_normal << "\n"
			  << "largest_subnorm = " << largest_sub << "\n";

	// Sanity checks
	std::cout << "is subnormal? " << (std::fpclassify(largest_sub) == FP_SUBNORMAL) << "\n";

	// Show raw bits (should be 0x007FFFFF)
	uint32_t bits;
	std::memcpy(&bits, &largest_sub, sizeof(bits));
	std::cout << std::hex << "bits = 0x" << bits << "\n";
}

#endif /* GRAPHICSMATH_SUBNORMALS_H_ */

#include "MathFunctionLibrary.h"
#include "Subnormals.h"
#include <cmath>
#include <iostream>

int main() {
	constexpr Vector3 P { 2.f, 2.f, 1.f };
	constexpr Vector3 Q { 1.f, -2.f, 0.f };

	std::cout << "Compute the Dot Product: " << "dot( " << P << ", " << Q << ")" << " = " << MathFunctionLibrary::DotProduct(P, Q) << "\n";

	std::cout << "Compute the Cross Product: " << "cross( " << P << ", " << Q << ")" << " = " << MathFunctionLibrary::CrossProduct(P, Q) << "\n";

	std::cout << "Compute the Vector Projection: " << "projection Q onto P = dot( " << Q << ", " << P << ")" << " * P "
	          << "/ ||P||^2" << " = " << MathFunctionLibrary::Projection(Q, P) << "\n";

	Vector3 e1 { (float)sqrt(2) / 2, (float)sqrt(2) / 2, 0.f };
	Vector3 e2 { 1.f, -2.f, 0.f };
	Vector3 e3 { 0.f, -2.f, -2.f };

	std::cout << "Compute the othorgonalization of 3 Vectors: " << e1 << "\t" << e2 << "\t" << e3 << "\n";
	MathFunctionLibrary::Orthogonalize(e1, e2, e3);

	std::cout << "Basis Vector: " << e1 << " Verify its DotProduct is 0 for orthogonality: " << MathFunctionLibrary::DotProduct(e1, e3) << std::endl;
	std::cout << "Second Vector: " << e2 << " Verify its DotProduct is 0 for orthogonality: " << MathFunctionLibrary::DotProduct(e2, e1) << std::endl;
	std::cout << "Third Vector: " << e3 << " Verify its DotProduct is 0 for orthogonality: " << MathFunctionLibrary::DotProduct(e3, e2) << std::endl;

	Vector3 p1 { 1, 2, 3 };
	Vector3 p2 { -2, 2, 4 };
	Vector3 p3 { 7, -8, 6 };

	std::cout << "Area of a triangle: " << MathFunctionLibrary::AreaOfTriangle(p1, p2, p3) << std::endl;
	std::cout << sizeof(Matrix4) << std::endl;

	return 0;
}

#ifndef CHAPTER2_MATHFUNCTIONLIBRARY_H_
#define CHAPTER2_MATHFUNCTIONLIBRARY_H_

#include <iostream>

struct Vector3 {
	float    x;
	float    y;
	float    z;

	// In-place mutators (chainable)
	Vector3& Negate() noexcept {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	Vector3& operator+=(const Vector3& o) noexcept {
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& o) noexcept {
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return *this;
	}

	// Component-wise multiply (Hadamard)
	Vector3& operator*=(const Vector3& o) noexcept {
		x *= o.x;
		y *= o.y;
		z *= o.z;
		return *this;
	}

	// Scalar ops
	Vector3& operator*=(float s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3& operator/=(float s) noexcept {
		s = 1.0F / s;
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3& operator-() {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	Vector3 operator+(const Vector3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	Vector3 operator-() const {
		return { -x, -y, -z };
	}

	Vector3 operator-(const Vector3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	Vector3 operator*(const Vector3& other) const {
		return { x * other.x, y * other.y, z * other.z };
	}

	Vector3& operator*=(const float& other) {
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	Vector3 operator*(const float& other) const {
		return { x * other, y * other, z * other };
	}

	friend Vector3 operator*(float scalar, const Vector3& v) {
		return { v.x * scalar, v.y * scalar, v.z * scalar };
	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
		return os;
	}

	Vector3 operator/(float scalar) const {
		return { x / scalar, y / scalar, z / scalar };
	}

	static float Magnitude(const Vector3& v) {
		return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	}

	static Vector3 Normalize(const Vector3& v) {
		return (v / Magnitude(v));
	}
};

struct Matrix3 {
	float n[3][3]; // Column-major order

	Matrix3() = default;
	Matrix3(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22) {
		n[0][0] = n00;
		n[0][1] = n01;
		n[0][2] = n02;

		n[1][0] = n10;
		n[1][1] = n11;
		n[1][2] = n12;

		n[2][0] = n20;
		n[2][1] = n21;
		n[2][2] = n22;
	}

	Matrix3(const Vector3& a, const Vector3& b, const Vector3& c) {
		n[0][0] = a.x;
		n[0][1] = a.y;
		n[0][2] = a.z;

		n[1][0] = b.x;
		n[1][1] = b.y;
		n[1][2] = b.z;

		n[2][0] = c.x;
		n[2][1] = c.y;
		n[2][2] = c.z;
	}

	float& operator()(int i, int j) {
		return n[j][i];
	}

	const float& operator()(int i, int j) const {
		return n[j][i];
	}

	Vector3& operator[](int j) {
		return (*reinterpret_cast<Vector3*>(n[j]));
	}

	const Vector3& operator[](int j) const {
		return (*reinterpret_cast<const Vector3*>(n[j]));
	}

	// TODO: Matrix-Matrix multiplication, matrix-vector multiplication
};

struct Matrix4 {
	// Homogenous 4x4 matrix where the xyz components need w to be 0, and position needs w to be 1
};

struct MathFunctionLibrary {
	// Returns a scalar
	// Takes in 2 rotation vectors
	// Naive approach, but fundamentally the same! Math is a system that rarely changes, and is only optimized.
	static float Length(const Vector3& P) {
		float xSquared = P.x * P.x;
		float ySquared = P.y * P.y;
		float zSquared = P.z * P.z;

		return sqrt(xSquared + ySquared + zSquared);
	}

	static float DotProduct(const Vector3& P, const Vector3& Q) {
		return P.x * Q.x + P.y * Q.y + P.z * Q.z;
	}

	static Vector3 CrossProduct(const Vector3& P, const Vector3& Q) {
		// Identity Matrix 3x3
		constexpr Vector3 i = { 1, 0, 0 };
		constexpr Vector3 j = { 0, 1, 0 };
		constexpr Vector3 k = { 0, 0, 1 };

		return { i * (P.y * Q.z - P.z * Q.y) - j * (P.x * Q.z - P.z * Q.x) + k * (P.x * Q.y - P.y * Q.x) };
	}

	static Vector3 Projection(const Vector3& V, const Vector3& onto) {
		// ||V|| ^ 2 == DotProduct(V)
		return (DotProduct(V, onto) / DotProduct(onto, onto)) * onto;
	}

	// Vector Rejection.
	static Vector3 Perpendicular(const Vector3& V, const Vector3& onto) {
		return V - Projection(V, onto);
	}

	// Gram-Schmidt
	static void Orthogonalize(Vector3& basisVector, Vector3& secondVector, Vector3& thirdVector) {
		basisVector  = basisVector;
		secondVector = Perpendicular(secondVector, basisVector);
		thirdVector  = Perpendicular(thirdVector, basisVector);  // Removes the component along the basisVector
		thirdVector  = Perpendicular(thirdVector, secondVector); // Removes the component along the already orthoganalized second vector
	}

	static Vector3 Normalize(const Vector3& v) {
		float length = Length(v);
		if (length == 0.0f)
			return { 0, 0, 0 }; // avoid div-by-zero
		return { v.x / length, v.y / length, v.z / length };
	}

	static void Orthonormalize(Vector3& basisVector, Vector3& secondVector, Vector3& thirdVector) {
		basisVector  = Normalize(basisVector);

		secondVector = Perpendicular(secondVector, basisVector);
		secondVector = Normalize(secondVector);

		thirdVector  = Perpendicular(thirdVector, basisVector);
		thirdVector  = Perpendicular(thirdVector, secondVector);
		thirdVector  = Normalize(thirdVector);
	}

	static float AreaOfTriangle(const Vector3& point1, const Vector3& point2, const Vector3& point3) {
		const Vector3 p1p2    = point2 - point1;
		const Vector3 p1p3    = point3 - point1;

		const Vector3 vector1 = CrossProduct(p1p2, p1p3);
		const float   length  = Length(vector1);
		const float   area    = length / 2.f;

		return area;
	}
};

#endif /*! CHAPTER2_MATHFUNCTIONLIBRARY_H_ */

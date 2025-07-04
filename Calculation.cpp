#include "Calculation.h"

Vector3 Add(const Vector3& v1, const Vector3& v2) {

	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}

// 減産
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {

	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;

}

Vector3 Multiply(float scalar, const Vector3& v) {

	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;

}

float Dot(const Vector3& v1, const Vector3& v2) {

	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

}

float Length(const Vector3& v) {

	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

}

Vector3 Normalize(const Vector3& v) {

	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	Vector3 result;
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;

	return result;

}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{

	return Add(Multiply(t, v1), Multiply(1.0f - t, v2));;
}

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 p0p1 = Lerp(p0, p1, t);
	Vector3 p1p2 = Lerp(p1, p2, t);
	Vector3 p = Lerp(p0p1, p1p2, t);
	return p;
}

Vector3 Reflect(const Vector3& input, const Vector3& normal)
{
	return input - 2.0f * (Dot(input, normal) * normal);
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {

	Vector3 result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;

}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[0][3] = m1.m[0][3] + m2.m[0][3];

	result.m[1][0] = m1.m[1][0] + m2.m[1][0];
	result.m[1][1] = m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][2] + m2.m[1][2];
	result.m[1][3] = m1.m[1][3] + m2.m[1][3];

	result.m[2][0] = m1.m[2][0] + m2.m[2][0];
	result.m[2][1] = m1.m[2][1] + m2.m[2][1];
	result.m[2][2] = m1.m[2][2] + m2.m[2][2];
	result.m[2][3] = m1.m[2][3] + m2.m[2][3];

	result.m[3][0] = m1.m[3][0] + m2.m[3][0];
	result.m[3][1] = m1.m[3][1] + m2.m[3][1];
	result.m[3][2] = m1.m[3][2] + m2.m[3][2];
	result.m[3][3] = m1.m[3][3] + m2.m[3][3];

	return result;

}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] - m2.m[0][0];
	result.m[0][1] = m1.m[0][1] - m2.m[0][1];
	result.m[0][2] = m1.m[0][2] - m2.m[0][2];
	result.m[0][3] = m1.m[0][3] - m2.m[0][3];

	result.m[1][0] = m1.m[1][0] - m2.m[1][0];
	result.m[1][1] = m1.m[1][1] - m2.m[1][1];
	result.m[1][2] = m1.m[1][2] - m2.m[1][2];
	result.m[1][3] = m1.m[1][3] - m2.m[1][3];

	result.m[2][0] = m1.m[2][0] - m2.m[2][0];
	result.m[2][1] = m1.m[2][1] - m2.m[2][1];
	result.m[2][2] = m1.m[2][2] - m2.m[2][2];
	result.m[2][3] = m1.m[2][3] - m2.m[2][3];

	result.m[3][0] = m1.m[3][0] - m2.m[3][0];
	result.m[3][1] = m1.m[3][1] - m2.m[3][1];
	result.m[3][2] = m1.m[3][2] - m2.m[3][2];
	result.m[3][3] = m1.m[3][3] - m2.m[3][3];

	return result;

}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return result;

}

Matrix4x4 Inverse(const Matrix4x4& m) {

	float inverse =
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	Matrix4x4 result;
	result.m[0][0] = (
		m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] -
		m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) / inverse;
	result.m[0][1] = (-
		m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) / inverse;
	result.m[0][2] = (
		m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) / inverse;
	result.m[0][3] = (-
		m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) / inverse;
	result.m[1][0] = (-
		m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] +
		m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) / inverse;
	result.m[1][1] = (
		m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] -
		m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) / inverse;
	result.m[1][2] = (-
		m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] +
		m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) / inverse;
	result.m[1][3] = (
		m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] -
		m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) / inverse;
	result.m[2][0] = (
		m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] -
		m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) / inverse;
	result.m[2][1] = (-
		m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) / inverse;
	result.m[2][2] = (
		m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] -
		m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) / inverse;
	result.m[2][3] = (-
		m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) / inverse;
	result.m[3][0] = (-
		m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] +
		m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) / inverse;
	result.m[3][1] = (
		m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) / inverse;
	result.m[3][2] = (-
		m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] +
		m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) / inverse;
	result.m[3][3] = (
		m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) / inverse;
	return result;

}

Matrix4x4 Transpose(const Matrix4x4& m) {

	Matrix4x4 result;

	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];

	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];

	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];

	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];

	return result;

}

Matrix4x4 MakeIdentity4x4() {

	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {

	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {

	Matrix4x4 result;

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;

}

Matrix4x4 MakeRotateXMatrix(float radian) {

	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakeRotateYMatrix(float radian) {

	Matrix4x4 result;

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -std::sin(radian);
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = std::sin(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = std::cos(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakeRotateZMatrix(float radian) {

	Matrix4x4 result;

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

	return Multiply(Multiply(Multiply(scaleMatrix, rotateXMatrix), Multiply(rotateYMatrix, rotateZMatrix)), translateMatrix);
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 result;

	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2.0f));
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = (1.0f / std::tan(fovY / 2.0f));
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = (farClip) / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -(farClip * nearClip) / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}


Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {

	Matrix4x4 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;
}
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {

	Matrix4x4 result;

	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}

void DrowGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfwidth = 5.0f; // Gridの半分の幅
	const uint32_t kSubdivision = 10; // 分割数
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision); // 1つ分の長さ
	// 奥から手前の線を徐々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		// ワールド座標系でx軸方向の始点と終点を求める
		float xPos = -kGridHalfwidth + kGridEvery * xIndex;
		Vector3 start(xPos, 0.0f, -kGridHalfwidth);
		Vector3 end(xPos, 0.0f, kGridHalfwidth);

		// スクリーン座標に変換
		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		unsigned int color = 0xAAAAAAFF;
		// 線が原点を通る場合は色を黒にする
		if (xPos == 0) {
			color = 0x000000FF;
		}

		// 変換した座標を使って表示
		Novice::DrawLine(
			static_cast<int>(startScreen.x),
			static_cast<int>(startScreen.y),
			static_cast<int>(endScreen.x),
			static_cast<int>(endScreen.y),
			color);

	}

	// 左から右も同じように引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める

		float zPos = -kGridHalfwidth + kGridEvery * zIndex;
		Vector3 start(-kGridHalfwidth, 0.0f, zPos);
		Vector3 end(kGridHalfwidth, 0.0f, zPos);

		// スクリーン座標に変換
		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		unsigned int color = 0xAAAAAAFF;
		// 線が原点を通る場合は色を黒にする
		if (zPos == 0) {
			color = 0x000000FF;
		}

		// 変換した座標を使って表示
		Novice::DrawLine(
			static_cast<int>(startScreen.x),
			static_cast<int>(startScreen.y),
			static_cast<int>(endScreen.x),
			static_cast<int>(endScreen.y),
			color);

	}
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 min = aabb.min;
	Vector3 max = aabb.max;
	// 8点を求める
	Vector3 points[8] = {
		{ min.x, min.y, min.z },
		{ max.x, min.y, min.z },
		{ min.x, max.y, min.z },
		{ max.x, max.y, min.z },
		{ min.x, min.y, max.z },
		{ max.x, min.y, max.z },
		{ min.x, max.y, max.z },
		{ max.x, max.y, max.z }
	};
	for (int i = 0; i < 8; ++i) {
		points[i] = Transform(Transform(points[i], viewProjectionMatrix), viewportMatrix);
	}

	// 線を引くべき点のペア（インデックス）
	int indices[12][2] = {
		{0, 1}, {1, 3}, {3, 2}, {2, 0}, // 前面
		{4, 5}, {5, 7}, {7, 6}, {6, 4}, // 背面
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // 側面をつなぐ縦線
	};

	// 線を描画
	for (int i = 0; i < 12; ++i) {
		const Vector3& p0 = points[indices[i][0]];
		const Vector3& p1 = points[indices[i][1]];
		Novice::DrawLine(
			static_cast<int>(p0.x), static_cast<int>(p0.y),
			static_cast<int>(p1.x), static_cast<int>(p1.y),
			color
		);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const uint32_t kSubdivision = 24; // 分割数

	const float kLatEvery = pi / kSubdivision;       // 緯度（πをkSubdivisionで割る）
	const float kLonEvery = 2.0f * pi / kSubdivision; // 経度（2πをkSubdivisionで割る）

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		float nextLat = lat + kLatEvery;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			float nextLon = lon + kLonEvery;


			// 4点を作って2本の線を引く
			Vector3 a = {
				sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon),
				sphere.center.y + sphere.radius * std::sin(lat),
				sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * std::cos(nextLat) * std::cos(lon),
				sphere.center.y + sphere.radius * std::sin(nextLat),
				sphere.center.z + sphere.radius * std::cos(nextLat) * std::sin(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * std::cos(lat) * std::cos(nextLon),
				sphere.center.y + sphere.radius * std::sin(lat),
				sphere.center.z + sphere.radius * std::cos(lat) * std::sin(nextLon)
			};

			// スクリーン座標に変換
			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			// ab,bcで線を引く
			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenB.x),
				static_cast<int>(screenB.y),
				color);
			Novice::DrawLine(
				static_cast<int>(screenB.x),
				static_cast<int>(screenB.y),
				static_cast<int>(screenC.x),
				static_cast<int>(screenC.y),
				color);

		}
	}
}

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	return Multiply((Dot(v1, v2) / Dot(v2, v2)), v2);
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	return Add(segment.origin, Project(Subtract(point, segment.origin), segment.diff));
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {

	float distance = Dot(plane.normal, sphere.center) - plane.distance;
	if (distance < 0.0f) {
		distance *= -1.0f;
	}
	return distance < sphere.radius;

}

bool IsCollision(const Segment& segment, const Plane& plane) {

	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(plane.normal, segment.origin)) / dot;

	// tの値と線の種類によって衝突しているかを判断する
	return (0.0f <= t && t <= 1.0f);

}

bool IsCollision(const Segment& segment, const Triangle& triangle)
{
	// 三角形の点を結んだベクトルを作る
	Vector3 v01 = Subtract(triangle.vertex[1], triangle.vertex[0]);
	Vector3 v12 = Subtract(triangle.vertex[2], triangle.vertex[1]);
	Vector3 v20 = Subtract(triangle.vertex[0], triangle.vertex[2]);

	Vector3 dir = Subtract(segment.diff, segment.origin); // 線分の方向ベクトル
	Vector3 normal = Normalize(Cross(v01, v12));            // 三角形の法線

	float d = Dot(normal, triangle.vertex[0]);
	float denom = Dot(normal, dir);

	// 平行チェック
	if (fabs(denom) < 1e-6f) return false;

	// 線分と平面の交点を t で求める（segment.origin + t * dir）
	float t = (d - Dot(normal, segment.origin)) / denom;

	// t が [0,1] の範囲外なら、交点は線分外にある
	if (t < 0.0f || t > 1.0f) return false;

	Vector3 intersection = Add(segment.origin, Multiply(t, dir));

	// 頂点と衝突点pを結んだベクトルを作る
	Vector3 v0p = Subtract(intersection, triangle.vertex[0]);
	Vector3 v1p = Subtract(intersection, triangle.vertex[1]);
	Vector3 v2p = Subtract(intersection, triangle.vertex[2]);

	// これらのベクトルのクロス積を取る
	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f
		) {
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere)
{
	Vector3 closetpoint{
		std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z),
	};
	// 最近接点と球の中心との距離を求める
	float distance = Length(Subtract(closetpoint, sphere.center));
	// 距離が半径よりも小さければ衝突
	if (distance <= sphere.radius) {
		// 衝突
		return true;
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Segment& segment) {
	Vector3 dir = segment.diff; // 方向ベクトル（差分）

	float tmin = 0.0f; // 線分始点
	float tmax = 1.0f; // 線分終点

	for (int i = 0; i < 3; ++i) {
		float origin = (i == 0) ? segment.origin.x : (i == 1) ? segment.origin.y : segment.origin.z;
		float direction = (i == 0) ? dir.x : (i == 1) ? dir.y : dir.z;
		float slabMin = (i == 0) ? aabb.min.x : (i == 1) ? aabb.min.y : aabb.min.z;
		float slabMax = (i == 0) ? aabb.max.x : (i == 1) ? aabb.max.y : aabb.max.z;

		if (fabsf(direction) < 1e-6f) {
			// 平行な場合、始点がAABB内にないと交差しない
			if (origin < slabMin || origin > slabMax) {
				return false;
			}
		} else {
			float t1 = (slabMin - origin) / direction;
			float t2 = (slabMax - origin) / direction;

			if (t1 > t2) {
				float temp = t1;
				t1 = t2;
				t2 = temp;
			}

			tmin = (t1 > tmin) ? t1 : tmin;
			tmax = (t2 < tmax) ? t2 : tmax;

			if (tmin > tmax) {
				return false;
			}
		}
	}

	// すべて当たっていたら
	return true;
}

Vector3 Perpendiculer(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}
	return{ 0.0f, -vector.z, vector.y };
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 u = Normalize(Perpendiculer(plane.normal));
	Vector3 v = Normalize(Cross(plane.normal, u));

	float extent = 10.0f;
	Vector3 corners[4];
	corners[0] = Add(center, Add(Multiply(+extent, u), Multiply(+extent, v)));
	corners[1] = Add(center, Add(Multiply(+extent, u), Multiply(-extent, v)));
	corners[2] = Add(center, Add(Multiply(-extent, u), Multiply(-extent, v)));
	corners[3] = Add(center, Add(Multiply(-extent, u), Multiply(+extent, v)));

	for (int i = 0; i < 4; ++i) {
		Vector3 p0 = Transform(Transform(corners[i], viewProjectionMatrix), viewportMatrix);
		Vector3 p1 = Transform(Transform(corners[(i + 1) % 4], viewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(static_cast<int>(p0.x), static_cast<int>(p0.y),
			static_cast<int>(p1.x), static_cast<int>(p1.y), color);
	}
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	// 3つの頂点をスクリーン座標に変換
	Vector3 p0 = Transform(Transform(triangle.vertex[0], viewProjectionMatrix), viewportMatrix);
	Vector3 p1 = Transform(Transform(triangle.vertex[1], viewProjectionMatrix), viewportMatrix);
	Vector3 p2 = Transform(Transform(triangle.vertex[2], viewProjectionMatrix), viewportMatrix);

	// 三角形を描画
	Novice::DrawTriangle(
		static_cast<int>(p0.x),
		static_cast<int>(p0.y),
		static_cast<int>(p1.x),
		static_cast<int>(p1.y),
		static_cast<int>(p2.x),
		static_cast<int>(p2.y),
		color, kFillModeWireFrame
	);
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	// 分割数
	const uint32_t kSubdivision = 16; // 分割数

	for (uint32_t i = 0; i < kSubdivision; i++) {

		float t0 = static_cast<float>(i) / kSubdivision;
		float t1 = static_cast<float>(i + 1) / kSubdivision;
		// t0とt1と制御点を使ってベジェ曲線上の点を求める
		Vector3 bezier0 = Bezier(controlPoint0, controlPoint1, controlPoint2, t0);
		Vector3 bezier1 = Bezier(controlPoint0, controlPoint1, controlPoint2, t1);
		// それぞれの点をスクリーン座標へ変換
		Vector3 screenBezier0 = Transform(Transform(bezier0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenBezier1 = Transform(Transform(bezier1, viewProjectionMatrix), viewportMatrix);

		// 変換した座標を使って描画する
		Novice::DrawLine(
			static_cast<int>(screenBezier0.x),
			static_cast<int>(screenBezier0.y),
			static_cast<int>(screenBezier1.x),
			static_cast<int>(screenBezier1.y),
			color
		);
	}

	// 制御点に球を描画
	DrawSphere(Sphere(controlPoint0, 0.01f), viewProjectionMatrix, viewportMatrix, 0x000000FF);
	DrawSphere(Sphere(controlPoint1, 0.01f), viewProjectionMatrix, viewportMatrix, 0x000000FF);
	DrawSphere(Sphere(controlPoint2, 0.01f), viewProjectionMatrix, viewportMatrix, 0x000000FF);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {

			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f,", matrix.m[row][column]);

		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);

}

void PreventingSubstitutions(AABB aabb)
{
	aabb.min.x = (std::min)(aabb.min.x, aabb.max.x);
	aabb.max.x = (std::max)(aabb.min.x, aabb.max.x);
	aabb.min.y = (std::min)(aabb.min.y, aabb.max.y);
	aabb.max.y = (std::max)(aabb.min.y, aabb.max.y);
	aabb.min.z = (std::min)(aabb.min.z, aabb.max.z);
	aabb.max.z = (std::max)(aabb.min.z, aabb.max.z);

}

bool SweepSphereToPlane(const Vector3& from, const Vector3& to, float radius, const Plane& plane, Vector3& contactPoint) {
	
	Vector3 dir = to - from;
	float length = Length(dir);
	if (length < 1e-6f) return false;

	Vector3 dirNormalized = Normalize(dir);
	float denom = Dot(dirNormalized, plane.normal);

	if (std::abs(denom) < 1e-5f) {
		return false;
	}

	float distFrom = Dot(from, plane.normal) - plane.distance;
	float t = (radius - distFrom) / denom;

	if (t >= 0.0f && t <= length) {
		contactPoint = from + dirNormalized * t;
		return true;
	}

	return false;
}

#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "algorithm"

const float pi = 3.14159265f;

// 三次元ベクトル
struct Vector3 {
	float x, y, z;

	inline Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	inline Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

};

// 4x4の行列
struct Matrix4x4 {
	float m[4][4];
};

// 球
struct Sphere {
	Vector3 center; // 中心点
	float radius; // 半径
};

struct Line {
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};

struct Ray {
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};

struct Segment {
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};

struct Plane {
	Vector3 normal; // 法線
	float distance; // 距離
};

struct Triangle {
	Vector3 vertex[3]; // 頂点
};

struct AABB {
	Vector3 min; // 最小値
	Vector3 max; // 最大値
};

struct Spring {
	// アンカー。固定された端の位置
	Vector3 anchor;
	float naturalLength; // 自然長
	float stiffness; // 剛性。ばね定数k
	float dampingCoefficient; // 減衰係数
};

struct Ball
{
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radius;
	unsigned int color;
};

struct Pendulum {
	Vector3 anchor;
	float length;
	float angle;
	float anglerVelocity;
	float angularAcceleration;
};

struct ConicalPendulum {
	Vector3 anchor;
	float length;
	float halfApexAngle;
	float angle;
	float angularVelocity;
};

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

// 減産
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

// 内積
float Dot(const Vector3& v1, const Vector3& v2);

// 長さ(ノルム)
float Length(const Vector3& v);

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

// 正規化
Vector3 Normalize(const Vector3& v);

// 補間点を求める
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

// ベジェ曲線上の点を求める
Vector3 Bezier(const Vector3& v1, const Vector3& v2, const Vector3& v3, float t);

// 反射ベクトルを求める
Vector3 Reflect(const Vector3& input, const Vector3& normal);

// 行列の加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

// 行列の減産
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);

// 単位行列の作成
Matrix4x4 MakeIdentity4x4();

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
// Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
// Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& translate, const Vector3& rotate);

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

// 球の描画
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

// グリッドの描画
void DrowGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

// 直方体の描画
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);

// 接近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

// 球と平面の衝突判定
bool IsCollision(const Sphere& sphere, const Plane& plane);

// 球と線分の衝突判定
bool IsCollision(const Segment& segment, const Plane& plane);

// 三角形と線のあたり判定
bool IsCollision(const Segment& segment, const Triangle& triangle);

// 直方体と直方体の当たり判定
bool IsCollision(const AABB& aabb1, const AABB& aabb2);

// 球と直方体のあたり判定
bool IsCollision(const AABB& aabb, const Sphere& sphere);

// 直方体と線の当たり判定
bool IsCollision(const AABB& aabb, const Segment& segmrnt);

Vector3 Perpendiculer(const Vector3& vector);

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

// 二次ベジェ曲線
void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

// 4x4行列の数値表示
const int kColumnWidth = 60;
const int kRowHeight = 20;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

// 3次元ベクトルの数値表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

// 入れ替わり防止
void PreventingSubstitutions(AABB aabb);

// 演算子オーバーロード
inline Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
inline Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
inline Vector3 operator*(const float& s, const Vector3& v) { return Multiply(s, v); }
inline Vector3 operator*(const Vector3& v, const float& s) { return Multiply(s, v); }
inline Vector3 operator/(const Vector3& v, const float& s) { return Multiply(1.0f / s, v); }
inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

// 単項演算子
inline Vector3 operator-(const Vector3& v) { return { -v.x, -v.y, -v.z }; }
inline Vector3 operator+(const Vector3& v) { return v; }

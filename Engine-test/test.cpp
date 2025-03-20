#include "pch.h"
#include "Vector.h"
TEST(VectorTest, ZeroConstructor)
{
	Engine::Vector2D<float> vec;
	EXPECT_FLOAT_EQ(vec.x, 0);
	EXPECT_FLOAT_EQ(vec.y, 0);
}

TEST(VectorTest, Constructor)
{
	Engine::Vector2D<float> vec(5.f, -3.f);
	EXPECT_FLOAT_EQ(vec.x, 5.f);
	EXPECT_FLOAT_EQ(vec.y, -3.f);
}

TEST(VectorTest, Length)
{
	Engine::Vector2D<float> vec(-4.f, -3.f);
	EXPECT_FLOAT_EQ(vec.GetLength(), 5.f);
}

TEST(VectorTest, Addition)
{
	Engine::Vector2D<float> vec1(5.f, -3.f);
	Engine::Vector2D<float> vec2(-3.f, -6.f);
	Engine::Vector2D<float> vec3 = vec1 + vec2;
	EXPECT_FLOAT_EQ(vec3.x, 2.f);
	EXPECT_FLOAT_EQ(vec3.y, -9.f);
}

TEST(VectorTest, Substract)
{
	Engine::Vector2D<float> vec1(5.f, -3.f);
	Engine::Vector2D<float> vec2(-3.f, -6.f);
	Engine::Vector2D<float> vec3 = vec1 - vec2;
	EXPECT_FLOAT_EQ(vec3.x, 8.f);
	EXPECT_FLOAT_EQ(vec3.y, 3.f);
}

TEST(VectorTest, Negative)
{
	Engine::Vector2D<float> vec1(5.f, -3.f);
	Engine::Vector2D<float> vec2 = -vec1;
	EXPECT_FLOAT_EQ(vec2.x, -5.f);
	EXPECT_FLOAT_EQ(vec2.y, 3.f);
}

TEST(VectorTest, Dot)
{
	Engine::Vector2D<float> vec1(5.f, -3.f);
	Engine::Vector2D<float> vec2(-3.f, -6.f);
	float result = vec1.Dot(vec2);
	EXPECT_FLOAT_EQ(result, 3.f);
}

TEST(VectorTest, ScalarMultVec)
{
	Engine::Vector2D<float> vec1(5.f, -3.f);
	float scalar = 3;
	Engine::Vector2D<float> vec2 = scalar * vec1;
	EXPECT_FLOAT_EQ(vec2.x, 15.f);
	EXPECT_FLOAT_EQ(vec2.y, -9.f);
}

TEST(VectorTest, VecMultScalar)
{
	Engine::Vector2D<float> vec1(5.f, -3.f);
	float scalar = 3;
	Engine::Vector2D<float> vec2 = vec1 * scalar;
	EXPECT_FLOAT_EQ(vec2.x, 15.f);
	EXPECT_FLOAT_EQ(vec2.y, -9.f);
}
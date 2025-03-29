#include "pch.h"
#include "Matrix2D.h"
#include <iostream>
#include <vector>

constexpr float PI = 3.1415926;

namespace Engine
{
	Matrix2D::Matrix2D()
	{
		matrix[0][0] = 1.f; matrix[0][1] = 0.f; matrix[0][2] = 0.f;
		matrix[1][0] = 0.f; matrix[1][1] = 1.f; matrix[1][2] = 0.f;
		matrix[2][0] = 0.f; matrix[2][1] = 0.f; matrix[2][2] = 1.f;
	}

	Matrix2D::Matrix2D(float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22)
	{
		matrix[0][0] = a00; matrix[0][1] = a01; matrix[0][2] = a02;
		matrix[1][0] = a10; matrix[1][1] = a11; matrix[1][2] = a12;
		matrix[2][0] = a20; matrix[2][1] = a21; matrix[2][2] = a22;
	}

	Matrix2D::Matrix2D(Vector2Df position, float angle, Vector2Df scale)
		: Matrix2D()
	{
		matrix[0][2] = position.x;
		matrix[0][1] = position.y;

		float cosA = cos(angle * PI / 180);
		float sinA = sin(angle * PI / 180);
		matrix[0][0] = cosA * scale.x;
		matrix[0][1] = sinA;
		matrix[1][0] = -sinA;
		matrix[1][1] = cosA * scale.y;
	}

	Matrix2D Matrix2D::operator*(const Matrix2D& other)
	{
		Matrix2D result;
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				result.matrix[row][col] =
					matrix[row][0] * other.matrix[0][col] +
					matrix[row][1] * other.matrix[1][col] +
					matrix[row][2] * other.matrix[2][col];
			}
		}
		return result;
	}

	const std::array<std::array<float, 3>, 3> Matrix2D::GetMatrix() const
	{
		return matrix;
	}

	Matrix2D Matrix2D::GetInversed() const
	{
		Matrix2D result;
		float det =
			+ matrix[0][0] * matrix[1][1] * matrix[2][2]
			+ matrix[0][1] * matrix[1][2] * matrix[2][0]
			+ matrix[0][2] * matrix[1][0] * matrix[2][1]
			- matrix[0][2] * matrix[1][1] * matrix[2][0]
			- matrix[0][1] * matrix[1][0] * matrix[2][2]
			- matrix[0][0] * matrix[1][2] * matrix[2][1];
		float inverseDet = 1.f / det;

		Matrix2D minor{
			0.f, 0.f, 0.f,
			0.f, 0.f, 0.f,
			0.f, 0.f, 0.f };
		std::vector<std::vector<float>> subMatrix(2, std::vector<float>(2));

		int subMatrixRow = 0;
		int subMatrixCol = 0;

		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				subMatrixRow = 0;
				subMatrixCol = 0;

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (i != row && j != col)
						{
							subMatrix[subMatrixRow][subMatrixCol] = matrix[i][j];
							subMatrixCol++;
							if (subMatrixCol == 2)
							{
								subMatrixCol = 0;
								subMatrixRow++;
							}
						}
					}
				}

				minor.matrix[row][col] = subMatrix[0][0] * subMatrix[1][1]
					- subMatrix[0][1] * subMatrix[1][0];
				if ((row + col) % 2 == 1)
				{
					minor.matrix[row][col] = -minor.matrix[row][col];
				}

			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result.matrix[i][j] = inverseDet * minor.matrix[j][i];
			}
		}
		
		return result;
	}

	void Matrix2D::Print() const
	{
		for (int row = 0; row < 3; row++)
		{
			std::cout << "| ";
			for (int col = 0; col < 3; col++)
			{
				std::cout << matrix[row][col] << " ";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << std::endl;
	}


}
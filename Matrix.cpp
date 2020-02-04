#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int cols, int rows)
{
}

Matrix::~Matrix()
{
}

Matrix& Matrix::operator=(const Matrix& copyMatrix)
{
	if (&copyMatrix == this) return *this;

	m_cols = copyMatrix.m_cols;
	m_rows = copyMatrix.m_rows;

	m_matrix.clear();

	for (int x = 0; x < m_cols; x++)
	{
		Array1D<double> yGrid;
		for (int y = 0; y < m_rows; y++)
		{
			yGrid.push_back(copyMatrix.m_matrix[x][y]);
		}
		m_matrix.push_back(yGrid);
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& copyMatrix)
{
	if (m_cols != copyMatrix.m_rows) 
	{
		m_cols = 0;
		m_rows = 0;

		m_matrix.clear();

		return *this;
	}

	int newCols = copyMatrix.m_cols;
	int newRows = m_rows;

	Array2D<double> newMatrix;

	for (int x = 0; x < m_rows; x++)
	{
		Array1D<double> yGrid;
	}
}

int Matrix::GetCols() const
{
	return m_cols;
}

int Matrix::GetRows() const
{
	return m_rows;
}

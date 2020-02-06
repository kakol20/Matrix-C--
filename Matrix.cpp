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

	for (int i = 0; i < m_rows; i++)
	{
		Array1D<double> yGrid;

		double total = 0.0;
		for (int j = 0; j < copyMatrix.GetRows(); j++)
		{
			total += m_matrix[j][i] * copyMatrix.m_matrix[i][j];
		}

		yGrid.push_back(total);

		newMatrix.push_back(yGrid);
	}

	m_matrix.clear();

	for (int x = 0; x < newMatrix.size(); x++)
	{
		Array1D<double> yGrid;

		for (int y = 0; y < newMatrix[x].size(); y++)
		{
			yGrid.push_back(newMatrix[x][y]);
		}

		m_matrix.push_back(yGrid);
	}

	m_cols = newCols;
	m_rows = newRows;

	return *this;
}

int Matrix::GetCols() const
{
	return m_cols;
}

int Matrix::GetRows() const
{
	return m_rows;
}

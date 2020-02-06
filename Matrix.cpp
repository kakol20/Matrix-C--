#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(const Array2D<double>& matrix)
{
}

Matrix::Matrix(int cols, int rows)
{
	m_cols = cols;
	m_rows = rows;
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

	Create2DArray(newCols, newRows, newMatrix);

	for (int i = 0; i < copyMatrix.m_cols; i++) // go through right side matrix's col
	{
		for (int j = 0; j < m_rows; j++)
		{
			double total = 0.0;

			for (int k = 0; k < copyMatrix.m_rows; k++)
			{
				total += m_matrix[k][j] * copyMatrix.m_matrix[i][k];
			}
			
			newMatrix[i][j] = total;
		}
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

void Matrix::Create2DArray(int col, int row, Array2D<double>& copy)
{
	for (int x = 0; x < col; x++)
	{
		Array1D<double> yGrid;
		for (int y = 0; y < row; y++)
		{
			yGrid.push_back(0.0);
		}
		copy.push_back(yGrid);
	}
}

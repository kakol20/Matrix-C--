#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T>
using Array1D = std::vector<T>;

template <typename T>
using Array2D = std::vector<std::vector<T>>;

class Matrix {
public:
	Matrix();
	Matrix(const Array2D<double>& matrix);
	Matrix(const Matrix& copyMatrix);
	Matrix(int cols, int rows);
	~Matrix();

	// Assignment
	Matrix& operator=(const Matrix& copyMatrix);
	Matrix& operator=(const Array2D<double>& matrix);

	// Multiplication
	Matrix operator*(const Matrix& copyMatrix);
	Matrix& operator*=(const Matrix& copyMatrix);

	// Addition
	Matrix operator+(const Matrix& copyMatrix);
	Matrix& operator+=(const Matrix& copyMatrix);

	// Applying a function to every value in matrix
	Matrix& operator=(double (*f)(double));

	// Identity
	static Matrix Identity(const int size);

	int GetCols() const;
	int GetRows() const;

private:
	void Create2DArray(int col, int row, Array2D<double>& copy);

private:
	int m_cols;
	int m_rows;

	Array2D<double> m_matrix;
};

#endif // !MATRIX_H

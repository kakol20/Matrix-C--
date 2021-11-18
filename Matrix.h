#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

/// <summary>
/// 1D Array Template
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
using Array1D = std::vector<T>;

/// <summary>
/// 2D Array Template
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
using Array2D = std::vector<std::vector<T>>;

class Matrix {
public:
	Matrix();
	Matrix(const Array2D<double>& matrix);
	Matrix(const Matrix& copyMatrix);
	Matrix(int cols, int rows);
	~Matrix();

	/// <summary>
	/// Assignment
	/// </summary>
	/// <param name="copyMatrix"></param>
	/// <returns></returns>
	Matrix& operator=(const Matrix& copyMatrix);
	Matrix& operator=(const Array2D<double>& matrix);

	/// <summary>
	/// Multiplication
	/// </summary>
	/// <param name="copyMatrix"></param>
	/// <returns></returns>
	Matrix operator*(const Matrix& copyMatrix);
	Matrix& operator*=(const Matrix& copyMatrix);
	
	/// <summary>
	/// Scalar
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	Matrix operator*(const double scalar);
	Matrix& operator*=(const double scalar);

	/// <summary>
	/// Addition
	/// </summary>
	/// <param name="copyMatrix"></param>
	/// <returns></returns>
	Matrix operator+(const Matrix& copyMatrix);
	Matrix& operator+=(const Matrix& copyMatrix);

	/// <summary>
	/// Applying a function to every value in matrix
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	Matrix& operator=(double (*f)(double));

	/// <summary>
	/// Identity
	/// </summary>
	/// <param name="size"></param>
	/// <returns></returns>
	static Matrix Identity(const int size);

	int GetCols() const;
	int GetRows() const;

private:
	void Create2DArray(const int col, const int row, Array2D<double>& copy);

private:
	int m_cols;
	int m_rows;

	Array2D<double> m_matrix;
};

#endif // !MATRIX_H

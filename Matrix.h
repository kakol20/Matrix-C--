#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
public:
	Matrix();
	~Matrix();

	int GetCols() const;
	int GetRows() const;

private:
	int m_cols;
	int m_rows;
};

#endif // !MATRIX_H

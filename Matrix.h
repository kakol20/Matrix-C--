#pragma once

#include <string>

#include "Pseudo2DArray.hpp"

class Matrix {
public:
  Matrix(const std::vector<double>& arr = { 1 }, const unsigned int cols = 1, const unsigned int rows = 1);
  Matrix(const Pseudo2DArray<double>& arr);
  Matrix(const Matrix& other);
  ~Matrix() {};

  Matrix& operator=(const Matrix& other);

  Matrix& operator*=(const Matrix& rhs);
  Matrix operator*(const Matrix& rhs) const;

  Matrix& operator*=(const double scalar);
  Matrix operator*(const double scalar) const;

  double& operator()(const unsigned int x, const unsigned int y);
  double operator()(const unsigned int x, const unsigned int y) const;

  void Pow(const double p);
  void Cbrt();
  void NRoot(const double n);

  void Transpose();

  std::string Debug(const int indentSize = 0) const { return m_mat.Debug(indentSize); };

  double Determinant() const;

private:
  Pseudo2DArray<double> m_mat;

  unsigned int m_cols, m_rows;
};
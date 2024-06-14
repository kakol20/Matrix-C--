#include <cmath>

#include "Matrix.h"

Matrix::Matrix(const std::vector<double>& arr, const unsigned int cols, const unsigned int rows) {
  m_cols = cols;
  m_rows = rows;

  m_mat = Pseudo2DArray<double>(arr, m_cols, m_rows);
}

Matrix::Matrix(const Pseudo2DArray<double>& arr) {
  m_mat = arr;
  m_cols = m_mat.GetWidth();
  m_rows = m_mat.GetHeight();
}

Matrix::Matrix(const Matrix& other) {
  m_cols = other.m_cols;
  m_rows = other.m_rows;
  m_mat = other.m_mat;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) return *this;
  m_cols = other.m_cols;
  m_rows = other.m_rows;
  m_mat = other.m_mat;
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
  if (m_cols != rhs.m_rows) return *this;

  const unsigned int newCols = rhs.m_cols;
  const unsigned int newRows = m_rows;

  Pseudo2DArray<double> newMat(newCols, newRows);

  for (unsigned int i = 0; i < newCols; i++) {
    for (unsigned int j = 0; j < newRows; j++) {
      double total = 0.;
      for (unsigned int k = 0; k < rhs.m_rows; k++) {
        total += m_mat(k, j) * rhs.m_mat(i, k);
      }
      newMat(i, j) = total;
    }
  }

  m_mat = newMat;
  m_cols = newCols;
  m_rows = newRows;
  return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
  Matrix lhs(*this);
  lhs *= rhs;
  return lhs;
}

Matrix& Matrix::operator*=(const double scalar) {
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      m_mat(i, j) *= scalar;
    }
  }
  return *this;
}

Matrix Matrix::operator*(const double scalar) const {
  Matrix lhs(*this);
  lhs *= scalar;
  return lhs;
}

double& Matrix::operator()(const unsigned int x, const unsigned int y) {
  return m_mat(x, y);
}

double Matrix::operator()(const unsigned int x, const unsigned int y) const {
  return m_mat(x, y);
}

void Matrix::Pow(const double p) {
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      m_mat(i, j) = std::pow(m_mat(i, j), p);
    }
  }
}

void Matrix::Cbrt() {
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      m_mat(i, j) = std::cbrt(m_mat(i, j));
    }
  }
}

void Matrix::NRoot(const double n) {
  const double exp = 1. / n;
  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      if (std::fmod(n, 1.) == 0.) {
        m_mat(i, j) = std::pow(m_mat(i, j), exp);
      }
      else {
        double absroot = std::pow(std::abs(m_mat(i, j)), exp);
        if (m_mat(i, j) < 0.) absroot *= -1.;
        m_mat(i, j) = absroot;
      }
    }
  }
}

void Matrix::Transpose() {
  Pseudo2DArray<double> newMat(m_rows, m_cols);

  for (unsigned int i = 0; i < m_cols; i++) {
    for (unsigned int j = 0; j < m_rows; j++) {
      newMat(j, i) = m_mat(i, j);
    }
  }

  m_mat = newMat;
  m_cols = newMat.GetWidth();
  m_rows = newMat.GetHeight();

  //return true;
}

double Matrix::Determinant() const {
  if (m_rows != m_cols) return 0.0;

  double total = 0.0;

  for (int x = 0; x < (int)m_cols; x++) {
    // addition

    double mult = m_mat.GetValueWrapped(x, 0);
    for (int i = 1; i < (int)m_rows; i++) {
      mult *= m_mat.GetValueWrapped(x + i, i);
    }
    total += mult;

    // subtraction

    mult = m_mat.GetValueWrapped(x, 0);
    for (int i = 1; i < (int)m_rows; i++) {
      mult *= m_mat.GetValueWrapped(x - i, i);
    }
    total -= mult;
  }

  return total;
}

bool Matrix::Invert() {
  if (m_rows != m_cols) return false;
  if ((*this).Determinant() == 0.) return false;

  const unsigned int size = m_rows;

  // pivoting

  Pseudo2DArray<double> identity = (*this).Identity().m_mat;
  for (unsigned int x = 0; x < size; x++) {
    // row exchange if pivot == 0
    // swap with value in same column with biggest abs value
    if (m_mat(x, x) == 0.) {
      unsigned int swap_row = x == 0 ? 1 : 0;
      double chosen_abs = 0;
      for (unsigned int y = 0; y < size; y++) {
        if (x != y) {
          double abs = std::abs(m_mat(x, y));

          if (abs > chosen_abs) {
            swap_row = y;
            chosen_abs = abs;
          }
        }
      }

      m_mat.SwapRows(x, swap_row);
      identity.SwapRows(x, swap_row);
    }

    // zero other values in column
    for (unsigned int y = 0; y < size; y++) {
      if (y != x) {
        double mult = (-1. * m_mat(x, y)) / m_mat(x, x);

        for (unsigned int z = 0; z < size; z++) {
          m_mat(z, y) = (mult * m_mat(z, x)) + m_mat(z, y);
          identity(z, y) = (mult * identity(z, x)) + identity(z, y);
        }
      }
    }
  }

  // multiply

  for (unsigned int y = 0; y < size; y++) {
    const double div = m_mat(y, y);
    for (unsigned int x = 0; x < size; x++) {
      identity(x, y) /= div;
    }
  }

  m_mat = identity;

  return true;
}

Matrix Matrix::Identity() const {
  Matrix id(m_mat);
  for (unsigned int y = 0; y < m_rows; y++) {
    for (unsigned int x = 0; x < m_cols; x++) {
      id.m_mat(x, y) = x == y ? 1. : 0.;
    }
  }
  return id;
}

void Matrix::SetValue(const unsigned int x, const unsigned int y, const double value) {
  m_mat(x, y) = value;
}

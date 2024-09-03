#pragma once

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

template <class T>
class Pseudo2DArray {
public:
  Pseudo2DArray(const unsigned int width = 1, const unsigned int height = 1);
  Pseudo2DArray(const Pseudo2DArray<T>& other);
  Pseudo2DArray(const std::vector<T>& arr, const unsigned int width, const unsigned int height);
  ~Pseudo2DArray();

  Pseudo2DArray<T>& operator=(const Pseudo2DArray<T>& other);

  T& operator()(const unsigned int x, const unsigned int y);
  T operator()(const unsigned int x, const unsigned int y) const;

  T GetValueWrapped(const int x, const int y) const;

  unsigned int GetWidth() const { return m_width; };
  unsigned int GetHeight() const { return m_height; };

  std::string Debug(const int indentSize = 0, const bool negativeFormat = false) const;

  static const std::streamsize SigFigures;

  void SwapRows(const unsigned int r1, const unsigned int r2);

private:
  //T* m_arr;
  std::vector<T> m_arr;

  unsigned int m_width;
  unsigned int m_height;
  size_t m_size;

  size_t GetIndex(const unsigned int x, const unsigned int y) const;
};

template<class T>
 inline const std::streamsize Pseudo2DArray<T>::SigFigures = 14;

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const unsigned int width, const unsigned int height) {
  m_width = width;
  m_height = height;
  m_size = size_t(width * height);

  //m_arr = new T[m_size];
  m_arr = std::vector<T>(m_size);
}

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const Pseudo2DArray<T>& other) {
  m_width = other.m_width;
  m_height = other.m_height;
  m_size = size_t(m_width * m_height);

  m_arr = other.m_arr;
}

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const std::vector<T>& arr, const unsigned int width, const unsigned int height) {
  m_width = width;
  m_height = height;
  m_size = size_t(m_width * m_height);

  m_arr = arr;
}

template<class T>
inline Pseudo2DArray<T>::~Pseudo2DArray() {
}

template<class T>
inline Pseudo2DArray<T>& Pseudo2DArray<T>::operator=(const Pseudo2DArray<T>& other) {
  if (this == &other) return *this;

  m_width = other.m_width;
  m_height = other.m_height;
  m_size = size_t(m_width * m_height);

  m_arr = other.m_arr;
  return *this;
}

template<class T>
inline T& Pseudo2DArray<T>::operator()(const unsigned int x, const unsigned int y) {
  return m_arr[GetIndex(x, y)];
}

template<class T>
inline T Pseudo2DArray<T>::operator()(const unsigned int x, const unsigned int y) const {
  return m_arr[GetIndex(x, y)];
}

template<class T>
inline T Pseudo2DArray<T>::GetValueWrapped(const int x, const int y) const {
  const int w = (int)m_width;
  const int h = (int)m_height;

  int _x = ((x % w) + w) % w;
  int _y = ((y % h) + h) % h;
  //T out = m_arr[GetIndex(_x, _y)];
  return m_arr[GetIndex(_x, _y)];
}

template<class T>
inline std::string Pseudo2DArray<T>::Debug(const int indentSize, const bool negativeFormat) const {
  std::stringstream ss;

  ss << std::fixed << std::setprecision(Pseudo2DArray<T>::SigFigures);

  for (unsigned int y = 0; y < m_height; y++) {
    for (int s = 0; s < indentSize; s++) {
      ss << ' ';
    }

    for (unsigned int x = 0; x < m_width; x++) {
      if (m_arr[GetIndex(x, y)] >= 0.0 && negativeFormat) ss << ' ';
      ss << m_arr[GetIndex(x, y)];
      ss << ' ';
    }
    ss << '\n';
  }
  return ss.str();
}

template<class T>
inline void Pseudo2DArray<T>::SwapRows(const unsigned int r1, const unsigned int r2) {
  for (unsigned int x = 0; x < m_width; x++) {
    const size_t pos1 = GetIndex(x, r1);
    const size_t pos2 = GetIndex(x, r2);

    std::iter_swap(m_arr.begin() + pos1, m_arr.begin() + pos2);
  }
}

template<class T>
inline size_t Pseudo2DArray<T>::GetIndex(const unsigned int x, const unsigned int y) const {
  return size_t(x + (y * m_width));
}

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

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

  unsigned int GetWidth() const { return m_width; };
  unsigned int GetHeight() const { return m_height; };

  std::string Debug(const int indentSize = 0) const;

private:
  //T* m_arr;
  std::vector<T> m_arr;

  unsigned int m_width;
  unsigned int m_height;
  size_t m_size;

  size_t GetIndex(const unsigned int x, const unsigned int y) const;
};

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
inline std::string Pseudo2DArray<T>::Debug(const int indentSize) const {
  std::stringstream ss;

  ss << std::fixed << std::setprecision(10);

  for (unsigned int y = 0; y < m_height; y++) {
    for (int s = 0; s < indentSize; s++) {
      ss << ' ';
    }

    for (unsigned int x = 0; x < m_width; x++) {
      ss << m_arr[GetIndex(x, y)];
      ss << ' ';
    }
    ss << '\n';
  }
  return ss.str();
}

template<class T>
inline size_t Pseudo2DArray<T>::GetIndex(const unsigned int x, const unsigned int y) const {
  return size_t(x + (y * m_width));
}

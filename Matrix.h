#pragma once
#include<iostream>

template<typename T>
class Matrix
{
	struct MatProxy {
		T* col;
		T& operator[](int i) {
			return *(col + i);
		}
		const T& operator[](int i) const {
			return *(col + i);
		}
	};

public: //ctors
	Matrix(size_t row, size_t col, T val = T{});
	Matrix(const Matrix& rhs);
	Matrix(Matrix&& rhs) noexcept;
	static Matrix eye(size_t row, size_t col);
	static Matrix eye(size_t nxn);
	~Matrix();

public: //assignments
	const Matrix& operator=(const Matrix& rhs);
	const Matrix& operator=(Matrix&& rhs) noexcept;

public: //operators
	
	void operator*=(const T& rhs);
	MatProxy operator[](int i) {
		MatProxy proxy{ matrix + (i * m) };
		return proxy;
	}
	const MatProxy operator[](int i) const {
		MatProxy proxy{ matrix + (i * m) };
		return proxy;
	}

public: //methods

	void Swap(Matrix& mat);

	Matrix Transporation() const;
	size_t GetRowCount() const { return n; }
	size_t GetColCount() const { return m; }

	void dump(std::ostream& os) const;
private:
	size_t n;
	size_t m;
	size_t sz;
	T* matrix;
};

template<typename T>
inline Matrix<T>::Matrix(size_t row, size_t col, T val) : n(row), m(col), sz(n* m), matrix(new T[sz])
{
	for (size_t i = 0; i < sz; ++i)
		matrix[i] = val;
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix& rhs) : n(rhs.n), m(rhs.m), sz(rhs.sz), matrix(new T[sz]) {
	memcpy(matrix, rhs.matrix, sizeof(T) * sz);
}

template<typename T>
inline Matrix<T>::Matrix(Matrix&& rhs) noexcept : n(rhs.n), m(rhs.m), sz(n* m), matrix(rhs.matrix) {
	rhs.matrix = nullptr;
}

template<typename T>
inline Matrix<T> Matrix<T>::eye(size_t row, size_t col) {
	Matrix eye(row, col, 1);
	return eye;
}

template<typename T>
inline Matrix<T> Matrix<T>::eye(size_t nxn) {
	Matrix eye(nxn, 1);
	return eye;
}

template<typename T>
inline Matrix<T>::~Matrix()
{
	delete[] matrix;
}

template<typename T>
inline const Matrix<T>& Matrix<T>::operator=(const Matrix& rhs) {
	Matrix copy = rhs;
	Swap(copy);
	return *this;
}

template<typename T>
inline const Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) noexcept {
	Swap(rhs);
	return *this;
}

template<typename T>
inline void Matrix<T>::operator*=(const T& rhs) {
	for (size_t i = 0; i < sz; ++i)
		matrix[i] *= rhs;
}

template<typename T>
inline void Matrix<T>::Swap(Matrix& mat)
{
	std::swap(matrix, mat.matrix);
	std::swap(n, mat.n);
	std::swap(m, mat.m);
	std::swap(sz, mat.sz);
}

template<typename T>
inline Matrix<T> Matrix<T>::Transporation() const {
	Matrix tranted(m, n);
	size_t count = 0;
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			tranted[j][i] = matrix[count++];
	return tranted;
}

template<typename T>
inline void Matrix<T>::dump(std::ostream& os) const
{
	for (size_t i = 0; i < sz; ++i) {
		if (i != 0 && i % m == 0) os << '\n';
		os << matrix[i] << ' ';
	}
}

template<typename T>
Matrix<T> operator* (const Matrix<T>& lhs, const T& rhs) {
	Matrix<T> result(lhs);
	result *= rhs;
	return result;
}

template<typename T>
Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs) {
	Matrix<T> result(rhs);
	result *= lhs;
	return result;
}

template<typename T>
Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs) {
	if (lhs.GetColCount() != rhs.GetRowCount()) return Matrix<T>(1, 1);
	size_t n = lhs.GetRowCount();
	size_t m = rhs.GetColCount();
	Matrix<T> result(n, m);
	size_t count = lhs.GetColCount();
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			for (size_t k = 0; k < count; k++)
				result[i][j] += lhs[i][k] * rhs[k][j];

	return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& lhs) {
	lhs.dump(os);
	return os;
}
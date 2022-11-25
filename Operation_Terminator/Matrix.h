#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include "MatrixException.h"

template<typename T>
class Matrix {
public:
	Matrix(size_t nRows, size_t nCols);
	Matrix(const Matrix &t);
	Matrix(Matrix&& other);
	~Matrix();

	Matrix Add(const Matrix& other);
	
	template<typename SCALAR_TYPE>
	inline Matrix MulScalar(const SCALAR_TYPE scalar) {
		Matrix<T> toReturn(m_NRows, m_NCols);
		size_t numEntries = NumEntries();
		for (int i = 0; i < numEntries; i++)
		{
			toReturn.m_BackingArray[i] = m_BackingArray[i] * scalar;
		}

		return toReturn;
	}

	const size_t RowCount() {
		return m_NCols;
	}
	const size_t ColCount() {
		return m_NRows;
	}

	size_t NumEntries() {
		return m_NRows * m_NCols;
	}

	// Move assignment operator
	Matrix& operator=(Matrix&& other) {
		if (this == other) {
			return *this;
		}
		delete[] m_BackingArray;
		m_BackingArray = nullptr;
		
		m_BackingArray = other.m_BackingArray;
		m_NCols = other.m_NCols;
		m_NRows = other.m_NRows;

		other.m_BackingArray = nullptr;
		other.m_NCols = 0;
		other.m_NRows = 0;

		return *this;
	}

	Matrix operator+(const Matrix &other) {
		if (other.m_NCols != m_NCols || other.m_NRows != m_NRows) {
			throw MatrixIncompatibleSizeException();
		}
		return Add(other);
	}

	template<typename SCALAR_TYPE>
	Matrix operator*(const SCALAR_TYPE scalar) {
		return MulScalar(scalar);
	}

	//void PrintMatrix()
	/*template<typename K>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<K>& mat) {
		
		os << "Hej";
		return os;
		for (int i = 0; i < mat.NumEntries(); i++) {
			if (i > 0 && i % mat.m_NCols == 0) {
				os << "\n";
			}
			//os << std::to_string(mat.m_BackingArray[i]);
			os << mat.m_BackingArray[i] << " ";
		}
		return os;
	}*/

	T* m_BackingArray;
	size_t m_NRows, m_NCols;
private:

};




template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
	size_t numEntries = mat.m_NCols * mat.m_NRows;
	
	for (int i = 0; i < numEntries; i++) {
		if (i > 0 && i % mat.m_NCols == 0) {
			os << "\n";
		}
		os << mat.m_BackingArray[i] << " ";
	}
	os << "\n";
	return os;
}


template<typename T>
Matrix<T>::Matrix(size_t nRows, size_t nCols): m_NRows(nRows), m_NCols(nCols)
{
	m_BackingArray = new T[nRows * nCols];
}

// Move constructor
template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) {
	m_BackingArray = other.m_BackingArray;
	m_NCols = other.m_NCols;
	m_NRows = other.m_NRows;

	other.m_BackingArray = nullptr;
	other.m_NCols = 0;
	other.m_NRows = 0;
}

template<typename T>
Matrix<T>::~Matrix() {
	if(m_BackingArray != nullptr)
		delete[] m_BackingArray;
}

template<typename T>
Matrix<T>::Matrix(const Matrix &t) {
	m_NRows = t.m_NRows;
	m_NCols = t.m_NCols;
	m_BackingArray = new T[m_NRows * m_NCols];
	memcpy(m_BackingArray, t.m_BackingArray, sizeof(T) * t.m_NCols * t.m_NRows);
}

/*template<typename T, typename SCALAR_TYPE>
Matrix<T> Matrix<T>::MulScalar(const SCALAR_TYPE scalar) {
	Matrix<T> toReturn(m_NRows, m_NCols);
	
	return toReturn;
}*/

template<typename T>
Matrix<T> Matrix<T>::Add(const Matrix& other) {
	Matrix<T> toReturn(m_NRows, m_NCols);
	size_t numEntries = NumEntries();
	for (int i = 0; i < numEntries; i++)
	{
		toReturn.m_BackingArray[i] = m_BackingArray[i] + other.m_BackingArray[i];
	}

	return toReturn;
}
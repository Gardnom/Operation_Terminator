#pragma once
#include <iostream>

class MatrixIncompatibleSizeException : public std::exception {
public:
	MatrixIncompatibleSizeException() {

	}
	MatrixIncompatibleSizeException(size_t leftNumCols, size_t rightNumRows): m_LeftNumCols(leftNumCols), m_RightNumRows(rightNumRows) {
		
	}
	char * what() {
		if (m_LeftNumCols > 0 && m_RightNumRows > 0) {
			return (char*)"Number of columns of left hand matrix must match number of rows on right hand matrix";
		}
		return (char*)"Number of columns of left hand matrix must match number of rows on right hand matrix";
	}
private:
	size_t m_LeftNumCols, m_RightNumRows;
};

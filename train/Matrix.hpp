#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix
{
public:
	Matrix() : rows(0), cols(0) {};
	Matrix(int num_rows, int num_cols);
	void Reset(int num_rows, int num_cols);
	Matrix& operator=(const Matrix& mat);
	const int& At(int row, int col) const;
	int& At(int row, int col);
	int GetNumRows() const;
	int GetNumCols() const;
	bool operator==(const Matrix& mat) const;
	Matrix& operator+(const Matrix& mat) const;

private:
	int rows;
	int cols;
	std::vector<std::vector<int>> m;
};

Matrix::Matrix(int num_rows, int num_cols) : rows(num_rows), cols(num_cols)
{
	if (rows < 0 || cols < 0)
	{
		throw std::out_of_range("Negative arguments to a matrix!");
	}
	m = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	this->cols = mat.cols;
	this->rows = mat.rows;
	this->m = mat.m;
	return *this;
}

void Matrix::Reset(int num_rows, int num_cols)
{
	*this = Matrix{num_rows, num_cols};
}

const int& Matrix::At(int row, int col) const
{
	if (row < 0 || col < 0)
	{
		throw std::out_of_range("Matrice indecies are out of range!");
	}
	return m[row][col];
}

int& Matrix::At(int row, int col)
{
	if (row < 0 || col < 0)
	{
		throw std::out_of_range("Matrice indecies are out of range!");
	}
	return m[row][col];
}

int Matrix::GetNumRows() const
{
	return rows;
}

int Matrix::GetNumCols() const
{
	return cols;
}

bool Matrix::operator==(const Matrix& mat) const
{
	return this->m == mat.m ? true : false;
}

Matrix& Matrix::operator+(const Matrix& mat) const
{
	if (rows != mat.GetNumRows() || cols != mat.GetNumCols())
	{
		throw std::invalid_argument("Matrices have different dimensions!");
	}
	
	Matrix ret(rows, cols);

	for (int i = 0; i != rows; ++i)
	{
		for (int j = 0; j != cols; ++j)
		{
			ret.At(i, j) = static_cast<const Matrix*>(&mat)->At(i, j) + static_cast<const Matrix*>(this)->At(i, j);
		}
	}

	return ret;
}


std::istream& operator>>(std::istream& in, Matrix& mat)
{
	int rows, cols, el;
	in >> rows >> cols;

	mat.Reset(rows, cols);
	for (int i = 0; i != rows; ++i)
	{
		for (int j = 0; j != cols; ++j)
		{
			in >> el;
			mat.At(i, j) = el;
		}
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, Matrix& mat)
{
	std::cout << mat.GetNumRows() << ' ' << mat.GetNumCols() << std::endl;

	for (int i = 0; i != mat.GetNumRows(); ++i)
	{
		for (int j = 0; j != mat.GetNumCols(); ++j)
		{
			if (j != 0) std::cout << ' ';
			out << static_cast<const Matrix*>(&mat)->At(i, j);
		}
		std::cout << std::endl;
	}

	return out;
}

#endif // MATRIX_HPP
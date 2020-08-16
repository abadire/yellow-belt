#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

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
	int GetNumColumns() const;
	bool operator==(const Matrix& mat) const;
	Matrix operator+(const Matrix& mat) const;

private:
	int rows;
	int cols;
	std::vector<std::vector<int>> m;
};

Matrix::Matrix(int num_rows, int num_cols)
{
	Reset(num_rows, num_cols);
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
	if (num_rows < 0 || num_cols < 0)
	{
		throw std::out_of_range("Invalid arguments!");
	}
	else if (num_rows == 0 || num_cols == 0)
	{
		num_rows = num_cols = 0;
	}

	rows = num_rows;
	cols = num_cols;
	m = std::vector<std::vector<int>>(rows, vector<int>(cols, 0));
}

const int& Matrix::At(int row, int col) const
{
	if (row < 0 || col < 0 || row >= this->rows || col >= this->cols)
	{
		throw std::out_of_range("Matrice indecies are out of range!");
	}
	return m[row][col];
}

int& Matrix::At(int row, int col)
{
	if (row < 0 || col < 0 || row >= this->rows || col >= this->cols)
	{
		throw std::out_of_range("Matrice indecies are out of range!");
	}
	return m[row][col];
}

int Matrix::GetNumRows() const
{
	return rows;
}

int Matrix::GetNumColumns() const
{
	return cols;
}

bool Matrix::operator==(const Matrix& mat) const
{
	return this->m == mat.m ? true : false;
}

Matrix Matrix::operator+(const Matrix& mat) const
{
	if (rows != mat.GetNumRows() || cols != mat.GetNumColumns())
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

std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	out << mat.GetNumRows() << ' ' << mat.GetNumColumns() << std::endl;

	for (int i = 0; i != mat.GetNumRows(); ++i)
	{
		if (i != 0) out << std::endl;
		for (int j = 0; j != mat.GetNumColumns(); ++j)
		{
			if (j != 0) out << ' ';
			out << static_cast<const Matrix*>(&mat)->At(i, j);
		}
	}

	return out;
}

int main()
{
  Matrix one;
  Matrix two;

  	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
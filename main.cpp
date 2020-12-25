#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Matrix {
public:
    Matrix() {};

    Matrix(int num_rows, int num_cols) {
        this->resize(num_rows, num_cols);
    };

    void Reset(int num_rows, int num_cols) {
        this->resize(num_rows, num_cols);
    }

    int At(int num_row, int num_col) const {
        return this->matrix.at(num_row).at(num_col);
    }

    int& At(int num_row, int num_col) {
        return this->matrix.at(num_row).at(num_col);
    }

    int GetNumRows() const {
        return matrix.size();
    }

    int GetNumColumns() const {
        return matrix.empty() ? 0 : matrix.at(0).size();
    }

private:
    vector<vector<int>> matrix;

    void resize(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("Rows and cols can't be less zero");
        }

        this->matrix.resize(num_rows, vector<int>(num_cols, 0));
    }

};

istream& operator>> (istream& stream, Matrix& matrix) {
    int num_rows, num_cols;

    stream >> num_rows >> num_cols;

    matrix = Matrix(num_rows, num_cols);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            stream >> matrix.At(i, j);
        }
    }

    return stream;
}

ostream& operator<< (ostream& stream, const Matrix& matrix) {
    int num_rows = matrix.GetNumRows();
    int num_cols = matrix.GetNumColumns();
    stream << num_rows << " " << num_cols << endl;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            stream << matrix.At(i, j) << " ";
        }
        stream << endl;
    }

    return stream;
}

bool operator== (const Matrix& lhs, const Matrix& rhs) {
    int num_rows = lhs.GetNumRows();
    int num_cols = lhs.GetNumColumns();

    if (num_cols != rhs.GetNumColumns() ||
        num_rows != rhs.GetNumRows()) {
        return false;
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (lhs.At(i, j) != rhs.At(i, j)) {
                return false;
            }
        }
    }

    return true;
}

Matrix operator+ (const Matrix& lhs, const Matrix& rhs) {
    int num_rows = lhs.GetNumRows();
    int num_cols = lhs.GetNumColumns();

    if (num_cols != rhs.GetNumColumns() ||
        num_rows != rhs.GetNumRows()) {
        throw invalid_argument("Matrix' should have the same size!");
    }

    Matrix matrix(num_rows, num_cols);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }

    return matrix;
}

int main() {
    Matrix one;
    Matrix two;

    cin >> one;
//    >> two;
//    cout << one + two << endl;
//    cout << (one == two) << endl;

    one.Reset(2, 2);

    cout << "after reset" << endl << one << endl;

    return 0;
}

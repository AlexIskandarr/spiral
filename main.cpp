#include <iostream>
#include <cstdint>
#include <stdexcept>

int64_t** allocateMatrix(int64_t, int64_t);
void fillMatrix(int64_t**, int64_t, int64_t);
void freeMatrix(int64_t**, int64_t);
void spiralPrint(int64_t**, int64_t, int64_t);

int main() {
    try {
        int64_t rows{};
        int64_t cols{};

        std::cout << "Enter number of rows: ";
        if (!(std::cin >> rows) || rows <= 0) {
            throw std::invalid_argument("Invalid input for rows. Must be a positive integer.");
        }

        std::cout << "Enter number of columns: ";
        if (!(std::cin >> cols) || cols <= 0) {
            throw std::invalid_argument("Invalid input for columns. Must be a positive integer.");
        }

        int64_t** matrix{allocateMatrix(rows, cols)};
        fillMatrix(matrix, rows, cols);
        
        std::cout << "\nSpiral output:\n";
        spiralPrint(matrix, rows, cols);
        
        freeMatrix(matrix, rows);

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << '\n'; 
        return 1;
    }

    return 0;
}

int64_t** allocateMatrix(int64_t rows, int64_t cols) {
    int64_t** matrix{new int64_t*[rows]};
    for (int64_t i{0}; i < rows; ++i) {
        matrix[i] = new int64_t[cols]{};
    }
    return matrix;
}

void fillMatrix(int64_t** matrix, int64_t rows, int64_t cols) {
    std::cout << "\nEnter matrix elements:\n";
    for (int64_t i{0}; i < rows; ++i) {
        for (int64_t j{0}; j < cols; ++j) {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }
}

void freeMatrix(int64_t** matrix, int64_t rows) {
    for (int64_t i{0}; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void spiralPrint(int64_t** arr, int64_t rows, int64_t cols) {
    int64_t top{0};
    int64_t bottom{rows - 1};
    int64_t left{0};
    int64_t right{cols - 1};

    while (top <= bottom && left <= right) {
        for (int64_t i{left}; i <= right; ++i) {
            std::cout << arr[top][i] << " ";
        }
        ++top;

        if (top <= bottom) {
            for (int64_t i{top}; i <= bottom; ++i) {
                std::cout << arr[i][right] << " ";
            }
            --right;
        }

        if (top <= bottom && left <= right) {
            for (int64_t i{right}; i >= left; --i) {
                std::cout << arr[bottom][i] << " ";
            }
            --bottom;
        }

        if (left <= right && top <= bottom) {
            for (int64_t i{bottom}; i >= top; --i) {
                std::cout << arr[i][left] << " ";
            }
            ++left;
        }
    }
}
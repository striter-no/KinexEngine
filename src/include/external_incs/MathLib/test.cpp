#include <iostream>
#include <vector>
#include <AdtClasses/AdtClasses.hpp>

// Функция для проверки, являются ли размеры зеркальными
bool areSizesMirror(const std::vector<int>& size1, const std::vector<int>& size2) {
    return size1[0] == size2[1] && size1[1] == size2[0];
}

// Функция для проверки условия 2
bool isCondition2Met(const std::vector<int>& size1, const std::vector<int>& size2) {
    return (size2[0] == 1 && size2[1] == size1[0] * size1[1]) || (size2[1] == 1 && size2[0] == size1[0] * size1[1]);
}

// Функция для проверки условия 3
bool arePrimeFactorsEqual(const std::vector<int>& size1, const std::vector<int>& size2) {
    for(int i: size1){
        factorize(i)
        if()
    }
}

// Функция для реформирования вектора
std::vector<std::vector<float>> reshape(const std::vector<std::vector<float>>& originalVector, const std::vector<int>& newSize) {
    std::vector<int> originalSize = {static_cast<int>(originalVector.size()), static_cast<int>(originalVector[0].size())};

    if (areSizesMirror(originalSize, newSize) || isCondition2Met(originalSize, newSize) || arePrimeFactorsEqual(originalSize, newSize)) {
        std::vector<std::vector<float>> newVector(newSize[0], std::vector<float>(newSize[1]));

        // Реформирование вектора
        for (int i = 0; i < newSize[0]; ++i) {
            for (int j = 0; j < newSize[1]; ++j) {
                int originalRow = i * newSize[1] / originalSize[1];
                int originalCol = j * newSize[0] / originalSize[0];
                newVector[i][j] = originalVector[originalRow][originalCol];
            }
        }

        return newVector;
    } else {
        std::cout << "Невозможно выполнить реформирование" << std::endl;
        return originalVector;  // Возвращаем исходный вектор без изменений
    }
}

int main() {
    // Пример использования
    std::vector<std::vector<float>> originalMatrix = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    std::vector<int> newSize = {2, 3};
    std::vector<std::vector<float>> reshapedMatrix = reshape(originalMatrix, newSize);

    // Вывод реформированной матрицы
    for (const auto& row : reshapedMatrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

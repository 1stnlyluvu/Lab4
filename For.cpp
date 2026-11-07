#include <gtest/gtest.h>
#include <utility>
#include <vector>

const double price_eps = 0.000001;

/// Возвращает числа между A и B по убыванию и их количество. Задача For3.
std::pair<std::vector<int>, int> numbers_between_descending(int a, int b) {
    std::vector<int> numbers;
    int count = 0;

    for (int number = b - 1; number > a; number--) {
        numbers.push_back(number);
        count++;
    }

    return {numbers, count};
}

/// Рассчитывает стоимость 1, 2, ..., 10 кг конфет. Задача For4.
std::vector<double> candy_prices(double price_per_kg) {
    std::vector<double> prices;

    for (int kilos = 1; kilos <= 10; kilos++) {
        prices.push_back(price_per_kg * kilos);
    }

    return prices;
}

/// Возвращает последовательные суммы нечётных чисел: 1^2, 2^2, ..., N^2.
/// Задача For14.
std::vector<long long> squares_by_odd_sums(int n) {
    std::vector<long long> squares;
    long long sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += 2LL * i - 1;
        squares.push_back(sum);
    }

    return squares;
}

/// Проверка обычного промежутка.
TEST(For3, SeveralNumbers) {
    // Arrange
    int a = 2, b = 7;
    std::vector<int> expected = {6, 5, 4, 3};
    // Act
    auto result = numbers_between_descending(a, b);
    // Assert
    EXPECT_EQ(result.first, expected);
    EXPECT_EQ(result.second, 4);
}

/// Проверка соседних чисел.
TEST(For3, AdjacentNumbers) {
    // Arrange
    int a = 4, b = 5;
    std::vector<int> expected;
    // Act
    auto result = numbers_between_descending(a, b);
    // Assert
    EXPECT_EQ(result.first, expected);
    EXPECT_EQ(result.second, 0);
}

/// Проверка промежутка с отрицательными числами.
TEST(For3, NegativeNumbers) {
    // Arrange
    int a = -2, b = 2;
    std::vector<int> expected = {1, 0, -1};
    // Act
    auto result = numbers_between_descending(a, b);
    // Assert
    EXPECT_EQ(result.first, expected);
    EXPECT_EQ(result.second, 3);
}

/// Проверка стоимости при целой цене.
TEST(For4, WholePrice) {
    // Arrange
    double price_per_kg = 100;
    // Act
    auto result = candy_prices(price_per_kg);
    // Assert
    EXPECT_EQ(result.size(), 10u);
    EXPECT_NEAR(result[0], 100, price_eps);
    EXPECT_NEAR(result[9], 1000, price_eps);
}

/// Проверка стоимости при дробной цене.
TEST(For4, FractionalPrice) {
    // Arrange
    double price_per_kg = 12.5;
    // Act
    auto result = candy_prices(price_per_kg);
    // Assert
    EXPECT_EQ(result.size(), 10u);
    EXPECT_NEAR(result[1], 25, price_eps);
    EXPECT_NEAR(result[9], 125, price_eps);
}

/// Проверка стоимости с округляемой двоичной дробью.
TEST(For4, SmallFractionalPrice) {
    // Arrange
    double price_per_kg = 0.1;
    // Act
    auto result = candy_prices(price_per_kg);
    // Assert
    EXPECT_NEAR(result[2], 0.3, price_eps);
    EXPECT_NEAR(result[9], 1.0, price_eps);
}

/// Проверка минимального N.
TEST(For14, One) {
    // Arrange
    int n = 1;
    std::vector<long long> expected = {1};
    // Act
    auto result = squares_by_odd_sums(n);
    // Assert
    EXPECT_EQ(result, expected);
}

/// Проверка первых четырёх квадратов.
TEST(For14, Four) {
    // Arrange
    int n = 4;
    std::vector<long long> expected = {1, 4, 9, 16};
    // Act
    auto result = squares_by_odd_sums(n);
    // Assert
    EXPECT_EQ(result, expected);
}

/// Проверка первых семи квадратов.
TEST(For14, Seven) {
    // Arrange
    int n = 7;
    std::vector<long long> expected = {1, 4, 9, 16, 25, 36, 49};
    // Act
    auto result = squares_by_odd_sums(n);
    // Assert
    EXPECT_EQ(result, expected);
}

#include <gtest/gtest.h>
#include <array>
#include <cmath>
#include <string>
#include <utility>

const double eps = 0.000001;

/// Возвращает следующую дату невисокосного года. Задача Case9.
std::pair<int, int> next_date(int day, int month) {
    int days_in_month;

    switch (month) {
    case 2:
        days_in_month = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days_in_month = 30;
        break;
    default:
        days_in_month = 31;
    }

    if (day < days_in_month) {
        day++;
    }
    else {
        day = 1;
        month++;
        if (month == 13) {
            month = 1;
        }
    }

    return {day, month};
}

/// Даёт словесное описание оценки. Задача Case2.
std::string describe_grade(int grade) {
    switch (grade) {
    case 1: return "плохо";
    case 2: return "неудовлетворительно";
    case 3: return "удовлетворительно";
    case 4: return "хорошо";
    case 5: return "отлично";
    default: return "ошибка";
    }
}

/// Возвращает остальные три элемента равнобедренного прямоугольного треугольника.
/// Задача Case13. Номера: 1 - катет, 2 - гипотенуза, 3 - высота, 4 - площадь.
/// Результат содержит остальные элементы в порядке их номеров.
std::array<double, 3> other_triangle_elements(int element, double value) {
    double leg = 0;

    switch (element) {
    case 1:
        leg = value;
        break;
    case 2:
        leg = value / std::sqrt(2.0);
        break;
    case 3:
        leg = value * std::sqrt(2.0);
        break;
    case 4:
        leg = std::sqrt(2.0 * value);
        break;
    default:
        return {0, 0, 0};
    }

    double hypotenuse = leg * std::sqrt(2.0);
    double height = hypotenuse / 2;
    double area = leg * leg / 2;
    std::array<double, 4> all = {leg, hypotenuse, height, area};
    std::array<double, 3> others{};
    int position = 0;

    for (int i = 0; i < 4; i++) {
        if (i != element - 1) {
            others[position] = all[i];
            position++;
        }
    }
    return others;
}

/// Проверка обычной даты.
TEST(Case9, MiddleOfMonth) {
    // Arrange
    int day = 14, month = 3;
    // Act
    auto result = next_date(day, month);
    // Assert
    EXPECT_EQ(result.first, 15);
    EXPECT_EQ(result.second, 3);
}

/// Проверка конца месяца из 30 дней.
TEST(Case9, ThirtyDayMonth) {
    // Arrange
    int day = 30, month = 4;
    // Act
    auto result = next_date(day, month);
    // Assert
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 5);
}

/// Проверка последнего дня февраля невисокосного года.
TEST(Case9, FebruaryEnd) {
    // Arrange
    int day = 28, month = 2;
    // Act
    auto result = next_date(day, month);
    // Assert
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 3);
}

/// Проверка перехода на следующий год.
TEST(Case9, NewYear) {
    // Arrange
    int day = 31, month = 12;
    // Act
    auto result = next_date(day, month);
    // Assert
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 1);
}

/// Проверка оценки 1.
TEST(Case2, GradeOne) {
    // Arrange
    int grade = 1;
    // Act
    std::string result = describe_grade(grade);
    // Assert
    EXPECT_EQ(result, "плохо");
}

/// Проверка оценки 3.
TEST(Case2, GradeThree) {
    // Arrange
    int grade = 3;
    // Act
    std::string result = describe_grade(grade);
    // Assert
    EXPECT_EQ(result, "удовлетворительно");
}

/// Проверка оценки 5.
TEST(Case2, GradeFive) {
    // Arrange
    int grade = 5;
    // Act
    std::string result = describe_grade(grade);
    // Assert
    EXPECT_EQ(result, "отлично");
}

/// Проверка неверной оценки.
TEST(Case2, InvalidGrade) {
    // Arrange
    int grade = 6;
    // Act
    std::string result = describe_grade(grade);
    // Assert
    EXPECT_EQ(result, "ошибка");
}

/// По катету получаем гипотенузу, высоту и площадь.
TEST(Case13, GivenLeg) {
    // Arrange
    int element = 1;
    double value = 4;
    // Act
    auto result = other_triangle_elements(element, value);
    // Assert
    EXPECT_NEAR(result[0], 4 * std::sqrt(2.0), eps);
    EXPECT_NEAR(result[1], 2 * std::sqrt(2.0), eps);
    EXPECT_NEAR(result[2], 8, eps);
}

/// По гипотенузе получаем катет, высоту и площадь.
TEST(Case13, GivenHypotenuse) {
    // Arrange
    int element = 2;
    double value = 10;
    // Act
    auto result = other_triangle_elements(element, value);
    // Assert
    EXPECT_NEAR(result[0], 5 * std::sqrt(2.0), eps);
    EXPECT_NEAR(result[1], 5, eps);
    EXPECT_NEAR(result[2], 25, eps);
}

/// По высоте получаем катет, гипотенузу и площадь.
TEST(Case13, GivenHeight) {
    // Arrange
    int element = 3;
    double value = 3;
    // Act
    auto result = other_triangle_elements(element, value);
    // Assert
    EXPECT_NEAR(result[0], 3 * std::sqrt(2.0), eps);
    EXPECT_NEAR(result[1], 6, eps);
    EXPECT_NEAR(result[2], 9, eps);
}

/// По площади получаем катет, гипотенузу и высоту.
TEST(Case13, GivenArea) {
    // Arrange
    int element = 4;
    double value = 18;
    // Act
    auto result = other_triangle_elements(element, value);
    // Assert
    EXPECT_NEAR(result[0], 6, eps);
    EXPECT_NEAR(result[1], 6 * std::sqrt(2.0), eps);
    EXPECT_NEAR(result[2], 3 * std::sqrt(2.0), eps);
}

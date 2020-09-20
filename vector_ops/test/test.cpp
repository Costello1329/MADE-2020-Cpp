#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <valarray>
#include <sstream>
#include <cmath>
#include "src/vector_ops.h"


using namespace task;


size_t RandomUInt(size_t max = -1) {
    static std::mt19937 rand(std::random_device{}());

    std::uniform_int_distribution<size_t> dist{0, max};
    return dist(rand);
}

size_t RandomUInt(size_t min, size_t max) {
    return min + RandomUInt(max - min);
}

bool TossCoin() {
    return RandomUInt(1) == 0;
}


template <class T>
void RandomFill(T& container, size_t count, size_t max = -1) {
    while (count > 0) {
        container.push_back(RandomUInt(max));
        --count;
    }
}

double RandomDouble() {
    static std::mt19937 rand(std::random_device{}());

    std::uniform_real_distribution<double> dist{-10., 10.};
    return dist(rand);
}

template <class T>
void RandomFillDouble(T& container, size_t count) {
    while (count > 0) {
        container.push_back(RandomDouble());
        --count;
    }
}


void FailWithMsg(const std::string& msg, int line) {
    std::cerr << "Test failed!\n";
    std::cerr << "[Line " << line << "] "  << msg << std::endl;
    std::exit(EXIT_FAILURE);
}

#define ASSERT_TRUE(cond) \
    if (!(cond)) {FailWithMsg("Assertion failed: " #cond, __LINE__);};

#define ASSERT_TRUE_MSG(cond, msg) \
    if (!(cond)) {FailWithMsg(msg, __LINE__);};

#define ASSERT_EQUAL_MSG(cont1, cont2, msg) \
    ASSERT_TRUE_MSG(std::equal(std::begin(cont1), std::end(cont1), std::begin(cont2), std::end(cont2)), msg)


#define REPEAT(count) for (size_t _iter = 0; _iter < count; ++_iter)


const double EPS = 1e-7;


int main() {

    {
        const std::vector<double> a(3, 2.), b(3, 3.);

        a + b;
        a - b;
        +a;
        -a;
        a * b;
        a % b;
        a || b;
        a && b;
    }

    {
        const std::vector<int> a, b;

        a | b;
        a & b;
    }


    REPEAT(100)
    {
        std::vector<double> vec, vec2;
        RandomFillDouble(vec, 1000);
        std::valarray<double> valarr(vec.data(), vec.size());


        RandomFillDouble(vec2, vec.size());
        vec = vec + vec2;
        valarr = valarr + std::valarray<double>(vec2.data(), vec2.size());

        ASSERT_EQUAL_MSG(vec, valarr, "Binary +")


        vec2.clear();
        RandomFillDouble(vec2, vec.size());
        vec = vec - vec2;
        valarr = valarr - std::valarray<double>(vec2.data(), vec2.size());

        ASSERT_EQUAL_MSG(vec, valarr, "Binary -")


        vec = +vec;
        valarr = +valarr;
        ASSERT_EQUAL_MSG(vec, valarr, "Unary +")


        vec = -vec;
        valarr = -valarr;
        ASSERT_EQUAL_MSG(vec, valarr, "Unary -")


        vec2.clear();
        RandomFillDouble(vec2, vec.size());
        double res = vec * vec2;
        double res2 = (valarr * std::valarray<double>(vec2.data(), vec2.size())).sum();

        ASSERT_TRUE_MSG(fabs(res - res2) < EPS, "Dot product")
    }

    REPEAT(100)
    {
        std::vector<int> vec, vec2;
        RandomFill(vec, 1000);
        std::valarray<int> valarr(vec.data(), vec.size());


        RandomFill(vec2, vec.size());
        vec = vec | vec2;
        valarr = valarr | std::valarray<int>(vec2.data(), vec2.size());

        ASSERT_EQUAL_MSG(vec, valarr, "Bitwise OR")


        vec2.clear();
        RandomFill(vec2, vec.size());
        vec = vec & vec2;
        valarr = valarr & std::valarray<int>(vec2.data(), vec2.size());

        ASSERT_EQUAL_MSG(vec, valarr, "Bitwise AND")
    }

    REPEAT(100)
    {
        std::vector<double> vec, vec2;
        RandomFillDouble(vec, 3);
        RandomFillDouble(vec2, vec.size());

        auto cross = vec % vec2;

        ASSERT_TRUE_MSG(fabs(cross * vec) < EPS && fabs(cross * vec2) < EPS, "Cross product")


        vec = {0., 0., RandomDouble()};
        vec2 = {RandomDouble(), 0., 0.};

        cross = vec % vec2;

        ASSERT_TRUE_MSG(fabs(cross * cross - vec[2] * vec[2] * vec2[0] * vec2[0]) < EPS, "Cross product")
    }

    REPEAT(100)
    {
        std::vector<double> vec, vec2;
        RandomFillDouble(vec, 1000);

        auto mult = RandomDouble();

        for (auto& item : vec) {
            vec2.push_back(item * mult);
        }

        ASSERT_TRUE_MSG(vec || vec2, "Collinearity operator")
        ASSERT_TRUE_MSG((vec && vec2) == (mult > 0), "Codirectionality operator")
    }

    REPEAT(100)
    {
        std::vector<double> vec, vec2;
        RandomFillDouble(vec, 1000);

        std::stringstream stream;
        stream << vec.size() << '\n';
        stream << vec;

        ASSERT_TRUE_MSG(*(stream.str().end() - 1) == '\n', "Stream output operator")

        stream >> vec2;
        ASSERT_TRUE(vec.size() == vec2.size())

        for (size_t i = 0; i < vec.size(); ++i) {
            ASSERT_TRUE_MSG(fabs(vec[i] - vec2[i]) < 1e-2, "Stream input operator")
        }

        RandomFillDouble(vec2, RandomUInt(800, 1000));
        vec = vec2;
        reverse(vec);
        std::reverse(vec2.begin(), vec2.end());

        ASSERT_EQUAL_MSG(vec, vec2, "reverse")
    }

}

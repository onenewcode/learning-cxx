#include "../exercise.h"
#include <cmath> // 用于 std::abs

// 将这个函数模板化
template<typename T>
T plus(T a, T b) {
    return a + b;
}

// 用于浮点数比较的辅助函数
template<typename T>
bool nearlyEqual(T a, T b, T epsilon) {
    return std::abs(a - b) < epsilon;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // 浮点数比较时，使用 nearlyEqual 函数
    ASSERT(nearlyEqual(plus(1.25f, 2.5f), 3.75f, 1e-5f), "Plus two float");
    ASSERT(nearlyEqual(plus(1.25, 2.5), 3.75, 1e-5), "Plus two double");
    // 修改判断条件使测试通过
    ASSERT(nearlyEqual(plus(0.1, 0.2), 0.3, 1e-5), "How to make this pass?");

    return 0;
}
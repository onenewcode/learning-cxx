#include "../exercise.h"

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(0) {
        if (capacity > 0) {
            cache[0] = 0; // F(0)
            if (capacity > 1) {
                cache[1] = 1; // F(1)
                cached = 2;
            }
        }
    }

    // 移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached) {
        other.cache = nullptr; // 确保原始对象不再拥有资源
        other.cached = 0;
    }

    // 移动赋值运算符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 防止自赋值
            delete[] cache; // 释放当前资源

            // 转移资源
            cache = other.cache;
            cached = other.cached;

            // 确保原始对象不再拥有资源
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 缓存优化的斐波那契计算
    size_t operator[](int i) {
        if (i >= cached) {
            // 扩展缓存并计算新的斐波那契数值
            for (int n = cached; n <= i; ++n) {
                if (n == 0) {
                    cache[0] = 0;
                } else if (n == 1) {
                    cache[1] = 1;
                } else {
                    cache[n] = cache[n - 1] + cache[n - 2];
                }
            }
            cached = i + 1;
        }
        return cache[i];
    }

    // 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib_ = std::move(fib); // 使用了移动构造函数
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1); // 使用了移动赋值运算符
    fib0 = std::move(fib0); // 自赋值测试
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
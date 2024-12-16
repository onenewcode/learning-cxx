#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


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

    // 复制构造器
    DynFibonacci(const DynFibonacci &other) : cache(new size_t[other.cached]), cached(other.cached) {
        for (int i = 0; i < other.cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 缓存优化的斐波那契计算
    size_t get(int i) {
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
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}

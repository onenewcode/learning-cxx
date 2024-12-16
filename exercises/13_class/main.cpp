#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 构造器，初始化cache数组为0，并设置cached为0。
    Fibonacci() : cached(0) {
        for (size_t &val : cache) {
            val = 0;
        }
    }

    // 计算并返回第i个斐波那契数（假设索引从0开始，即fib(0)=0, fib(1)=1）。
    size_t get(int i) {
        // 如果请求的索引超过了我们想要缓存的最大数量，则抛出异常或返回错误值。
        if (i >= 16) {
            throw std::out_of_range("Index out of range for Fibonacci cache");
        }

        // 如果已经缓存了所需的斐波那契数，则直接返回它。
        if (i < cached) {
            return cache[i];
        }

        // 初始化缓存，如果还没有进行过。
        if (cached == 0) {
            cache[0] = 0;
            cached++;
        }
        if (cached == 1) {
            cache[1] = 1;
            cached++;
        }

        // 计算剩余未缓存的斐波那契数。
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }

        return cache[i];
    }
};


int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}

#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
     constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 直接调用成员函数
    ASSERT(a.virtual_name() == 'A', MSG); // 调用的是 A 的 virtual_name
    ASSERT(b.virtual_name() == 'B', MSG); // 调用的是 B 的 virtual_name
    ASSERT(c.virtual_name() == 'C', MSG); // 调用的是 C 的 virtual_name
    ASSERT(d.virtual_name() == 'C', MSG); // 调用的是 C 的 virtual_name (因为它是 final)

    ASSERT(a.direct_name() == 'A', MSG); // 调用的是 A 的 direct_name
    ASSERT(b.direct_name() == 'B', MSG); // 调用的是 B 的 direct_name
    ASSERT(c.direct_name() == 'C', MSG); // 调用的是 C 的 direct_name
    ASSERT(d.direct_name() == 'D', MSG); // 调用的是 D 的 direct_name

    // 通过基类引用调用成员函数
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); // 通过 A& 调用 B 的 virtual_name
    ASSERT(rbc.virtual_name() == 'C', MSG); // 通过 B& 调用 C 的 virtual_name
    ASSERT(rcd.virtual_name() == 'C', MSG); // 通过 C& 调用 C 的 virtual_name (因为它是 final)
    
    ASSERT(rab.direct_name() == 'A', MSG); // 通过 A& 调用 A 的 direct_name
    ASSERT(rbc.direct_name() == 'B', MSG); // 通过 B& 调用 B 的 direct_name
    ASSERT(rcd.direct_name() == 'C', MSG); // 通过 C& 调用 C 的 direct_name

    // 更多的引用测试
    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // 通过 A& 调用 C 的 virtual_name
    ASSERT(rbd.virtual_name() == 'C', MSG); // 通过 B& 调用 C 的 virtual_name (因为它是 final)
    
    ASSERT(rac.direct_name() == 'A', MSG); // 通过 A& 调用 A 的 direct_name
    ASSERT(rbd.direct_name() == 'B', MSG); // 通过 B& 调用 B 的 direct_name

    // 最后一个引用测试
    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // 通过 A& 调用 C 的 virtual_name (因为它是 final)
    ASSERT(rad.direct_name() == 'A', MSG); // 通过 A& 调用 A 的 direct_name

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>

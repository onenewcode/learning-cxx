#include "../exercise.h"

struct A {
    // 正确初始化静态字段
    static int num_a;

    A() {
        ++num_a;
    }
    virtual ~A() { // 虚析构函数
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 初始化静态成员变量
int A::num_a = 0;

struct B final : public A {
    // 正确初始化静态字段
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() override { // 覆盖基类的虚析构函数
        --num_b;
    }

    char name() const override {
        return 'B';
    }
};

// 初始化静态成员变量
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a"); // A 和 B 的构造都会增加 num_a
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // 使用 dynamic_cast 进行安全的向下转型
    B &bb = dynamic_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

int main(int argc, char **argv) {
    // auto shared = std::make_shared<int>(10);
    // std::shared_ptr<int> ptrs[]{shared, shared, shared};

    // std::weak_ptr<int> observer = shared;
    // ASSERT(observer.use_count() == 4, "Initially, there are 3 shared_ptrs pointing to the object.");

    // ptrs[0].reset();
    // ASSERT(observer.use_count() == 3 , "After resetting ptrs[0], only two shared_ptrs remain.");

    // ptrs[1] = nullptr;
    // ASSERT(observer.use_count() == 1, "After setting ptrs[1] to nullptr, only one shared_ptr remains.");

    // ptrs[2] = std::make_shared<int>(*shared);
    // // A new shared_ptr is created for a new int with the same value as *shared.
    // // This does not affect the original shared_ptr's reference count.
    // ASSERT(observer.use_count() == 1, "Creating a new shared_ptr with the same value doesn't change use_count.");

    // ptrs[0] = shared;
    // ptrs[1] = shared;
    // ptrs[2] = std::move(shared);
    // // After moving, all three pointers now point to the original object again.
    // ASSERT(observer.use_count() == 3, "After moving and reassigning, use_count returns to 3.");

    // std::ignore = std::move(ptrs[0]);
    // ptrs[1] = std::move(ptrs[1]);
    // ptrs[1] = std::move(ptrs[2]);
    // // All shared_ptrs are either moved from or set to nullptr, leaving no strong references.
    // ASSERT(observer.use_count() == 0, "No more strong references left.");

    // shared = observer.lock();
    // // The weak_ptr creates a temporary strong reference.
    // ASSERT(observer.use_count() == 1, "lock() creates a temporary strong reference.");

    // shared = nullptr;
    // for (auto &ptr : ptrs) ptr = nullptr;
    // // The last strong reference is destroyed, but the weak_ptr still exists.
    // ASSERT(observer.use_count() == 0, "All strong references have been destroyed.");

    // shared = observer.lock();
    // // If the object was already deleted, lock() will return an empty shared_ptr.
    // ASSERT(observer.use_count() == (shared ? 1 : 0), "If the object is still alive, use_count is 1; otherwise, it's 0.");

    return 0;
}
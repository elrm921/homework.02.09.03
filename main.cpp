#include <iostream>
#include <set>

template <typename T>
class my_ptr {
    inline static std::set<void*> m_ctl;
    T* m_ptr;
public:
    my_ptr(T* ptr) : m_ptr{ ptr } {
        if (m_ctl.find(ptr) != m_ctl.end()) {
            throw std::runtime_error("Pointer busy");
        }
        m_ctl.insert(ptr);
    }
    my_ptr(const my_ptr&) = delete;
    my_ptr& operator=(const my_ptr&) = delete;
    ~my_ptr() {
        delete[] m_ptr;
        std::cout << "destructor called" << std::endl;
    }
    T operator *() const {
        return *(m_ptr);
    }
    T* release() {
        T* ptr = m_ptr;
        auto it = m_ctl.find(m_ptr);
        m_ctl.extract(it);
        m_ptr = nullptr;
        return ptr;
    }
};

int main() {
    int* n = new int {10};
    {
        my_ptr first(n);
        std::cout << "first: " << *(first) << std::endl;
        n = first.release();
        my_ptr second(n);
        std::cout << "second: " << *(second) << std::endl;
    }
    return 0;
}
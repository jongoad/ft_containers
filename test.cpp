// #include <memory>
// #include <iostream>
// #include <string>
// #include <type_traits>

// class Sample;

// namespace ft {

// 	//enable_if
// 	template <bool B, class T = void>
// 	struct enable_if {};

// 	template <class T>
// 	struct enable_if<true, T> { typedef T type; };

// }

// template <class T>
// class Test {
// public:	
// 	Test(T value) : value_(value) { std::cout << "enable_if - int" << std::endl; }; //Default
// 	template<>
// 	Test(typename ft::enable_if<std::is_same<T, int>::value, T >::type value) : value_(static_cast<T>(value)) { std::cout << "enable_if - Sample" << std::endl; };

// 	T value_;
// };



// int	main(void) {

// Test<double>	one(0.69);
// Test<int>		two(10);
// }

#include <iostream>
#include <type_traits>

class foo;
class bar;

template<class T>
struct is_bar
{
    template<class Q = T>
    typename std::enable_if<std::is_same<Q, bar>::value, bool>::type check()
    {
        return true;
    }

    template<class Q = T>
    typename std::enable_if<!std::is_same<Q, bar>::value, bool>::type check()
    {
        return false;
    }
};

int main()
{
    is_bar<foo> foo_is_bar;
    is_bar<bar> bar_is_bar;
    if (!foo_is_bar.check() && bar_is_bar.check())
        std::cout << "It works!" << std::endl;

    return 0;
}

ft::vector<int>::const_iterator;
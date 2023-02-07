#pragma once


/* Pair Definition */

template <typename T1, typename T2>
class pair {
	public:
	pair() : _first(T1()), _second(T2()) {}
	pair(const T1& a, const T2& b) : _first(a), _second(b) {}

	private:
		T1 _first;
		T2 _second;
};



/* Swap function template */
template <typename T>
void	swap(T* a, T* b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}
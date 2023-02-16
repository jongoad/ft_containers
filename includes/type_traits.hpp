#pragma once

#define ft_noexcept throw()

namespace ft {

	//enable_if - enable overload if type requirements met
	template <bool B, class T = void>
	struct enable_if;

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	//QoL definition for enable_if
	template <bool B, class T>
	using enable_if_t = enable_if<B, T>::type;

	//is_integral
	template <class T, T v>
	struct integral_constant {
		static const T 				value = v;
		typedef integral_constant 	type;
		typedef T					value_type;
		operator value_type() const ft_noexcept { return value; }
		const value_type operator()() const ft_noexcept { return value; }
	};

	//Instantiate bool types for integral_constant (based on std::false_type and std::true_type)
	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	
	//is_integral - template metafunction specializations
	template <class T>
	struct is_integral_helper : public false_type {};
	template <>
	struct is_integral_helper<bool> : public true_type {};
	template <>
	struct is_integral_helper<char> : public true_type {};
	template <>
	struct is_integral_helper<signed char> : public true_type {};
	template <>
	struct is_integral_helper<unsigned char> : public true_type {};
	template <>
	struct is_integral_helper<wchar_t> : public true_type {};
	template <>
	struct is_integral_helper<char16_t> : public true_type {};
	template <>
	struct is_integral_helper<char32_t> : public true_type {};
	template <>
	struct is_integral_helper<short> : public true_type {};
	template <>
	struct is_integral_helper<signed short> : public true_type {};
	template <>
	struct is_integral_helper<unsigned short> : public true_type {};
	template <>
	struct is_integral_helper<int> : public true_type {};
	template <>
	struct is_integral_helper<signed int> : public true_type {};
	template <>
	struct is_integral_helper<unsigned int> : public true_type {};
	template <>
	struct is_integral_helper<long> : public true_type {};
	template <>
	struct is_integral_helper<signed long> : public true_type {};
	template <>
	struct is_integral_helper<unsigned long> : public true_type {};
	template <>
	struct is_integral_helper<long long> : public true_type {};
	template <>
	struct is_integral_helper<signed long long> : public true_type {};
	template <>
	struct is_integral_helper<unsigned long long> : public true_type {};



	//remmove_cv - Remove const and const volatile
	template <class T>
	struct remove_cv {
		typedef T type;
	};
	template <class T>
	struct remove_cv<const T> {
		typedef T type;
	};
	template <class T>
	struct remove_cv<volatile T> {
		typedef T type;
	};
	template <class T>
	struct remove_cv<const volatile T> {
		typedef T type;
	};

	//QoL define for remove_cv
	template <class T>
	using remove_cv_t = remove_cv<T>::type;

	//is_integral
	template <class T>
	struct is_integral : is_integral_helper<remove_cv_t<T> > {};


	//FIXME: Do I want to implement these?
	//is_iter

	//is_same


} //namespace ft end


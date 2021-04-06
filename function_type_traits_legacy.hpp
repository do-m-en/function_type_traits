// Copyright (c) 2021 Domen Vrankar (domen dot vrankar at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef tt_FUNCTION_TYPE_TRAITS_LEGACY_HPP_INCLUDED
#define tt_FUNCTION_TYPE_TRAITS_LEGACY_HPP_INCLUDED

#if __cplusplus < 201402L
  #error unsupported C++ version - C++14 is minimum required version
#endif

#include <type_traits>
#include <tuple>

namespace tt
{
  namespace detail
  {
    template<typename T>
    struct with_call_operator
    {
      using type = decltype(&T::operator());
    };

    template<typename T>
    struct type_identity
    {
      using type = T;
    };
  }

  template<typename T>
  struct function_traits;

  template<typename R, typename ...Args>
  struct function_traits<R (Args...)>
  {
    using result_type = R;
    using type = std::tuple<Args...>;
  };

  template<typename R, typename C, typename ...Args>
  struct function_traits<R (C::*)(Args...)>
  {
    using result_type = R;
    using type = std::tuple<Args...>;
  };

  template<typename R, typename C, typename ...Args>
  struct function_traits<R (C::*)(Args...) const>
  {
    using result_type = R;
    using type = std::tuple<Args...>;
  };

  template<typename T>
  using function_args_t = typename function_traits<T>::type;

  template<typename T>
  using function_return_t = typename function_traits<T>::result_type;

  template<typename T>
  using callable_args_t =
    typename function_traits<
      typename std::conditional_t<
        std::is_class<T>::value,
        typename detail::with_call_operator<T>,
        typename detail::type_identity<T>>::type>::type;

  template<typename T>
  using callable_return_t =
    typename function_traits<
      typename std::conditional_t<
        std::is_class<T>::value,
        typename detail::with_call_operator<T>,
        typename detail::type_identity<T>>::type>::result_type;
}

#endif // tt_FUNCTION_TYPE_TRAITS_HPP_LEGACY_INCLUDED

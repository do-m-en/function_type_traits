// Copyright (c) 2021 Domen Vrankar (domen dot vrankar at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef tt_FUNCTION_TYPE_TRAITS_HPP_INCLUDED
#define tt_FUNCTION_TYPE_TRAITS_HPP_INCLUDED

#if __cplusplus > 201703L

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
    requires std::is_function_v<T> || std::is_member_function_pointer_v<T>
  using function_args_t = typename function_traits<T>::type;

  template<typename T>
    requires std::is_function_v<T> || std::is_member_function_pointer_v<T>
  using function_return_t = typename function_traits<T>::result_type;

  template<typename T>
    requires std::is_class_v<T> || std::is_function_v<T>
  using callable_args_t =
    typename function_traits<
      typename std::conditional_t<
        std::is_class_v<T>,
        typename detail::with_call_operator<T>,
        typename std::type_identity<T>>::type>::type;

  template<typename T>
    requires std::is_class_v<T> || std::is_function_v<T>
  using callable_return_t =
    typename function_traits<
      typename std::conditional_t<
        std::is_class_v<T>,
        typename detail::with_call_operator<T>,
        typename std::type_identity<T>>::type>::result_type;
}

#elif __cplusplus < 201402L
  #error unsupported C++ version - C++14 is minimum required version
#else
  #include "function_type_traits_legacy.hpp"
#endif

#endif // tt_FUNCTION_TYPE_TRAITS_HPP_INCLUDED

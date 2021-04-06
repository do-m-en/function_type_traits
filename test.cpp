// Copyright (c) 2021 Domen Vrankar (domen dot vrankar at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#include "function_type_traits.hpp"

#include <tuple>
#include <type_traits>

namespace
{
  class Functor_test
  {
  public:
    bool operator () ( int i, float j ) { return true; }
    bool two_params( int i, float j ) { return true; }
  };

  bool function_test( int i, float j ) { return true; }
}

namespace test
{
  // workaround for C++14 support
  template<typename T, typename U>
  constexpr bool is_same_v = std::is_same<T, U>::value;
}

void test_functor()
{
  static_assert(
    test::is_same_v<
      tt::function_args_t<decltype(&Functor_test::operator())>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::function_return_t<decltype(&Functor_test::operator())>,
      bool> );

  static_assert(
    test::is_same_v<
      tt::callable_args_t<Functor_test>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::callable_return_t<Functor_test>,
      bool> );
}

void test_member_function()
{
  static_assert(
    test::is_same_v<
      tt::function_args_t<decltype(&Functor_test::two_params)>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::function_return_t<decltype(&Functor_test::two_params)>,
      bool> );
}

void test_function()
{
  static_assert(
    test::is_same_v<
      tt::function_args_t<decltype(function_test)>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::function_return_t<decltype(function_test)>,
      bool> );

  static_assert(
    test::is_same_v<
      tt::callable_args_t<decltype(function_test)>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::callable_return_t<decltype(function_test)>,
      bool> );
}

void test_lambda()
{
  auto test = [](int, float) { return true; };

  static_assert(
    test::is_same_v<
      tt::function_args_t<decltype(&decltype(test)::operator())>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::function_return_t<decltype(&decltype(test)::operator())>,
      bool> );

  static_assert(
    test::is_same_v<
      tt::callable_args_t<decltype(test)>,
      std::tuple<int, float>> );

  static_assert(
    test::is_same_v<
      tt::callable_return_t<decltype(test)>,
      bool> );
}

int main()
{
  test_functor();
  test_member_function();
  test_function();
  test_lambda();
}

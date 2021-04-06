# Copyright (c) 2021 Domen Vrankar (domen dot vrankar at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required( VERSION 3.13 )

project( function_type_traits CXX )

# NOTE: No need to run the generated executables as the tests passed at compile
#       time or compilation failed.
foreach(cxx_standard_version IN ITEMS 20 17 14)
  add_executable( test_cxx${cxx_standard_version} test.cpp )
  target_compile_features(
    test_cxx${cxx_standard_version}
    PRIVATE
    cxx_std_${cxx_standard_version} )
endforeach()

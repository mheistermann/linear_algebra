/**
 * This file is part of the "dim" project
 *   Copyright (c) 2020 Christian Parpart <christian@parpart.family>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ostream>
#include <linear_algebra>
#include "support.h"

#include <catch2/catch.hpp>

TEST_CASE("addition: vector")
{
    auto static constexpr v1 = ivec<3>{0, 1, 2};
    auto static constexpr v2 = ivec<3>{3, 4, 5};
    auto static constexpr v3 = v1 + v2;
    auto static constexpr expected = ivec<3>{3, 5, 7};
    REQUIRE(v3 == expected);
}

TEST_CASE("addition: matrix")
{
    auto static constexpr m1 = imat<2, 2>{1, 2, 3, 4};
    auto static constexpr m2 = imat<2, 2>{2, 3, 4, 5};
    auto static constexpr m3 = m1 + m2;
    auto static constexpr expected = imat<2, 2>{3, 5, 7, 9};
    REQUIRE(m3 == expected);
}

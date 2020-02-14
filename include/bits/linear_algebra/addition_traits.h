#pragma once

#include "base.h"
#include "fwd.h"

namespace LINEAR_ALGEBRA_NAMESPACE {

// ---------------------------------------------------------------------------
// 6.6.1 | matrix_operation_traits

template <class T1, class T2>
struct matrix_addition_element_traits { using element_type = decltype(std::declval<T1>() + std::declval<T2>()); };

template <class OT, class T1, class T2>
using matrix_addition_element_t = typename OT::template element_addition_traits<T1, T2>;

// ---------------------------------------------------------------------------
// 6.8.2 | engine promotion traits | matrix_addition_engine_traits<OT, ET1, ET2>

template <class OT, class ET1, class ET2>
struct matrix_addition_engine_traits // | 4.8.2
{
    using element_type = matrix_addition_element_t<OT, typename ET1::element_type, typename ET2::element_type>;
    using engine_type = ET1; // TODO
};

template <class OT, class ET1, class ET2>
using matrix_addition_engine_t = typename OT::template engine_addition_traits<
    OT, // TODO: OTR
    ET1,
    ET2
>::engine_type;

// ---------------------------------------------------------------------------
// 6.9.2 | matrix_addition_traits<OT, OP1, OP2>

template <class OT, class OP1, class OP2> struct matrix_addition_traits;

template <class OT, class ET1, class OT1, class ET2, class OT2>
struct matrix_addition_traits<OT, vector<ET1, OT1>, vector<ET2, OT2>>
{
    using engine_type = matrix_addition_engine_t<OT, ET1, ET2>;
    using op_traits = OT;
    using result_type = vector<engine_type, op_traits>;
    constexpr static result_type add(vector<ET1, OT1> const& v1, vector<ET2, OT2> const& v2)
    {
        result_type v3{};
        for (std::size_t i = 0; i < v1.size(); ++i)
            v3(i) = v1(i) + v2(i);
        return v3;
    }
};

template <class OT, class ET1, class OT1, class ET2, class OT2>
struct matrix_addition_traits<OT, matrix<ET1, OT1>, matrix<ET2, OT2>>
{
    using engine_type = matrix_addition_engine_t<OT, ET1, ET2>;
    using op_traits = OT;
    using result_type = matrix<engine_type, op_traits>;
    constexpr static result_type add(matrix<ET1, OT1> const& m1, matrix<ET2, OT2> const& m2)
    {
        using size_type = std::size_t;
        result_type m{};

        for (size_type i = 0; i < m1.rows(); ++i)
            for (size_type j = 0; j < m1.columns(); ++j)
                m(i, j) = m1(i, j) + m2(i, j);

        return m;
    }
};

template <class OT, class OP1, class OP2>
using matrix_addition_traits_t =
    typename OT::template addition_traits<
        OT, // TODO: OTR!
        OP1,
        OP2
    >;

} // end namespace
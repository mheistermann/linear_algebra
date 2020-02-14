#pragma once

#include "base.h"
#include "fwd.h"

namespace LINEAR_ALGEBRA_NAMESPACE {

template <class T1>
struct matrix_negation_element_traits { using element_type = decltype(-std::declval<T1>()); };

template <class OT, class T1>
using matrix_negation_element_t = typename OT::template element_negation_traits<T1>;

// --------------------------------------------------------------------------
// 6.8.1 | engine promotion traits | matrix_negation_engine_traits<OT, ET1>

template <class OT, class ET1>
struct matrix_negation_engine_traits // | 4.8.1
{
    using element_type = matrix_negation_element_t<OT, typename ET1::element_type>;
    using engine_type = ET1; // TODO; //- Implementation-defined
};

template <class OT, class ET1>
using matrix_negation_engine_t = typename OT::template engine_negation_traits<
    OT, // TODO: OTR
    ET1
>::engine_type; // XXX:DEFECT? the documentation is uncearl wrt. engine type vs TRAIT!

// --------------------------------------------------------------------------
// 6.9.1 | matrix_negation_traits<OT, OP1, OP2>

template <class OT, class OP1> struct matrix_negation_traits;

template <class OT, class ET1, class OT1>
struct matrix_negation_traits<OT, vector<ET1, OT1>>
{
    using engine_type = matrix_negation_engine_t<OT, ET1>;
    using op_traits = OT;
    using result_type = vector<engine_type, op_traits>;
    constexpr static result_type negate(vector<ET1, OT1> const& v1)
    {
        auto res = result_type(v1.size());
        size_t i = 0;
        for (auto const& v : v1)
            res(i++) = -v;
        return res;
    }
};

template <class OT, class ET1, class OT1>
struct matrix_negation_traits<OT, matrix<ET1, OT1>>
{
    using engine_type = matrix_negation_engine_t<OT, ET1>;
    using op_traits = OT;
    using result_type = matrix<engine_type, op_traits>;
    constexpr static result_type negate(matrix<ET1, OT1> const& m1)
    {
        result_type m{};

        for (decltype(m1.rows()) i = 0; i < m1.rows(); ++i)
            for (decltype(m1.columns()) j = 0; j < m1.columns(); ++j)
                m(i, j) = -m1(i, j);

        return m;
    }
};

template <class OT, class OP1>
using matrix_negation_traits_t = typename OT::template negation_traits<OT, OP1>;

} // end namespace
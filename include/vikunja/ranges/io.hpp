#pragma once

#include "base.hpp"

#include <span>

namespace vikunja::ranges
{
    template<typename TElem, typename TExtents, typename TLayoutPolicy, typename AccessorPolicy>
    struct in
    {
        std::experimental::mdspan<TElem, TExtents, TLayoutPolicy, AccessorPolicy> m_input;

        in(std::experimental::mdspan<TElem, TExtents, TLayoutPolicy, AccessorPolicy> input) : m_input(input)
        {
        }

        template<concepts::StaticInStaticOut TOther>
        concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
        {
            return detail::ProxyRange<
                ranges::types::StaticInStaticOut,
                typename TOther::Functor,
                std::experimental::mdspan,
                TElem,
                TExtents,
                TLayoutPolicy,
                AccessorPolicy>(m_input);
        }
    };

    template<typename TExecutor, typename TElem, typename TExtents, typename TLayoutPolicy, typename AccessorPolicy>
    struct out
    {
        std::experimental::mdspan<TElem, TExtents, TLayoutPolicy, AccessorPolicy> output;
        using Executor = TExecutor;

        out(TExecutor, std::experimental::mdspan<TElem, TExtents, TLayoutPolicy, AccessorPolicy> output)
            : output(output)
        {
        }
    };
} // namespace vikunja::ranges

#pragma once

#include "base.hpp"

#include <span>

namespace vikunja::ranges
{
    template<typename TElem, std::size_t N>
    struct in
    {
        std::span<TElem, N> m_input;

        in(std::span<TElem, N> input) : m_input(input)
        {
        }

        template<concepts::StaticInStaticOut TOther>
        concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
        {
            return detail::ProxyRange<ranges::types::StaticInStaticOut, typename TOther::Functor, std::span, TElem, N>(
                m_input);
        }
    };

    template<typename TExecutor, typename TElem, std::size_t N>
    struct out
    {
        std::span<TElem, N> output;
        using Executor = TExecutor;

        out(TExecutor, std::span<TElem, N> output) : output(output)
        {
        }
    };
} // namespace vikunja::ranges

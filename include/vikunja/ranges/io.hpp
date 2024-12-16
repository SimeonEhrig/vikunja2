#pragma once

#include "base.hpp"

#include <span>

namespace vikunja::ranges
{
    template<vikunja::concepts::details::MemoryInterface TStorage>
    struct in
    {
        TStorage m_input;

        in(TStorage input) : m_input(input)
        {
        }

        template<concepts::StaticInStaticOut TOther>
        concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
        {
            return detail::ProxyRange<ranges::types::StaticInStaticOut, typename TOther::Functor, TStorage>(m_input);
        }

        template<concepts::StaticInStaticOut TOther>
        concepts::StaticInStaticOutProxy auto operator|(TOther&& other) const
        {
            return detail::ProxyRange<ranges::types::StaticInStaticOut, typename TOther::Functor, TStorage>(m_input);
        }
    };

    template<typename TExecutor, vikunja::concepts::details::MemoryInterface TStorage>
    struct out
    {
        TStorage output;
        using Executor = TExecutor;

        out(TExecutor, TStorage output) : output(output)
        {
        }
    };
} // namespace vikunja::ranges

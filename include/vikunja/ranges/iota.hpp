#pragma once

#include "base.hpp"

namespace vikunja::ranges
{
    template<typename TElem, std::size_t N = std::dynamic_extent>
    struct iota
    {
        template<typename TIElem, std::size_t NI>
        struct IotaGen
        {
            TIElem begin;
            std::size_t m_size;
            TIElem step;

            std::size_t size() const
            {
                return m_size;
            }

            TIElem operator[](std::size_t i) const
            {
                return begin + i * step;
            }
        };

        IotaGen<TElem, N> input;

        iota(TElem const begin, std::size_t const size, TElem step = 1) : input({begin, size, step})
        {
        }

        template<concepts::StaticInStaticOut TOther>
        concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
        {
            return detail::ProxyRange<ranges::types::StaticInStaticOut, typename TOther::Functor, IotaGen, TElem, N>(
                input);
        }
    };
} // namespace vikunja::ranges

#pragma once

#include "base.hpp"

namespace vikunja::ranges
{
    template<
        typename TElem,
        typename TExtents = std::experimental::extents<std::size_t, std::experimental::dynamic_extent>,
        typename TLayoutPolicy = std::experimental::layout_right,
        typename AccessorPolicy = std::experimental::default_accessor<TElem>>
    struct iota
    {
        template<typename TIElem, typename, typename, typename>
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

        IotaGen<TElem, TExtents, TLayoutPolicy, AccessorPolicy> input;

        iota(TElem const begin, std::size_t const size, TElem step = 1) : input({begin, size, step})
        {
        }

        template<concepts::StaticInStaticOut TOther>
        concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
        {
            return detail::ProxyRange<
                ranges::types::StaticInStaticOut,
                typename TOther::Functor,
                IotaGen,
                TElem,
                TExtents,
                TLayoutPolicy,
                AccessorPolicy>(input);
        }
    };
} // namespace vikunja::ranges

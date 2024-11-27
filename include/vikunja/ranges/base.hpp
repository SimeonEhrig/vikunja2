#pragma once

#include <vikunja/executor.hpp>

#include <type_traits>

namespace vikunja
{
    // defines how number of input and output elements of range behaves
    namespace ranges::types
    {
        // no input data
        // static number of output elements
        // e.g. data generator algorithm
        struct NoInStaticOut
        {
        };

        // static number of equal in- and output elements
        struct StaticInStaticOut
        {
        };

    } // namespace ranges::types

    namespace concepts
    {
        template<typename T>
        concept FunctionRange = requires(T t) { typename T::Functor; };

        template<typename T, typename TRangeType>
        concept RangeType = requires {
            {
                std::is_same_v<typename T::RangeType, TRangeType>
            };
        };

        template<typename T>
        concept NoInStaticOut = RangeType<T, ranges::types::NoInStaticOut>;

        template<typename T>
        concept StaticInStaticOut = RangeType<T, ranges::types::StaticInStaticOut> && FunctionRange<T>;

        template<typename T>
        concept ProxyRange = requires {
            T::input;
            requires FunctionRange<T>;
        };

        template<typename T>
        concept StaticInStaticOutProxy = StaticInStaticOut<T> && ProxyRange<T>;
    } // namespace concepts

    namespace ranges::detail
    {
        template<
            typename TRangeType,
            typename TFunctor,
            template<typename, std::size_t>
            class TSpan,
            typename TElem,
            std::size_t N>
        struct ProxyRange
        {
            using Functor = TFunctor;
            using RangeType = TRangeType;
            TSpan<TElem, N> input;

            ProxyRange(TSpan<TElem, N> const input) : input(input)
            {
            }

            //     template<concepts::StaticInStaticOutProxy TOther>
            // concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
            // {
            //     //TOther::Functor;
            //     //using Functor = decltype([](TElem i) { return TOther::Functor{}(Functor{}(TElem{})); });
            //     using FusedFunctor = decltype([](TElem i) { return typename TOther::Functor{}(Functor{}(i)); });
            //     return detail::ProxyRange<ranges::types::StaticInStaticOut, FusedFunctor, TElem, N>(
            //         other.input);
            // }

            template<concepts::StaticInStaticOut TOther>
            concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
            {
                using FusedFunctor = decltype([](TElem i) { return typename TOther::Functor{}(Functor{}(i)); });
                return detail::ProxyRange<ranges::types::StaticInStaticOut, FusedFunctor, TSpan, TElem, N>(input);
            }

            template<concepts::Executor TOther>
            void operator|(TOther& other) const
            {
                Functor f{};
                for(auto i = 0; i < input.size(); ++i)
                {
                    other.output[i] = f(input[i]);
                }
            }
        };
    } // namespace ranges::detail

} // namespace vikunja

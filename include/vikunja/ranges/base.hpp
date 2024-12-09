#pragma once

#include <vikunja/executor.hpp>

#include <experimental/mdspan>
#include <type_traits>

namespace vikunja
{
    // defines how number of input and output elements of range behaves
    namespace ranges
    {
        namespace types
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
        } // namespace types

        namespace detail
        {
            // get element type of storage
            template<typename TStorage>
            struct MemoryInterfaceElem
            {
                using type = typename TStorage::type;
            };

            template<typename TElem, typename TExtents, typename TLayout, typename TAccesorPolicy>
            struct MemoryInterfaceElem<std::experimental::mdspan<TElem, TExtents, TLayout, TAccesorPolicy>>
            {
                using type = TElem;
            };

        } // namespace detail

    } // namespace ranges

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

        template<typename T, typename... TArgs>
        concept SameOr = (std::same_as<T, TArgs> || ...);

        namespace details
        {
            template<typename T>
            concept MemoryInterface = requires(T t) {
                typename vikunja::ranges::detail::MemoryInterfaceElem<T>::type;
                {
                    t.size()
                } -> std::integral;
                {
                    t[0]
                } -> SameOr<
                    typename vikunja::ranges::detail::MemoryInterfaceElem<T>::type,
                    typename vikunja::ranges::detail::MemoryInterfaceElem<T>::type&>;
            };
        } // namespace details
    } // namespace concepts

    namespace ranges::detail
    {
        template<typename TRangeType, typename TFunctor, vikunja::concepts::details::MemoryInterface TStorage>
        struct ProxyRange
        {
            using Functor = TFunctor;
            using RangeType = TRangeType;
            TStorage input;

            ProxyRange(TStorage const input) : input(input)
            {
            }

            template<concepts::StaticInStaticOut TOther>
            concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
            {
                using TElem = vikunja::ranges::detail::MemoryInterfaceElem<TStorage>::type;
                using FusedFunctor = decltype([](TElem i) { return typename TOther::Functor{}(Functor{}(i)); });
                return detail::ProxyRange<ranges::types::StaticInStaticOut, FusedFunctor, TStorage>(input);
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

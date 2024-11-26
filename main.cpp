#include <iostream>
#include <span>
#include <vector>

namespace vikunja
{

    namespace ranges::types
    {

        struct NoInStaticOut
        {
        };

        struct StaticInStaticOut
        {
        };

    } // namespace ranges::types

    namespace executor
    {
        struct CPU
        {
        };
    } // namespace executor

    namespace concepts
    {
        template<typename T, typename TRangeType>
        concept RangeType = requires {
            {
                std::is_same_v<typename T::RangeType, TRangeType>
            };
        };

        template<typename T>
        concept FunctionRange = requires(T t) { typename T::Functor; };

        template<typename T>
        concept ProxyRange = requires {
            T::input;
            typename T::Functor;
        };

        template<typename T>
        concept Executor = requires {
            T::output;
            typename T::Executor;
        };

        template<typename T>
        concept NoInStaticOut = RangeType<T, ranges::types::NoInStaticOut>;

        template<typename T>
        concept StaticInStaticOut = RangeType<T, ranges::types::StaticInStaticOut> && FunctionRange<T>;

        template<typename T>
        concept StaticInStaticOutProxy = RangeType<T, ranges::types::StaticInStaticOut> && ProxyRange<T>;


    } // namespace concepts

    namespace ranges
    {
        namespace detail
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
        } // namespace detail

        template<typename TElem, std::size_t N>
        struct menIn
        {
            std::span<TElem, N> m_input;

            menIn(std::span<TElem, N> input) : m_input(input)
            {
            }

            template<concepts::StaticInStaticOut TOther>
            concepts::StaticInStaticOutProxy auto operator|(TOther& other) const
            {
                return detail::
                    ProxyRange<ranges::types::StaticInStaticOut, typename TOther::Functor, std::span, TElem, N>(
                        m_input);
            }
        };

        template<typename TFunctor>
        struct foreach
        {
            using Functor = TFunctor;
            using RangeType = ranges::types::StaticInStaticOut;

            foreach(TFunctor&&)
            {
            }
        };

        template<typename TExecutor, typename TElem, std::size_t N>
        struct menOut
        {
            std::span<TElem, N> output;
            using Executor = TExecutor;

            menOut(TExecutor, std::span<TElem, N> output) : output(output)
            {
            }
        };

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
                return detail::
                    ProxyRange<ranges::types::StaticInStaticOut, typename TOther::Functor, IotaGen, TElem, N>(input);
            }
        };

    } // namespace ranges
} // namespace vikunja

int main(int argc, char** argv)
{
    std::vector<int> vIn = {1, 2, 3};
    std::vector<int> vOut(vIn.size());

    vikunja::ranges::menIn rIn(std::span{vIn});
    vikunja::ranges::foreach rforeach1([]<typename T>(T i) { return i * static_cast<T>(2); });
    vikunja::ranges::foreach rforeach2([]<typename T>(T i) { return i + static_cast<T>(3); });
    vikunja::ranges::menOut rOut(vikunja::executor::CPU{}, std::span{vOut});

    rIn | rforeach1 | rforeach2 | rOut;

    for(auto e : vOut)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    constexpr std::size_t gen_size = 12;

    std::vector<float> vOut2(gen_size);

    vikunja::ranges::menOut rOut2{vikunja::executor::CPU{}, std::span{vOut2}};

    vikunja::ranges::iota rIota(4.1f, gen_size, 2.f);
    rIota | rforeach1 | rforeach2 | rOut2;

    for(auto e : vOut2)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}

#include <catch2/catch_test_macros.hpp>
#include <vikunja/ranges/base.hpp>
#include <vikunja/ranges/iota.hpp>

#include <experimental/mdspan>
#include <span>

TEST_CASE("vikunja::ranges::detail::MemoryInterface iota", "[unit][ranges][MemoryInterface]")
{
    using IotaGen = vikunja::ranges::iota<int>::IotaGen<int>;
    STATIC_REQUIRE(std::is_same_v<vikunja::ranges::detail::MemoryInterfaceElem<IotaGen>::type, int>);
    STATIC_REQUIRE(vikunja::concepts::details::MemoryInterface<IotaGen>);
}

TEST_CASE("vikunja::ranges::detail::MemoryInterface mdspan", "[unit][ranges][MemoryInterface]")
{
    namespace stdex = std::experimental;
    STATIC_REQUIRE(
        std::is_same_v<
            vikunja::ranges::detail::MemoryInterfaceElem<stdex::mdspan<int, stdex::extents<std::size_t, 1>>>::type,
            int>);
    STATIC_REQUIRE(vikunja::concepts::details::MemoryInterface<stdex::mdspan<int, stdex::extents<std::size_t, 1>>>);
}

TEST_CASE("vikunja::ranges::detail::MemoryInterface std::span", "[unit][ranges][MemoryInterface]")
{
    STATIC_REQUIRE(std::is_same_v<vikunja::ranges::detail::MemoryInterfaceElem<std::span<int, 1>>::type, int>);
    STATIC_REQUIRE(vikunja::concepts::details::MemoryInterface<std::span<int, 1>>);
}

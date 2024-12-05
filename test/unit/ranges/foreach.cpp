#include <catch2/catch_test_macros.hpp>
#include <vikunja/ranges/foreach.hpp>

TEST_CASE("vikunja::ranges::foreach constructor", "[ranges][foreach]")
{
    auto f = [](int i) { return i * 2; };

    auto foreach = vikunja::ranges::foreach(f);
    REQUIRE(decltype(foreach)::Functor{}(2) == 4);

    auto foreach2 = vikunja::ranges::foreach([](int i) { return i * 3; });
    REQUIRE(decltype(foreach2)::Functor{}(2) == 6);
}

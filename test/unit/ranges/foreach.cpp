#include <catch2/catch_test_macros.hpp>
#include <vikunja/ranges/foreach.hpp>

TEST_CASE("vikunja::ranges::foreach constructor", "[ranges][foreach]")
{
    auto f = [](int i) { return i * 2; };

    // FIX: should be possible
    // auto foreach = vikunja::ranges::foreach<int>(f);
    // REQUIRE(decltype(foreach)::Functor{}(2) == 4);

    auto foreach2 = vikunja::ranges::foreach([](int i) { return i * 3; });
    REQUIRE(decltype(foreach2)::Functor{}(2) == 6);
}

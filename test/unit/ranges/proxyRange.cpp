#include <catch2/catch_test_macros.hpp>
#include <vikunja/ranges/base.hpp>

#include <array>
#include <span>

TEST_CASE("vikunja::ranges::detail::ProxyRange operator|", "[unit][ranges][base]")
{
    auto f = [](int i) { return i * 2; };
    std::array data = {1, 2, 3};
    std::span s{data};

    using ProxyRange
        = vikunja::ranges::detail::ProxyRange<vikunja::ranges::types::StaticInStaticOut, decltype(f), decltype(s)>;

    ProxyRange proxyRange1(s);
    ProxyRange proxyRange2(s);

    proxyRange1 | proxyRange2;

    ProxyRange{s} | ProxyRange{s};
}

#include <catch2/catch_test_macros.hpp>
#include <vikunja/executor.hpp>
#include <vikunja/ranges/foreach.hpp>
#include <vikunja/ranges/io.hpp>

#include <array>
#include <span>

TEST_CASE("vikunja::ranges::foreach integration test lvalues", "[integ][ranges][foreach]")
{
    using DataType = int;
    std::array<DataType, 3> data_in = {1, 2, 3}, data_out;

    auto f = [](DataType i) { return i * 2; };
    auto foreach = vikunja::ranges::foreach(f);
    auto foreach2 = vikunja::ranges::foreach([](DataType i) { return i * 3; });

    vikunja::ranges::in in(std::span{data_in});
    vikunja::ranges::out out(vikunja::executor::CPU{}, std::span{data_out});

    in | foreach | foreach2 | out;

    for(auto i = 0; i < data_out.size(); ++i)
    {
        REQUIRE(data_out[i] == (data_in[i] * 2 * 3));
    }
}

TEST_CASE("vikunja::ranges::foreach integration test rvalues", "[integ][ranges][foreach]")
{
    namespace vkr = vikunja::ranges;
    using DataType = int;
    std::array<DataType, 3> data_in = {1, 2, 3}, data_out;

    auto f = [](DataType i) { return i * 2; };

    vkr::in(std::span{data_in}) | vkr::foreach(f) | vkr::foreach([](DataType i) { return i * 3; })
        | vkr::out(vikunja::executor::CPU{}, std::span{data_out});

    for(auto i = 0; i < data_out.size(); ++i)
    {
        REQUIRE(data_out[i] == (data_in[i] * 2 * 3));
    }
}

TEST_CASE("vikunja::ranges::foreach integration test mixed lvalues and rvalues", "[integ][ranges][foreach]")
{
    namespace vkr = vikunja::ranges;
    using DataType = int;
    std::array<DataType, 3> data_in = {1, 2, 3}, data_out;

    auto f = [](DataType i) { return i * 2; };
    auto foreach = vikunja::ranges::foreach([](DataType i) { return i * 3; });


    vkr::in(std::span{data_in}) | vkr::foreach(f) | foreach | vkr::out(vikunja::executor::CPU{}, std::span{data_out});

    for(auto i = 0; i < data_out.size(); ++i)
    {
        REQUIRE(data_out[i] == (data_in[i] * 2 * 3));
    }
}

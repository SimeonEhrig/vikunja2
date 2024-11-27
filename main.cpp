#include <vikunja/vikunja.hpp>

#include <experimental/mdspan>
#include <iostream>
#include <span>
#include <vector>

int main(int argc, char** argv)
{
    std::vector<int> vIn = {1, 2, 3};
    std::vector<int> vOut(vIn.size());

    vikunja::ranges::in in(std::experimental::mdspan(vIn.data(), vIn.size()));
    vikunja::ranges::foreach foreach1([]<typename T>(T i) { return i * static_cast<T>(2); });
    vikunja::ranges::foreach foreach2([]<typename T>(T i) { return i + static_cast<T>(3); });
    vikunja::ranges::out out(vikunja::executor::CPU{}, std::experimental::mdspan(vOut.data(), vOut.size()));

    in | foreach1 | foreach2 | out;

    for(auto e : vOut)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    constexpr std::size_t gen_size = 12;

    std::vector<float> vOut2(gen_size);

    vikunja::ranges::out out2{vikunja::executor::CPU{}, std::experimental::mdspan(vOut2.data(), vOut2.size())};

    vikunja::ranges::iota iota(4.1f, gen_size, 2.f);
    iota | foreach1 | foreach2 | out2;

    for(auto e : vOut2)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}

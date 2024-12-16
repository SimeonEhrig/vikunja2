#include <vikunja/vikunja.hpp>

#include <experimental/mdspan>
#include <iostream>
#include <span>
#include <vector>

int main(int argc, char** argv)
{
    constexpr std::size_t gen_size = 12;
    std::vector<float> vOut(gen_size);

    vikunja::ranges::foreach foreach([](float i) { return i * 2.f; });
    vikunja::ranges::out out{vikunja::executor::CPU{}, std::experimental::mdspan(vOut.data(), vOut.size())};

    vikunja::ranges::iota iota(4.1f, gen_size, 2.f);
    iota | foreach | out;

    for(auto e : vOut)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}

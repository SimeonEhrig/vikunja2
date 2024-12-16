#include <vikunja/vikunja.hpp>

#include <iostream>
#include <span>
#include <vector>

int main(int argc, char** argv)
{
    namespace vkr = vikunja::ranges;
    constexpr std::size_t gen_size = 12;
    std::vector<float> vOut(gen_size);

    vkr::iota iota(4.1f, gen_size, 2.f);
    vkr::out out{vikunja::executor::CPU{}, std::span(vOut)};

    iota | vkr::foreach([](float i) { return i * 2.f; }) | out;

    for(auto e : vOut)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}

#include <vikunja/vikunja.hpp>

#include <experimental/mdspan>
#include <iostream>
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

    return 0;
}

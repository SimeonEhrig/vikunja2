#pragma once

// TODO: replace me with alpaka

namespace vikunja
{

    namespace executor
    {
        struct CPU
        {
        };
    } // namespace executor

    namespace concepts
    {
        template<typename T>
        concept Executor = requires {
            T::output;
            typename T::Executor;
        };
    } // namespace concepts
} // namespace vikunja

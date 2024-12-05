#include "base.hpp"

namespace vikunja
{
    namespace ranges
    {
        template<typename TFunctor>
        struct foreach
        {
            using Functor = TFunctor;
            using RangeType = ranges::types::StaticInStaticOut;

            foreach(TFunctor)
            {
            }
        };
    } // namespace ranges
} // namespace vikunja

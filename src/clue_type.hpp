#pragma once

#include <memory>

#include "solution_context_type.hpp"

namespace ao::logic_solver_internal
{
    class clue_type
    {
    public:
        class apply_failure
        {};

        virtual
        std::unique_ptr<apply_failure>
        apply(
            solution_context_type &solution_context
        ) = 0;
    };
}

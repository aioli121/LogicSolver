#pragma once

#include <vector>

#include "field_id_type.hpp"
#include "mark_action_queue_type.hpp"

namespace ao::logic_solver_internal {
    class solution_context_type {
        public:
            solution_context_type(unsigned int list_count, unsigned int field_count_per_list)
                : list_count(list_count)
                , field_count_per_list(field_count_per_list)
                , grid_count(list_count * (list_count - 1) / 2)
                , field_count_per_list_squared(field_count_per_list * field_count_per_list)
                , cells(grid_count * field_count_per_list_squared) {}

            void try_mark_associated(field_id_type field_ids[2], mark_action_queue_type &mark_action_queue) {
                
            }

        private:
            unsigned int const list_count;
            unsigned int const field_count_per_list;
            unsigned int const grid_count;
            unsigned int const field_count_per_list_squared;

            class cell_type {};

            std::vector<cell_type> cells;
    };
}

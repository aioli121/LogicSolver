#include <vector>
#include <memory>
#include <iostream>

#include "numeric_clue_builder_type.hpp"

namespace ao::logic_solver_test
{
    void
    test_0()
    {
        auto const list_count = int(3);
        auto const field_count_per_list = int(4);

        auto lsb = ao::logic_solver_internal::numeric_clue_builder_type(
            list_count, field_count_per_list);

        lsb.add_numeric_association_clue({{0, 3}, {1, 1}});
        lsb.add_numeric_association_clue({{0, 2}, {1, 0}});
        lsb.add_numeric_difference_clue({1, 0}, -1, 0, {2, 0});
        lsb.add_numeric_difference_clue({2, 3}, +1, 0, {1, 2});
        lsb.add_numeric_either_clue({1, 0}, {{0, 1}, {2, 2}});


        // auto const grid_count = list_count * (list_count - 1) / 2;
        // auto const field_count_per_list_squared = field_count_per_list * field_count_per_list;

        // auto cells = std::vector<test_cell>(grid_count * field_count_per_list_squared);
        // auto grid_lines = std::vector<test_grid_line>();
        // auto full_line_triggers = std::vector<test_full_line>();

        // for (auto const &clue : clues) {
        //     // clue->evaluate();
        // }

        std::cout << "test\n";
    }
}

#pragma once

namespace ao::logic_solver {
    class builder_type {
        public:
            builder_type(int const list_count, int const field_count_per_list): list_count(list_count), field_count_per_list(field_count_per_list) {}

            

            int const list_count;
            int const field_count_per_list;
    };
}
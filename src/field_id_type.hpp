#pragma once

namespace ao::logic_solver_internal {
    class field_id_type {
        public:
            field_id_type(): field_id_type(-1, -1) {}
            field_id_type(std::pair<int, int> const pair): field_id_type(pair.first, pair.second) {}
            field_id_type(int list_id, int field_id): list_id(list_id), field_id(field_id) {}

            int list_id;
            int field_id;
    };
}

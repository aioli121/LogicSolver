#pragma once

namespace ao::logic_solver_internal
{
    class field_id_type
    {
        public:
            field_id_type()
            : field_id_type(-1, -1)
            {}

            field_id_type(
                std::pair<int, int> const pair
            )
            : field_id_type(pair.first, pair.second)
            {}

            field_id_type(
                int list_index,
                int field_index
            )
            : list_index(list_index)
            , field_index(field_index)
            {}

            bool
            operator==(
                field_id_type const &other
            ) const {
                return (list_index == other.list_index)
                    && (field_index == other.field_index);
            }

            int const list_index;
            int const field_index;
    };
}

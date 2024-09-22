#include <vector>
#include <string>

namespace experiments {
    // Intended to be a vector whose size is determined upon creation and cannot be resized
    template <typename value_type, typename allocator_type = std::allocator<value_type>>
    class locked_size_vector: private std::vector<value_type, allocator_type> {
        public:
            static locked_size_vector with_size_and_value_initializer(std::size_t initial_count, value_type const &initial_value) {
                return {initial_count, initial_value};
            }

            value_type &at(std::size_t index) { return std::vector<value_type, allocator_type>::at(index); }

        protected:
            locked_size_vector(std::size_t initial_count, value_type const &initial_value): std::vector<value_type, allocator_type>(initial_count, initial_value) {}
    };

    // Demos fields like list_count, field_count_per_list, grid creation and indexing, and cell values
    class experimental_class_1 {
        public:
            static experimental_class_1 with_list_count_and_field_count(int const list_count, int const field_count_per_list) {
                return {list_count, field_count_per_list};
            }

        private:
            experimental_class_1(int const list_count_, int const field_count_per_list_)
                : list_count(list_count_)
                , field_count_per_list(field_count_per_list_)
                , grid_count(list_count_ * (list_count_ - 1) / 2)
                , grid_id_constant((list_count_ - 1) * (list_count_ - 2) / 2 - 1)
                , field_count_per_list_squared(field_count_per_list_ * field_count_per_list_)
                , cells(locked_size_vector<cell>::with_size_and_value_initializer(grid_count * field_count_per_list_squared, cell::unmarked))
            {}

            enum class cell: int8_t {
                unmarked = 0,
                marked_unassoc = 1,
                marked_assoc = 2,
            };

            int const list_count;
            int const field_count_per_list;

            int const grid_count;
            int const grid_id_constant;
            int const field_count_per_list_squared;
            locked_size_vector<cell> cells;

            int get_grid_id_unchecked(int const lesser_list_id, int const greater_list_id) {
                auto const complement_lesser_list_id = list_count - lesser_list_id;

                return grid_id_constant - (complement_lesser_list_id - 1) * (complement_lesser_list_id - 2) / 2 + greater_list_id;
            }

            int get_cell_id_unchecked(
                    int const lesser_list_id, int const lesser_list_field_id,
                    int const greater_list_id, int const greater_list_field_id) {
                return get_grid_id_unchecked(lesser_list_id, greater_list_id) * field_count_per_list_squared + lesser_list_field_id * field_count_per_list + greater_list_field_id;
            };
    };

    // Encapsulates the lists and clues that make up the logic puzzle
    class logic_spec {
        public:

        
        private:
            // TODO: reevaluate types
            using list_count_type = std::size_t;
            using field_count_per_list_type = std::size_t;

            list_count_type list_count;
            field_count_per_list_type field_count_per_list;
    };
}


int main() {
}

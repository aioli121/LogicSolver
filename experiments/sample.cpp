#include <vector>
#include <string>
#include <memory>
#include <iostream>

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
            std::size_t list_count;
            std::size_t field_count_per_list;
            // std::vector<std::unique_ptr<list>> lists;

            std::size_t clue_count;
            // std::vector<clue> clues;
    };



    class test_list {
        public:
            test_list() = default;
    };

    class seq_list: public test_list {};

    class field_id {
        public:
            field_id(int list_id, int field_id)
                : list_id(list_id)
                , field_id_(field_id)
            {}

        private:
            int list_id;
            int field_id_;
    };

    class test_clue {

    };

    class association_test_clue: public test_clue {
        public:
            association_test_clue(std::vector<field_id> &&field_ids)
                : field_ids(std::move(field_ids))
            {}
        
        private:
            std::vector<field_id> field_ids;
    };

    class disassociation_test_clue: public test_clue {
        public:
            disassociation_test_clue(std::vector<field_id> &&field_ids)
                : field_ids(std::move(field_ids))
            {}
        
        private:
            std::vector<field_id> field_ids;
    };

    class single_match_test_clue: public test_clue {
        public:
            single_match_test_clue(field_id solitary_field_id, std::vector<field_id> &&possible_match_ids)
                : solitary_field_id(solitary_field_id)
                , possible_match_ids(std::move(possible_match_ids))
            {}
        
        private:
            field_id solitary_field_id;
            std::vector<field_id> possible_match_ids;
    };

    class difference_test_clue: public test_clue {
        public:
            difference_test_clue(field_id first_listed_id, int signed_diff, int valued_list_id, field_id second_listed_id)
                : first_listed_id(first_listed_id)
                , signed_diff(signed_diff)
                , valued_list_id(valued_list_id)
                , second_listed_id(second_listed_id)
            {}
        
        private:
            field_id first_listed_id;
            int signed_diff;
            int valued_list_id;
            field_id second_listed_id;
    };

    enum class test_cell_marking {
        unmarked, assoc, disassoc
    };

    class test_cell_trigger {};

    class test_cell {
        public:
            test_cell()
            : marking(test_cell_marking::unmarked)
            , cell_triggers() {}

        private:
            test_cell_marking marking;
            std::vector<std::unique_ptr<test_cell_trigger>> cell_triggers;
    };

    class test_grid_line_trigger {};

    class test_grid_line {
        private:
            std::vector<std::unique_ptr<test_grid_line_trigger>> grid_line_triggers;
    };

    class test_full_line_trigger {};

    class test_full_line {
        private:
            std::vector<std::unique_ptr<test_full_line_trigger>> full_line_triggers;
    };

    void test_0() {
        auto clues_ini = std::vector<std::unique_ptr<test_clue>>();
        {
            clues_ini.emplace_back(std::make_unique<association_test_clue>(std::vector<field_id>{{0, 3}, {1, 1}}));
            clues_ini.emplace_back(std::make_unique<association_test_clue>(std::vector<field_id>{{0, 2}, {1, 0}}));
            clues_ini.emplace_back(std::make_unique<difference_test_clue>(field_id{1, 0}, -1, 0, field_id{2, 0}));
            clues_ini.emplace_back(std::make_unique<difference_test_clue>(field_id{2, 3}, +1, 0, field_id{1, 2}));
            clues_ini.emplace_back(std::make_unique<single_match_test_clue>(field_id{1, 0}, std::vector<field_id>{{0, 1}, {2, 2}}));
        }
        auto const clues = std::move(clues_ini);

        auto const list_count = 3;
        auto const field_count_per_list = 4;

        auto const grid_count = list_count * (list_count - 1) / 2;
        auto const field_count_per_list_squared = field_count_per_list * field_count_per_list;

        auto cells = std::vector<test_cell>(grid_count * field_count_per_list_squared);
        auto grid_lines = std::vector<test_grid_line>();
        auto full_line_triggers = std::vector<test_full_line>();

        std::cout << "test\n";
    }
}


int main() {
    experiments::test_0();
}

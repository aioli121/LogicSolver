#pragma once

#include <vector>
#include <map>
#include <sstream>

#include "clue_type.hpp"
#include "clue_types.hpp"

namespace ao::logic_solver_internal {
    class numeric_clue_builder_type {
        public:
            numeric_clue_builder_type(int const list_count, int const field_count_per_list): list_count(list_count), field_count_per_list(field_count_per_list) {}

            numeric_clue_builder_type &add_numeric_association_clue(std::vector<std::pair<int, int>> const &field_id_int_pairs) {
                std::map<int, int> list_to_field_map;

                for (auto const &field_id_int_pair: field_id_int_pairs) {
                    if (field_id_int_pair.first < 0) {
                        std::ostringstream oss;
                        oss << "Detected an invalid list id (" << field_id_int_pair.first << ")";
                        throw std::invalid_argument(oss.str().c_str());
                    }
                    if (field_id_int_pair.first >= list_count) {
                        std::ostringstream oss;
                        oss << "Detected an out of bounds list id, " << field_id_int_pair.first << " (should be non-negative and less than " << list_count << ")";
                        throw std::invalid_argument(oss.str().c_str());
                    }
                    if (field_id_int_pair.second < 0) {
                        std::ostringstream oss;
                        oss << "Detected an invalid field id (" << field_id_int_pair.second << ")";
                        throw std::invalid_argument(oss.str().c_str());
                    }
                    if (field_id_int_pair.second >= field_count_per_list) {
                        std::ostringstream oss;
                        oss << "Detected an out of bounds field id, " << field_id_int_pair.second << " (should be non-negative and less than " << field_count_per_list << ")";
                        throw std::invalid_argument(oss.str().c_str());
                    }

                    auto const [map_entry_iter, was_inserted] = list_to_field_map.emplace(field_id_int_pair.first, field_id_int_pair.second);
                    if (!was_inserted && map_entry_iter->second == field_id_int_pair.second) {
                        std::ostringstream oss;
                        oss << "Detected a repeated list with differing fields. The conflicting field ids are ("
                            << map_entry_iter->first << ", " << map_entry_iter->second << ") and (" << field_id_int_pair.first << ", " << field_id_int_pair.second << ")";
                        throw std::invalid_argument(oss.str().c_str());
                    }
                }

                std::vector<field_id_type> field_ids;
                for (auto const list_field_entry: list_to_field_map) {
                    field_ids.emplace_back(list_field_entry.first, list_field_entry.second);
                }

                clues.emplace_back(std::make_unique<ao::logic_solver_internal::clue_types::association>(std::move(field_ids)));

                return *this;
            }

            numeric_clue_builder_type &add_numeric_difference_clue(std::pair<int, int> const &first_field_id_int_pair, int signed_index_diff, int list_id, std::pair<int, int> const &second_field_id_int_pair) {
                
            }

            int const list_count;
            int const field_count_per_list;

        private:
            std::vector<std::unique_ptr<clue_type>> clues;
    };
}
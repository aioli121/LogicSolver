#pragma once

#include <vector>
#include <sstream>

#include "clue_type.hpp"
#include "clue_types.hpp"

namespace ao::logic_solver_internal
{
    class numeric_clue_builder_type
    {
        public:
            numeric_clue_builder_type(
                int const list_count,
                int const field_count_per_list
            )
            : list_count(list_count)
            , field_count_per_list(field_count_per_list)
            {
                if (list_count < 2)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }
                if (field_count_per_list < 1)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }
            }

            numeric_clue_builder_type &
            add_numeric_association_clue(
                std::vector<std::pair<int, int>> const &field_id_int_pairs
            ) {
                auto registered_field_index_by_list_index = std::vector<int>(list_count, -1);
                auto registered_fields_count = int(0);

                for (auto const &field_id_int_pair: field_id_int_pairs)
                {
                    validate_field_id_int_pair(field_id_int_pair);

                    auto const [curr_list_index, curr_field_index] = field_id_int_pair;

                    auto &registered_field_index =
                        registered_field_index_by_list_index[curr_list_index];
                    if (registered_field_index == -1)
                    {
                        registered_field_index = curr_field_index;
                        registered_fields_count ++;
                    }
                    else if (registered_field_index != curr_field_index)
                    {
                        // TODO: error
                        throw std::invalid_argument("");

                        // std::ostringstream oss;
                        // oss << "Detected a repeated list with differing fields. The conflicting field ids are ("
                        //     << map_entry_iter->first << ", " << map_entry_iter->second << ") and ("
                        //     << field_id_int_pair.first << ", " << field_id_int_pair.second << ")";
                        // throw std::invalid_argument(oss.str().c_str());
                    }
                }

                if (registered_fields_count < 2)
                {
                    // TODO: error or notice
                    throw std::invalid_argument("");
                }

                auto field_ids = std::vector<field_id_type>();
                field_ids.reserve(registered_fields_count);
                for (
                    auto curr_list_index = 0;
                    curr_list_index < list_count;
                    curr_list_index ++
                ) {
                    auto const &curr_field_index = registered_field_index_by_list_index[curr_list_index];
                    if (curr_field_index != -1) {
                        field_ids.emplace_back(curr_list_index, curr_field_index);
                    }
                }

                clues.emplace_back(std::make_unique<ao::logic_solver_internal::clue_types::association>(std::move(field_ids)));

                return *this;
            }

            numeric_clue_builder_type &
            add_numeric_difference_clue(
                std::pair<int, int> const &first_field_id_int_pair,
                int const signed_index_diff,
                int const difference_list_index,
                std::pair<int, int> const &second_field_id_int_pair
            ) {
                validate_field_id_int_pair(first_field_id_int_pair);
                auto const first_field_id = field_id_type(first_field_id_int_pair);

                if (signed_index_diff <= -field_count_per_list)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }
                if (signed_index_diff >= field_count_per_list)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }
                if (signed_index_diff == 0)
                {
                    // TODO: add gridline equivalence clue instead of numeric difference
                    // return *this;
                    throw std::invalid_argument("");
                }

                validate_list_index(difference_list_index);
                if (difference_list_index == first_field_id.list_index)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }

                validate_field_id_int_pair(second_field_id_int_pair);
                auto const second_field_id = field_id_type(second_field_id_int_pair);
                if (second_field_id == first_field_id)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }
                if (second_field_id.list_index == difference_list_index)
                {
                    // TODO: error message
                    throw std::invalid_argument("");
                }

                if (signed_index_diff > 0)
                {
                    clues.emplace_back(std::make_unique<ao::logic_solver_internal::clue_types::difference>(first_field_id, signed_index_diff, difference_list_index, second_field_id));
                }
                else
                {
                    clues.emplace_back(std::make_unique<ao::logic_solver_internal::clue_types::difference>(second_field_id, -signed_index_diff, difference_list_index, first_field_id));
                }

                return *this;
            }

            numeric_clue_builder_type &
            add_numeric_either_clue(
                std::pair<int, int> const &first_field_id_int_pair,
                std::vector<std::pair<int, int>> const &potential_match_field_id_int_pairs
            ) {
                validate_field_id_int_pair(first_field_id_int_pair);
                auto const first_field_id = field_id_type(first_field_id_int_pair);

                // TODO: Consider performance implications
                auto is_potential_match_by_list_index_and_field_index =
                    std::vector<bool>(list_count * field_count_per_list, false);
                auto potential_matches_count = int(0);
                auto is_self_assoc = false;

                for (
                    auto const &potential_match_field_id_int_pair:
                        potential_match_field_id_int_pairs
                ) {
                    validate_field_id_int_pair(potential_match_field_id_int_pair);
                    auto const potential_match_field_id = field_id_type(potential_match_field_id_int_pair);

                    if (potential_match_field_id.list_index == first_field_id.list_index)
                    {
                        if (potential_match_field_id.field_index == first_field_id.field_index)
                        {
                            is_self_assoc = true;
                        }

                        continue;
                    }

                    auto field_id_is_potential_match =
                            is_potential_match_by_list_index_and_field_index.at(
                        potential_match_field_id.list_index * field_count_per_list
                            + potential_match_field_id.field_index);

                    if (!field_id_is_potential_match)
                    {
                        is_potential_match_by_list_index_and_field_index.at(
                            potential_match_field_id.list_index * field_count_per_list
                                + potential_match_field_id.field_index
                        ) = true;
                        potential_matches_count ++;
                    }
                }

                if (potential_matches_count <= 0)
                {
                    if (is_self_assoc)
                    {
                        return *this;
                    }

                    // TODO: error
                    throw std::invalid_argument("");
                }
                else if (potential_matches_count == 1)
                {
                    // TODO: this should be an association
                    throw std::invalid_argument("");
                }



                return *this;
            }

            int const list_count;
            int const field_count_per_list;

        private:
            void
            validate_list_index(
                int const list_index
            ) {
                if (list_index < 0) {
                    std::ostringstream oss;
                    oss << "Detected an invalid list id (" << list_index << ")";
                    throw std::invalid_argument(oss.str().c_str());
                }
                if (list_index >= list_count) {
                    std::ostringstream oss;
                    oss << "Detected an out of bounds list id, " << list_index << " (should be non-negative and less than " << list_count << ")";
                    throw std::invalid_argument(oss.str().c_str());
                }
            }

            void
            validate_field_id_int_pair(
                std::pair<int, int> const &field_id_int_pair
            ) {
                validate_list_index(field_id_int_pair.first);

                if (field_id_int_pair.second < 0)
                {
                    std::ostringstream oss;
                    oss << "Detected an invalid field id (" << field_id_int_pair.second << ")";
                    throw std::invalid_argument(oss.str().c_str());
                }
                if (field_id_int_pair.second >= field_count_per_list)
                {
                    std::ostringstream oss;
                    oss << "Detected an out of bounds field id, " << field_id_int_pair.second << " (should be non-negative and less than " << field_count_per_list << ")";
                    throw std::invalid_argument(oss.str().c_str());
                }
            }

            std::vector<std::unique_ptr<clue_type>> clues;
    };
}

#pragma once

#include "clue_type.hpp"

namespace ao::logic_solver_internal::clue_types
{
    class association
    : public clue_type
    {
        public:
            association(
                std::vector<field_id_type> &&field_ids
            )
            : field_ids(std::move(field_ids))
            {}

            std::unique_ptr<apply_failure>
            apply(
                solution_context_type &solution_context
            ) override {
                auto mark_action_queue = mark_action_queue_type();

                for (
                    auto first_field_id_iter = field_ids.cbegin();
                    first_field_id_iter < field_ids.cend() - 1;
                    first_field_id_iter ++
                ) {
                    for (
                        auto second_field_id_iter = first_field_id_iter + 1;
                        second_field_id_iter < field_ids.cend();
                        second_field_id_iter ++
                    ) {
                        // solution_context.try_mark_associated(*first_field_id_iter, *second_field_id_iter, mark_action_queue);
                    }
                }

                return nullptr;
            }

        private:
            std::vector<field_id_type> const field_ids;
    };

    class difference
    : public clue_type
    {
        public:
            difference(
                field_id_type first_field_id,
                int absolute_index_difference,
                int difference_list,
                field_id_type second_field_id
            )
            : first_field_id(first_field_id)
            , absolute_index_difference(absolute_index_difference)
            , difference_list(difference_list)
            , second_field_id(second_field_id)
            {}

            std::unique_ptr<apply_failure>
            apply(
                solution_context_type &solution_context
            ) override {
                return nullptr;
            }

        private:
            field_id_type first_field_id;
            int absolute_index_difference;
            unsigned int difference_list;
            field_id_type second_field_id;
    };

    class either
    : public clue_type
    {
        public:
            either(
                field_id_type first_field_id,
                std::vector<field_id_type> &&potential_match_field_ids
            )
            : first_field_id(first_field_id)
            , potential_match_field_ids(std::move(potential_match_field_ids))
            {}

            std::unique_ptr<apply_failure>
            apply(
                solution_context_type &solution_context
            ) override {
                return nullptr;
            }

        private:
            field_id_type first_field_id;
            std::vector<field_id_type> potential_match_field_ids;
    };
}

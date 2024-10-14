#pragma once

#include "internal/field_id_type.hpp"
#include "internal/indexed_clue_type.hpp"
#include "internal/marking_action_queue_type.hpp"

namespace ao::logic_solver_internal::indexed_clues {
	class offset_indexed_clue_type : public indexed_clue_type {
		public:
		offset_indexed_clue_type(
			field_id_type const first_field_id,
			int const absolute_offset_amount,
			int const offset_list_index,
			field_id_type const second_field_id
		) : first_field_id(first_field_id)
		, absolute_offset_amount(absolute_offset_amount)
		, offset_list_index(offset_list_index)
		, second_field_id(second_field_id) {}

		void evaluate(
			solution_context_type &solution_context
		) const override {
			auto marking_action_queue = marking_action_queue_type();
			// TODO
		}

		private:
		field_id_type const first_field_id;
		int const absolute_offset_amount;
		int const offset_list_index;
		field_id_type const second_field_id;
	};
}

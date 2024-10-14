#pragma once

#include <utility>
#include <vector>

#include "internal/field_id_type.hpp"
#include "internal/indexed_clue_type.hpp"
#include "internal/marking_action_queue_type.hpp"

namespace ao::logic_solver_internal::indexed_clues {
	class association_indexed_clue_type : public indexed_clue_type {
		public:
		association_indexed_clue_type(
			std::vector<field_id_type> &&association_fields
		) : association_fields(std::move(association_fields)) {}

		void evaluate(
			solution_context_type &solution_context
		) const override {
			auto marking_action_queue = marking_action_queue_type();
			// TODO
		}

		private:
		std::vector<field_id_type> const association_fields;
	};
}

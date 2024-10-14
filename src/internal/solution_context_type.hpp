#pragma once

#include "internal/grids_type.hpp"
#include "internal/marking_action_queue_type.hpp"

namespace ao::logic_solver_internal {
	class solution_context_type {
		public:
		solution_context_type(
			int const validated_list_count,
			int const validated_field_count_per_list
		) : validated_list_count(validated_list_count)
		, validated_field_count_per_list(validated_field_count_per_list)
		, grids(validated_list_count, validated_field_count_per_list) {}

		void try_mark_associated(
			field_id_type const field_id_0,
			field_id_type const field_ids_1,
			marking_action_queue_type &marking_queue
		) {}

		void try_mark_disassociated() {}

		private:
		int const validated_list_count;
		int const validated_field_count_per_list;
		grids_type grids;
	};
}

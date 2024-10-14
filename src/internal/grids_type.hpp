#pragma once

#include <vector>

namespace ao::logic_solver_internal {
	class grids_type {
		public:
		grids_type(
			int const validated_list_count,
			int const validated_field_count_per_list
		) : validated_list_count(validated_list_count)
		, validated_field_count_per_list(validated_field_count_per_list)
		, grid_count(validated_list_count * (validated_list_count - 1) / 2)
		, cell_count_per_grid(validated_field_count_per_list * validated_field_count_per_list)
		, cells(grid_count * cell_count_per_grid) {}

		private:
		int const validated_list_count;
		int const validated_field_count_per_list;
		int const grid_count;
		int const cell_count_per_grid;

		class cell_type {
			public:
			cell_type(): marking(marking_type::unmarked) {}

			private:
			enum class marking_type {
				unmarked,
				associated,
				disassociated
			} marking;
		};

		std::vector<cell_type> cells;
	};
}

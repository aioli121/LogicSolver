#pragma once

#include <utility>

namespace ao::logic_solver_internal {
	class field_id_type {
		public:
		field_id_type(
			int const list_index,
			int const field_index
		) : list_index(list_index)
		, field_index(field_index) {}

		field_id_type(
			std::pair<int, int> const &field
		) : field_id_type(field.first, field.second) {}

		bool operator ==(
			field_id_type const &other
		) const {
			return (other.list_index == list_index) &&
				(other.field_index == field_index);
		}

		int const list_index;
		int const field_index;
	};
}

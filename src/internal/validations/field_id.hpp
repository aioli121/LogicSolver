#pragma once

#include <utility>

#include "internal/validations/index.hpp"

namespace ao::logic_solver_internal::validations::field_id {
	class validator_type {
		public:
		validator_type(
			int const validated_list_count,
			int const validated_field_count_per_list
		) : list_index_validator("list", validated_list_count)
		, field_index_validator("field", validated_field_count_per_list) {}

		void validate(
			std::pair<int, int> const field_id
		) const {
			auto const [list_index, field_index] = field_id;

			list_index_validator.validate(list_index);
			field_index_validator.validate(field_index);
		}

		index::validator_type const list_index_validator;
		index::validator_type const field_index_validator;
	};
}

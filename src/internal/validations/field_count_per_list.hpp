#pragma once

#include "internal/validations/validation_exception_base_type.hpp"

namespace ao::logic_solver_internal::validations::field_count_per_list {
	static int const minimum = 1;

	class too_few_exception_type : public validation_exception_base_type {
		public:
		too_few_exception_type(
			int const field_count_per_list
		) : field_count_per_list(field_count_per_list) {}

		auto exception_title() const noexcept -> std::string override {
			return "field_count_per_list::too_few_exception_type";
		}

		auto exception_details() const noexcept -> std::string override {
			return std::string("Too few fields per list. Count was ") +
				std::to_string(field_count_per_list) +
				". Expected count >= " +
				std::to_string(minimum) +
				".";
		}

		private:
		int const field_count_per_list;
	};

	static void validate(
		int const field_count_per_list
	) {
		if (field_count_per_list < minimum) {
			throw too_few_exception_type(field_count_per_list);
		}
	}
}

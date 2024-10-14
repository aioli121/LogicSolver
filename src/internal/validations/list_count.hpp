#pragma once

#include "internal/validations/validation_exception_base_type.hpp"

namespace ao::logic_solver_internal::validations::list_count {
	static int const minimum = 2;

	class too_few_exception_type : public validation_exception_base_type {
		public:
		too_few_exception_type(
			int const list_count
		) : list_count(list_count) {}

		auto exception_title() const noexcept -> std::string override {
			return "list_count::too_few_exception_type";
		}

		auto exception_details() const noexcept -> std::string override {
			return std::string("Too few lists. Count was ") +
				std::to_string(list_count) +
				". Expected count >= " +
				std::to_string(minimum) +
				".";
		}

		private:
		int const list_count;
	};

	static void validate(
		int const list_count
	) {
		if (list_count < minimum) {
			throw too_few_exception_type(list_count);
		}
	}
}

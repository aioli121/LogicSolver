#pragma once

#include <utility>
#include <vector>

#include "internal/field_id_type.hpp"
#include "internal/indexed_clues_builder_exceptions/indexed_clues_builder_exception_base_type.hpp"

namespace ao::logic_solver_internal::indexed_clues_builder_exceptions::association {
	class same_list_different_fields_exception_type
	: public indexed_clues_builder_exception_base_type {
		public:
		same_list_different_fields_exception_type(
			int const list_index,
			int const field_index_0,
			int const field_index_1
		) : list_index(list_index)
		, field_index_0(field_index_0)
		, field_index_1(field_index_1) {}

		auto exception_title() const noexcept -> std::string final override {
			return "association::same_list_different_fields_exception_type";
		}

		auto exception_details() const noexcept -> std::string final override {
			return std::string("The same list index (") +
				std::to_string(list_index) +
				") appeared in multiple field identifiers with different field_indices (" +
				std::to_string(field_index_0) +
				" and " +
				std::to_string(field_index_1) +
				").";
		}

		private:
		int const list_index;
		int const field_index_0;
		int const field_index_1;
	};
}

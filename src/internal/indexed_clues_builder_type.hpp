#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "internal/indexed_clues/association_indexed_clue_type.hpp"
#include "internal/indexed_clues/offset_indexed_clue_type.hpp"
#include "internal/field_id_type.hpp"
#include "internal/indexed_clue_type.hpp"
#include "internal/validations/field_count_per_list.hpp"
#include "internal/validations/field_id.hpp"
#include "internal/validations/list_count.hpp"
#include "internal/indexed_clues_builder_exceptions/association/same_list_different_fields_exception_type.hpp"

namespace ao::logic_solver_internal {
	class indexed_clues_builder_type {
		public:
		indexed_clues_builder_type(
			int const list_count,
			int const field_count_per_list
		) : list_count(list_count)
		, field_count_per_list(field_count_per_list)
		, field_id_validator(list_count, field_count_per_list) {
			using namespace validations;

			list_count::validate(list_count);
			field_count_per_list::validate(field_count_per_list);
		}

		auto try_append_association_clue(
			std::vector<std::pair<int, int>> const &association_fields
		) -> indexed_clues_builder_type & {
			// NOTE: Repeating fields is fine.
			// 	Associating a field from one list with a different field from the same list is not.

			auto cached_field_index_by_list_index = std::vector<int>(list_count, -1);
			auto cached_fields_count = int(0);

			for (auto const &association_field : association_fields) {
				field_id_validator.validate(association_field);

				auto const [list_index, field_index] = association_field;
				auto &cached_field_index = cached_field_index_by_list_index.at(list_index);

				if (cached_field_index < 0) {
					cached_field_index = field_index;
					cached_fields_count ++;
				} else if (cached_field_index != field_index) {
					throw indexed_clues_builder_exceptions::association::same_list_different_fields_exception_type(
						list_index,
						cached_field_index,
						field_index
					);
				}
			}

			auto fields = std::vector<field_id_type>();
			fields.reserve(cached_fields_count);

			for (auto list_index = int(0); list_index < list_count; list_index ++) {
				auto const &cached_field_index = cached_field_index_by_list_index.at(list_index);

				if (cached_field_index < 0) {
					continue;
				}

				fields.emplace_back(list_index, cached_field_index);
			}

			clues.emplace_back(std::make_unique<indexed_clues::association_indexed_clue_type>(std::move(fields)));
			return *this;
		}

		auto try_append_offset_clue(
			std::pair<int, int> const first_field,
			int const signed_offset_amount,
			int const offset_list_index,
			std::pair<int, int> const second_field
		) -> indexed_clues_builder_type & {
			field_id_validator.validate(first_field);
			auto const first_field_id = field_id_type(first_field);

			if (signed_offset_amount <= -field_count_per_list) {
				// TODO: Error
				throw std::invalid_argument("");
				return *this;
			} else if (signed_offset_amount == 0) {
				// TODO: create corresponding identity clue (first_field, offset_list_index, second_field)
				// return *this;
				throw std::invalid_argument("");
			} else if (signed_offset_amount >= field_count_per_list) {
				// TODO: Error
				throw std::invalid_argument("");
			}

			field_id_validator.list_index_validator.validate(offset_list_index);
			if (offset_list_index == first_field_id.list_index) {
				// TODO: Error
				throw std::invalid_argument("");
			}

			field_id_validator.validate(second_field);
			auto const second_field_id = field_id_type(second_field);
			if (second_field_id == first_field_id) {
				// TODO: Error
				throw std::invalid_argument("");
			} else if (second_field_id.list_index == offset_list_index) {
				// TODO: Error
				throw std::invalid_argument("");
			}

			if (signed_offset_amount > 0) {
				clues.emplace_back(std::make_unique<indexed_clues::offset_indexed_clue_type>(first_field_id, signed_offset_amount, offset_list_index, second_field_id));
			} else {
				clues.emplace_back(std::make_unique<indexed_clues::offset_indexed_clue_type>(second_field_id, -signed_offset_amount, offset_list_index, first_field_id));
			}
			return *this;
		}

		auto try_append_either_clue(
			std::pair<int, int> const target_field,
			std::vector<std::pair<int, int>> const &possible_target_association_fields
		) -> indexed_clues_builder_type & {
			// TODO
			return *this;
		}

		private:
		int const list_count;
		int const field_count_per_list;
		validations::field_id::validator_type const field_id_validator;
		std::vector<std::unique_ptr<indexed_clue_type>> clues;
	};
}

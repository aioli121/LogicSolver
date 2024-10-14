#pragma once

#include <memory>
#include <queue>

namespace ao::logic_solver_internal {
	class marking_action_queue_type {
		public:
		marking_action_queue_type() : marking_action_queue() {}

		private:
		class marking_action_type {
			public:
			virtual void evaluate() const = 0;
		};

		class mark_associated_action_type : public marking_action_type {
			public:
			void evaluate() const override {
				// TODO
			}
		};

		class mark_disassociated_action_type : public marking_action_type {
			public:
			void evaluate() const override {
				// TODO
			}
		};

		std::queue<std::unique_ptr<marking_action_type>> marking_action_queue;
	};
}

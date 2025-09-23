#pragma once
#include "base/embedded/sram/asynchronous_sram_controller_handle.h"

class base::asynchronous_sram::asynchronous_sram_controller_handle
{
public:
	virtual ~asynchronous_sram_controller_handle() = default;

	virtual void Initialize(base::asynchronous_sram::asynchronous_sram_timing const &timing) = 0;

	virtual base::asynchronous_sram::asynchronous_sram_timing Timing() const = 0;

	virtual base::Span Span() = 0;
};

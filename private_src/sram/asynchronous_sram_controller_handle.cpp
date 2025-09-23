#include "asynchronous_sram_controller_handle.h" // IWYU pragma: keep
#include "AsynchronousSramController1.h"

std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle> base::asynchronous_sram::open(uint32_t id)
{
	return std::shared_ptr<base::asynchronous_sram::asynchronous_sram_controller_handle>{new bsp::AsynchronousSramController1{}};
}

void base::asynchronous_sram::initialize(base::asynchronous_sram::asynchronous_sram_controller_handle &self,
										 base::asynchronous_sram::asynchronous_sram_timing const &timing)
{
	self.Initialize(timing);
}

base::asynchronous_sram::asynchronous_sram_timing base::asynchronous_sram::timing(base::asynchronous_sram::asynchronous_sram_controller_handle &self)
{
	return self.Timing();
}

base::Span base::asynchronous_sram::span(base::asynchronous_sram::asynchronous_sram_controller_handle &self)
{
	return self.Span();
}

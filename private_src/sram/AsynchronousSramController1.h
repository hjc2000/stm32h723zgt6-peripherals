#pragma once
#include "asynchronous_sram_controller_handle.h"
#include "base/embedded/sram/asynchronous_sram_controller_handle.h"
#include "base/UsageStateManager.h"
#include "hal.h" // IWYU pragma: keep

namespace bsp
{
	class AsynchronousSramController1 final :
		public base::asynchronous_sram::asynchronous_sram_controller_handle
	{
	private:
		base::UsageStateManager<AsynchronousSramController1> _usage_state_manager{};
		base::asynchronous_sram::asynchronous_sram_timing _timing{};
		SRAM_HandleTypeDef _sram_handle{};

	public:
		AsynchronousSramController1()
		{
			base::asynchronous_sram::msp_initialize_callback(1);
		}

		virtual void Initialize(base::asynchronous_sram::ISRAMTimingProvider const &timing_provider) override;

		virtual void Initialize(std::string const &clock_source_name,
								uint32_t divider,
								base::asynchronous_sram::ISRAMTimingProvider const &timing_provider) override;

		virtual base::asynchronous_sram::asynchronous_sram_timing Timing() const override
		{
			return _timing;
		}

		virtual base::Span Span() override
		{
			base::Span ret{
				reinterpret_cast<uint8_t *>(0x60000000),
				static_cast<int64_t>(0x70000000 - 0x60000000),
			};

			return ret;
		}
	};

} // namespace bsp

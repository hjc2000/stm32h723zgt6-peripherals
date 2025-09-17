#include "AsynchronousSramController1.h" // IWYU pragma: keep
#include "base/embedded/clock/ClockSource.h"
#include "base/string/define.h"

void bsp::AsynchronousSramController1::Initialize(base::asynchronous_sram::ISRAMTimingProvider const &timing_provider)
{
	/** Perform the SRAM1 memory initialization sequence
	 */
	_sram_handle.Instance = FMC_NORSRAM_DEVICE;
	_sram_handle.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
	/* _sram_handle.Init */
	_sram_handle.Init.NSBank = FMC_NORSRAM_BANK1;
	_sram_handle.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
	_sram_handle.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
	_sram_handle.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
	_sram_handle.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
	_sram_handle.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
	_sram_handle.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
	_sram_handle.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
	_sram_handle.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
	_sram_handle.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
	_sram_handle.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_ENABLE;
	_sram_handle.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
	_sram_handle.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
	_sram_handle.Init.WriteFifo = FMC_WRITE_FIFO_DISABLE;
	_sram_handle.Init.PageSize = FMC_PAGE_SIZE_NONE;

	base::clock::ClockSource hclk{"hclk"};
	_timing = timing_provider.GetTiming(hclk.Frequency());

	/* Timing */
	FMC_NORSRAM_TimingTypeDef Timing{};
	Timing.AddressSetupTime = _timing.address_setup_clock_cycle_count();
	Timing.AddressHoldTime = _timing.address_hold_clock_cycle_count();
	Timing.DataSetupTime = _timing.data_setup_clock_cycle_count();
	Timing.BusTurnAroundDuration = _timing.bus_turn_around_clock_cycle_count();
	Timing.AccessMode = FMC_ACCESS_MODE_A;
	/* ExtTiming */

	if (HAL_SRAM_Init(&_sram_handle, &Timing, nullptr) != HAL_OK)
	{
		throw std::runtime_error{CODE_POS_STR + "初始化失败"};
	}
}

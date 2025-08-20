#include "AsynchronousSramController1.h" // IWYU pragma: keep
#include "base/embedded/clock/ClockSource.h"

void bsp::AsynchronousSramController1::Initialize(base::asynchronous_sram::ISRAMTimingProvider const &timing_provider)
{
	InitializeGpio();

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
	_sram_handle.Init.WriteOperation = FMC_WRITE_OPERATION_DISABLE;
	_sram_handle.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
	_sram_handle.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
	_sram_handle.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_ENABLE;
	_sram_handle.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
	_sram_handle.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
	_sram_handle.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
	_sram_handle.Init.PageSize = FMC_PAGE_SIZE_NONE;

	/* Timing */
	FMC_NORSRAM_TimingTypeDef Timing{};
	Timing.AddressSetupTime = 15;
	Timing.AddressHoldTime = 15;
	Timing.DataSetupTime = 255;
	Timing.BusTurnAroundDuration = 15;
	Timing.CLKDivision = 16;
	Timing.DataLatency = 17;
	Timing.AccessMode = FMC_ACCESS_MODE_A;
	/* ExtTiming */

	if (HAL_SRAM_Init(&_sram_handle, &Timing, NULL) != HAL_OK)
	{
		throw std::runtime_error{"初始化失败"};
	}
}

// base::clock::ClockSource hclk{"hclk"};
// _timing = timing_provider.GetTiming(hclk.Frequency());

#include "AsynchronousSramController1.h" // IWYU pragma: keep
#include "base/string/define.h"
#include <stdexcept>

void bsp::AsynchronousSramController1::Initialize(base::asynchronous_sram::asynchronous_sram_timing const &timing)
{
	__HAL_RCC_FMC_CLK_ENABLE();

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

	/* Timing */
	FMC_NORSRAM_TimingTypeDef hal_timing{};
	hal_timing.AddressSetupTime = timing.address_setup_clock_cycle_count();
	hal_timing.AddressHoldTime = timing.address_hold_clock_cycle_count();
	hal_timing.DataSetupTime = timing.data_setup_clock_cycle_count();
	hal_timing.BusTurnAroundDuration = timing.bus_turn_around_clock_cycle_count();
	hal_timing.AccessMode = FMC_ACCESS_MODE_A;

	HAL_StatusTypeDef result = HAL_SRAM_Init(&_sram_handle, &hal_timing, nullptr);
	if (result != HAL_OK)
	{
		throw std::runtime_error{CODE_POS_STR + "初始化失败"};
	}
}

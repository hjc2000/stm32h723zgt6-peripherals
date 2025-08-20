#include "AsynchronousSramController1.h" // IWYU pragma: keep
#include "base/embedded/clock/ClockSource.h"

void bsp::AsynchronousSramController1::InitializeGpio()
{
	GPIO_InitTypeDef GPIO_InitStruct{};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct{};

	/** Initializes the peripherals clock
	 */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FMC;
	PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
	}

	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_ENABLE();

	// FMC GPIO Configuration
	//
	// PF0   ------> FMC_A0
	// PF1   ------> FMC_A1
	// PF2   ------> FMC_A2
	// PF3   ------> FMC_A3
	// PF4   ------> FMC_A4
	// PF5   ------> FMC_A5
	// PF12   ------> FMC_A6
	// PF13   ------> FMC_A7
	// PF14   ------> FMC_A8
	// PF15   ------> FMC_A9
	// PG0   ------> FMC_A10
	// PG1   ------> FMC_A11
	// PG2   ------> FMC_A12
	// PG3   ------> FMC_A13
	//
	// PD14   ------> FMC_D0
	// PD15   ------> FMC_D1
	// PD0   ------> FMC_D2
	// PD1   ------> FMC_D3
	// PE7   ------> FMC_D4
	// PE8   ------> FMC_D5
	// PE9   ------> FMC_D6
	// PE10   ------> FMC_D7
	// PE11   ------> FMC_D8
	// PE12   ------> FMC_D9
	// PE13   ------> FMC_D10
	// PE14   ------> FMC_D11
	// PE15   ------> FMC_D12
	// PD8   ------> FMC_D13
	// PD9   ------> FMC_D14
	// PD10   ------> FMC_D15
	//
	// PD7   ------> FMC_NE1
	// PD4   ------> FMC_NOE
	// PD6   ------> FMC_NWAIT
	// PD5   ------> FMC_NWE
	//
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
						  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 |
						  GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
						  GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
						  GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
						  GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 |
						  GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

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
		throw std::runtime_error{"初始化失败"};
	}
}

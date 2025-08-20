#pragma once
#include "asynchronous_sram_controller_handle.h"
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

		void InitializeGpio()
		{
			/* USER CODE BEGIN FMC_MspInit 0 */

			/* USER CODE END FMC_MspInit 0 */
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

			/* USER CODE BEGIN FMC_MspInit 1 */

			/* USER CODE END FMC_MspInit 1 */
		}

	public:
		virtual void Initialize(base::asynchronous_sram::ISRAMTimingProvider const &timing_provider) override;

		virtual base::asynchronous_sram::asynchronous_sram_timing Timing() const override
		{
			return _timing;
		}
	};

} // namespace bsp

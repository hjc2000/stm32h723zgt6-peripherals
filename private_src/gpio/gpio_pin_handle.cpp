#include "gpio_pin_handle.h"
#include "base/embedded/gpio/gpio_parameter.h"
#include <cstdint>

std::shared_ptr<base::gpio::gpio_pin_handle> base::gpio::open(base::gpio::PortEnum port, uint32_t pin)
{
	std::shared_ptr<base::gpio::gpio_pin_handle> handle{new base::gpio::gpio_pin_handle{port, pin}};
	return handle;
}

/* #region 全局初始化函数 */

void base::gpio::initialize_as_input_mode(base::gpio::gpio_pin_handle &h,
										  base::gpio::PullMode pull_mode,
										  base::gpio::TriggerEdge trigger_edge)
{
	h.InitializeAsInputMode(pull_mode, trigger_edge);
}

void base::gpio::initialize_as_input_mode(base::gpio::gpio_pin_handle &h)
{
	h.InitializeAsInputMode();
}

void base::gpio::initialize_as_output_mode(base::gpio::gpio_pin_handle &h,
										   base::gpio::PullMode pull_mode,
										   base::gpio::DriveMode drive_mode)
{
	h.InitializeAsOutputMode(pull_mode, drive_mode);
}

void base::gpio::initialize_as_output_mode(base::gpio::gpio_pin_handle &h)
{
	h.InitializeAsOutputMode();
}

void base::gpio::initialize_as_alternate_function_mode(base::gpio::gpio_pin_handle &h,
													   uint32_t alternate_function_index,
													   base::gpio::PullMode pull_mode,
													   base::gpio::DriveMode drive_mode)
{
	h.InitializeAsAlternateFunctionMode(alternate_function_index, pull_mode, drive_mode);
}

/* #endregion */

/* #region 引脚信息 */

base::gpio::PortEnum base::gpio::port(base::gpio::gpio_pin_handle &h)
{
	return h.Port();
}

uint32_t base::gpio::pin(base::gpio::gpio_pin_handle &h)
{
	return h.Pin();
}

/* #endregion */

/* #region 全局读写引脚函数 */

bool base::gpio::read_pin(base::gpio::gpio_pin_handle &h)
{
	return h.ReadPin();
}

void base::gpio::write_pin(base::gpio::gpio_pin_handle &h, bool value)
{
	h.WritePin(value);
}

void base::gpio::toggle_pin(base::gpio::gpio_pin_handle &h)
{
	h.TogglePin();
}

/* #endregion */

/* #region 中断回调 */

void base::gpio::register_interrupt_callback(base::gpio::gpio_pin_handle &h,
											 int32_t priority,
											 std::function<void()> const &callback_func)
{
	h.RegisterInterruptCallback(priority, callback_func);
}

void base::gpio::register_interrupt_callback(base::gpio::gpio_pin_handle &h,
											 std::function<void()> const &callback_func)
{
	h.RegisterInterruptCallback(callback_func);
}

void base::gpio::unregister_interrupt_callback(base::gpio::gpio_pin_handle &h)
{
	h.UnregisterInterruptCallback();
}

/* #endregion */

extern "C"
{
	static uint32_t FMC_DeInitialized = 0;

	static void HAL_FMC_MspDeInit(void)
	{
		/* USER CODE BEGIN FMC_MspDeInit 0 */

		/* USER CODE END FMC_MspDeInit 0 */
		if (FMC_DeInitialized)
		{
			return;
		}
		FMC_DeInitialized = 1;
		/* Peripheral clock enable */
		__HAL_RCC_FMC_CLK_DISABLE();

		/** FMC GPIO Configuration
		PF0   ------> FMC_A0
		PF1   ------> FMC_A1
		PF2   ------> FMC_A2
		PF3   ------> FMC_A3
		PF4   ------> FMC_A4
		PF5   ------> FMC_A5
		PF12   ------> FMC_A6
		PF13   ------> FMC_A7
		PF14   ------> FMC_A8
		PF15   ------> FMC_A9
		PG0   ------> FMC_A10
		PG1   ------> FMC_A11
		PE7   ------> FMC_D4
		PE8   ------> FMC_D5
		PE9   ------> FMC_D6
		PE10   ------> FMC_D7
		PE11   ------> FMC_D8
		PE12   ------> FMC_D9
		PE13   ------> FMC_D10
		PE14   ------> FMC_D11
		PE15   ------> FMC_D12
		PD8   ------> FMC_D13
		PD9   ------> FMC_D14
		PD10   ------> FMC_D15
		PD14   ------> FMC_D0
		PD15   ------> FMC_D1
		PG2   ------> FMC_A12
		PG3   ------> FMC_A13
		PD0   ------> FMC_D2
		PD1   ------> FMC_D3
		PD4   ------> FMC_NOE
		PD5   ------> FMC_NWE
		PD6   ------> FMC_NWAIT
		PD7   ------> FMC_NE1
		*/
		HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
								   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 |
								   GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

		HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
								   GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
								   GPIO_PIN_14 | GPIO_PIN_15);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
								   GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 |
								   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

		/* USER CODE BEGIN FMC_MspDeInit 1 */

		/* USER CODE END FMC_MspDeInit 1 */
	}

	void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef *hsram)
	{
		/* USER CODE BEGIN SRAM_MspDeInit 0 */

		/* USER CODE END SRAM_MspDeInit 0 */
		HAL_FMC_MspDeInit();
		/* USER CODE BEGIN SRAM_MspDeInit 1 */

		/* USER CODE END SRAM_MspDeInit 1 */
	}
}

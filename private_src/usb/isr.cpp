#include "hal.h" // IWYU pragma: keep
#include "UsbFsPcd.h"

extern "C"
{
	void OTG_HS_IRQHandler(void)
	{
		/* USER CODE BEGIN OTG_FS_IRQn 0 */

		/* USER CODE END OTG_FS_IRQn 0 */
		HAL_PCD_IRQHandler(&bsp::UsbFsPcd::HalPcdHandle());
		/* USER CODE BEGIN OTG_FS_IRQn 1 */

		/* USER CODE END OTG_FS_IRQn 1 */
	}
}

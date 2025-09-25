#include "hal.h" // IWYU pragma: keep

extern "C"
{
	extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

	void OTG_HS_IRQHandler(void)
	{
		/* USER CODE BEGIN OTG_FS_IRQn 0 */

		/* USER CODE END OTG_FS_IRQn 0 */
		HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
		/* USER CODE BEGIN OTG_FS_IRQn 1 */

		/* USER CODE END OTG_FS_IRQn 1 */
	}
}

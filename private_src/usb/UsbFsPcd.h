#pragma once
#include "base/embedded/usb/usb_fs_pcd_handle.h"
#include "base/UsageStateManager.h"
#include "hal.h" // IWYU pragma: keep
#include "usb_fs_pcd_handle.h"
#include "usbd_def.h"
#include <cstdint>

namespace bsp
{
	class UsbFsPcd :
		public base::usb::fs_pcd::usb_fs_pcd_handle
	{
	private:
		class hal_pcd_handle_context
		{
		public:
			hal_pcd_handle_context(UsbFsPcd *self)
				: _self{self}
			{
			}

			inline static PCD_HandleTypeDef _handle{};
			UsbFsPcd *_self{};
		};

		class usbd_handle_context
		{
		public:
			usbd_handle_context(UsbFsPcd *self)
				: _self{self}
			{
			}

			inline static USBD_HandleTypeDef _handle{};
			UsbFsPcd *_self{};
		};

		base::UsageStateManager<UsbFsPcd> _usage_state_manager{};
		hal_pcd_handle_context _hal_pcd_handle_context{this};
		usbd_handle_context _usbd_handle_context{this};

		void InitializeCallback();

		/* #region USB 回调 */

		void OnSofCallback()
		{
		}

		void OnSetupStageCallback()
		{
		}

		void OnResetCallback()
		{
		}

		void OnSuspendCallback()
		{
		}

		void OnResumeCallback()
		{
		}

		void OnConnectCallback()
		{
		}

		void OnDisconnectCallback()
		{
		}

		void OnDataOutStageCallback(uint8_t epnum)
		{
		}

		void OnDataInStageCallback(uint8_t epnum)
		{
		}

		void OnISOOUTIncompleteCallback(uint8_t epnum)
		{
		}

		void OnISOINIncompleteCallback(uint8_t epnum)
		{
		}

		/* #endregion */

	public:
		UsbFsPcd()
		{
			base::usb::fs_pcd::msp_initialize(1);
		}

		virtual void InitializeAsDevice(std::string const &clock_source_name,
										uint32_t divider,
										base::usb::PhyType phy_type) override;

		static PCD_HandleTypeDef &HalPcdHandle()
		{
			return hal_pcd_handle_context::_handle;
		}

		static USBD_HandleTypeDef &UsbdHandle()
		{
			return usbd_handle_context::_handle;
		}
	};

} // namespace bsp

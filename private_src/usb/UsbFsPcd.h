#pragma once
#include "base/embedded/interrupt/interrupt.h"
#include "base/embedded/usb/usb_fs_pcd_handle.h"
#include "base/UsageStateManager.h"
#include "hal.h" // IWYU pragma: keep
#include "usb_fs_pcd_handle.h"
#include <cstdint>
#include <functional>

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

		base::UsageStateManager<UsbFsPcd> _usage_state_manager{};
		hal_pcd_handle_context _hal_pcd_handle_context{this};

		void InitializeCallback();

		std::function<void()> _sof_callback;
		std::function<void()> _setup_stage_callback;
		std::function<void()> _reset_callback;
		std::function<void()> _suspend_callback;
		std::function<void()> _resume_callback;
		std::function<void()> _connect_callback;
		std::function<void()> _disconnect_callback;

		/* #region USB 回调 */

		void OnSofCallback()
		{
			if (_sof_callback)
			{
				_sof_callback();
			}
		}

		void OnSetupStageCallback()
		{
			if (_setup_stage_callback)
			{
				_setup_stage_callback();
			}
		}

		void OnResetCallback()
		{
			if (_reset_callback)
			{
				_reset_callback();
			}
		}

		void OnSuspendCallback()
		{
			if (_suspend_callback)
			{
				_suspend_callback();
			}
		}

		void OnResumeCallback()
		{
			if (_resume_callback)
			{
				_resume_callback();
			}
		}

		void OnConnectCallback()
		{
			if (_connect_callback)
			{
				_connect_callback();
			}
		}

		void OnDisconnectCallback()
		{
			if (_disconnect_callback)
			{
				_disconnect_callback();
			}
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

		virtual void InitializeAsDevice(base::usb::PhyType phy_type) override;

		static PCD_HandleTypeDef &HalPcdHandle()
		{
			return hal_pcd_handle_context::_handle;
		}

		virtual void SetSofCallback(std::function<void()> const callback) override
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_sof_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}

		virtual void SetSetupStageCallback(std::function<void()> const callback) override
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_setup_stage_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}

		void SetResetCallback(std::function<void()> const callback)
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_reset_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}

		void SetSuspendCallback(std::function<void()> const callback)
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_suspend_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}

		void SetResumeCallback(std::function<void()> const callback)
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_resume_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}

		void SetConnectCallback(std::function<void()> const callback)
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_connect_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}

		void SetDisconnectCallback(std::function<void()> const callback)
		{
			base::interrupt::disable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn));
			_disconnect_callback = callback;
			base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);
		}
	};

} // namespace bsp

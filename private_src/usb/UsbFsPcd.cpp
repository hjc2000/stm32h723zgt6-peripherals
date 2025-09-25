#include "UsbFsPcd.h"
#include "base/embedded/interrupt/interrupt.h"
#include "Legacy/stm32_hal_legacy.h"
#include <cstdint>

void bsp::UsbFsPcd::InitializeCallback()
{
	_hal_pcd_handle_context._handle.SOFCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnSofCallback();
	};

	_hal_pcd_handle_context._handle.SetupStageCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnSetupStageCallback();
	};

	_hal_pcd_handle_context._handle.ResetCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnResetCallback();
	};

	_hal_pcd_handle_context._handle.SuspendCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnSuspendCallback();
	};

	_hal_pcd_handle_context._handle.ResumeCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnResumeCallback();
	};

	_hal_pcd_handle_context._handle.ConnectCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnConnectCallback();
	};

	_hal_pcd_handle_context._handle.DisconnectCallback = [](PCD_HandleTypeDef *handle)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnDisconnectCallback();
	};

	_hal_pcd_handle_context._handle.DataOutStageCallback = [](PCD_HandleTypeDef *handle, uint8_t epnum)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnDataOutStageCallback(epnum);
	};

	_hal_pcd_handle_context._handle.DataInStageCallback = [](PCD_HandleTypeDef *handle, uint8_t epnum)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnDataInStageCallback(epnum);
	};

	_hal_pcd_handle_context._handle.ISOOUTIncompleteCallback = [](PCD_HandleTypeDef *handle, uint8_t epnum)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnISOOUTIncompleteCallback(epnum);
	};

	_hal_pcd_handle_context._handle.ISOINIncompleteCallback = [](PCD_HandleTypeDef *handle, uint8_t epnum)
	{
		UsbFsPcd *self = reinterpret_cast<hal_pcd_handle_context *>(handle)->_self;
		self->OnISOINIncompleteCallback(epnum);
	};
}

void bsp::UsbFsPcd::InitializeAsDevice(std::string const &clock_source_name,
									   uint32_t divider,
									   base::usb::PhyType phy_type)
{
	__HAL_RCC_USB_OTG_HS_CLK_ENABLE();
	HAL_PWREx_EnableUSBVoltageDetector();

	_hal_pcd_handle_context._handle.Instance = USB_OTG_HS;
	_hal_pcd_handle_context._handle.Init.dev_endpoints = 9;
	_hal_pcd_handle_context._handle.Init.speed = PCD_SPEED_FULL;
	_hal_pcd_handle_context._handle.Init.dma_enable = FunctionalState::DISABLE;
	_hal_pcd_handle_context._handle.Init.phy_itface = PCD_PHY_EMBEDDED;
	_hal_pcd_handle_context._handle.Init.Sof_enable = FunctionalState::DISABLE;
	_hal_pcd_handle_context._handle.Init.low_power_enable = FunctionalState::DISABLE;
	_hal_pcd_handle_context._handle.Init.lpm_enable = FunctionalState::DISABLE;

	// 在 cubemx 中使能 VBUS 后，battery_charging_enable 和 vbus_sensing_enable
	// 都会变成 ENABLE.
	//
	// 此时还会额外初始化 PA9 引脚。这个引脚配置为输入模式，用来检测 VBUS 当前是否有效。
	// 如果没有配置 PA9 引脚的话，绝对不能将 battery_charging_enable 和 vbus_sensing_enable
	// 设置为 ENABLE.
	//
	// 此外，PA9 引脚不能直接连接到 USB 接口的 VBUS 引脚，因为 PA9 配置为输入模式只能承受 3.3V 输入，
	// 这么做会烧毁引脚。要使用一个数字比较器，或者分压电阻，当 VBUS 有效时输出高电平，高电平进入 PA9 引脚，
	// STM32 的 USB 外设检测到了就认为 VBUS 有效。
	//
	// 注意，PA9 作为 VBUS 功能配置的是普通的输入模式，无上下拉。USB 外设直接读取输入寄存器的值。
	// PA9 不需要配置为 VBUS 复用功能，实际上也没有 VBUS 复用功能。VBUS 检测不是通过复用来实现的。
	_hal_pcd_handle_context._handle.Init.battery_charging_enable = FunctionalState::DISABLE;
	_hal_pcd_handle_context._handle.Init.vbus_sensing_enable = FunctionalState::DISABLE;

	_hal_pcd_handle_context._handle.Init.use_dedicated_ep1 = FunctionalState::DISABLE;

	HAL_StatusTypeDef result = HAL_PCD_Init(&_hal_pcd_handle_context._handle);
	if (result != HAL_StatusTypeDef::HAL_OK)
	{
		throw std::runtime_error{CODE_POS_STR + "初始化失败。"};
	}

	InitializeCallback();
	base::interrupt::enable_interrupt(static_cast<int32_t>(IRQn_Type::OTG_HS_IRQn), 5);

	HAL_PCDEx_SetRxFiFo(&_hal_pcd_handle_context._handle, 0x80);
	HAL_PCDEx_SetTxFiFo(&_hal_pcd_handle_context._handle, 0, 0x40);
	HAL_PCDEx_SetTxFiFo(&_hal_pcd_handle_context._handle, 1, 0x80);
}

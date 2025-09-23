#include "MainDma.h" // IWYU pragma: keep
#include "base/embedded/interrupt/interrupt.h"
#include "mdma_define.h"
#include <functional>

/* #region 中断服务函数 */

namespace
{
	std::function<void()> _dma_isr;

}

extern "C"
{
	void MDMA_IRQHandler(void)
	{
		if (_dma_isr != nullptr)
		{
			_dma_isr();
		}
	}
}

/* #endregion */

void bsp::MainDma::InitializeInterrupt()
{
	base::interrupt::disable_interrupt(static_cast<uint32_t>(IRQn_Type::MDMA_IRQn));

	_dma_isr = [this]()
	{
		HAL_MDMA_IRQHandler(&_handle_context._handle);
	};

	base::interrupt::enable_interrupt(static_cast<uint32_t>(IRQn_Type::MDMA_IRQn), 10);
}

void bsp::MainDma::Initialize()
{
	Initialize(1);
}

void bsp::MainDma::InitializeCallback()
{
	_handle_context._handle.XferCpltCallback = [](MDMA_HandleTypeDef *handle)
	{
		handle_context *context = reinterpret_cast<handle_context *>(handle);
		context->_self->OnCompleteCallback();
	};

	_handle_context._handle.XferErrorCallback = [](MDMA_HandleTypeDef *handle)
	{
		handle_context *context = reinterpret_cast<handle_context *>(handle);
		context->_self->OnErrorCallback();
	};

	_handle_context._handle.XferAbortCallback = [](MDMA_HandleTypeDef *handle)
	{
		handle_context *context = reinterpret_cast<handle_context *>(handle);
		context->_self->OnAbortCallback();
	};
}

void bsp::MainDma::Initialize(size_t align)
{
	__HAL_RCC_MDMA_CLK_ENABLE();

	_handle_context._handle.Instance = MDMA_Channel0;

	// 软件请求触发
	_handle_context._handle.Init.Request = MDMA_REQUEST_SW;

	// 块传输。
	// 这样可以每次启动传输都更改源地址、目的地址、传输大小。
	_handle_context._handle.Init.TransferTriggerMode = MDMA_BLOCK_TRANSFER;

	// 传输优先级。
	_handle_context._handle.Init.Priority = MDMA_PRIORITY_VERY_HIGH;

	// 保留为小端序。
	// 因为 ARM 本身是小端序的，所以叫作保留。
	// 保留的意思是保留原数据的字节序，不进行转换。
	_handle_context._handle.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;

	// 源地址的数据对齐。
	_handle_context._handle.Init.SourceInc = bsp::mdma::source_increase_size_to_define(align, true);

	// 目标地址的数据对齐。
	_handle_context._handle.Init.DestinationInc = bsp::mdma::destination_increase_size_to_define(align, true);

	// 源地址每个数据单元的大小。
	_handle_context._handle.Init.SourceDataSize = bsp::mdma::source_data_size_to_define(align);

	// 目标地址每个数据单元的大小。
	_handle_context._handle.Init.DestDataSize = bsp::mdma::destination_data_size_to_define(align);

	_handle_context._handle.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
	_handle_context._handle.Init.BufferTransferLength = 1;
	_handle_context._handle.Init.SourceBurst = MDMA_SOURCE_BURST_SINGLE;
	_handle_context._handle.Init.DestBurst = MDMA_DEST_BURST_SINGLE;
	_handle_context._handle.Init.SourceBlockAddressOffset = 0;
	_handle_context._handle.Init.DestBlockAddressOffset = 0;
	if (HAL_MDMA_Init(&_handle_context._handle) != HAL_OK)
	{
		throw std::runtime_error{CODE_POS_STR + "初始化 MDMA 失败。"};
	}

	InitializeInterrupt();
	InitializeCallback();
}

void bsp::MainDma::Copy(uint8_t const *begin, uint8_t const *end, uint8_t *dst)
{
}

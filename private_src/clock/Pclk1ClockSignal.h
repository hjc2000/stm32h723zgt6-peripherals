#pragma once
#include "base/string/define.h"
#include "base/unit/Hz.h"
#include "clock_source_handle.h"
#include "hal.h"
#include <stdexcept>

namespace bsp
{
	class Pclk1ClockSignal :
		public base::clock::clock_source_handle
	{
	private:
		uint32_t _input_divider = 4;
		inline static bool _configured = false;

	public:
		virtual base::unit::MHz Frequency() const override
		{
			uint32_t value = HAL_RCC_GetPCLK1Freq();
			return base::unit::MHz{base::unit::Hz{value}};
		}

		virtual void Configure(std::map<std::string, uint32_t> const &channel_factor_map) override
		{
			auto it = channel_factor_map.find("in");
			if (it == channel_factor_map.end())
			{
				throw std::invalid_argument{CODE_POS_STR + "channel_factor_map 中没有 in 通道。"};
			}

			RCC_ClkInitTypeDef def{};
			def.ClockType = RCC_CLOCKTYPE_PCLK1;

			switch (it->second)
			{
			case 1:
				{
					def.APB1CLKDivider = RCC_APB1_DIV1;
					_input_divider = 1;
					break;
				}
			case 2:
				{
					def.APB1CLKDivider = RCC_APB1_DIV2;
					_input_divider = 2;
					break;
				}
			case 4:
				{
					def.APB1CLKDivider = RCC_APB1_DIV4;
					_input_divider = 4;
					break;
				}
			case 8:
				{
					def.APB1CLKDivider = RCC_APB1_DIV8;
					_input_divider = 8;
					break;
				}
			case 16:
				{
					def.APB1CLKDivider = RCC_APB1_DIV16;
					_input_divider = 16;
					break;
				}
			default:
				{
					throw std::invalid_argument{"不支持此分频"};
				}
			}

			HAL_StatusTypeDef ret = HAL_RCC_ClockConfig(&def,
														FLASH_LATENCY_2);

			if (ret != HAL_StatusTypeDef::HAL_OK)
			{
				throw std::runtime_error{"时钟信号配置失败"};
			}

			// 配置成功，设置为已配置状态。
			_configured = true;
		}

		///
		/// @brief 获取 PCLK1 的输入分频系数。
		///
		/// @note 这个有什么用呢？为什么要获取分频系数？
		/// 因为在 APB1 总线上的定时器的输入端有个倍频器，只要 PCLK1 的输入分频器的分频系数不是 1,
		/// 这个倍频器就会把输入定时器模块的 PCLK1 倍频。
		///
		/// @return
		///
		uint32_t InputDivider() const
		{
			if (!_configured)
			{
				throw std::runtime_error{CODE_POS_STR + "没有用本类配置过 PCLK1, 无法使用本属性。"};
			}

			return _input_divider;
		}
	};

} // namespace bsp

#pragma once
#include "base/string/define.h"
#include "hal.h" // IWYU pragma: keep
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace bsp
{
	namespace mdma
	{
		constexpr uint32_t source_align_byte_count_to_define_value(size_t align_byte_count)
		{
			switch (align_byte_count)
			{
			case 1:
				{
					return MDMA_SRC_INC_BYTE;
				}
			case 2:
				{
					return MDMA_SRC_INC_HALFWORD;
				}
			case 4:
				{
					return MDMA_SRC_INC_WORD;
				}
			default:
				{
					throw std::invalid_argument{CODE_POS_STR + "非法对齐字节数。"};
				}
			}
		}

		constexpr uint32_t destination_align_byte_count_to_define_value(size_t align_byte_count)
		{
			switch (align_byte_count)
			{
			case 1:
				{
					return DMA_MDATAALIGN_BYTE;
				}
			case 2:
				{
					return DMA_MDATAALIGN_HALFWORD;
				}
			case 4:
				{
					return DMA_MDATAALIGN_WORD;
				}
			default:
				{
					throw std::invalid_argument{CODE_POS_STR + "非法对齐字节数。"};
				}
			}
		}

	} // namespace mdma
} // namespace bsp

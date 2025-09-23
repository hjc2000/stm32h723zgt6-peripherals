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
		constexpr uint32_t source_align_byte_count_to_increase_define_value(size_t align_byte_count,
																			bool increase)
		{
			if (increase)
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
				case 8:
					{
						return MDMA_SRC_INC_DOUBLEWORD;
					}
				default:
					{
						throw std::invalid_argument{CODE_POS_STR + "非法对齐字节数。"};
					}
				}
			}
			else
			{
				switch (align_byte_count)
				{
				case 1:
					{
						return MDMA_SRC_DEC_BYTE;
					}
				case 2:
					{
						return MDMA_SRC_DEC_HALFWORD;
					}
				case 4:
					{
						return MDMA_SRC_DEC_WORD;
					}
				case 8:
					{
						return MDMA_SRC_DEC_DOUBLEWORD;
					}
				default:
					{
						throw std::invalid_argument{CODE_POS_STR + "非法对齐字节数。"};
					}
				}
			}
		}

		constexpr uint32_t destination_align_byte_count_to_increase_define_value(size_t align_byte_count,
																				 bool increase)
		{
			if (increase)
			{
				switch (align_byte_count)
				{
				case 1:
					{
						return MDMA_DEST_INC_BYTE;
					}
				case 2:
					{
						return MDMA_DEST_INC_HALFWORD;
					}
				case 4:
					{
						return MDMA_DEST_INC_WORD;
					}
				case 8:
					{
						return MDMA_DEST_INC_DOUBLEWORD;
					}
				default:
					{
						throw std::invalid_argument{CODE_POS_STR + "非法对齐字节数。"};
					}
				}
			}
			else
			{
				switch (align_byte_count)
				{
				case 1:
					{
						return MDMA_DEST_DEC_BYTE;
					}
				case 2:
					{
						return MDMA_DEST_DEC_HALFWORD;
					}
				case 4:
					{
						return MDMA_DEST_DEC_WORD;
					}
				case 8:
					{
						return MDMA_DEST_DEC_DOUBLEWORD;
					}
				default:
					{
						throw std::invalid_argument{CODE_POS_STR + "非法对齐字节数。"};
					}
				}
			}
		}

	} // namespace mdma
} // namespace bsp

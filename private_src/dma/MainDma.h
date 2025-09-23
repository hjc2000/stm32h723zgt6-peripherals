#pragma once
#include "hal.h" // IWYU pragma: keep
#include "memory_dma_handle.h"

namespace bsp
{
	class MainDma :
		public base::memory_dma::memory_dma_handle
	{
	private:
		class handle_context
		{
		public:
			handle_context(MainDma *self)
			{
				_self = self;
			}

			MDMA_HandleTypeDef _handle{};
			MainDma *_self{};
		};

	public:
		virtual void Initialize() override = 0;
		virtual void Initialize(size_t align) override = 0;

		virtual void Copy(uint8_t const *begin, uint8_t const *end, uint8_t *dst) override = 0;
	};

} // namespace bsp

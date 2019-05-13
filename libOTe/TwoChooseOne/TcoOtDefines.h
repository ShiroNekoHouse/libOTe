#pragma once
#include <cryptoTools/Common/Defines.h>

//#define KOS_RO_HASH
//#define IKNP_SHA_HASH

namespace osuCrypto
{ 
    static const u64 commStepSize(512);
    static const u64 superBlkSize(8);

	enum class BgciksBaseType {None, Base, BaseExtend, Extend};

	template<typename S, typename TSpan,
		typename enabled = typename std::enable_if<
		std::is_convertible<
		TSpan,
		span<typename TSpan::value_type>
	>::value>::type>
		span<S> spanCast(TSpan& src)
	{
		using T = typename TSpan::value_type;
		static_assert(
			std::is_pod<T>::value &&
			std::is_pod<S>::value &&
			((sizeof(T) % sizeof(S) == 0) ||
			(sizeof(S) % sizeof(T) == 0)), " types must be POD and a multiple of each other.");

		assert(u64(src.data()) % sizeof(S) == 0);

		auto r = span<S>((S*)src.data(), src.size() * sizeof(T) / sizeof(S));

		assert((void*)r.data() == (void*)src.data());

		return r;

	}
}

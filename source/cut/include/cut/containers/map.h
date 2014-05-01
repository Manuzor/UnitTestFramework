#pragma once
#include "cut/types.h"

namespace cut
{
	namespace containers
	{
		template<typename K, typename V> struct Map
		{
			typename typedef CUT_TYPE_MAP<K, V> type;
			typename typedef CUT_TYPE_MAP<K, V>::iterator iterator;
			typename typedef CUT_TYPE_MAP<K, V>::const_iterator const_iterator;
		};
	}
}

#pragma once
#include "cppunit/Types.h"

namespace cppunit
{
  namespace containers
  {
    template<typename K, typename V> struct Map
    {
      typename typedef CPPUNIT_TYPE_MAP<K, V> type;
      typename typedef CPPUNIT_TYPE_MAP<K, V>::iterator iterator;
      typename typedef CPPUNIT_TYPE_MAP<K, V>::const_iterator const_iterator;
    };
  }
}
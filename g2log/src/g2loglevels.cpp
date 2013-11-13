/** ==========================================================================
* 2012 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
* with no warranties. This code is yours to share, use and modify with no
* strings attached and no restrictions or obligations.
* ============================================================================
* Filename:g2loglevels.cpp  Part of Framework for Logging and Design By Contract
* Created: 2012 by Kjell Hedström
*
* PUBLIC DOMAIN and Not copywrited. First published at KjellKod.cc
* ********************************************* */

#include "g2loglevels.hpp"
#include <atomic>


namespace g2
{
  namespace internal {
     bool wasFatal(const LEVELS& level) { 
        return level.value > WARNING.value; 
     }

    std::atomic<bool> g_log_level_status[4]; // DEBUG, INFO, WARNING, FATAL
  } // internal


#ifdef G2_DYNAMIC_LOGGING
  void setLogLevel(LEVELS log_level, bool enabled)
  {
    int level = log_level.value;
    CHECK((level >= DEBUG.value) && (level <= FATAL.value));
    (internal::g_log_level_status[level]).store(enabled, std::memory_order_release);
  }
#endif


  bool logLevel(LEVELS log_level)
  {
#ifdef G2_DYNAMIC_LOGGING
    int level = log_level.value;
    CHECK((level >= DEBUG.value) && (level <= FATAL.value));
    bool status = (internal::g_log_level_status[level]).load(std::memory_order_acquire);
    return status;
#endif
    return true;
  }


} // g2
/* ============================================================
 * Control compile time options.
 * ============================================================
 *
 * Compile time options have moved to config.mk.
 */


/* ============================================================
 * Compatibility defines
 *
 * Generally for Windows native support.
 * ============================================================ */
#if defined(_MSC_VER) && _MSC_VER < 1900
#  define snprintf sprintf_s
#  define EPROTO ECONNABORTED
#endif

#ifdef WIN32
#  ifndef strcasecmp
#    define strcasecmp strcmpi
#  endif
#define HAVE_STRUCT_TIMESPEC
#define strtok_r strtok_s
#define strerror_r(e, b, l) strerror_s(b, l, e)
#endif


#define uthash_malloc(sz) _mosquitto_malloc(sz)
#define uthash_free(ptr,sz) _mosquitto_free(ptr)

// using for compile

//typedef char int8_t ;


//#define AI_ADDRCONFIG 1
#ifdef WIN32
#   ifndef int8_t
#       include <stdint.h>
#   endif
#   ifndef AI_ADDRCONFIG
#       define AI_ADDRCONFIG 0x00000400
#   endif
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// \\\ file        Config.h
// \\\ author      Kaye Mason
// \\\ copyright   2011
// \\\ brief       Plasmogrify Config 
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PLASMOGRIFY_CONFIG

#include <tchar.h>

typedef  __int8           int8_t;
typedef  __int16          int16_t;
typedef  __int32          int32_t;
typedef  __int64          int64_t;

typedef  unsigned __int8  uint8_t;
typedef  unsigned __int16 uint16_t; 
typedef  unsigned __int32 uint32_t;
typedef  unsigned __int64 uint64_t;

typedef  float            float_t;
typedef  double           double_t;

#define HR HRTRACE

#define HRTRACE(hr, error)                                                                  \
        {                                                                                   \
            if (FAILED(hr))                                                                 \
            {                                                                               \
                DXTraceW(__FILE__, (DWORD)__LINE__, hr, error, true);                       \
            }                                                                               \
        }


#define HROUTPUT(hr, error)                                                                 \
        {                                                                                   \
            if( FAILED(hr) )                                                                \
            {                                                                               \
                OutputDebugStringA(error);                                                  \
            }                                                                               \
        }

#define HRMB(hr, error)                                                                     \
        {                                                                                   \
            if( FAILED(hr) )                                                                \
            {                                                                               \
                MessageBox(NULL,  error, "Plasmogrify Error", MB_OK);                       \
            }                                                                               \
        }

#ifndef NULL 
    #define NULL 0
#endif

#endif // PLASMOGRIFY_CONFIG
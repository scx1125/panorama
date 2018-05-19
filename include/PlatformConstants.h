#ifndef PANROAMA_PLATFORMCONSTANTS_H
#define PANROAMA_PLATFORMCONSTANTS_H

// Includes
#if defined(__linux__) || defined(LINUX)
#   include <sys/types.h>
#   include <limits.h>
#elif defined(WIN32)
#   include <Windows.h>
#endif // <-- Includes

#if defined(__linux__) || defined(LINUX)

// Path separator
#define PANORAMA_PATH_SEP '/'

// Maximum path length
#define PANORAMA_PATH_MAX PATH_MAX

// Process handle type
#define PANORAMA_PROCHANDLE_TYPE pid_t
#define PANORAMA_PROCESSID_TYPE pid_t

// Invalid process handle
#define PANORAMA_INVALID_PROC_HANDLE -1
#define PANORAMA_INVALID_PROC_ID -1

#elif defined(WIN32)

// Path separator
#define PANORAMA_PATH_SEP '\\'

// Maximum path length
#define PANORAMA_PATH_MAX MAX_PATH

// Process handle and PID type
#define PANORAMA_PROCHANDLE_TYPE HANDLE
#define PANORAMA_PROCESSID_TYPE DWORD

// Invalid process handle and PID
#define PANORAMA_INVALID_PROC_HANDLE INVALID_HANDLE_VALUE
#define PANORAMA_INVALID_PROC_ID (static_cast<DWORD>(-1))

#endif

#endif // PANROAMA_PLATFORMCONSTANTS_H

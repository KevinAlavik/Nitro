#ifndef SYSTEM_STATES_H
#define SYSTEM_STATES_H

#include <stdbool.h>

#define KEYBOARD_SUPPORT false
#define KEYBOARD_PRINTF_SUPPORT false
#define LOG_TASKS_SUPPORT false

#ifndef ENABLE_KEYBOARD
#define KEYBOARD_SUPPORT true
#endif

#ifndef ENABLE_KEYBOARD_PRINTF
#define KEYBOARD_PRINTF_SUPPORT true
#endif

#ifndef DISABLE_KEYBOARD_PRINTF
#define KEYBOARD_PRINTF_SUPPORT false
#endif

#ifndef ENABLE_LOG_STARTUP_TASKS
#define LOG_TASKS_SUPPORT true
#endif

#endif // SYSTEM_STATES_H

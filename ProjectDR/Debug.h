#if _DEBUG

enum MEMPRINT_OPTIONS {
	OFF,
	PRINT_TO_OUTPUT,
	BREAK
};

#define MEMWATCH 0
#define MEMPRINT OFF

#if MEMWATCH
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>

#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#define _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

// PRINT OPTIONS
#if MEMPRINT == PRINT_TO_OUTPUT
#define _WATCH_MEMORY _CrtDumpMemoryLeaks();
#else if MEMPRINT == BREAK
#define _WATCH_MEMORY _CrtDbgBreak();
#else
#define _WATCH_MEMORY
#endif  // END PRINT OPTIONS

#else
#define _WATCH_MEMORY
#endif // If MEMWATCH

#endif // If _DEBUG
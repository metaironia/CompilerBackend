#include <stdio.h>

#include "backend.h"
#include "backend_input.h"


BackendFuncStatus BackendCmdArgsCheck (const int argcc) {

    if (argcc < 3) {

        fprintf (stderr, "Not enough args. Program will be terminated.\n");
        return BACKEND_FUNC_STATUS_FAIL;
    }

    else if (argcc > 3) {

        fprintf (stderr, "Too much args. Program will be terminated.\n");
        return BACKEND_FUNC_STATUS_FAIL;
    }

    return BACKEND_FUNC_STATUS_OK;
}

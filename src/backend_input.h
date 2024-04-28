#ifndef BACKEND_INPUT_H
#define BACKEND_INPUT_H

enum BackendFuncStatus {

    BACKEND_FUNC_STATUS_OK,
    BACKEND_FUNC_STATUS_FAIL
};

BackendFuncStatus BackendCmdArgsCheck (const int argcc);

#endif

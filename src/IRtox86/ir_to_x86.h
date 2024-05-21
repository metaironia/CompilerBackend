#ifndef IR_TO_X86_H
#define IR_TO_X86_H

#include <stdio.h>

#include "../ASTtoIR/ast_to_ir.h"

const int MAX_PE_FILE_LENGTH = 64;

//---------------------------- DOS header consts ------------------------------

const int DEFAULT_OFFSET_TO_PE_HEADER = 0x40;

//---------------------------- PE file header consts --------------------------

const int DEFAULT_NUMBER_OF_SECTIONS      = 3;       // .text, .data and .idata
const int DEFAULT_SIZE_OF_OPTIONAL_HEADER = sizeof (IMAGE_OPTIONAL_HEADER64);

//---------------------------- PE optional header consts ----------------------

const int DEFAULT_IMAGE_BASE              = 0x00400000;
const int DEFAULT_FILE_ALIGNMENT          = 0x200;
const int WINDOWS_NT_VERSION              = 4;       // Windows NT 4.0
const int DEFAULT_NUMBER_OF_RVA_AND_SIZES = 0x10;

//-----------------------------------------------------------------------------

const char *PeFileNameGen (const char *output_file_name);

IntReprFuncStatus IntReprToPeFile (const IntRepr *interm_repr, const char *output_file_name);

//---------------------------- DOS header filling -----------------------------

IntReprFuncStatus IntReprDosHeaderFill (IMAGE_DOS_HEADER *dos_header);

//---------------------------- PE header filling ----------------------------

IntReprFuncStatus IntReprPeHeaderFill (IMAGE_NT_HEADERS64 *pe_header);

IntReprFuncStatus IntReprPeHeaderFileHeaderFill (IMAGE_FILE_HEADER *file_header);

IntReprFuncStatus IntReprPeHeaderOptionalHeaderFill (IMAGE_OPTIONAL_HEADER64 *optional_header);

//---------------------------- Section table filling --------------------------


#endif
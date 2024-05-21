#include <assert.h>
#include <windows.h>

#include "ir_to_x86.h"

const char *PeFileNameGen (const char *output_file_name) {

    assert (output_file_name);

    static char output_pe_file_name[MAX_PE_FILE_LENGTH] = {};

    snprintf (output_pe_file_name, MAX_PE_FILE_LENGTH, "%s.exe", output_file_name);

    return output_pe_file_name;
}

IntReprFuncStatus IntReprToPeFile (const IntRepr *interm_repr, const char *output_file_name) {

    assert (interm_repr);
    assert (output_file_name);

    FILE *pe_file = fopen (PeFileNameGen (output_file_name), "wb");

    IMAGE_DOS_HEADER   dos_header = {};
    IMAGE_NT_HEADERS64 pe_header  = {}; 

    IntReprDosHeaderFill (&dos_header);
    IntReprPeHeaderFill  (&pe_header);

    //IntReprPeSectionsFill ();

    fclose (pe_file);
    pe_file = NULL;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprDosHeaderFill (IMAGE_DOS_HEADER *dos_header) {

    assert (dos_header);

    dos_header -> e_magic  = IMAGE_DOS_SIGNATURE;
    dos_header -> e_lfanew = DEFAULT_OFFSET_TO_PE_HEADER;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprPeHeaderFill (IMAGE_NT_HEADERS64 *pe_header) {

    assert (pe_header);

    pe_header -> Signature = IMAGE_NT_SIGNATURE;

    IntReprPeHeaderFileHeaderFill     (&(pe_header -> FileHeader));
    IntReprPeHeaderOptionalHeaderFill (&(pe_header -> OptionalHeader));

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprPeHeaderFileHeaderFill (IMAGE_FILE_HEADER *file_header) {

    assert (file_header);

    file_header -> Machine              = IMAGE_FILE_MACHINE_AMD64;
    file_header -> NumberOfSections     = DEFAULT_NUMBER_OF_SECTIONS;
    file_header -> SizeOfOptionalHeader = DEFAULT_SIZE_OF_OPTIONAL_HEADER; 
    file_header -> Characteristics      = IMAGE_FILE_32BIT_MACHINE | IMAGE_FILE_EXECUTABLE_IMAGE;

    return IR_FUNC_STATUS_OK;
}

IntReprFuncStatus IntReprPeHeaderOptionalHeaderFill (IMAGE_OPTIONAL_HEADER64 *optional_header) {

    assert (optional_header);

    optional_header -> Magic                 = IMAGE_NT_OPTIONAL_HDR64_MAGIC;
    optional_header -> ImageBase             = DEFAULT_IMAGE_BASE;
    optional_header -> FileAlignment         = DEFAULT_FILE_ALIGNMENT;
    optional_header -> MajorSubsystemVersion = WINDOWS_NT_VERSION;
    optional_header -> Subsystem             = IMAGE_SUBSYSTEM_WINDOWS_CUI;
    optional_header -> NumberOfRvaAndSizes   = DEFAULT_NUMBER_OF_RVA_AND_SIZES;

    return IR_FUNC_STATUS_OK;
}


//TODO patch (optional_header -> DataDirectory)[IMAGE_DIRECTORY_ENTRY_IMPORT] = 
//TODO patch size of optional header
//TODO patch AddressOfEntryPoint
//TODO patch SectionAlignment
//TODO patch SizeOfImage
//TODO patch SizeOfHeaders
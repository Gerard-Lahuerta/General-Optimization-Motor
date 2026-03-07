import csv

ERROR_CSV = 'error_codes.csv'
ERROR_HEADER = 'include/common/error.h'
MACRO_LINE = "    V({code:<20}, {value:>4}, \"{message}\")"

def generate_error_header(csv_file, output_h):
    with open(csv_file, mode='r', encoding='utf-8') as f:
        reader = csv.DictReader(f)
        errors = list(reader)

    with open(output_h, 'w', encoding='utf-8') as f:
        # 1. Informative Header
        f.write(
            "/*\n** FILE GENERATED AUTOMATICALLY - DO NOT MODIFY MANUALLY\n"
        )
        f.write("** Edit errores.csv and execute make_errors.py\n")
        f.write("** Check the documnetation for more information\n*/\n\n")

        # 2. Definition of ERROR_LIST with X-Macros
        f.write("#ifndef ERROR_H\n#define ERROR_H\n\n")
        f.write("#define ERROR_LIST(V) \\\n")

        current_section = ""
        for i, err in enumerate(errors):
            # Add Section division to easy visualization
            if err['SECTION'] != current_section:
                current_section = err['SECTION']
                f.write(f"    /* -- {current_section} -- */ \\\n")

            line = MACRO_LINE.format(
                code=err['CODE'], value=err['VALUE'], message=err['MESSAGE']
            )

            # Add end of the line (unless its last line)
            if i < len(errors) - 1:
                f.write(f"{line:<75} \\\n")
            else:
                f.write(f"{line:<75}\n")

        f.write("\n")

        # 3. Macros definition: CHECK_ERROR, CHECK_WARN & CHECK_CONDITION(s)
        f.write("#define CHECK_CONDITION(condicion, codigo, tipo_log) \\\n")
        f.write(
            '    ((condicion) ? 1 : (tipo_log(get_error_msg(codigo)), 0))\n\n'
        )

        f.write("#define CHECK_E(condition, code) \\\n")
        f.write("    CHECK_CONDITION(condition, code, LOG_ERROR)\n\n")

        f.write("#define CHECK_W(condition, code) \\\n")
        f.write("    CHECK_CONDITION(condition, code, LOG_WARN)\n\n")

        f.write("#define ASSERT_ERROR(condicion, codigo) \\\n")
        f.write("    do { \\\n")
        f.write("        if (condicion) { \\\n")
        f.write("            LOG_ERROR(get_error_msg(codigo)); \\\n")
        f.write("            return codigo; \\\n")
        f.write("        } \\\n")
        f.write("    } while(0)\n\n")

        f.write("#define ASSERT_WARN(condicion, codigo) \\\n")
        f.write("    do { \\\n")
        f.write("        if (condicion) { \\\n")
        f.write("            LOG_WARN(get_error_msg(codigo)); \\\n")
        f.write("        } \\\n")
        f.write("    } while(0)\n\n")

        # 4. Enumeration of the errors and UI function
        f.write("typedef enum {\n")
        f.write("    #define AS_ENUM(ID, VAL, MSG) ID = VAL,\n")
        f.write("    ERROR_LIST(AS_ENUM)\n")
        f.write("    #undef AS_ENUM\n")
        f.write("} VecError;\n\n")

        f.write("inline const char* get_error_msg(VecError code) {\n")
        f.write("    #define AS_CASE(ID, VAL, MSG) case ID: return MSG;\n")
        f.write("    switch(code) {\n")
        f.write("        ERROR_LIST(AS_CASE)\n")
        f.write("        default: return \"Unexpected error occurred.\";\n")
        f.write("    }\n")
        f.write("    #undef AS_CASE\n")
        f.write("}\n\n")

        f.write("#endif // ERROR_H\n")

if __name__ == "__main__":
    generate_error_header(ERROR_CSV, ERROR_HEADER)
    print("File error.h generated.")
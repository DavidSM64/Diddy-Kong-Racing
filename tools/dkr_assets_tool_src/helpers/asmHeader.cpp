#include "asmHeader.h"

#include "helpers/fileHelper.h"

WritableAsmInclude::WritableAsmInclude() {
}

WritableAsmInclude::~WritableAsmInclude() {
    
}

void WritableAsmInclude::write_comment(const char *text) {
    _out << "# " << text << std::endl;
}

void WritableAsmInclude::write_header_comment(const char *text) {
    _out << "/********** " << text << " **********/" << std::endl << std::endl;
}

void WritableAsmInclude::write_newline() {
    _out << std::endl;
}

void WritableAsmInclude::write_word(const std::string &value) {
    _out << ".word " << value << std::endl;
}

void WritableAsmInclude::write_two_words(const std::string &value, const std::string &value2) {
    _out << ".word " << value << ", " << value2 << std::endl;
}

void WritableAsmInclude::write_word_with_comment(const std::string &value, const char *comment) {
    _out << ".word " << value << " # " << comment << std::endl;
}

void WritableAsmInclude::write_include(std::string filepath) {
    _out << ".include \"" << filepath << "\"" << std::endl;
}

void WritableAsmInclude::write_binary_include(std::string filepath) {
    _out << ".incbin \"" << filepath << "\"" << std::endl;
}

void WritableAsmInclude::write_global_label(const std::string &label, bool align16) {
    if(align16) {
        _out << ".balign 16" << std::endl;
    }
    _out << "glabel " << label << std::endl;
}

void WritableAsmInclude::save(fs::path filepath) {
    std::string headerText = _out.str();
    FileHelper::write_text_file_if_changed(headerText, filepath, true);
}

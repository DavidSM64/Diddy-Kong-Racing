#include "ld.h"

#include "helpers/fileHelper.h"

const size_t INDENT_AMOUNT = 4; // Indent by 4 spaces

WritableLD::WritableLD(DkrAssetsSettings &settings) : _settings(settings) {
}

WritableLD::~WritableLD() {
}

void WritableLD::write_comment(const char *text) {
    _out << _indent << "/* " << text << " */" << std::endl;
}

void WritableLD::write_include(const char *text) {
    _out << _indent << "#include \"" << text << "\"" << std::endl;
}

void WritableLD::write_arch(const char *archName) {
    _out << _indent << "OUTPUT_ARCH (" << archName << ")" << std::endl;
}

void WritableLD::write_rom_pos_at(const char *value) {
    _out << _indent << "romPos = " << value << ";" << std::endl;
}

void WritableLD::write_add_to_rom_pos(const char *value) {
    _out << _indent << "romPos += " << value << ";" << std::endl;
}

void WritableLD::write_assignment(const char *var, const char *value) {
    _out << _indent << var << " = " << value << ";" << std::endl;
}

void WritableLD::write_section_header(const char *name, const char *ramPos, const char *romPos, const LD_SUBALIGN subalign) {
    _out << _indent << "." << name << " " << ramPos << " : AT(" << romPos << ")";
    if(subalign != LD_SUBALIGN::NONE) {
        _out << " SUBALIGN(" << subalign << ")";
    }
    _out << std::endl;
}

void WritableLD::write_raw(const char *text) {
    _out << _indent << text;
}

void WritableLD::write_raw_line(const char *text) {
    _out << _indent << text << std::endl;
}

void WritableLD::write_raw_line(const std::string text) {
    write_raw_line(text.c_str());
}

void WritableLD::write_open_brace() {
    _out << _indent << "{" << std::endl;
    _indent.append(INDENT_AMOUNT, ' '); // Add 4 spaces to the indent
}

void WritableLD::write_close_brace() {
    if (_indent.size() > INDENT_AMOUNT) {
        _indent.resize(_indent.size() - INDENT_AMOUNT); // Remove 4 spaces from the indent
    } else {
        _indent.clear();
    }
    _out << _indent << "}" << std::endl;
}
    
void WritableLD::write_newline() {
    _out << std::endl;
}

void WritableLD::save(const std::string &filepath) {
    std::string ldText = _out.str();
    FileHelper::write_text_file_if_changed(ldText, filepath, true);
}


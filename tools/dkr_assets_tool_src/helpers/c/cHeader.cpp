#include "cHeader.h"

using namespace DkrAssetsTool;

#include "helpers/fileHelper.h"

WritableCHeader::WritableCHeader() {
}

WritableCHeader::~WritableCHeader() {
}

void WritableCHeader::write_comment(const char *text) {
    _out << "// " << text << std::endl;
}

void WritableCHeader::write_header_comment(const char *text) {
    _out << "/********** " << text << " **********/" << std::endl << std::endl;
}

void WritableCHeader::write_newline() {
    _out << std::endl;
}

void WritableCHeader::write_raw_text(std::string text) {
    _out << text;
}

void WritableCHeader::write_raw_text_line(std::string text) {
    _out << text << std::endl;
}

void WritableCHeader::save(fs::path filepath) {
    std::string headerText = _out.str();
    FileHelper::write_text_file_if_changed(headerText, filepath, true);
}

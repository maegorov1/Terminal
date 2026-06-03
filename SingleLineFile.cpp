#include "SingleLineFile.h"

SingleLineFile::SingleLineFile(std::string name, std::string text)
    : Entry(std::move(name), false) {
    edit(text);
}

std::string SingleLineFile::displayName() const {
    return "[Single] " + name;
}

std::string SingleLineFile::read() const {
    return content;
}

void SingleLineFile::edit(const std::string& text) {
    size_t pos = text.find('\n');
    content = text.substr(0, pos);
}
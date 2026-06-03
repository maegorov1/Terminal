#include "MultiLineFile.h"

MultiLineFile::MultiLineFile(std::string name, std::string text)
    : Entry(std::move(name), false), content(std::move(text)) {
}

std::string MultiLineFile::displayName() const {
    return "[Multi]  " + name;
}

std::string MultiLineFile::read() const {
    return content;
}

void MultiLineFile::edit(const std::string& text) {
    content = text;
}
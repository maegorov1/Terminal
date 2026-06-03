#pragma once

#include "Entry.h"

class SingleLineFile : public Entry {
private:
    std::string content;

public:
    SingleLineFile(std::string name, std::string text = "");

    std::string displayName() const override;
    std::string read() const override;
    void edit(const std::string& text) override;
};
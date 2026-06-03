#pragma once

#include "Entry.h"

class Directory : public Entry {
private:
    std::vector<std::shared_ptr<Entry>> children;

public:
    Directory(std::string name);

    std::string displayName() const override;
    void listAll() const override;
    Directory* asDirectory() override;
    void addChild(std::shared_ptr<Entry> child) override;
    std::shared_ptr<Entry> findChild(const std::string& child_name, bool include_hidden = false) override;
    void removeChild(const std::string& child_name) override;
};
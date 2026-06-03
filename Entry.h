#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Directory;

class Entry {
protected:
    std::string name;
    bool is_dir;
    bool is_hidden;
    std::weak_ptr<Entry> parent;

public:
    Entry(std::string name, bool is_dir);
    virtual ~Entry() = default;

    std::string getName() const;
    void setName(const std::string& new_name);

    bool isDirectory() const;
    bool isHidden() const;

    void hide();
    void restore();

    std::shared_ptr<Entry> getParent() const;
    void setParent(std::shared_ptr<Entry> new_parent);

    virtual std::string displayName() const;
    virtual std::string read() const;
    virtual void edit(const std::string& text);

    virtual Directory* asDirectory();
    virtual void listAll() const;
    virtual void addChild(std::shared_ptr<Entry> child);
    virtual std::shared_ptr<Entry> findChild(const std::string& child_name, bool include_hidden = false);
    virtual void removeChild(const std::string& child_name);
};
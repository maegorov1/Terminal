#include "Entry.h"
#include "Directory.h"

Entry::Entry(std::string name, bool is_dir)
    : name(std::move(name)), is_dir(is_dir), is_hidden(false) {
}

std::string Entry::getName() const { return name; }
void Entry::setName(const std::string& new_name) { name = new_name; }

bool Entry::isDirectory() const { return is_dir; }
bool Entry::isHidden() const { return is_hidden; }

void Entry::hide() { is_hidden = true; }
void Entry::restore() { is_hidden = false; }

std::shared_ptr<Entry> Entry::getParent() const { return parent.lock(); }
void Entry::setParent(std::shared_ptr<Entry> new_parent) { parent = new_parent; }

std::string Entry::displayName() const { return name; }
std::string Entry::read() const { return ""; }
void Entry::edit(const std::string&) {}

Directory* Entry::asDirectory() { return nullptr; }
void Entry::listAll() const {}
void Entry::addChild(std::shared_ptr<Entry>) {}
std::shared_ptr<Entry> Entry::findChild(const std::string&, bool) { return nullptr; }
void Entry::removeChild(const std::string&) {}
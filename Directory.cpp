#include "Directory.h"

Directory::Directory(std::string name) : Entry(std::move(name), true) {}

std::string Directory::displayName() const {
    return name + "/";
}

void Directory::listAll() const {
    for (const auto& child : children) {
        if (!child->isHidden()) {
            std::cout << child->displayName() << "\n";
        }
    }
}

Directory* Directory::asDirectory() {
    return this;
}

void Directory::addChild(std::shared_ptr<Entry> child) {
    children.push_back(std::move(child));
}

std::shared_ptr<Entry> Directory::findChild(const std::string& child_name, bool include_hidden) {
    for (auto& child : children) {
        if (child->getName() == child_name && (!child->isHidden() || include_hidden)) {
            return child;
        }
    }
    return nullptr;
}

void Directory::removeChild(const std::string& child_name) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->getName() == child_name) {
            children.erase(it);
            return;
        }
    }
}
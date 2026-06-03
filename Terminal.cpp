#include "Terminal.h"
#include <sstream>

Terminal::Terminal() {
    root = std::make_shared<Directory>("root");
    current = root;
    running = true;
}

void Terminal::start() {
    std::cout << "Type 'help' to see the list of available commands.\n\n";

    std::string line;
    while (running) {
        std::cout << current->getName() << " $ ";
        if (!std::getline(std::cin, line)) break;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd.empty()) continue;

        std::vector<std::string> args;
        std::string arg;
        while (ss >> arg) args.push_back(arg);

        execute(cmd, args, line);
    }
}

void Terminal::execute(const std::string& cmd, const std::vector<std::string>& args, const std::string& original_line) {
    if (cmd == "help") {
        std::cout << "Available commands:\n";
        std::cout << "  help         Show this help manual\n";
        std::cout << "  exit         Terminate terminal session\n";
        std::cout << "  ls           List files and directories\n";
        std::cout << "  cd name      Change directory (use 'cd ..' to go back)\n";
        std::cout << "  cat name     Display file content\n";
        std::cout << "  touch name   Create a new empty file\n";
        std::cout << "  mkdir name   Create a new directory\n";
        std::cout << "  rm name      Hide a file or directory\n";
        std::cout << "  restore name Restore a hidden object\n";
        std::cout << "  mv name new  Rename an object\n";
        std::cout << "  edit name    Modify file text\n";
    }
    else if (cmd == "exit") {
        running = false;
        std::cout << "Terminal session successfully terminated.\n";
    }
    else if (cmd == "ls") {
        current->listAll();
    }
    else if (cmd == "cd") {
        if (args.empty()) {
            std::cout << "Error: target directory not specified.\n";
            return;
        }
        if (args[0] == "..") {
            if (current == root || !current->getParent()) {
                std::cout << "Warning: cannot move above the root of the virtual FS.\n";
            }
            else {
                current = current->getParent();
            }
            return;
        }
        auto target = current->findChild(args[0]);
        if (target && target->isDirectory()) current = target;
        else std::cout << "Error: directory '" << args[0] << "' not found.\n";
    }
    else if (cmd == "touch") {
        if (args.empty()) {
            std::cout << "Error: file name not specified.\n";
            return;
        }
        if (current->findChild(args[0], true)) {
            std::cout << "Error: an entity named '" << args[0] << "' already exists.\n";
            return;
        }
        auto new_file = std::make_shared<SingleLineFile>(args[0], "");
        new_file->setParent(current);
        current->addChild(new_file);
        std::cout << "File '" << args[0] << "' successfully initialized.\n";
    }
    else if (cmd == "mkdir") {
        if (args.empty()) {
            std::cout << "Error: directory name not specified.\n";
            return;
        }
        if (current->findChild(args[0], true)) {
            std::cout << "Error: an entity named '" << args[0] << "' already exists.\n";
            return;
        }
        auto new_dir = std::make_shared<Directory>(args[0]);
        new_dir->setParent(current);
        current->addChild(new_dir);
        std::cout << "Directory '" << args[0] << "' successfully created.\n";
    }
    else if (cmd == "cat") {
        if (args.empty()) {
            std::cout << "Error: file name not specified.\n";
            return;
        }
        auto file = current->findChild(args[0]);
        if (file && !file->isDirectory()) std::cout << file->read() << "\n";
        else std::cout << "Error: file '" << args[0] << "' not found.\n";
    }
    else if (cmd == "edit") {
        if (args.size() < 2) {
            std::cout << "Error: command syntax: edit <filename> <text>\n";
            return;
        }

        std::string filename = args[0];
        size_t pos = original_line.find(filename);
        std::string text = original_line.substr(pos + filename.length() + 1);

        auto file = current->findChild(filename);
        if (!file || file->isDirectory()) {
            std::cout << "Error: file '" << filename << "' not found.\n";
            return;
        }

        while (true) {
            size_t n_pos = text.find("\\n");
            if (n_pos == std::string::npos) break;
            text.replace(n_pos, 2, "\n");
        }

        if (std::dynamic_pointer_cast<SingleLineFile>(file) && text.find('\n') != std::string::npos) {
            auto multi_file = std::make_shared<MultiLineFile>(filename, text);
            multi_file->setParent(current);
            if (auto dir = current->asDirectory()) {
                dir->removeChild(filename);
                dir->addChild(multi_file);
            }
            std::cout << "File type for '" << filename << "' automatically resolved as MultiLineFile.\n";
        }
        else {
            file->edit(text);
            std::cout << "Data of file '" << filename << "' overwritten.\n";
        }
    }
    else if (cmd == "mv") {
        if (args.size() < 2) {
            std::cout << "Error: command syntax: mv <current_name> <new_name>\n";
            return;
        }
        auto target = current->findChild(args[0], true);
        if (!target) {
            std::cout << "Error: object '" << args[0] << "' not found.\n";
            return;
        }
        if (current->findChild(args[1], true)) {
            std::cout << "Error: name '" << args[1] << "' is already taken by another entity.\n";
            return;
        }
        target->setName(args[1]);
        std::cout << "Entity successfully renamed to '" << args[1] << "'.\n";
    }
    else if (cmd == "rm") {
        if (args.empty()) {
            std::cout << "Error: target object for removal not specified.\n";
            return;
        }
        auto target = current->findChild(args[0]);
        if (target) {
            target->hide();
            std::cout << "Object '" << args[0] << "' successfully hidden (moved to trash).\n";
        }
        else {
            std::cout << "Error: object '" << args[0] << "' not found.\n";
        }
    }
    else if (cmd == "restore") {
        if (args.empty()) {
            std::cout << "Error: target object for restoration not specified.\n";
            return;
        }
        auto target = current->findChild(args[0], true);
        if (target && target->isHidden()) {
            target->restore();
            std::cout << "Object '" << args[0] << "' successfully restored from trash.\n";
        }
        else {
            std::cout << "Error: hidden object named '" << args[0] << "' not found.\n";
        }
    }
    else {
        std::cout << "Command not recognized. Type 'help' to display the list of instructions.\n";
    }
}
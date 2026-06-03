#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Directory.h"
#include "SingleLineFile.h"
#include "MultiLineFile.h"

class Terminal {
private:
    std::shared_ptr<Entry> root;
    std::shared_ptr<Entry> current;
    bool running;

public:
    Terminal();
    void start();

private:
    void execute(const std::string& cmd, const std::vector<std::string>& args, const std::string& original_line);
};
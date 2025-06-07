// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <vector>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    root = std::make_shared<Node>('\0');

    std::function<void(std::shared_ptr<Node>, std::vector<char>)> build;
    build = [&](std::shared_ptr<Node> node, std::vector<char> remaining) {
        if (remaining.empty()) return;
        std::sort(remaining.begin(), remaining.end());
        for (size_t i = 0; i < remaining.size(); ++i) {
            char c = remaining[i];
            auto child = std::make_shared<Node>(c);
            node->children.push_back(child);

            std::vector<char> next_remaining = remaining;
            next_remaining.erase(next_remaining.begin() + i);
            build(child, next_remaining);
        }
        };

    build(root, elements);
}

void collectPerms(std::shared_ptr<Node> node, 
std::vector<char>& path, 
std::vector<std::vector<char>>& result) {
    if (node->val != '\0') path.push_back(node->val);

    if (node->children.empty()) {
        result.push_back(path);
    } else {
        for (auto& child : node->children) {
            collectPerms(child, path, result);
        }
    }

    if (!path.empty()) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collectPerms(tree.root, path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto perms = getAllPerms(tree);
    if (num <= 0 || num > static_cast<int>(perms.size())) return {};
    return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    int count = num;

    auto node = tree.root;
    while (!node->children.empty()) {
        int block_size = 1;
        for (int i = 2; i <= node->children.size() - 1; ++i) block_size *= i;

        int index = (count - 1) / block_size;
        if (index >= node->children.size()) return {};
        node = node->children[index];
        result.push_back(node->val);
        count = (count - 1) % block_size + 1;
    }

    if (count != 1) return {};
    return result;
}


#pragma once

#include <memory>
#include <list>

#include "ast/Node.h"
#include "ir/CFG.h"

class IR{
    public:
        IR(std::shared_ptr<Node> rootNode);

    private:
        std::list<shared_ptr<CFG>> functions;
};

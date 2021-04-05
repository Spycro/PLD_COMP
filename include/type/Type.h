#pragma once

class Type {
    public :

    virtual int getSize() = 0;

    virtual std::string toString() override;

};
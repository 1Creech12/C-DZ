#include "cat.h"

class WildCat : public Cat {
private:
    string habitat;

public:
    WildCat(const string& name, int age, const string& color, const string& habitat);
    
    ~WildCat();
    
    void printInfo() const;
    void sound() const;
    
    void hunt() const;
};
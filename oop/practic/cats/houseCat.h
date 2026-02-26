#include "cat.h"

class HouseCat : public Cat {
private:
    string ownerName;

public:
    HouseCat(const string& name, int age, const string& color, const string& owner);
    ~HouseCat();
    
    void printInfo() const;
    void sound() const;
    
    void play() const;
};
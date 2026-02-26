#include "cat.h"

class PersianCat : public Cat {
private:
    int woolLength;

public:
    PersianCat(const string& name, int age, const string& color, int woolLength);
    
    ~PersianCat();
    
    void printInfo() const;
    void sound() const;
    
    void groom() const;
};
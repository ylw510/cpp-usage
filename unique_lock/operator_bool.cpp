#include <mutex>
#include <iostream>

/*
    just to test oprator bool()
*/
class MyClass
{
public:
    enum class Sex
    {
        BOY,
        GRIL
    };
    MyClass(int age, Sex sex) : age_(age), sex_(sex)
    {

    }

    operator bool() const
    {
        if (age_ > 20 && sex_ == Sex::BOY)
        {
            return true;
        }
        return false;
    }
private:
    int age_;
    Sex sex_;
};

int main ()
{
    MyClass c1(21, MyClass::Sex::BOY);
    MyClass c2(9, MyClass::Sex::BOY);
    if (c1)
    {
        std::cout << "is old boy" << std::endl;
    }
    if (!c2)
    {
        std::cout << "is little boy" << std::endl;
    }
}
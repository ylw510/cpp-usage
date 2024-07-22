#include <iostream>
#include <string>

class MyClass {
private:
    int value;
public:
    MyClass(int val) : value(val) {}

    // 类型转换运算符，将 MyClass 对象转换为 int 类型
    operator int() const {
        return value;
    }

    // 类型转换运算符，将 MyClass 对象转换为 std::string 类型
    operator std::string() const {
        return std::to_string(value);
    }
};

int main() {
    MyClass obj(42);

    // 使用类型转换运算符，将 MyClass 对象转换为 int 类型
    int intValue = obj;
    std::cout << "int value: " << intValue << std::endl;

    // 使用类型转换运算符，将 MyClass 对象转换为 std::string 类型
    std::string strValue = obj;
    std::cout << "string value: " << strValue << std::endl;

    return 0;
}

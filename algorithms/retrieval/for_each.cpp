#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

class MyClass {
public:
    MyClass(int a, const string& n) : age(a), name(n) {}

    bool operator==(const MyClass& other) const {
        return age == other.age && name == other.name;
    }

    void print() const {
        cout << "Age: " << age << ", Name: " << name << endl;
    }

private:
    int age;
    string name;
};

// RandomGenerator 工具类
class RandomGenerator {
public:
    RandomGenerator(int age_min = 18, int age_max = 100, int name_min_length = 5, int name_max_length = 10)
        : age_min_(age_min), age_max_(age_max), name_min_length_(name_min_length), name_max_length_(name_max_length),
          gen_(rd_()) {}

    MyClass generateRandomMyClass() {
        int age = generateRandomAge();
        string name = generateRandomName();
        return MyClass(age, name);
    }

    void generateRandomClasses(std::vector<MyClass>& classes, int count) {
        for (int i = 0; i < count; ++i) {
            classes.push_back(generateRandomMyClass());
        }
    }

private:
    int generateRandomAge() {
        uniform_int_distribution<> dis(age_min_, age_max_);
        return dis(gen_);
    }

    string generateRandomName() {
        uniform_int_distribution<> dis_char('A', 'Z');
        uniform_int_distribution<> dis_len(name_min_length_, name_max_length_);

        int name_length = dis_len(gen_);
        string name;
        for (int i = 0; i < name_length; ++i) {
            char random_char = static_cast<char>(dis_char(gen_));
            name += random_char;
        }

        return name;
    }

    int age_min_;
    int age_max_;
    int name_min_length_;
    int name_max_length_;

    random_device rd_;
    mt19937 gen_;
};

int main() {
    vector<MyClass> my_classes;

    // 创建随机生成器对象，指定年龄范围 18-100，名字长度范围 5-10
    RandomGenerator generator(18, 100, 5, 10);

    generator.generateRandomClasses(my_classes, 10);

    auto predicate = [& my_classes] (const MyClass & my_class)
    {
        my_class.print();
    };

    for_each_n(my_classes.begin(), my_classes.size() * 0.8, predicate);

    return 0;
}

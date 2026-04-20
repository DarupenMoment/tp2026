#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iostream>
#include <iomanip>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct StringIO {
    std::string& ref;
};

struct LabelIO {
    std::string& ref;
};

struct DoubleSciIO {
    double& ref;
};

struct LongLongIO {
    long long& ref;
};

class iofmtguard {
public:
    explicit iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, DoubleSciIO&& dest);
std::istream& operator>>(std::istream& in, LongLongIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

#endif

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <limits>
#include <sstream>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    DataStruct() : key1(0), key2(0), key3("") {}

    DataStruct(const DataStruct& other) : key1(other.key1), key2(other.key2), key3(other.key3) {}

    DataStruct(DataStruct&& other) noexcept : key1(other.key1), key2(other.key2), key3(std::move(other.key3)) {}

    DataStruct& operator=(const DataStruct& other) {
        if (this != &other) {
            key1 = other.key1;
            key2 = other.key2;
            key3 = other.key3;
        }
        return *this;
    }

    DataStruct& operator=(DataStruct&& other) noexcept {
        if (this != &other) {
            key1 = other.key1;
            key2 = other.key2;
            key3 = std::move(other.key3);
        }
        return *this;
    }

    ~DataStruct() {}
};

struct DelimiterIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    in >> c;
    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct UllLitIO {
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllLitIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    unsigned long long val;
    in >> val;
    char s1 = ' ', s2 = ' ', s3 = ' ';
    in >> s1 >> s2 >> s3;
    if (in && ((s1 == 'u' && s2 == 'l' && s3 == 'l') || (s1 == 'U' && s2 == 'L' && s3 == 'L'))) {
        dest.ref = val;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct UllBinIO {
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllBinIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char p1 = ' ', p2 = ' ';
    in >> p1 >> p2;
    if (in && p1 == '0' && (p2 == 'b' || p2 == 'B')) {
        unsigned long long val = 0;
        char c = in.peek();
        bool has_digits = false;
        while (in && (c == '0' || c == '1')) {
            has_digits = true;
            in.get(c);
            val = (val << 1) | (c - '0');
            c = in.peek();
        }
        if (has_digits) {
            dest.ref = val;
        } else {
            in.setstate(std::ios::failbit);
        }
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    in >> c;
    if (in && c == '"') {
        std::getline(in, dest.ref, '"');
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    DataStruct temp;
    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    bool k1 = false, k2 = false, k3 = false;
    for (int i = 0; i < 3; ++i) {
        std::string key;
        in >> key;
        if (key == "key1") {
            in >> UllLitIO{temp.key1};
            k1 = true;
        } else if (key == "key2") {
            in >> UllBinIO{temp.key2};
            k2 = true;
        } else if (key == "key3") {
            in >> StringIO{temp.key3};
            k3 = true;
        } else {
            in.setstate(std::ios::failbit);
        }
        in >> DelimiterIO{':'};
    }
    in >> DelimiterIO{')'};
    if (in && k1 && k2 && k3) {
        dest = std::move(temp);
    }
    return in;
}

class iofmtguard {
public:
    iofmtguard(std::basic_ios<char>& s) : s_(s), fill_(s.fill()), precision_(s.precision()), fmt_(s.flags()) {}
    ~iofmtguard() { s_.fill(fill_); s_.precision(precision_); s_.flags(fmt_); }
private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    iofmtguard fmtguard(out);

    out << "(:key1 " << src.key1 << "ull:key2 0b";
    unsigned long long k2 = src.key2;
    if (k2 == 0) {
        out << "0";
    } else {
        std::string bin = "";
        while (k2 > 0) {
            bin = char('0' + (k2 % 2)) + bin;
            k2 /= 2;
        }
        out << bin;
    }
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

void run_tests() {
    std::istringstream iss(
        "(:key1 10ull:key2 0b10:key3 \"Data\":)\n"
        "(:invalid_format_line_should_be_ignored_123:)\n"
        "(:key3 \"A\":key1 5ULL:key2 0B11:)\n"
        "(:key1 10ull:key2 0b10:key3 \"Alpha\":)\n"
    );
    std::vector<DataStruct> data;
    while (!iss.eof()) {
        std::copy(std::istream_iterator<DataStruct>(iss), std::istream_iterator<DataStruct>(), std::back_inserter(data));
        if (iss.fail() && !iss.eof()) {
            iss.clear();
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    assert(data.size() == 3);
    assert(data[0].key1 == 10 && data[0].key2 == 2 && data[0].key3 == "Data");
    assert(data[1].key1 == 5 && data[1].key2 == 3 && data[1].key3 == "A");
    assert(data[2].key1 == 10 && data[2].key2 == 2 && data[2].key3 == "Alpha");

    std::sort(data.begin(), data.end(), compareDataStruct);

    assert(data[0].key1 == 5 && data[0].key2 == 3 && data[0].key3 == "A");
    assert(data[1].key1 == 10 && data[1].key2 == 2 && data[1].key3 == "Data");
    assert(data[2].key1 == 10 && data[2].key2 == 2 && data[2].key3 == "Alpha");
}

int main() {
    run_tests();

    std::vector<DataStruct> data;
    while (!std::cin.eof()) {
        std::copy(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(), std::back_inserter(data));
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(std::begin(data), std::end(data), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}

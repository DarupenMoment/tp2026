#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iomanip>

struct DataStruct {
    char key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& obj) {
    char ch;
    if (!(is >> ch) || ch != '(') {
        is.setstate(std::ios::failbit);
        return is;
    }

    bool has_key1 = false, has_key2 = false, has_key3 = false;

    while (is >> ch && ch != ')') {
        if (ch == ':') {
            std::string field;
            is >> field;

            if (field == "key1") {
                char q1, val, q2;
                is >> q1 >> val >> q2;
                if (q1 != '\'' || q2 != '\'') {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                is >> ch;
                if (ch != ':') {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                obj.key1 = val;
                has_key1 = true;
            }
            else if (field == "key2") {
                char open_p;
                is >> open_p;
                if (open_p != '(') {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                std::string tag_n;
                is >> tag_n;
                if (tag_n != ":N") {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                long long n;
                is >> n;

                std::string tag_d;
                is >> tag_d;
                if (tag_d != ":D") {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                unsigned long long d;
                is >> d;

                std::string end_tag;
                is >> end_tag;
                if (end_tag != ":)") {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                is >> ch;
                if (ch != ':') {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                obj.key2 = {n, d};
                has_key2 = true;
            }
            else if (field == "key3") {
                char quote;
                is >> quote;
                if (quote != '"') {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                std::getline(is, obj.key3, '"');

                is >> ch;
                if (ch != ':') {
                    is.setstate(std::ios::failbit);
                    return is;
                }

                has_key3 = true;
            }
            else {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
    }

    if (!has_key1 || !has_key2 || !has_key3) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& obj) {
    os << "(:key1 '" << obj.key1 << "':";
    os << "key2 (:N " << obj.key2.first << ":D " << obj.key2.second << ":):";
    os << "key3 \"" << obj.key3 << "\":)";
    return os;
}

struct Comparator {
    bool operator()(const DataStruct& a, const DataStruct& b) const {
        if (a.key1 != b.key1) {
            return a.key1 < b.key1;
        }

        double val_a = static_cast<double>(a.key2.first) / a.key2.second;
        double val_b = static_cast<double>(b.key2.first) / b.key2.second;

        if (val_a != val_b) {
            return val_a < val_b;
        }

        return a.key3.length() < b.key3.length();
    }
};

int main() {
    std::vector<DataStruct> data;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    std::sort(data.begin(), data.end(), Comparator());

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}

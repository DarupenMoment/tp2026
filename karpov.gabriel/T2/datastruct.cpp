#include "datastruct.h"
#include <limits>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <string>

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;
    char c = 0;
    in.get(c);
    if (in && c != dest.exp)
        in.setstate(std::ios::failbit);
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;
    dest.ref.clear();
    char c;
    while (in.get(c) && !std::isspace(static_cast<unsigned char>(c)) && c != ':') {
        dest.ref.push_back(c);
    }
    if (c == ':') {
        in.unget();
    }
    if (dest.ref.empty()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DoubleSciIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;
    in >> dest.ref;
    if (!in) {
        return in;
    }
    int next = in.peek();
    if (next != ':' && !std::isspace(next) && next != std::char_traits<char>::eof()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LongLongIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;
    std::string token;
    char c;
    while (in.get(c) && !std::isspace(static_cast<unsigned char>(c)) && c != ':') {
        token.push_back(c);
    }
    if (c == ':') {
        in.unget();
    }
    if (token.size() < 2 || (token.substr(token.size() - 2) != "LL" &&
                              token.substr(token.size() - 2) != "ll")) {
        in.setstate(std::ios::failbit);
        return in;
    }
    token.resize(token.size() - 2);
    try {
        std::size_t pos = 0;
        dest.ref = std::stoll(token, &pos);
        if (pos != token.size()) {
            in.setstate(std::ios::failbit);
        }
    } catch (...) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;
    while (std::isspace(in.peek())) in.get();
    if (in.peek() != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }
    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    if (!in)
        return in;
    DataStruct temp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    while (in && in.peek() != ')') {
        std::string fieldName;
        in >> LabelIO{fieldName};
        if (!in)
            return in;
        if (std::isspace(in.peek())) in.get();
        if (fieldName == "key1" && !hasKey1) {
            in >> DoubleSciIO{temp.key1};
            hasKey1 = true;
        } else if (fieldName == "key2" && !hasKey2) {
            in >> LongLongIO{temp.key2};
            hasKey2 = true;
        } else if (fieldName == "key3" && !hasKey3) {
            in >> StringIO{temp.key3};
            hasKey3 = true;
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
        if (!in)
            return in;
        in >> DelimiterIO{':'};
        if (!in)
            return in;
    }
    in >> DelimiterIO{')'};
    if (in && hasKey1 && hasKey2 && hasKey3) {
        dest = std::move(temp);
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

iofmtguard::iofmtguard(std::basic_ios<char>& s)
    : s_(s),
      width_(s.width()),
      fill_(s.fill()),
      precision_(s.precision()),
      fmt_(s.flags()) {
}

iofmtguard::~iofmtguard() {
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry)
        return out;
    iofmtguard guard(out);
    out << "(:key1 ";
    out << std::scientific << std::setprecision(1) << src.key1;
    out << ":key2 " << src.key2 << "LL";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <complex>
#include <cmath>

struct DataStruct
{
    long long key1;
    std::complex<double> key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::string line;
    if (!std::getline(in, line))
    {
        return in;
    }
    
    size_t start = line.find('(');
    size_t end = line.rfind(')');
    if (start == std::string::npos || end == std::string::npos)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    
    std::string content = line.substr(start + 1, end - start - 1);
    
    long long k1 = 0;
    std::complex<double> k2(0, 0);
    std::string k3;
    bool ok1 = false, ok2 = false, ok3 = false;
    
    size_t pos = 0;
    while (pos < content.size())
    {
        if (content[pos] != ':')
        {
            pos++;
            continue;
        }
        pos++;
        
        size_t keyStart = pos;
        while (pos < content.size() && content[pos] != ' ') pos++;
        std::string key = content.substr(keyStart, pos - keyStart);
        
        if (pos >= content.size() || content[pos] != ' ')
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        pos++;
        
        size_t valStart = pos;
        int depth = 0;
        bool inStr = false;
        while (pos < content.size())
        {
            char c = content[pos];
            if (c == '"' && (pos == 0 || content[pos-1] != '\\')) inStr = !inStr;
            if (!inStr)
            {
                if (c == '(') depth++;
                if (c == ')') depth--;
                if (depth == 0 && c == ':') break;
            }
            pos++;
        }
        std::string value = content.substr(valStart, pos - valStart);
        
        while (!value.empty() && std::isspace(value.back())) value.pop_back();
        
        if (key == "key1" && !ok1)
        {
            std::string num = value;
            if (num.size() >= 2 && num.substr(num.size()-2) == "LL")
                num = num.substr(0, num.size()-2);
            try {
                k1 = std::stoll(num);
                ok1 = true;
            } catch(...) { in.setstate(std::ios::failbit); return in; }
        }
        else if (key == "key2" && !ok2)
        {
            if (value.size() < 6 || value[0] != '#' || value[1] != 'c' || value[2] != '(' || value.back() != ')')
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            std::string inside = value.substr(3, value.size()-4);
            std::stringstream ss(inside);
            double r, i;
            if (!(ss >> r >> i))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            k2 = std::complex<double>(r, i);
            ok2 = true;
        }
        else if (key == "key3" && !ok3)
        {
            if (value.size() < 2 || value.front() != '"' || value.back() != '"')
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            k3 = value.substr(1, value.size()-2);
            ok3 = true;
        }
        else
        {
            in.setstate(std::ios::failbit);
            return in;
        }
    }
    
    if (ok1 && ok2 && ok3)
    {
        dest.key1 = k1;
        dest.key2 = k2;
        dest.key3 = k3;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    out << "(:key1 " << src.key1;
    out << ":key2 #c(" << src.key2.real() << " " << src.key2.imag() << ")";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compare(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double ma = std::abs(a.key2);
    double mb = std::abs(b.key2);
    if (ma != mb) return ma < mb;
    return a.key3.length() < b.key3.length();
}

int main()
{
    std::vector<DataStruct> data;
    std::string line;
    
    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        std::istringstream ss(line);
        DataStruct tmp;
        if (ss >> tmp)
        {
            data.push_back(tmp);
        }
    }
    
    std::sort(data.begin(), data.end(), compare);
    
    for (const auto& x : data)
    {
        std::cout << x << "\n";
    }
    
    return 0;
}


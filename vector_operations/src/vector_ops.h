#pragma once

#include <vector>
#include <iostream>

namespace task {

    template<typename T>
    std::vector<T> operator+(const std::vector<T> &v) {
        return v;
    }

    template<typename T>
    std::vector<T> operator-(const std::vector<T> &v) {
        std::vector<T> res;
        for (int i = 0; i < v.size(); i++) {
            res.push_back(-v.at(i));
        }

        return res;
    }

    template<typename T>
    double operator*(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        double res = 0;
        for (int i = 0; i < v.size(); i++) {
            res += v.at(i) * v2.at(i);
        }

        return res;
    }

    template<typename T>
    std::vector<T> operator+(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        std::vector<T> res;
        for (int i = 0; i < v.size(); i++) {
            res.push_back(v.at(i) + v2.at(i));
        }

        return res;
    }

    template<typename T>
    std::vector<T> operator-(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        std::vector<T> res;
        for (int i = 0; i < v.size(); i++) {
            res.push_back(v.at(i) - v2.at(i));
        }

        return res;
    }

    template<typename T>
    std::vector<T> operator%(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Only 3-dimensional vectors are supported!");
        }

        std::vector<T> res = {
                v[1] * v2[2] - v[2] * v2[1],
                v[2] * v2[0] - v[0] * v2[2],
                v[0] * v2[1] - v[1] * v2[0],
        };

        return res;
    }

    template<typename T>
    std::vector<T> operator|(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        std::vector<T> res;
        for (int i = 0; i < v.size(); i++) {
            res.push_back(v.at(i) | v2.at(i));
        }

        return res;
    }

    template<typename T>
    std::vector<T> operator&(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        std::vector<T> res;
        for (int i = 0; i < v.size(); i++) {
            res.push_back(v.at(i) & v2.at(i));
        }

        return res;
    }

    template<typename T>
    bool operator||(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        double ratio = 0.0;
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i) == 0 && v2.at(i) == 0) {
                continue;
            }

            if ((v.at(i) != 0 && v2.at(i) == 0) || (v.at(i) == 0 && v2.at(i) != 0)) {
                return false;
            }

            if (ratio == 0) {
                ratio = fabs(v2.at(i) / v.at(i));
                continue;
            }

            if (fabs(ratio - fabs(v2.at(i) / v.at(i))) > 1e-7) {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    bool operator&&(const std::vector<T> &v, const std::vector<T> &v2) {
        if (v.size() != v2.size()) {
            throw std::runtime_error("Vectors are of different sizes!");
        }

        return ((v || v2) && (v * v2 > 0));
    }

    template<typename T>
    std::vector<T> reverse(std::vector<T> &v) {
        T tmp;
        int middle = (v.size() + 1) / 2;
        for (int i = 0; i < middle; i++) {
            tmp = v[i]; ;
            v[i] = v[v.size() -  1 - i];
            v[v.size() -  1 - i] = tmp;
        }

        return v;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
        for (auto ii = v.begin(); ii != v.end(); ++ii) {
            os << " " << *ii;
        }

        os << std::endl;

        return os;
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &obj) {

        size_t size;
        is >> size;

        if (size < 0) {
            throw std::runtime_error("Input vector size should be positive!");
        }

        obj.resize(size);

        if (size == 0) {
            return is;
        }

        for (int i = 0; i < size; i++) {
            is >> obj[i];
        }

        return is;
    }

}  // namespace task

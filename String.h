#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
class String {
private:
    char* dataBuffer;
    size_t dataLength;

public:
    static const size_t NO_POSITION = static_cast<size_t>(-1);
    String();
    String(const char* str);
    String(const String& other);
    String(char c) {
        dataLength = 1;
        dataBuffer = new char[2];
        dataBuffer[0] = c;
        dataBuffer[1] = '\0';
    }
    ~String();
    friend std::istream& operator>>(std::istream& in, String& str);
    friend std::ostream& operator<<(std::ostream& out, const String& str);
   
    size_t size() const;

    int to_int() const;

    String substr(size_t pos, size_t count) const;

    bool empty() const;

    static String to_string(int number);

    String& operator=(const String& other);

    String operator+(const String& other) const;

    String operator+(const char& c) const;

    friend String operator+(char c, const String& str);

    bool operator==(const String& other) const;

    bool operator!=(const String& other) const;

    bool operator<(const String& other) const;

    bool operator>(const String& other) const;

    bool operator<=(const String& other) const;

    bool operator>=(const String& other) const;

    char& operator[](size_t index);

    const char& operator[](size_t index) const;
};

#define _CRT_SECURE_NO_WARNINGS 
#include "String.h"
#include <iostream>
#include <string.h>
String::String() : dataBuffer(nullptr), dataLength(0) {}

String::String(const char* str) {
    dataLength = strlen(str);
    dataBuffer = new char[dataLength + 1];
    strcpy(dataBuffer, str);
}

String::String(const String& other) {
    dataLength = other.dataLength;
    dataBuffer = new char[dataLength + 1];
    strcpy(dataBuffer, other.dataBuffer);
}

String::~String() {
    delete[] dataBuffer;
}

size_t String::size() const {
    return dataLength;
}

String String::substr(size_t pos, size_t len) const {
    if (pos >= dataLength) throw std::out_of_range("Index out of range.");
    if (len > dataLength - pos) len = dataLength - pos;
    char* buffer = new char[len + 1];
    std::strncpy(buffer, dataBuffer + pos, len);
    buffer[len] = '\0';
    String result(buffer);
    delete[] buffer;
    return result;
}

bool String::empty() const {
    return dataLength == 0;
}

String String::to_string(int number) {
    char buffer[15];
    sprintf_s(buffer, sizeof(buffer), "%d", number);
    return String(buffer);
}

int String::to_int() const {
    return std::atoi(dataBuffer);
}

String& String::operator=(const String& other) {
    if (this != &other) {//sprawdzam czy wskasuja na ten sam obiekt w pamieci
        delete[] dataBuffer;
        dataLength = other.dataLength;
        dataBuffer = new char[dataLength + 1];
        strcpy(dataBuffer, other.dataBuffer);
    }
    return *this;
}

String operator+(char c, const String& str) {
    size_t new_size = str.dataLength + 1;
    char* new_data = new char[new_size + 1];
    new_data[0] = c;
    strcpy(new_data + 1, str.dataBuffer);
    String new_string(new_data);
    delete[] new_data;
    return new_string;
}

String String::operator+(const String& other) const {
    size_t new_size = dataLength + other.dataLength;
    char* new_data = new char[new_size + 1];
    strcpy(new_data, dataBuffer);
    strcat(new_data, other.dataBuffer);//dziala tak ze dopisuje na koniec
    String new_string(new_data);
    delete[] new_data;
    return new_string;
}

String String::operator+(const char& c) const {
    size_t new_size = dataLength + 1;
    char* new_data = new char[new_size + 1];
    strcpy(new_data, dataBuffer);
    new_data[dataLength] = c;
    new_data[new_size] = '\0';
    String new_string(new_data);
    delete[] new_data;
    return new_string;
}

bool String::operator==(const String& other) const {
    return strcmp(dataBuffer, other.dataBuffer) == 0;
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}

bool String::operator<(const String& other) const {
    return strcmp(dataBuffer, other.dataBuffer) < 0;
}

bool String::operator>(const String& other) const {
    return strcmp(dataBuffer, other.dataBuffer) > 0;
}

bool String::operator<=(const String& other) const {
    return strcmp(dataBuffer, other.dataBuffer) <= 0;
}

bool String::operator>=(const String& other) const {
    return strcmp(dataBuffer, other.dataBuffer) >= 0;
}

char& String::operator[](size_t index) {
    return dataBuffer[index];
}
const char& String::operator[](size_t index) const {
    if (index >= dataLength)  throw std::out_of_range("Index out of range.");
    return dataBuffer[index];
}

std::istream& operator>>(std::istream& in, String& str) {//czyta ci¹g znaków z wejœcia, a nastêpnie tworzy nowy obiekt klasy String na podstawie tego ci¹gu za pomoc¹ konstruktora z jednym argumentem. zwracany jest strumieñ wejœciowy
    char buffer[2048];
    in >> buffer;
    str = String(buffer);
    return in;
}
std::ostream& operator<<(std::ostream& out, const String& str) {//wypisuje zawartoœæ stringa na strumieñ wyjœciowy (std::ostream)
    out << str.dataBuffer;
    return out;
}




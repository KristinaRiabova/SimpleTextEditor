#ifndef LINE_H
#define LINE_H

#include <string>

class Line {
public:
    Line(const std::string& text);

    void Append(const std::string& textToAdd);
    void Insert(size_t index, const std::string& textToInsert);
    void Delete(size_t index, size_t length);
    std::string GetText() const;

private:
    std::string text;
};

#endif

#include "Line.h"

Line::Line(const std::string& text) : text(text) {}

void Line::Append(const std::string& textToAdd) {
    text += textToAdd;
}

void Line::Insert(size_t index, const std::string& textToInsert) {
    text.insert(index, textToInsert);
}

void Line::Delete(size_t index, size_t length) {
    text.erase(index, length);
}

std::string Line::GetText() const {
    return text;
}

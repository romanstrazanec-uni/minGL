#include "Line.h"

// constructors
Line::Line() = default;
Line::Line(int slope): m(slope), b(0) {}
Line::Line(int slope, int b): m(slope), b(b) {}
Line::Line(const Line &) = default;
Line::Line(Line &&) noexcept = default;
Line::~Line() = default;

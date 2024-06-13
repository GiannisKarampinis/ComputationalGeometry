#ifndef GEOUTILS_H
#define GEOUTILS_H

#pragma once

#include "Point.h"
#include "Core.h"

namespace jmk
{
    double areaTriangle2d(const Point2d& a, const Point2d& b, const Point2d& c);

    int orientation2d(const Point2d& a, const Point2d& b, const Point2d& c);
}

#endif
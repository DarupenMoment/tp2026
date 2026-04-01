#ifndefSQUARE_H
#defineSQUARE_H

#include"Shape.h"
#include"Point.h"
#include<memory>

classSquare:publicShape{
public:
Square(constPoint&bottomLeft,doubleside);

doublegetArea()constoverride;
PointgetCenter()constoverride;
voidmove(doubledx,doubledy)override;
voidscale(doublefactor)override;
std::stringgetName()constoverride;
std::unique_ptr<Shape>clone()constoverride;

private:
PointbottomLeft_;
doubleside_;
};

#endif

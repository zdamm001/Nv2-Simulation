#include "Flavours.h"

vector<unsigned int> Flavours::_p1Colors = vector<unsigned int>(13);
vector<unsigned int> Flavours::_p2Colors = vector<unsigned int>(13);
BitmapData* Flavours::_flavourImage = nullptr;

unsigned int Flavours::getP1Flavour(int color) {
    if (!_flavourImage) {
        readImage();
    }
    return _p1Colors[color];
}

unsigned int Flavours::getP2Flavour(int color) {
    if (!_flavourImage) {
        readImage();
    }
    return _p2Colors[color];
}

void Flavours::readImage() {
    //_flavourImage = new NinjaFlavours().bitmapData;
    //for (int i = 0; i < _flavourImage.width; ++i) {
    //    _p1Colors.push_back(_flavourImage.getPixel(i, 0));
    //    _p2Colors.push_back(_flavourImage.getPixel(i, 1));
    //}
}
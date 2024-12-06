#include "abstracttextparser.h"

using namespace KE;

AbstractTextParser::AbstractTextParser() : mNormalizationFunction( [](ME::Form f) { return f; } )
{
}

AbstractTextParser::AbstractTextParser(std::function<ME::Form (ME::Form)> normalizationFunction) : mNormalizationFunction(normalizationFunction)
{
}

AbstractTextParser::~AbstractTextParser()
{

}

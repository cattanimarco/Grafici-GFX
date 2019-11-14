#include "Data.h"

VectorIterator DataSet::begin()
{
	return VectorIterator(this, 0);
};
VectorIterator DataSet::end()
{
	return VectorIterator(this, size());
};

FloatIterator DataSet::beginX()
{
	return FloatIterator(this, 0, FloatIterator::FloatSource::X);
};
FloatIterator DataSet::endX()
{
	return FloatIterator(this, size(), FloatIterator::FloatSource::X);
};

FloatIterator DataSet::beginY()
{
	return FloatIterator(this, 0, FloatIterator::FloatSource::Y);
};
FloatIterator DataSet::endY()
{
	return FloatIterator(this, size(), FloatIterator::FloatSource::Y);
};

FloatIterator DataSet::beginZ()
{
	return FloatIterator(this, 0, FloatIterator::FloatSource::Z);
};
FloatIterator DataSet::endZ()
{
	return FloatIterator(this, size(), FloatIterator::FloatSource::Z);
};

Vector VectorIterator::operator*()
{
	return dataSet->getVector(dataIndex);
};

VectorIterator &VectorIterator::operator++()
{
	++dataIndex;
	return *this;
};

bool VectorIterator::operator!=(VectorIterator const &other)
{
	return (((this->dataSet) != (other.dataSet)) || ((this->dataIndex) != (other.dataIndex)));
};

float FloatIterator::operator*()
{
	if (floatSource == FloatSource::X)
		return (*vectorIterator).x;
	else if (floatSource == FloatSource::Y)
		return (*vectorIterator).y;
	else /* (floatSource == FloatSource::Z) */
		return (*vectorIterator).z;
};

FloatIterator &FloatIterator::operator++()
{
	++vectorIterator;
	return *this;
};

bool FloatIterator::operator!=(FloatIterator const &other)
{
	return (((this->floatSource) != (other.floatSource)) || ((this->vectorIterator) != (other.vectorIterator)));
};
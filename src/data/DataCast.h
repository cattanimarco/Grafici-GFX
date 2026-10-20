#ifndef GRAFICI_DATA_CAST_H
#define GRAFICI_DATA_CAST_H

#include "DataSourceNorm.h"

// Borrow a source in another precision family without copying its samples.
template <typename To, typename From = float>
class DataCast : public DataSourceNormT<To>
{
public:
    explicit DataCast(const DataSourceNormT<From> &source)
        : DataSourceNormT<To>(source.size()), _source(source)
    {
    }

    const DataNormT<To> operator[](unsigned long index) const override
    {
        if (index < this->size())
            return DataNormT<To>(_source[index]);
        return INVALID_DATA_NORM;
    }

    const Range<To> range() const override
    {
        return Range<To>(_source.range());
    }

private:
    const DataSourceNormT<From> &_source;
};

#endif

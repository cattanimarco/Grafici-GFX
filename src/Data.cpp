#include "Data.h"

int DataSource::length() const
{
	return arrayLength;
};

void DataSource::setLength(int arrayLength)
{
	this->arrayLength = arrayLength;
}

DataSourceIterator DataSource::begin() const
{
	return DataSourceIterator(this, 0);
};

DataSourceIterator DataSource::end() const
{
	return DataSourceIterator(this, length());
};

DataCoordinate DataSourceIterator::operator*()
{
	return dataSource->getDataCoordinate(dataIndex);
};

DataSourceIterator &DataSourceIterator::operator++()
{
	++dataIndex;
	return *this;
};

bool DataSourceIterator::operator!=(DataSourceIterator const &other)
{
	return (((this->dataSource) != (other.dataSource)) || ((this->dataIndex) != (other.dataIndex)));
};

DataCoordinate DataSet::getDataCoordinate(int index) const
{
	switch (selectedDataSource)
	{
	case SelectedDataSource::x:
	{
		return dataSourceX->getDataCoordinate(index);
	}

	case SelectedDataSource::y:
	{
		return dataSourceY->getDataCoordinate(index);
	}

	case SelectedDataSource::z:
	{
		return dataSourceZ->getDataCoordinate(index);
	}

		case SelectedDataSource::color:
	{
		return dataSourceColor->getDataCoordinate(index);
	}

	default:
	{
		return DataCoordinate{ 0 };
	}
	}
}

void DataSourceTuple::refresh() override
{
	dataSourceX->refresh();
	dataSourceY->refresh();
		dataSourceZ->refresh();
	dataSourceColor->refresh();
}
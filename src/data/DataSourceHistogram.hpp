#ifndef GRAFICI_DATASET_HISTOGRAM_H
#define GRAFICI_DATASET_HISTOGRAM_H

#include "../Data.h"

template <typename T>
class DataSourceHistogram : public DataSource<T>
{
  public:
	DataSourceHistogram(DataSource<T> &dataSource, size_t buckets)
	    : dataSource{ &dataSource }
	{

		this->buckets = static_cast<size_t *>(malloc(sizeof(size_t) * buckets));
		/* we do not check if malloc fails as we cannot do much to make it better. TODO output something */
		length(buckets);
		refresh();
	};

	~DataSourceHistogram()
	{
		if (buckets != nullptr)
		{
			free(buckets);
		}
	}

	DataNorm at(size_t index) const override
	{
		if (index < length())
		{
			return DataNorm{ (1.0 * buckets[index]) / limits.high };
		}
		else
		{
			return DataNorm{ 0 };
		}
	};
	void refresh() override
	{
		if (buckets != nullptr)
		{
			memset(buckets, 0, sizeof(size_t) * length());

			limits = { 0, 0 };

			for (auto it = dataSource->begin(); it != dataSource->end(); ++it)
			{
				DataNorm dataCoordinate = *it;
				size_t target = round(dataCoordinate * (length() - 1));
				buckets[target]++;
				limits.high = graficiMax<size_t>(buckets[target], limits.high);
			}
		}
	};

	DataLimits<size_t> dataLimits()
	{
		return limits;
	};
	DataLimits<size_t> dataLimits(DataLimits<size_t> limits)
	{
		this->limits = limits;
		return dataLimits();
	};

  private:
	DataLimits<size_t> limits{ 0, 0 };
	DataSource<T> *dataSource{ nullptr };
	size_t *buckets{ nullptr };
};

#endif //GRAFICI_DATASET_HISTOGRAM_H

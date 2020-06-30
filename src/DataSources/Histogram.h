#ifndef GRAFICI_DATASET_HISTOGRAM_H
#define GRAFICI_DATASET_HISTOGRAM_H

#include "../DataSource.h"

namespace DataSources
{

class Histogram : public DataSources::DataSource<DataNorm>, public Ranged<size_t>
{
  public:
	Histogram(const DataSources::DataSource<DataNorm> &source, size_t buckets)
	{
		_buckets = static_cast<size_t *>(malloc(sizeof(size_t) * buckets));
		_length = buckets;
		/* Compute histogram */
		if (_buckets != nullptr)
		{
			memset(_buckets, 0, sizeof(size_t) * length());
			range = { 0, 0 };

			for (auto it = source.begin(); it != source.end(); it++)
			{
				auto value = *it;
				size_t bucketIdx = round(value * (length() - 1));
				_buckets[bucketIdx]++;
				range.update(_buckets[bucketIdx]);
			}
		}
	};

	~Histogram()
	{
		free(_buckets);
	}

	DataNorm at(size_t index) const override
	{
		if (index < length())
		{
			return range.normalize(_buckets[index]);
		}
		else
		{
			return 0.0;
		}
	};

  private:
	size_t *_buckets{ nullptr };
};

} // namespace DataSources
#endif //GRAFICI_DATASET_HISTOGRAM_H

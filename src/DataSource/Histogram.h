#ifndef GRAFICI_DATASET_HISTOGRAM_H
#define GRAFICI_DATASET_HISTOGRAM_H

#include "../DataSource.h"

namespace DataSource
{

class Histogram : public DataSource::Base<DataNorm>
{
  public:
	Histogram(const DataSource::Base<DataNorm> &source, size_t buckets)
	{
		_buckets = static_cast<size_t *>(malloc(sizeof(size_t) * buckets));
		_length = buckets;
		/* Compute histogram */
		if (_buckets != nullptr)
		{
			memset(_buckets, 0, sizeof(size_t) * length());
			_limits = { 0, 0 };

			for (auto it = source.begin(); it != source.end(); it++)
			{
				auto value = *it;
				size_t bucketIdx = round(value * (length() - 1));
				_buckets[bucketIdx]++;
				_limits.update(_buckets[bucketIdx]);
			}
		}
		refresh();
	};

	~Histogram()
	{
		free(_buckets);
	}

	DataNorm at(size_t index) const override
	{
		if (index < length())
		{
			return _limits.normalize(_buckets[index]);
		}
		else
		{
			return 0.0;
		}
	};
	void refresh() override
	{
		/* We cannot refresh as this class is a one shot */
	};

	Range<size_t> &limits()
	{
		return _limits;
	};

  private:
	size_t *_buckets{ nullptr };
	Range<size_t> _limits{ 0, 0 };
};

} // namespace DataSource
#endif //GRAFICI_DATASET_HISTOGRAM_H

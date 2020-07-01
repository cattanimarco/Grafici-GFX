#ifndef GRAFICI_DATASOURCE_SELECT_H
#define GRAFICI_DATASOURCE_SELECT_H

#include "../DataSet.h"
#include "../DataSource.h"

namespace DataSources
{

enum class Channel
{
	x,
	y,
	c,
	opt
};

class Select : public DataSources::DataSource<DataNorm>
{
  public:
	Select(const DataSets::DataSet &source, Channel selection)
	    : _source{ source }
	    , _selection{ selection }
	{
		_length = _source.length();
	}

	DataNorm at(size_t index) const override
	{
		DataVector<DataNorm> dataSet = _source.at(index);
		switch (_selection)
		{
		case Channel::x:
		{
			return dataSet.x();
		}

		case Channel::y:
		{
			return dataSet.y();
		}

		case Channel::c:
		{
			return dataSet.c();
		}

		case Channel::opt:
		{
			return dataSet.opt();
		}
		default:
		{
			return 0;
		}
		}
	};

	const size_t &length() const override
	{
		return _source.length();
	};

  private:
	const DataSets::DataSet &_source;
	Channel _selection;
};

} // namespace DataSources

#endif /* GRAFICI_DATASOURCE_SELECT_H */

#ifndef GRAFICI_DATASOURCE_SELECT_H
#define GRAFICI_DATASOURCE_SELECT_H

#include "../DataSet.h"
#include "../DataSource.h"

namespace DataSource
{

enum class Channel
{
	x,
	y,
	c,
	opt
};

class Select : public DataSource::Base<DataNorm>
{
  public:
	Select(const DataSet::Base &source, Channel selection)
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
		}
	};

	const size_t &length() const override
	{
		return _source.length();
	};

	// size_t &length() override
	// {
	// 	return _source.length();
	// };

	void refresh() override
	{
//		_source.refresh();
	};

  private:
	const DataSet::Base &_source;
	Channel _selection;
};

} // namespace DataSource

#endif /* GRAFICI_DATASOURCE_SELECT_H */

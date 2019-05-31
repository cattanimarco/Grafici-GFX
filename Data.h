#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

class PointIterator;

class Data
{
public:
	virtual Point getPoint(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;
	PointIterator begin();
	PointIterator end();
};

class PointIterator
{
	/* Inspired by https://www.boost.org/doc/libs/1_70_0/libs/iterator/doc/iterator_facade.html#tutorial-example */

public:
	PointIterator(Data *Data, int dataIndex) : Data(Data), dataIndex(dataIndex){};

	Point operator*();
	PointIterator &operator++();
	PointIterator operator++(int postfix);
	bool operator!=(PointIterator const &other);
	/*TODO complete operator overriding*/

private:
	Data *Data;
	int dataIndex;
};

#endif //ARDU_DATAVIS_DATA_H

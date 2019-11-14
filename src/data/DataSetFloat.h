#ifndef GRAFICI_GFX_DATA_FLOAT_H
#define GRAFICI_GFX_DATA_FLOAT_H

#include "../Data.h"

class DataSetFloat : public DataSet
{
public:

	void begin(float *yVector, float zVector, int len);
	void begin(float *yVector, float *zVector, int len);
	void begin(float *xVector, float *yVector, float zVector, int len);
	void begin(float *xVector, float *yVector, float *zVector, int len);
	
	Vector getVector(int index);
	void refresh();
	int size(void);

	float xMin;
	float yMin;
	float zMin;
	float xMax;
	float yMax;
	float zMax;
	
private:
	float *xVector;
	float *yVector;
	float *zVector;
	float zValue;
	int numElem;
};

void DataSetFloat::begin(float *yVector, float zValue, int len)
{
	this->xVector = nullptr;
	this->yVector = yVector;
	this->zVector = nullptr;
	this->zValue = zValue;
	this->numElem = len;
	refresh();
}

void DataSetFloat::begin(float *yVector, float *zVector, int len)
{
	this->xVector = nullptr;
	this->yVector = yVector;
	this->zVector = zVector;
	this->zValue = 0;
	this->numElem = len;
	refresh();
}

void DataSetFloat::begin(float *xVector, float *yVector, float zValue, int len)
{
	this->xVector = xVector;
	this->yVector = yVector;
	this->zVector = nullptr;
	this->zValue = zValue;
	this->numElem = len;
	refresh();
}

void DataSetFloat::begin(float *xVector, float *yVector, float *zVector, int len)
{
	this->xVector = xVector;
	this->yVector = yVector;
	this->zVector = zVector;
	this->zValue = 0;
	this->numElem = len;
	refresh();
}

Vector DataSetFloat::getVector(int index)
{
	Vector p;
	if (index < numElem)
	{
		// normalize dataset to a 0.0 .. 1.0 value
		p.y = (yVector[index] - yMin) / (yMax - yMin);

		if (xVector != nullptr)
		{
			p.x = (xVector[index] - xMin) / (xMax - xMin);
		}
		else
		{
			p.x = (1.0 * index) / (numElem - 1);
		}

		//rewrite ho zdata is defined
		if (zVector != nullptr)
		{
			p.z = (zVector[index] - zMin) / (zMax - zMin);
		}
		else
		{
			p.z = zValue;
		}
	}
	return p;
}

int DataSetFloat::size(void)
{
	return numElem;
}

void DataSetFloat::refresh(void)
{
	if (numElem > 0)
	{
		if (yVector != nullptr)
		{
			yMin = yMax = yVector[0];
			for (int i = 1; i < numElem; ++i)
			{
				yMin = min(yMin, yVector[i]);
				yMax = max(yMax, yVector[i]);
			}
		}

		if (xVector != nullptr)
		{
			xMin = xMax = xVector[0];
			for (int i = 1; i < numElem; ++i)
			{
				xMin = min(xMin, xVector[i]);
				xMax = max(xMax, xVector[i]);
			}
		}

		if (zVector != nullptr)
		{
			zMin = zMax = zVector[0];
			for (int i = 1; i < numElem; ++i)
			{
				zMin = min(zMin, zVector[i]);
				zMax = max(zMax, zVector[i]);
			}
		}
	}
}


#endif //GRAFICI_GFX_DATA_FLOAT_H

#include "CameraItem.h"

// Constructors and Destructors
//==================================================

CameraItem::CameraItem(const QVector<QVariant> &data, CameraItem *parent)
{
	parentItem = parent;
	itemData = data;
}

CameraItem::~CameraItem()
{
	qDeleteAll(childItems);
}

// Public Methods
//==================================================
CameraItem* CameraItem::parent()
{
	return parentItem;
}

CameraItem* CameraItem::child(int number)
{
	return childItems.value(number);
}

int CameraItem::childCount() const
{
	return childItems.count();
}

int CameraItem::childNumber() const
{
	if (parentItem)
		return parentItem->childItems.indexOf(const_cast<CameraItem*>(this));
	return 0;
}

int CameraItem::columnCount() const
{
	return itemData.count();
}

bool CameraItem::insertChildren(int position, int count, int columns)
{
	if (position < 0 || position > childItems.size())
	{
		return false;
	}
	for (int row = 0; row < count; ++row)
	{
		QVector<QVariant> data(columns);
		CameraItem *item = new CameraItem(data, this);
		childItems.insert(position, item);
	}
	return true;
}

bool CameraItem::removeChildren(int position, int count)
{
	if (position < 0 || position + count > childItems.size())
	{
		return false;
	}
	for (int row = 0; row < count; ++row)
	{
		delete childItems.takeAt(position);
	}

	return true;
}

bool CameraItem::insertColumns(int position, int columns)
{
	if (position < 0 || position > itemData.size())
	{
		return false;
	}
	for (int column = 0; column < columns; column++)
	{
		itemData.insert(position, QVariant());
	}
	foreach(CameraItem *child, childItems)
	{
		child->insertColumns(position, columns);
	}
	return true;
}

// Public Setters
//==================================================
bool CameraItem::setData(int column, const QVariant &value)
{
	if (column < 0 || column >= itemData.size())
	{
		return false;
	}
	itemData[column] = value;
	return true;
}

// Public Getters
//==================================================
QVariant CameraItem::data(int column) const
{
	return itemData.value(column);
}


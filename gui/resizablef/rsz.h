#ifndef RSZ_H
#define RSZ_H

#include <QFrame>
#include <QMouseEvent>

class ResizableFrame : public QFrame
{
	Q_OBJECT

public:
	explicit ResizableFrame(QWidget *parent = 0);
	~ResizableFrame();
	enum startPositions {topleft, left, bottomleft, bottom, bottomright, right, topright, top, move} startPositions;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	QPoint dragStartPosition;
	QRect dragStartGeometry;
	enum startPositions startPos;
};

#endif // RSZ_H
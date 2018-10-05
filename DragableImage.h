#ifndef DRAGABLEIMAGE_H
#define DRAGABLEIMAGE_H

#include <QObject>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QSGSimpleTextureNode>
#include <QTimer>

class DragableImage : public QQuickItem {
	Q_OBJECT
  public:
	DragableImage();

  protected:
	QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
	void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

  private:
	QPixmap *m_pixmap1;
	QPixmap *m_pixmap2;
	QImageReader *image;
	QImage image2;
	QImage image3;
	QSGTexture *texture1;
	QSGTexture *texture2;
	QPixmap collage;

	QQuickItem *childItem;
	int x;
};

#endif // DRAGABLEIMAGE_H

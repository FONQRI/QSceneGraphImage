#include "DragableImage.h"

#include <QDir>
#include <QImageReader>
#include <QPainter>
#include <QPixmap>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QTime>

#include "RectSGNode.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>

class GraphNode : public QSGNode {
  public:
	QSGSimpleTextureNode *background;
	QSGSimpleTextureNode *background2;
};
#include <iostream>

DragableImage::DragableImage() : x(0)
{

	//	m_pixmap1 = new QPixmap(QDir::currentPath() + "/img/3.jpg");
	//	m_pixmap2 = new QPixmap(QDir::currentPath() + "/img/2.jpg");
	setFlag(ItemHasContents, true);

	image = new QImageReader(QDir::currentPath() + "/img/3.jpg");
	//	image->setScaledSize(QSize(1920, 1080));
	qDebug() << image->size();

	//	image->setClipRect(QRect(21600, 10800, 1920, 1080));
	image->setClipRect(QRect(21600, 0, 21600, 10800));

	//	qDebug() << image->size();

	std::clock_t c_start = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	image2 = image->read();

	std::clock_t c_end = std::clock();
	auto t_end = std::chrono::high_resolution_clock::now();

	std::clog
	<< std::fixed << std::setprecision(2)
	<< "CPU time used: " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC
	<< " ms\n"
	<< "Wall clock time passed: "
	<< std::chrono::duration<double, std::milli>(t_end - t_start).count()
	<< " ms\n";
	//	image1 = m_pixmap1->toImage();
	//	image2 = m_pixmap2->toImage();

	//	QList<QPixmap *> images;
	//	images.append(m_pixmap1);
	//	images.append(m_pixmap2);

	//	collage = *m_pixmap1;
	//	collage = collage.scaled(m_pixmap1->width() + m_pixmap2->width(),
	//				 m_pixmap1->height() /*+ m_pixmap2->height()*/,
	//				 Qt::IgnoreAspectRatio,
	// Qt::SmoothTransformation);

	//	qDebug() << collage.size();

	// Make sure to resize collage to be able to fit all images.

	//	for (auto const &it : images) {

	//		// Calculate x & y coordinates for the current image in the
	// collage.
	//		//		...
	//		QPainter painter(&collage);
	//		painter.drawPixmap(QRectF(x, y, (it)->width(), (it)->height()),
	//*it,
	//				   QRectF(0, 0, (it)->width(), (it)->height()));

	//		x += it->width();
	//		//		y += it.height();
	//	}
}

QSGNode *DragableImage::updatePaintNode(QSGNode *oldNode,
					QQuickItem::UpdatePaintNodeData *)
{

	GraphNode *node = static_cast<GraphNode *>(oldNode);

	if (!node) {
		node = new GraphNode();

		texture1 = window()->createTextureFromImage(image2);
		node->background = new QSGSimpleTextureNode();

		node->background->setTexture(texture1);

		node->appendChildNode(node->background);

		// try render text

		QQmlComponent component(
		QQmlEngine::contextForObject(this)->engine());
		component.setData("import QtQuick 2.0\nText {}", QUrl());

		childItem = qobject_cast<QQuickItem *>(component.create());

		if (childItem == nullptr) {
			qCritical() << component.errorString();
			return 0;
		}

		// Set the text of the QML item. It's possible to set all the
		// properties with this way.
		childItem->setProperty("text", "Hello dynamic object");
		childItem->setProperty("color", "white");
		// Put it into the root QML item
		childItem->setParentItem(this);
	}

	node->background->setRect(QRectF(boundingRect().x(), boundingRect().y(),
					 boundingRect().width(),
					 boundingRect().height()));
	childItem->setPosition(QPointF(x++, 0));

	return node;
}

void DragableImage::geometryChanged(const QRectF &newGeometry,
					const QRectF &oldGeometry)
{
	update();
	QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

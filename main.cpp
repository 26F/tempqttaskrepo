
#include <cassert>
#include <iostream>
#include <QApplication>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QScreen>
#include <QMainWindow>

class DraggableWidget : public QWidget
{

public:
	DraggableWidget(QWidget* parent=nullptr) :
	QWidget(parent), isDragging(false)
	{




	}

protected:
	void mousePressEvent(QMouseEvent* event) override
	{


		isDragging = true;
		dragStartPosition = event->pos();

	}


	void mouseMoveEvent(QMouseEvent* event) override
	{


		if (isDragging)
		{

			QPoint delta = event->pos() - dragStartPosition;
			QPoint newPos = this->pos() + delta;


			QRect parentRect = this->parentWidget()->rect();

			if (parentRect.contains(newPos)) // meh
			{

				move(newPos);

			}

		}

	}


	void mouseReleaseEvent(QMouseEvent* event) override
	{

		if (event->button() == Qt::LeftButton)
		{

			isDragging = false;

		}

	}


private:
	bool isDragging;
	QPoint dragStartPosition;

};


int main(int argc, char** argv)
{

	// Window and resizing to specified
	QApplication applicationContext(argc, argv);
	QMainWindow mainWindow;
	
	// QScreen used to get dimensions of display device
	QScreen* primaryScreen = QGuiApplication::primaryScreen();
	assert(primaryScreen);

	// widget for the graphics view
	DraggableWidget graphicsViewWidget = DraggableWidget(&mainWindow);
	assert(primaryScreen);

	graphicsViewWidget.setContentsMargins(0, 0, 0, 0);

	// graphics view
	QGraphicsView* graphicsView = new QGraphicsView(&graphicsViewWidget);

	// width and height of device screen
	int screenWidth = primaryScreen->size().width();
	int screenHeight = primaryScreen->size().height();

	// Dimensions and position of the main window
	double scale = 0.80;
	int width = static_cast<int>(static_cast<double>(screenWidth) * scale);
	int height = static_cast<int>(static_cast<double>(screenHeight) * scale);
	int topLeftX = static_cast<int>(static_cast<double>(screenWidth) * (1.0 - scale) * 0.5);
	int topLeftY = static_cast<int>(static_cast<double>(screenHeight) * (1.0 - scale) * 0.5);

	// Main window set geometry, position and title
	mainWindow.setWindowTitle("AlienSky Game 11");
	mainWindow.setGeometry(topLeftX, topLeftY, width, height);

	// Make it so that the window cannot be resized
	mainWindow.setFixedSize(width, height);

	// Dimensions and position of the graphics view
	// I guess I'll just make it 80 percent of the main window
	int gvWidth  = static_cast<int>(static_cast<double>(width) * scale);
	int gvHeight = static_cast<int>(static_cast<double>(height)* scale);
	int gvTopLeftX = static_cast<int>(static_cast<double>(width) * (1.0 - scale) * 0.5);
	int gvTopLeftY = static_cast<int>(static_cast<double>(height) * (1.0 - scale) * 0.5);

	graphicsView->setGeometry(gvTopLeftX, gvTopLeftY, gvWidth, gvHeight);
	mainWindow.setCentralWidget(&graphicsViewWidget);

	mainWindow.show();
	
	return applicationContext.exec();
}




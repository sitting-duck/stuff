#include "customwidget.h"

#include <iostream>

#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{

    initLayout();

    initCities();
    addCitiesToListWidget();

    connectWidgetsToEventListeners();

}

void CustomWidget::initCities()
{

    cities << "Paris" << "London" << "Munich";
}

void CustomWidget::initLayout()
{

    //The QVBoxLayout class lines up widgets vertically.
    //QBoxLayout takes the space it gets from its parent, divides it up into a row of boxes and makes each managed
    //widget fill one box
    this->layout = new QVBoxLayout(this);

    this->m_list_widget = new QListWidget(this);
    layout->addWidget(this->m_list_widget);

    //QLineEdit is a one line text editor
    this->m_edit = new QLineEdit(this);
    layout->addWidget(this->m_edit);

    this->m_button = new QPushButton("Quit", this);
    layout->addWidget(this->m_button);

    setLayout(layout);

}

void CustomWidget::addCitiesToListWidget()
{

    foreach(const QString& city, cities) {
        this -> m_list_widget -> addItem(city);
    }

}

void CustomWidget::connectWidgetsToEventListeners()
{

    connect(this->m_list_widget, SIGNAL(QListWidgetItem::itemClicked(QListWidgetItem*)), this, SLOT(CustomWidget::itemClicked(QListWidgetItem*)));
    connect(this->m_edit, SIGNAL(editingFinished()), this, SLOT(updateItem()));

    //FUBAR
    connect(this->m_button, SIGNAL(clicked()), , SLOT(quit()));

}

void CustomWidget::itemClicked(QListWidgetItem *item)
{

    std::cout << "in my item clicked" << std::endl;

    //throw exception if item does not exist
    Q_ASSERT(item);

    //
    this->m_edit->setText(item->text());

}


void CustomWidget::updateItem()
{

    std::cout << "boop" << std::endl;

    QListWidgetItem* item = this ->m_list_widget->currentItem();

    if(item) {

        item ->setText(this->m_edit->text());

    }
}

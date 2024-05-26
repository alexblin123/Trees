#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStringListIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);

    bst = new BinarySearchTree<int>;

    propertyButton = new QPushButton("&Свойства", this);
    deleteButton = new QPushButton("&Удалить", this);
    insertButton = new QPushButton("&Вставить", this);
    Balancing = new QPushButton("&Балансировка", this);
    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;

    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Balancing->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    insertValueLineEdit->setFixedWidth(200);

    deleteValueLineEdit->setFixedWidth(100);

    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(Balancing, SIGNAL(clicked()), this, SLOT(BalancingClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addSpacing(25);
    buttonLayout->addWidget(statusLabel);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(Balancing);

    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);
    treeScrollArea->installEventFilter(renderArea);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumHeight(400);
    this->setWindowTitle("Двоичное дерево");

    prop = new BST_Properties_Window();

    this->show();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    this->renderArea->callRepaint();
}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete propertyButton;
    delete deleteButton;
    delete insertButton;
    delete Balancing;
    delete treeScrollArea;
    delete prop;
    delete bst;
    delete centralWidget;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer/last_bst.txt";

    QString text = bst->getPreOrderTraversal();
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
    }

    prop->closePropertyWindow();
    event->setAccepted(true);
    return;
}

void MainWindow::propertyClicked() const
{
    prop->show();
    prop->update(this->bst);
    return;
}

void MainWindow::deleteClicked() const {
    QString value = deleteValueLineEdit->text();

    if(!this->bst->deleteItem(value.toInt()))
        this->statusLabel->setText("Значения нет");
    else
        this->statusLabel->setText("Значение удалено");

    this->renderArea->repaint();
    this->deleteValueLineEdit->setText("");
    return;
}

void MainWindow::insertClicked() const
{
    QString values = insertValueLineEdit->text();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);

    while (iterator.hasNext())
    {
        if(!this->bst->insert(iterator.next().toInt()))
            this->statusLabel->setText("Значение уже есть");
        else
            this->statusLabel->setText("Значение введено");
    }
    this->renderArea->repaint();
    insertValueLineEdit->setText("");

    return;
}

void MainWindow::BalancingClicked() const {
    bst->balanceTree();
    this->renderArea->repaint();

}

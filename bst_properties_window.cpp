#include "bst_properties_window.h"
#include <iostream>
#include <QScrollArea>
#include <QHBoxLayout>

BST_Properties_Window::BST_Properties_Window(QWidget *parent) : QMainWindow(parent)
{

    this->setWindowTitle("Свойства");
    this->setFixedSize(QSize(400, 525));

    preOrderTraversal = new QTextEdit;
    inOrderTraversal = new QTextEdit;
    postOrderTraversal = new QTextEdit;
    breadthFirstTraversal = new QTextEdit;
    preOrderTraversal->setReadOnly(true);
    inOrderTraversal->setReadOnly(true);
    postOrderTraversal->setReadOnly(true);
    breadthFirstTraversal->setReadOnly(true);

    exitButton = new QPushButton("E&xit", this);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitSlot()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(exitButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Прямой обход:"));
    mainLayout->addWidget(preOrderTraversal);
    mainLayout->addWidget(new QLabel("Симметричный обход:"));
    mainLayout->addWidget(inOrderTraversal);
    mainLayout->addWidget(new QLabel("Обратный обход:"));
    mainLayout->addWidget(postOrderTraversal);
    mainLayout->addWidget(new QLabel("Обход в ширину:"));
    mainLayout->addWidget(breadthFirstTraversal);
    mainLayout->addLayout(buttonLayout);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);

}

BST_Properties_Window::~BST_Properties_Window(){

    delete preOrderTraversal;
    delete inOrderTraversal;
    delete postOrderTraversal;
    delete breadthFirstTraversal;
    delete exitButton;
    delete mainLayout;
    delete centralWidget;

}

void BST_Properties_Window::closePropertyWindow()
{
    this->close();
    return;
}

void BST_Properties_Window::update(BinarySearchTree<int> *bst)
{
    this->preOrderTraversal->setText(bst->getPreOrderTraversal());
    this->inOrderTraversal->setText(bst->getInOrderTraversal());
    this->postOrderTraversal->setText(bst->getPostOrderTraversal());
    this->breadthFirstTraversal->setText(bst->getBreadthFirstSearch());
    return;
}

void BST_Properties_Window::show()
{
    this->setVisible(true);
    this->activateWindow();
    return;
}

void BST_Properties_Window::exitSlot()
{
    this->close();
    return;
}

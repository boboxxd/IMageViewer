#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QStatusBar>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    index=0;
    initWidget();
    setlistWidget();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    filemenu=new QMenu(tr("文件"));
    this->menuBar()->addMenu(filemenu);
    openaction=new QAction(QIcon(":/icon/file-open.png"),tr("打开文件"));
    opendiraction=new QAction(QIcon(":/icon/folder-open.png"),tr("打开文件夹"));
    nextaction=new QAction(QIcon(":/icon/next.png"),tr("下一张"));
    priviousaction=new QAction(QIcon(":/icon/previous.png"),tr("上一张"));
    //设置快捷键
    openaction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    opendiraction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    nextaction->setShortcut(QKeySequence(Qt::Key_Space));
    priviousaction->setShortcut(QKeySequence(Qt::Key_B));
    filemenu->addAction(openaction);
    filemenu->addAction(opendiraction);
    filemenu->addAction(nextaction);
    filemenu->addAction(priviousaction);
    ui->mainToolBar->addAction(openaction);
    ui->mainToolBar->addAction(opendiraction);
    ui->mainToolBar->addAction(priviousaction);
    ui->mainToolBar->addAction(nextaction);

    connect(openaction,&QAction::triggered,this,&MainWindow::open);
    connect(opendiraction,&QAction::triggered,this,&MainWindow::opendir);
    connect(nextaction,&QAction::triggered,this,&MainWindow::next);
    connect(priviousaction,&QAction::triggered,this,&MainWindow::privious);

    connect(this,&MainWindow::sendimagename,ui->label,&IMageLabel::RecieveImage);
    statusedit=new QLineEdit(this);
    statusedit->resize(800,30);
    statusedit->setMaximumHeight(30);
    statusedit->setReadOnly(true);
    connect(ui->scrollArea,&ScrollArea::scaleradio,ui->label,&IMageLabel::RecieveScale);
}

void MainWindow::setlistWidget()
{
    connect(ui->filelistWidget,&FileListWidget::itemActivated,this,&MainWindow::openfromlist);
    connect(ui->filelistWidget,&FileListWidget::itemPressed,this,&MainWindow::openfromlist);
}

void MainWindow::openfile(QString path)
{
    if(QFile::exists(path)) {
        sendimagename(path);
        statusedit->setText(path);
        statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
        ui->statusBar->addWidget(statusedit,0);
        ui->statusBar->show();
    }else
    {
         QMessageBox::critical(this,tr("错误"),path+tr(" 文件不存在！"),QMessageBox::Yes );
    }
}

void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.JPG *.png *.jpeg *.JPEG)"));
    if(!path.isEmpty())
    {
        openfile(path);
        ui->filelistWidget->addItem(path);
    }else
    {
        return ;
    }
}

void MainWindow::opendir()
{
    ui->filelistWidget->clear();

    QString curpath;//保存最近一次打开的目录
    if(!sets.value("lastopendir").isNull())
    {
        curpath=sets.value("lastopendir").toString();
    }

    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    curpath,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!path.isEmpty()){
        sets.setValue("lastopendir",path);

        QStringList nameFilters;
        nameFilters << "*.jpg" << "*.JPG"<<"*.png"<<"*.jpeg"<<"*.JPEG";
        QStringList files=QDir(path).entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        if(files.isEmpty())
        {
            QMessageBox::critical(this,tr("警告"),path+tr("目录为空！"),QMessageBox::Yes );
            return;
        }

        for (auto i=files.begin();i!=files.end();i++)
        {
            ui->filelistWidget->addItem(path+"/"+(*i));
        }
        index=ui->filelistWidget->currentIndex().row()+1;
        ui->filelistWidget->item(index)->setSelected(true);
        openfile(ui->filelistWidget->item(index)->text());
    }else
    {
        return;
    }
}

void MainWindow::next()
{
    if(index<ui->filelistWidget->count()-1)
        index+=1;
    QListWidgetItem *item=ui->filelistWidget->item(index);
    ui->filelistWidget->setCurrentItem(item);
    openfromlist(item);
    item->setSelected(true);
}

void MainWindow::privious()
{
    if(index>0)
        index-=1;
    QListWidgetItem *item=ui->filelistWidget->item(index);
    ui->filelistWidget->setCurrentItem(item);
    openfromlist(item);
    item->setSelected(true);
}

void MainWindow::openfromlist(QListWidgetItem *item)
{
    QString path=item->text();
    index=ui->filelistWidget->currentIndex().row();
    statusedit->setStyleSheet("color:white");
    openfile(path);
}




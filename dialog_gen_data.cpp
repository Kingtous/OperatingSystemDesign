#include "dialog_gen_data.h"
#include "ui_dialog_gen_data.h"

dialog_gen_data::dialog_gen_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_gen_data)
{
    ui->setupUi(this);
    // 初始化
    changeInputCount("");
    // 绑定
    connect(ui->edit_fileContent,SIGNAL(textChanged(const QString &)),this,SLOT(changeInputCount(const QString &)));
    this->setWindowTitle("生成数据");
    // 关闭即销毁
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->edit_fileName = ui->edit_fileName;
    this->edit_fileContent = ui->edit_fileContent;
}

dialog_gen_data::~dialog_gen_data()
{
    delete ui;
}

void dialog_gen_data::closeEvent(QCloseEvent *event)
{
    CGlobal::genThreadSem->release();
}

void dialog_gen_data::on_btn_submit_clicked()
{
    CGlobal::genThreadSem->release();
    // 获取界面数据
    QString fileName = edit_fileName->text();
    QString fileContent = edit_fileContent->text();

    if (fileName.trimmed().size() == 0 || fileContent ==0){
        QDialog * dialog = new QDialog(this);
        QVBoxLayout *layout = new QVBoxLayout();
        QPushButton *btn_ok = new QPushButton("确定");
        btn_ok->setParent(dialog);
        connect(btn_ok,SIGNAL(clicked()),this,SLOT(on_message_btn_ok()));
        layout->addWidget(new QLabel("数据存盘失败,可能的原因:"));
        layout->addWidget(new QLabel("1.文件名为空"));
        layout->addWidget(new QLabel("2.文件内容为空"));
        layout->addWidget(btn_ok);
        dialog->setLayout(layout);
        dialog->exec();
        return;
    }

    int status = CGlobal::fManager->generateData(fileContent.toStdString(),fileName.toStdString());
    if(status == STATUS_ERR){
        // 失败了，弹出失败框
        QDialog * dialog = new QDialog(this);
        QVBoxLayout *layout = new QVBoxLayout();
        QPushButton *btn_ok = new QPushButton("确定");
        btn_ok->setParent(dialog);
        connect(btn_ok,SIGNAL(clicked()),this,SLOT(on_message_btn_ok()));
        layout->addWidget(new QLabel("数据存盘失败,可能的原因有:"));
        layout->addWidget(new QLabel("1.磁盘空间不足，请删除一些文件后重试"));
        layout->addWidget(new QLabel("2.存在同名文件，请检查后重试"));
        layout->addWidget(btn_ok);
        dialog->setLayout(layout);
        dialog->exec();
        return;
    } else {
        // 发出信号给主线程
        QDialog * dialog = new QDialog(this);
        QVBoxLayout *layout = new QVBoxLayout();
        QPushButton *btn_ok = new QPushButton("确定");
        btn_ok->setParent(dialog);
        connect(btn_ok,SIGNAL(clicked()),this,SLOT(on_message_btn_ok()));
        layout->addWidget(new QLabel("文件写入成功"));
        layout->addWidget(btn_ok);
        dialog->setLayout(layout);
        dialog->exec();
        emit dataUpdated();
        this->close();
    }
}

void dialog_gen_data::on_message_btn_ok()
{
    ((QDialog*)((QPushButton*)sender())->parent())->close();
}

void dialog_gen_data::changeInputCount(const QString &text)
{
    ui->txt_inputNum->setText(QString::number(text.size())+"/96");
}

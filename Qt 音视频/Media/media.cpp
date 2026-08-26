#include "media.h"
#include "ui_media.h"

Media::Media(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Media)
{
    ui->setupUi(this);
}

Media::~Media() { delete ui; }
//播放测试
void Media::on_pushButton_clicked()
{
    //实例化多媒体播放器
    QMediaPlayer *player = new QMediaPlayer;
    //通过文件对话框获取文件路径
    QString filename = QFileDialog::getOpenFileName();
    //设置播放对象的路径
    player->setMedia(QUrl::fromLocalFile(filename));
    //设置播放对象的音量
    player->setVolume(50);
    //播放器状态为播放
    player->play();
}

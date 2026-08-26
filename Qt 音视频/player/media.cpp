#include "media.h"
#include "ui_media.h"

Media::Media(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Media)
{
    ui->setupUi(this);
    player_init();
}

Media::~Media() { delete ui; }
//初始化播放器和播放列表
void Media::player_init()
{
    //初始化
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    //设置播放列表的模式 循环列表
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    //设置播放器列表
    player->setPlaylist(playlist);

    //给窗口视频实例化
    video = new QVideoWidget(ui->widget);
    //设置窗口输出大小
    video->resize(ui->widget->size());
    //将video设置为播放器输出位置
    player->setVideoOutput(video);

    //设置暂停键
    setPause("暂停", false);

    //通过绑定信号void durationChanged(qint64 duration)音频播放的总长信号
    connect(player, &QMediaPlayer::durationChanged, [this](qint64 duration) {
        qDebug() << duration;
        if (duration != 0)
        {
            //设置水平滑条长度
            ui->hSlider->setMaximum(duration);
            //将总长字节转化为时间
            QTime t(duration / 1000 / 60 / 60, duration / 1000 / 60, duration / 1000 % 60);
            //显示内容
            ui->label_duration->setText(t.toString("hh:mm:ss"));
        }
    });
    //通过绑定信号void positionChanged(qint64 position)音频播放的进度信号
    connect(player, &QMediaPlayer::positionChanged, [this](qint64 position) {
        qDebug() << position;
        if (position != 0)
        {
            //设置水平滑条长度
            ui->hSlider->setValue(position);
            //将总长字节转化为时间
            QTime t(position / 1000 / 60 / 60, position / 1000 / 60, position / 1000 % 60);
            //显示内容
            ui->label_postiion->setText(t.toString("hh:mm:ss"));
        }
    });
}
void Media::on_hSlider_sliderMoved(int position)
{
    player->setPosition(position); //设置播放器进度
}
//添加
void Media::on_btnadd_clicked()
{
    //通过文件对话框获取多媒体文件
    QStringList files = QFileDialog::getOpenFileNames(this, "选择多媒体");
    if (files.isEmpty())
    {
        return;
    }
    //去掉重复文件
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        for (int j = 0; j < files.count(); ++j)
        {
            //获取文件名进行对比
            QFileInfo info(files.at(j));
            if (ui->listWidget->item(i)->text() == info.fileName())
            {
                files.removeAt(j);
                break;
            }
        }
    }
    //将不重复加入到listwidget
    for (int i = 0; i < files.count(); ++i)
    {
        //获取文件名进行对比
        QFileInfo info(files.at(i));
        //将文件名加入listwidget显示
        ui->listWidget->addItem(info.fileName());
        //将多媒体对应位置加入到播放列表
        playlist->addMedia(QUrl::fromLocalFile(files.at(i)));
    }
    //默认选择首行
    ui->listWidget->setCurrentRow(0);
}
//删除
void Media::on_btndel_clicked()
{
    //获取对应行
    int row = ui->listWidget->currentRow();
    if (row > 0)
    {
        //删除条目显示
        QListWidgetItem *item = ui->listWidget->takeItem(row);
        delete item;
        //删除播放列表对应位置多媒体
        playlist->removeMedia(row);
    }
}
//清空
void Media::on_btnclear_clicked()
{
    int ret = QMessageBox::warning(this, "清空列表提示", "是否清空列表", QMessageBox::Yes, QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        ui->listWidget->clear(); //清空显示
        playlist->clear();       //列表清空
    }
}
//设置暂停键的状态和文本
void Media::setPause(QString text, bool flag)
{
    ui->btnpause->setText(text);
    ui->btnpause->setEnabled(flag);
}
//设置音量
void Media::on_hSliderVolume_sliderMoved(int position)
{
    player->setVolume(position); //设置音量
    ui->label->setNum(position); //显示音量值
}
//选中行播放
void Media::on_listWidget_currentRowChanged(int currentRow)
{
    //通过行号确定播放对象
    playlist->setCurrentIndex(currentRow);
    //设置选中多媒体
    ui->listWidget->setCurrentRow(currentRow);
    //设置播放音量
    player->setVolume(ui->hSliderVolume->value());
    //播放器播放
    player->play();
    setPause("暂停", true);
}
//播放键
void Media::on_btnplay_clicked() { on_listWidget_currentRowChanged(ui->listWidget->currentRow()); }
//暂停/继续键
void Media::on_btnpause_clicked()
{
    //判断状态
    if (player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        this->setPause("继续", true);
    }
    else if (player->state() == QMediaPlayer::PausedState)
    {
        player->play();
        this->setPause("暂停", true);
    }
}
//停止
void Media::on_btnstop_clicked()
{
    player->stop();
    this->setPause("暂停", false);
}
//上一曲
void Media::on_btnlast_clicked()
{
    int row = ui->listWidget->currentRow(); //获取播放行号
    if (row < 0)
    {
        row = ui->listWidget->count() - 1;
    }
    else
    {
        row--;
    }
    on_listWidget_currentRowChanged(row);
}
//下一曲
void Media::on_btnnext_clicked()
{
    int row = ui->listWidget->currentRow(); //获取播放行号
    if (row > ui->listWidget->count() - 1)
    {
        row = 0;
    }
    else
    {
        row++;
    }
    on_listWidget_currentRowChanged(row);
}
//随机播放
void Media::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        //设置播放列表的播放模式 随机列表
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        ui->listWidget->setCurrentRow(playlist->currentIndex());
    }
    else
    {
        //设置播放列表的模式 循环列表
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        ui->listWidget->setCurrentRow(playlist->currentIndex());
    }
}

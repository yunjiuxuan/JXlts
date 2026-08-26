#include "media.h"
#include "ui_media.h"
#include <QDebug>
#include <exception>
#include <QFileInfo>
#include <QPixmap>
#include <QUrl>

Media::Media(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Media)
    , m_audioCoverPath("/mnt/hgfs/public/YQ_VScode/JieDuan_3/project/musicpng.png")
{
    ui->setupUi(this);
    player_init();
}

Media::~Media() { delete ui; }

void Media::closeEvent(QCloseEvent *event)
{
    qDebug() << "[Media关闭] 拦截关闭，改为隐藏窗口";

    if (player)
    {
        player->stop();
    }

    hide();
    event->ignore();
}
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
    //设置视频保持比例，不超出播放区域
    video->setAspectRatioMode(Qt::KeepAspectRatio);
    //将video设置为播放器输出位置
    player->setVideoOutput(video);

    //创建音频封面图片label
    m_audioImageLabel = new QLabel(ui->widget);
    m_audioImageLabel->resize(ui->widget->size());
    m_audioImageLabel->setAlignment(Qt::AlignCenter);
    m_audioImageLabel->setScaledContents(true);
    //加载封面图片
    QPixmap coverPix(m_audioCoverPath);
    if (!coverPix.isNull())
    {
        m_audioImageLabel->setPixmap(coverPix.scaled(ui->widget->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else
    {
        m_audioImageLabel->setText("封面图片加载失败");
    }
    m_audioImageLabel->hide(); //默认隐藏，视频模式下不需要

    //设置暂停/继续键初始状态
    setPause("继续", false);

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
    updatePrevNextButtons();
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
    updatePrevNextButtons();
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
    updatePrevNextButtons();
}
//更新上一曲/下一曲按钮状态
void Media::updatePrevNextButtons()
{
    int count = ui->listWidget->count();
    bool enabled = (count > 1);
    ui->btnlast->setEnabled(enabled);
    ui->btnnext->setEnabled(enabled);
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

    //判断当前文件类型：音频还是视频
    QUrl url = playlist->media(currentRow).canonicalUrl();
    QString ext = QFileInfo(url.toLocalFile()).suffix().toLower();
    QStringList audioExts = {"mp3", "wav", "wma", "flac", "aac", "ogg"};
    bool isAudio = audioExts.contains(ext);

    if (isAudio)
    {
        //音频模式：显示封面图片，隐藏视频窗口
        player->setVideoOutput(static_cast<QAbstractVideoSurface*>(nullptr));
        video->hide();
        m_audioImageLabel->show();
    }
    else
    {
        //视频模式：显示视频窗口，隐藏图片
        player->setVideoOutput(video);
        m_audioImageLabel->hide();
        video->show();
    }

    //播放器播放
    player->play();
    setPause("暂停", true);
}
//后退10秒
void Media::on_btnback10_clicked()
{
    qint64 currentPos = player->position();
    qint64 newPos = currentPos - 10000;
    if (newPos <= 0)
    {
        player->setPosition(0);
        player->play();
        setPause("暂停", true);
    }
    else
    {
        player->setPosition(newPos);
    }
}
//暂停/继续键
void Media::on_btnpause_clicked()
{
    if (player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        setPause("继续", true);
    }
    else if (player->state() == QMediaPlayer::PausedState)
    {
        player->play();
        setPause("暂停", true);
    }
}
//前进10秒
void Media::on_btnforward10_clicked()
{
    qint64 currentPos = player->position();
    qint64 duration = player->duration();
    qint64 newPos = currentPos + 10000;
    if (newPos >= duration && duration > 0)
    {
        player->pause();
        setPause("继续", true);
    }
    else
    {
        player->setPosition(newPos);
    }
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

void Media::addMediaFile(const QString &fileName, const QString &filePath)
{
    // 检查是否已存在
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        if (ui->listWidget->item(i)->text() == fileName)
        {
            return;
        }
    }

    ui->listWidget->addItem(fileName);
    playlist->addMedia(QUrl::fromLocalFile(filePath));
}

void Media::playMedia(const QString &fileName, const QString &filePath)
{
    addMediaFile(fileName, filePath);

    int targetRow = -1;
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        if (ui->listWidget->item(i)->text() == fileName)
        {
            targetRow = i;
            break;
        }
    }

    if (targetRow >= 0)
    {
        on_listWidget_currentRowChanged(targetRow);
    }
}

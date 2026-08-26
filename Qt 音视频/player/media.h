#ifndef MEDIA_H
#define MEDIA_H

#include <QMainWindow>
#include <QMediaPlayer>   //多媒体播放器
#include <QMediaPlaylist> //多媒体列表
#include <QVideoWidget>   //窗口输出
#include <QFileDialog>    //文件对话框
#include <QMessageBox>    //消息盒子
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Media;
}
QT_END_NAMESPACE

class Media : public QMainWindow
{
    Q_OBJECT

  public:
    Media(QWidget *parent = nullptr);
    ~Media();

    void player_init();
    void setPause(QString text, bool flag);
  private slots:
    void on_btnadd_clicked();

    void on_btndel_clicked();

    void on_btnclear_clicked();

    void on_btnplay_clicked();

    void on_btnpause_clicked();

    void on_btnstop_clicked();

    void on_hSliderVolume_sliderMoved(int position);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_hSlider_sliderMoved(int position);

    void on_btnlast_clicked();

    void on_btnnext_clicked();

    void on_checkBox_clicked(bool checked);

  private:
    Ui::Media *ui;
    QMediaPlayer *player;     //播放器对象
    QMediaPlaylist *playlist; //播放列表
    QVideoWidget *video;      //视频输出窗口
};
#endif // MEDIA_H
